#include "abstractitemmodel.h"

AbstractItemModel::AbstractItemModel()
    : m_header()
{

}

AbstractItemModel::~AbstractItemModel()
{

}

CStringData AbstractItemModel::headerData() const
{
    return m_header;
}

void AbstractItemModel::setHeaderData(const CStringData &data)
{
    m_header = data;
}
