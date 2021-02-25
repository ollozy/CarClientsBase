#include "abstractitemmodel.h"

#include "../app_core/cstringdata.h"

#include <cstring>
#include <cctype>

AbstractItemModel::AbstractItemModel()
    : m_headers(nullptr)
    , m_headersSize(-1)
{

}

AbstractItemModel::~AbstractItemModel()
{
    delete[] m_headers;
}

int AbstractItemModel::headerSize() const
{
    return m_headersSize;
}

void AbstractItemModel::setHeaderSize(int size)
{
    if(m_headersSize == size)
        return;

    m_headersSize = size;
    if(!m_headers)
        m_headers = new CStringData[m_headersSize];
}

CStringData AbstractItemModel::headerData(int column) const
{
    if(m_headersSize - 1 < column)
        return CStringData();

    return m_headers[column];
}

void AbstractItemModel::setHeaderData(const CStringData &data, int column)
{
    if(column > m_headersSize)
        return;

    m_headers[column] = data;
}

void AbstractItemModel::resizeHeaderStorage(int newSize)
{
    if(!(newSize > m_headersSize))
        return;

    CStringData *tempStorage = new CStringData[m_headersSize];
    for(int i = 0; i < m_headersSize; ++i)
        tempStorage[i] = m_headers[i];

    delete[] m_headers;
    m_headers = new CStringData[newSize];
    for(int i = 0; i < m_headersSize; ++i)
        m_headers[i] = tempStorage[i];

    m_headersSize = newSize;
    delete[] tempStorage;
}
