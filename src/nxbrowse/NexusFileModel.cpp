#include "NexusFileModel.hpp"

//===============implementation of static methods=============================
String NexusFileModel::_get_parent_path(const QModelIndex &parent)
{
    String *temp_ptr = static_cast<String*>(parent.internalPointer());

    String path(*temp_ptr);
    //delete temp_ptr;
    return path;
}

//-----------------------------------------------------------------------------
NexusFileModel::NexusFileModel(QList<NXFile> flist,QObject *parent):
    QAbstractItemModel(parent),
    _file_list(flist),
{ }

//-----------------------------------------------------------------------------
NexusFileModel::~NexusFileModel() { } 

//-----------------------------------------------------------------------------
int NexusFileModel::columnCount(const QModelIndex &parent) const
{
    return 2;
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
        o = _root_group[_get_parent_path(parent)];

        //if the parent is a field object we just return in invalid index - 
        //fields do not have children
        if(o.object_type() == pni::nx::NXObjectType::NXFIELD) return QModelIndex();

        //if the parent is a group object we can use
        NXGroup g(o);
        o = g[size_t(row)];
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
        o = _root_group[_get_parent_path(parent)];

        //if field return 0
        if(o.object_type() == pni::nx::NXObjectType::NXFIELD) return 0;
        
        NXGroup g(o);
        return size_t(g.nchilds());
    }
    else
    {
        return size_t(_file->nchilds());
    }
}

//-----------------------------------------------------------------------------
QVariant NexusFileModel::data(const QModelIndex &index, int role) const
{
    //obtain the object described by the index object
    NXObject o = _root_group[_get_parent_path(index)];

    if(role == Qt::DisplayRole)
        return QVariant(QString(o.name().c_str()));
    if(role == Qt::ToolTipRole)
    {
        if(o.object_type() == pni::nx::NXObjectType::NXFIELD)
        {
            return QVariant(QString("NXField object"));
        }
        else
        {
            return QVariant(QString("NXGroup object"));
        }
    }
    else
        return QVariant();

}

//-----------------------------------------------------------------------------
QModelIndex NexusFileModel::parent( const QModelIndex & index ) const
{
    NXObject o;
    if(index.isValid())
    {
        o = _root_group[_get_parent_path(index)];

        if(o.object_type() == pni::nx::NXObjectType::NXFIELD)
        {
            NXField f(o);
            o = f.parent();
        }
        else
        {
            NXGroup g(o);
            o = g.parent();
        }

        String *path = new String(o.path());

        return createIndex(0,0,path);
    }
    else
    {
        //in this case we are already at the top level
        return QModelIndex();
    }
}



