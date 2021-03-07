#ifndef ABSTRACTITEMMODEL_H
#define ABSTRACTITEMMODEL_H

#include "../app_core/modelindex.h"

class CStringData;

class AbstractItemModel
{
public:
    AbstractItemModel();
    virtual ~AbstractItemModel();

    virtual void initHeader() = 0;

    virtual CStringData data(const ModelIndex &index) const = 0;
    virtual void setData(const CStringData &data, const ModelIndex &index) = 0;

    virtual void clearModel() = 0;
    virtual int columnCount() const = 0;
    virtual int rowCount() const = 0;
    virtual void removeRow(int row) = 0;

    int headerSize() const;
    void setHeaderSize(int size);

    CStringData headerData(int column) const;

protected:
    void setHeaderData(const CStringData &data, int column);

private:
    void resizeHeaderStorage(int newSize);

private:
    CStringData *m_headers;
    int m_headersSize;
};

#endif // ABSTRACTITEMMODEL_H
