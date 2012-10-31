#include "RenderingPipeline.hpp"

#include<vtkImageMapToWindowLevelColors.h>
#include<vtkLogLookupTable.h>
#include<vtkScalarsToColors.h>
#include<vtkImageActor.h>
#include "ColorMaps.hpp"

//------------------------------------------------------------------------------
RenderingPipeline::RenderingPipeline(QVTKWidget *w):
                   tiff_reader(vtkSmartPointer<vtkTIFFReader>::New()),
                   image_viewer(vtkSmartPointer<vtkImageViewer2>::New()),
                   lookup_table(vtkSmartPointer<vtkLookupTable>::New()),
                   color_bar(vtkSmartPointer<vtkScalarBarActor>::New()),
                   image_info(vtkSmartPointer<vtkImageChangeInformation>::New()),
                   widget(w)
{
   
    tiff_reader->SetFileName("water.tif");
    tiff_reader->Update();

    //set input connection for the viewer
    image_info->SetInputConnection(tiff_reader->GetOutputPort());

    image_viewer->SetInputConnection(image_info->GetOutputPort());
    image_viewer->SetSlice(0);
    image_viewer->GetImageActor()->InterpolateOff();
   
    //setup the lookup table
    for(vtkIdType tid=0;tid<lookup_table->GetNumberOfTableValues();tid++)
    {   
        lookup_table->SetTableValue(tid,rgba[tid]);
    }
    resetLookupTable();
    lookup_table->Build();
    image_viewer->GetWindowLevel()->SetLookupTable(lookup_table);

    color_bar->SetLookupTable(lookup_table);
    image_viewer->GetRenderer()->AddActor(color_bar);
    
    image_viewer->SetupInteractor(widget->GetRenderWindow()->GetInteractor());
    widget->SetRenderWindow(image_viewer->GetRenderWindow());
    widget->show();
}

//-----------------------------------------------------------------------------
RenderingPipeline::~RenderingPipeline()
{
    tiff_reader->Delete();
    image_viewer->Delete();
    lookup_table->Delete();
    color_bar->Delete();
}

//-----------------------------------------------------------------------------
void RenderingPipeline::setLogScale()
{
    lookup_table->SetScaleToLog10();
    image_viewer->Render();
    widget->update();
}

//-----------------------------------------------------------------------------
void RenderingPipeline::rotateLeft()
{
    image_viewer->GetImageActor()->RotateZ(90);
    image_viewer->Render();
    widget->update();
}

//-----------------------------------------------------------------------------
void RenderingPipeline::rotateRight()
{
    image_viewer->GetImageActor()->RotateZ(-90);
    image_viewer->Render();
    widget->update();
}

//-----------------------------------------------------------------------------
void RenderingPipeline::setLinScale()
{
    lookup_table->SetScaleToLinear();
    image_viewer->Render();
    widget->update();
}

//-----------------------------------------------------------------------------
void RenderingPipeline::rangeChanged(Float64 min,Float64 max)
{
    image_viewer->SetColorLevel(min);
    image_viewer->SetColorWindow(max-min);
}

//------------------------------------------------------------------------------
double RenderingPipeline::getMax() const
{
    return tiff_reader->GetOutput()->GetScalarRange()[1];
}

//-----------------------------------------------------------------------------
double RenderingPipeline::getMin() const 
{
    return tiff_reader->GetOutput()->GetScalarRange()[0];
}

//-----------------------------------------------------------------------------
void RenderingPipeline::resetLookupTable()
{
    lookup_table->SetTableRange(getMin(),getMax());
}
