#ifndef __DETECTORDATA_HPP__
#define __DETECTORDATA_HPP__

#include<algorithm>
#include<pni/utils/Types.hpp>
#include<pni/utils/Array.hpp>

#include<QtCore>
#include<QFileInfo>

using namespace pni::utils;

class DetectorData : public QObject
{
    Q_OBJECT
    private:
        DArray<Float64> _data; //!< data array

    signals:
        void dataChanged(const DetectorData &d);
    public:
        //================public types=========================================
        typedef DArray<Float64> storage_type;
        //======================constructors===================================
        //! default constructor
        DetectorData();
        //! copy constructor
        DetectorData(const DetectorData &o);

        //! move constructor from array
        DetectorData(DArray<Float64> &&data);
        
        
        //======================public member functions========================
        const storage_type getData() const
        {
            return _data;
        }

        void loadData(const QFileInfo &path);


};
#endif
