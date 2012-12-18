#ifndef __NEXUSFILEMODEL_HPP__
#define __NEXUSFILEMODEL_HPP__

#include<QtGui>

#include <iostream>
#include <pni/utils/Types.hpp>
#include <pni/nx/NX.hpp>

using namespace pni::utils;
using namespace pni::nx::h5;


class NexusFileModel : public QAbstractItemModel
{
    Q_OBJECT
    private:
        QList<NXFile> &_file_list;

        static String _get_parent_path(const QModelIndex &parent);
    public:
        //--------------------------------------------------------------------
        NexusFileModel(NXFile &flist,QObject *parent = 0);

        //---------------------------------------------------------------------
        virtual ~NexusFileModel();

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
        
        //---------------------------------------------------------------------
        virtual QVariant data(const QModelIndex &index,
                              int role = Qt::DisplayRole ) const;

        
        //---------------------------------------------------------------------
        virtual QModelIndex parent( const QModelIndex & index ) const;

};



#endif
