#include "xml_utils.hpp"
#include "../common/string_utils.hpp"

//-----------------------------------------------------------------------------
shape_t dimensions2shape(const tree::ptree &dims)
{
    size_t rank = dims.get<size_t>("<xmlattr>.rank");
    shape_t s(rank);

    //initialize the shape with zero
    std::fill(s.begin(),s.end(),0);

    for(auto dim: dims)
    {
        if(dim.first != "dim") continue;

        auto index = dim.second.get<size_t>("<xmlattr>.index");
        auto value = dim.second.get<size_t>("<xmlattr>.value");
        s[index-1] = value;
    }

    return s;
}

//-----------------------------------------------------------------------------
void write_field(const tree::ptree &tag,const NXField &field)
{
    TypeID tid = field.type_id();

    if(tid == TypeID::UINT8) field.write(tag.get_value<UInt8>());
    else if(tid == TypeID::INT8) field.write(tag.get_value<Int8>());
    else if(tid == TypeID::UINT16) field.write(tag.get_value<UInt16>());
    else if(tid == TypeID::INT16) field.write(tag.get_value<Int16>());
    else if(tid == TypeID::UINT32) field.write(tag.get_value<UInt32>());
    else if(tid == TypeID::INT32) field.write(tag.get_value<Int32>());
    else if(tid == TypeID::UINT64) field.write(tag.get_value<UInt32>());
    else if(tid == TypeID::INT64) field.write(tag.get_value<Int64>());
    else if(tid == TypeID::FLOAT32) field.write(tag.get_value<Float32>());
    else if(tid == TypeID::FLOAT64) field.write(tag.get_value<Float64>());
    else if(tid == TypeID::FLOAT128) field.write(tag.get_value<Float128>());
    else if(tid == TypeID::COMPLEX32) field.write(tag.get_value<Complex32>());
    else if(tid == TypeID::COMPLEX64) field.write(tag.get_value<Complex64>());
    else if(tid == TypeID::COMPLEX128) field.write(tag.get_value<Complex128>());
    else if(tid == TypeID::BOOL) field.write(tag.get_value<Bool>());
    else if(tid == TypeID::STRING) field.write(trim(tag.get_value<String>()));
}
