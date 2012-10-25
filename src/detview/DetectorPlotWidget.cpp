#include "DetectorPlotWidget.hpp"

DetectorPlotWidget::DetectorPlotWidget()
{
    //create colormap
    color_map = new QwtLinearColorMap(Qt::black,Qt::white);
    color_map->setMode(QwtLinearColorMap::Mode::ScaledColors);

    //create a new spectrogram plotter
    spec_plot = new QwtPlotSpectrogram();
    spec_plot->setColorMap(*color_map);
    spec_plot->attach(this);



}

void DetectorPlotWidget::setData(DArray<Float64> &&data)
{
    auto s = data.shape<shape_t>();
    DetectorData rdata(std::move(data));

    spec_plot->setData(rdata);
    replot();

}
