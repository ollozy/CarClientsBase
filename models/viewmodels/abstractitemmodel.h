#ifndef ABSTRACTITEMMODEL_H
#define ABSTRACTITEMMODEL_H

#include "../../app_core/modelindex.h"
#include "../../app_core/cstringdata.h"

class AbstractItemModel
{
public:
    AbstractItemModel();
    virtual ~AbstractItemModel();

    virtual void initHeader() = 0;

    virtual CStringData data(const ModelIndex &index) const = 0;

    virtual int columnCount() const = 0;
    virtual int rowCount() const = 0;

    CStringData headerData() const;
    void setHeaderData(const CStringData &data);

private:
    CStringData m_header;
};

#endif // ABSTRACTITEMMODEL_H
