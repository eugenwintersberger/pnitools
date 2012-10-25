#ifndef __DETECTORPLOTWIDGET_HPP__
#define __DETECTORPLOTWIDGET_HPP__

#include<algorithm>
#include<pni/utils/Types.hpp>
#include<pni/utils/Array.hpp>

#include<qwt-qt4/qwt_plot.h>
#include<qwt-qt4/qwt_plot_spectrogram.h>
#include<qwt-qt4/qwt_raster_data.h>
#include<qwt-qt4/qwt_double_interval.h>

using namespace pni::utils;

class DetectorData : public QwtRasterData
{
    private:
        DArray<Float64> _data;
        Float64 _min;
        Float64 _max;

    public:
        //the copy constructor is for internal use only
        DetectorData(const DetectorData &o):
            _data(o._data),
            _min(o._min),
            _max(o._max)
        {
            auto s = _data.shape<shape_t>();
            setBoundingRect(QwtDoubleRect(0.,0.,double(s[0])-1.0,double(s[1])-1.0));
        }

        DetectorData(DArray<Float64> &&data):
            QwtRasterData(),
            _data(std::move(data))
        {
            _min = *(std::min_element(_data.begin(),_data.end()));
            _max = *(std::max_element(_data.begin(),_data.end()));

            auto s = _data.shape<shape_t>();
            setBoundingRect(QwtDoubleRect(0.,0.,double(s[0])-1.0,double(s[1])-1.0));
        }
    
        QwtDoubleInterval range() const
        {
            return QwtDoubleInterval(_min,_max);
        }

        QwtRasterData *copy() const
        {
            return new DetectorData(*this);
        }


        double value(double x,double y) const
        {
            double value;
            try
            {
                size_t i = size_t(x);
                size_t j = size_t(y);

                value = log(_data(i,j));
            }
            catch(IndexError &error)
            {
                size_t i = size_t(x);
                size_t j = size_t(y);
                std::cerr<<"Index is ("<<x<<","<<y<<")"<<std::endl;
                std::cerr<<"Shape is ";
                auto s = _data.shape<shape_t>();
                for(auto d: s) std::cerr<<d<<" ";
                std::cerr<<std::endl;
                std::cerr<<error<<std::endl;
                error.append(EXCEPTION_RECORD);
                throw error;
            }
            return value;
        }
};

class DetectorPlotWidget:public QwtPlot
{
    private:
        QwtPlotSpectrogram *spec_plot;

         
    public:
        DetectorPlotWidget();

        void setData(DArray<Float64> &&data);



};

#endif
