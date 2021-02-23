#ifndef ABSTRACTITEMMODEL_H
#define ABSTRACTITEMMODEL_H

#include "../app_core/modelindex.h"

class AbstractItemModel
{
public:
    AbstractItemModel();
    virtual ~AbstractItemModel();

    virtual const char *data() const = 0;
    virtual void setData(const char *data, const ModelIndex &index) = 0;

    virtual void insertColumn(int column) = 0;
    virtual void removeColumn(int column) = 0;
    virtual void insertRow(int row) = 0;
    virtual void removeRow(int row) = 0;
    virtual void columnCount() const = 0;
    virtual void rowCount() const;

    virtual void setHeaderData(const char *data, int column);
};

#endif // ABSTRACTITEMMODEL_H
