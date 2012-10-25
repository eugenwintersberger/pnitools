#ifndef __DETECTORPLOTWIDGET_HPP__
#define __DETECTORPLOTWIDGET_HPP__


#include<qwt-qt4/qwt_plot.h>
#include<qwt-qt4/qwt_plot_spectrogram.h>
#include<qwt-qt4/qwt_double_interval.h>
#include<qwt-qt4/qwt_color_map.h>

#include "DetectorData.hpp"

class DetectorPlotWidget:public QwtPlot
{
    private:
        QwtPlotSpectrogram *spec_plot;
        QwtLinearColorMap *color_map;
         
    public:
        DetectorPlotWidget();

        void setData(DArray<Float64> &&data);



};

#endif
