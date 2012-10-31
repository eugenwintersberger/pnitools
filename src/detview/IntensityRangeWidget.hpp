#ifndef __INTENSITYRANGEWIDGET_HPP__
#define __INTENSITYRANGEWIDGET_HPP__

#include<QtGui>

class IntensityRangeWidget : public QWidget
{
    Q_OBJECT
    private:
        QCheckBox *_fixed_check;
        QDoubleSpinBox *_maxbox;
        QDoubleSpinBox *_minbox;
    signals:
        void intensity_range_changed(double min,double max);

    public:
        //===============constructors==========================================
        //! default constructor
        IntensityRangeWidget();


        //==============public member functions================================
        //! set the intensity range
        void setRange(double min,double max);

        //---------------------------------------------------------------------
        void setMin(double min);

        void setMax(double max);

        void getMin() const;
        void getMax() const;




};
#endif
