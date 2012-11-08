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
        /*! 
        \bief set the intensity range

        \param min minimum value
        \param max maximum value
        */
        void setRange(double min,double max);

        //---------------------------------------------------------------------
        /*!
        \brief set minimum value

        Set the minimum value of the widget.
        \param min minimum value
        */
        void setMin(double min);

        //---------------------------------------------------------------------
        /*!
        \brief set maximum value
        
        Set the maximum value of the widget.
        \param max new maximum value
        */
        void setMax(double max);

        //---------------------------------------------------------------------
        /*!
        \brief get minimum value

        \return return the actual minimum value  of the widget
        */
        double getMin() const;

        //---------------------------------------------------------------------
        /*!
        \brief get maximum value

        \return return the actual maximum value of the widget.
        */
        double getMax() const;

};

#endif
