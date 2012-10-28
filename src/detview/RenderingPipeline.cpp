#include "RenderingPipeline.hpp"

#include<vtkImageMapToWindowLevelColors.h>
#include<vtkLogLookupTable.h>
#include<vtkScalarsToColors.h>
#include<vtkImageActor.h>

//------------------------------------------------------------------------------
RenderingPipeline::RenderingPipeline(QVTKWidget *w,const array_t &a):
                   image_array(vtkSmartPointer<vtkDoubleArray>::New()),
                   image_viewer(vtkSmartPointer<vtkImageViewer2>::New()),
                   image_data(vtkSmartPointer<vtkImageData>::New()),
                   lookup_table(vtkSmartPointer<vtkLookupTable>::New()),
                   transfer_func(vtkSmartPointer<vtkColorTransferFunction>::New()),
                   widget(w)
{
    setData(a);

    image_data->GetPointData()->SetScalars(image_array);
    image_data->SetScalarType(VTK_DOUBLE);
    image_data->SetSpacing(1.0,1.0,1.0);
    image_data->SetOrigin(0,0,0);

    image_viewer->SetInput(image_data);
    image_viewer->SetZSlice(0);
    image_viewer->GetImageActor()->InterpolateOff();

    transfer_func->SetColorSpaceToRGB();

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
    transfer_func->SetScaleToLog10();
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
    transfer_func->SetScaleToLinear();
    image_viewer->Render();
    widget->update();
}

//-----------------------------------------------------------------------------
void RenderingPipeline::setData(const array_t &a)
{
    auto s = a.shape<shape_t>(); 
    image_data->SetDimensions(s[1],s[0],1);
    image_array->SetArray(const_cast<Float64*>(a.storage().ptr()),
                 a.size(),1);
    image_data->SetOrigin(s[1]/2,s[0]/2,1);

    //have to setup the color lookup table
    Float64 mmax[2];
    Float64 min = *(std::min_element(a.begin(),a.end()));
    Float64 max = *(std::max_element(a.begin(),a.end()));
    mmax[0] = min; mmax[1] = max;
    transfer_func->AddRGBPoint(min,0,0,0);
    transfer_func->AddRGBPoint(max,1,1,1);
    transfer_func->Build();
    lookup_table->SetTableRange(min,max);
    lookup_table->Build();

    //set the lookup table for the viewer
    vtkImageMapToWindowLevelColors *imap = image_viewer->GetWindowLevel();
    imap->SetLookupTable(transfer_func);
    image_data->Update();

    image_viewer->SetColorWindow(max-min);
    image_viewer->SetColorLevel(min);

}
