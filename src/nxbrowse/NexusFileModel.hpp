#ifndef __NEXUSFILEMODEL_HPP__
#define __NEXUSFILEMODEL_HPP__

#include <iostream>
#include <pni/utils/Types.hpp>
#include <pni/nx/NX.hpp>

using namespace pni::utils;
using namespace pni::nx::h5;


class NexusFileModel : public QAbstractItemModel
{
    Q_OBJECT
    private:
        const NXFile *_file;
        NXGroup _root_group;

        static String _get_parent_path(const QModelIndex &parent);
    public:
        //---------------------------------------------------------------------
        NexusFileModel(const NXFile *f,QObject *parent = 0);

        //---------------------------------------------------------------------
        virtual ~NexusObjectModel();

        //---------------------------------------------------------------------
        virtual int columnCount (const QModelIndex &parent=QModelIndex() ) const;


        //---------------------------------------------------------------------
        virtual Qt::ItemFlags flags(const QModelIndex &index) const;


        //---------------------------------------------------------------------
        virtual QModelIndex index(int row,int column, 
                                  const QModelIndex &parent = QModelIndex())
                                  const;
        
        //---------------------------------------------------------------------
        virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;

};

template<typename NXTYPE> class NexusModel : public NexusObjectModel
{
    private:

    public:
        //---------------------------------------------------------------------
        virtual QVariant data(const QModelIndex &index,
                              int role = Qt::DisplayRole ) const;

        
        //---------------------------------------------------------------------
        virtual QModelIndex parent( const QModelIndex & index ) const;

};

//-----------------------------------------------------------------------------
template<typename NXTYPE>
QVariant NexusModel<NXTYPE>::data(const QModelIndex &index,int role) const
{

}

//-----------------------------------------------------------------------------
template<typename NXTYPE>
int NexusModel<NXTYPE>::rowCount(const QModelIndex &parent) const
{
}

//-----------------------------------------------------------------------------
QModelIndex NexusFileModel::parent( const QModelIndex & index ) const
{
}

#endif
