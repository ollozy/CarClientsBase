#include "cstringdata.h"

#include <cstring>
#include <cstdio>
#include <cstdlib>

CStringData::CStringData()
    : m_data(new char[100])
    , m_len(0)
{
    m_data[0] = '\0';
}

CStringData::CStringData(const char *data, int len)
    : m_len(len)
{
    m_data = new char[m_len];
    std::strncpy(m_data, data, len);
}

CStringData::CStringData(int data)
    : m_data(new char[100])
    , m_len(100)
{
    std::sprintf(m_data, "%d", data);
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

int CStringData::toInt() const
{
    return std::atoi(m_data);
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

void CStringData::setData(int data)
{
    m_len = 100;
    if(m_data)
        delete[] m_data;
    m_data = new char[m_len];

    std::sprintf(m_data, "%d", data);
}

bool CStringData::isEmpty() const
{
    return !(m_len > 0) || !m_data;
}
