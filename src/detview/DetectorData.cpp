
#include<pni/utils/io/CBFReader.hpp>
#include<pni/utils/io/TIFFReader.hpp>
#include<pni/utils/io/ImageInfo.hpp>


#include "DetectorData.hpp"

using namespace pni::io;

//-----------------------------------------------------------------------------
DetectorData::DetectorData():
    _data()
{}

//-----------------------------------------------------------------------------
DetectorData::DetectorData(const DetectorData &o):
              _data(o._data)
{ }

//-----------------------------------------------------------------------------
DetectorData::DetectorData(DArray<Float64> &&data):
              _data(std::move(data))
{ }

//-----------------------------------------------------------------------------
void DetectorData::loadData(const QFileInfo &path)
{
    typedef storage_type array_t;
    typedef array_t::storage_type buffer_t;

    ImageInfo info;
    buffer_t buffer;
    //choose the proper reader
    if(path.suffix()==QString("cbf"))
    {
        //open the file
        CBFReader reader(path.absoluteFilePath().toStdString());
        info=reader.info(0); //get file information
        buffer = reader.image<buffer_t>(0); 
    }
    else if(path.suffix() == QString("tif"))
    {
        TIFFReader reader(path.absoluteFilePath().toStdString());
        info = reader.info(0);
        buffer = reader.image<buffer_t>(0);
    }
    
    shape_t shape{info.nx(),info.ny()};

    //set the new array data
    _data = array_t(shape,std::move(buffer));

    emit dataChanged(*this);
}


