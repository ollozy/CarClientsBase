#include "modelindex.h"

ModelIndex::ModelIndex()
    : m_row(-1)
    , m_column(-1)
{

}

ModelIndex::ModelIndex(int row, int column)
    : m_row(row)
    , m_column(column)
{

}

ModelIndex::ModelIndex(const ModelIndex &other)
    : m_row(other.m_row)
    , m_column(other.m_column)
{

}

const ModelIndex &ModelIndex::operator=(const ModelIndex &other)
{
    if(this == &other)
        return *this;

    m_row = other.m_row;
    m_column = other.m_column;

    return *this;
}

bool ModelIndex::operator==(const ModelIndex &other)
{
    return m_row == other.m_row && m_column == other.m_column;
}

bool ModelIndex::operator!=(const ModelIndex &other)
{
    return !operator==(other);
}

int ModelIndex::row() const
{
    return m_row;
}

void ModelIndex::setRow(int row)
{
    if(m_row == row)
        return;

    m_row = row;
}

int ModelIndex::column() const
{
    return m_column;
}

void ModelIndex::setColunt(int column)
{
    if(m_column == column)
        return;

    m_column = column;
}

bool ModelIndex::isValid() const
{
    return !(m_row < 0) && !(m_column < 0);
}

bool ModelIndex::isMulti() const
{
    return (!(m_row < 0) && (m_column < 0))
            || ((m_row < 0) && !(m_column < 0));
}
