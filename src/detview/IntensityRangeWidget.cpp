#include "IntensityRangeWidget.hpp"

IntensityRangeWidget::IntensityRangeWidget():
    _fixed_check(new QCheckBox()),
    _maxbox(new QDoubleSpinBox()),
    _minbox(new QDoubleSpinBox())
{ }

//-----------------------------------------------------------------------------
void IntensityRangeWidget::setRange(double min,double max)
{
    setMin(min);
    setMax(max);
}

//-----------------------------------------------------------------------------
void IntensityRangeWidget::setMin(double value)
{
    _minbox->setValue(value);
}

//-----------------------------------------------------------------------------
void IntensityRangeWidget::setMax(double value)
{
    _maxbox->setValue(value);
}

//-----------------------------------------------------------------------------
double IntensityRangeWidget::getMin() const
{
    return _minbox->value();
}

//-----------------------------------------------------------------------------
double IntensityRangeWidget::getMax() const
{
    return _maxbox->value();
}
