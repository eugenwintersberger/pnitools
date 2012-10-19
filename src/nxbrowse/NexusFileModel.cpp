#include "NexusFileModel.hpp"

//===============implementation of static methods=============================
String NexusFileMode::_get_parent_path(const QModelIndex &parent)
{
    String *temp_ptr = std::static_cast<String*>(parent.InternalPointer());

    String path(*temp_ptr);
    delete temp_ptr;
    return path;
}

//-----------------------------------------------------------------------------
NexusFileModel::NexusFileModel(const NXFile *file,QObject *parent):
    QAbstractFileModel(parent),
    _file(file)
    _root_group(file.open['/'])
{}

//-----------------------------------------------------------------------------
NexusFileModel::~NexusFileModel()
{
    _root_group.close();
    _file->close();
}


//-----------------------------------------------------------------------------
int NexusFileModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}


//-----------------------------------------------------------------------------
Qt::ItemFlags NexusFileModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}


//-----------------------------------------------------------------------------
QModelIndex NexusFileModel::index(int row,int column,const QModelIndex &parent) const
{
    NXObject o;
    if(parent.isValid())
    {
        //get the object described by the path
        o = _root_group[_get_parent_path];

        //if the parent is a field object we just return in invalid index - 
        //fields do not have children
        if(o.object_type() == pni::nx::NXFIELD) return QModelIndex();

        //if the parent is a group object we can use
        o = o[row];
    }
    else
    {
        //if the parentis invalid we read the object directly from the root
        //group
        o = _root_group[size_t(row)];
    }    
    String *path = new String(o.path());
    return createIndex(row,column,path);

}

//-----------------------------------------------------------------------------
int NexusFileModel::rowCount(const QModelIndex &parent) const
{
    NXObject o;
    if(parent.isValid())
    {
        //get the parent object
        o = _root_group[_get_parent_path];

        //if field return 0
        if(o.object_type() == pni::nx::NXFIELD) return 0;
        
        NXGroup g(o);
        return size_t(g.nchil
    }
}







