#ifndef ABSTRACTITEMMODEL_H
#define ABSTRACTITEMMODEL_H

#include "../app_core/modelindex.h"

class CStringData;

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
    virtual void rowCount() const = 0;

    const CStringData &headerData(int column);
    void setHeaderData(const CStringData &data, int column);

private:
    void resizeHeaderStorage(int newSize);

private:
    CStringData *m_headers;
    int m_headersSize;;
};

#endif // ABSTRACTITEMMODEL_H
