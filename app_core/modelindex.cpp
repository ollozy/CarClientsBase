#include "modelindex.h"

ModelIndex::ModelIndex()
    : m_row(-1)
    , m_column(-1)
{

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
