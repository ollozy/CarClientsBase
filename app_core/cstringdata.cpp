#include "cstringdata.h"

#include <cstring>

CStringData::CStringData()
    : m_data(nullptr)
    , m_len(0)
{

}

CStringData::CStringData(const char *data, int len)
    : m_len(len)
{
    m_data = new char[m_len];
    std::strncpy(m_data, data, len);
}

CStringData::CStringData(const CStringData &other)
    : m_len(other.m_len)
{
    m_data = new char[m_len];
    std::strncpy(m_data, other.m_data, m_len);
}

CStringData::~CStringData()
{
    delete[] m_data;
}

const CStringData &CStringData::operator=(const CStringData &other)
{
    if(this == &other)
        return *this;

    m_len = other.m_len;

    if(m_data)
        delete[] m_data;
    m_data = new char[m_len];

    std::strncpy(m_data, other.m_data, m_len);

    return *this;
}

const char *CStringData::data() const
{
    return m_data;
}

int CStringData::length() const
{
    return m_len;
}

void CStringData::setData(const char *data, int len)
{
    m_len = len;
    if(m_data)
        delete[] m_data;
    m_data = new char[m_len];
    std::strncpy(m_data, data, m_len);
}

bool CStringData::isEmpty() const
{
    return m_len == 0 || !m_data;
}
