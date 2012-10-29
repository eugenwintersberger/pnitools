#include "RenderingPipeline.hpp"

#include<vtkImageMapToWindowLevelColors.h>
#include<vtkLogLookupTable.h>
#include<vtkScalarsToColors.h>
#include<vtkImageActor.h>
#include "ColorMaps.hpp"

//------------------------------------------------------------------------------
RenderingPipeline::RenderingPipeline(QVTKWidget *w):
                   image_array(vtkSmartPointer<vtkDoubleArray>::New()),
                   image_viewer(vtkSmartPointer<vtkImageViewer2>::New()),
                   image_data(vtkSmartPointer<vtkImageData>::New()),
                   lookup_table(vtkSmartPointer<vtkLookupTable>::New()),
                   color_bar(vtkSmartPointer<vtkScalarBarActor>::New()),
                   widget(w)
{
    image_data->GetPointData()->SetScalars(image_array);
    image_data->SetScalarType(VTK_DOUBLE);
    image_data->SetSpacing(1.0,1.0,1.0);
    image_data->SetOrigin(0,0,0);

    image_viewer->SetInput(image_data);
    image_viewer->SetZSlice(0);
    image_viewer->GetImageActor()->InterpolateOff();
   
    //setup the lookup table
    for(vtkIdType tid=0;tid<lookup_table->GetNumberOfTableValues();tid++)
    {   
        lookup_table->SetTableValue(tid,rgba[tid]);
    }
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
    image_array->Delete();
    image_viewer->Delete();
    image_data->Delete();
    lookup_table->Delete();
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

//-----------------------------------------------------------------------------
void RenderingPipeline::dataChanged(const DetectorData &d)
{
    typedef DetectorData::storage_type array_t;
    const array_t &data = d.getData();

    auto s = data.shape<shape_t>(); 
    //setup the image data
    image_array->SetArray(const_cast<Float64*>(data.storage().ptr()),
                          data.size(),1);

    image_data->SetDimensions(s[1],s[0],1);
    image_data->SetOrigin(0,0,0);
    image_data->Update();
}
