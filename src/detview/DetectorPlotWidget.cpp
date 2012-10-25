#include "DetectorPlotWidget.hpp"

DetectorPlotWidget::DetectorPlotWidget()
{
    //create a new spectrogram plotter
    spec_plot = new QwtPlotSpectrogram();
    spec_plot->attach(this);

}

void DetectorPlotWidget::setData(DArray<Float64> &&data)
{
    auto s = data.shape<shape_t>();
    DetectorData rdata(std::move(data));

    spec_plot->setData(rdata);
    replot();

}
