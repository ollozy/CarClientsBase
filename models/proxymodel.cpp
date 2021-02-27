#include "proxymodel.h"

#include "../app_core/cstringdata.h"

#include <cstring>

ProxyModel::ProxyModel()
    : m_currentModel(nullptr)
    , m_showedIndexes()
    , m_sortColumn(-1)
    , m_filterWord("\0")
{

}

CStringData ProxyModel::data(const ModelIndex &index) const
{
    if(index.row() == 0) {
        m_showedIndexes.clear();
        return m_currentModel->data(index);
    }

    for(int i = index.row(); i < m_currentModel->rowCount(); ++i) {
        ModelIndex mappedIndex(i, m_sortColumn);
        if(m_showedIndexes.contains(ModelIndex(i, index.column())))
            continue;
        CStringData data = m_currentModel->data(mappedIndex);
        if(filter(data.data())) {
            ModelIndex showedIndex(i, index.column());
            m_showedIndexes.append(showedIndex);
            return m_currentModel->data(showedIndex);
        }
    }

    return CStringData();
}

void ProxyModel::setData(const CStringData &data, const ModelIndex &index)
{
    m_currentModel->setData(data, index);
}

void ProxyModel::clearModel()
{
    m_currentModel->clearModel();
}

void ProxyModel::insertColumn(int column)
{
    m_currentModel->insertColumn(column);
}

void ProxyModel::removeColumn(int column)
{
    m_currentModel->removeColumn(column);
}

int ProxyModel::columnCount() const
{
    return m_currentModel->columnCount();
}

void ProxyModel::insertRow(int row)
{
    m_currentModel->insertRow(row);
}

void ProxyModel::removeRow(int row)
{
    m_currentModel->removeRow(row);
}

int ProxyModel::rowCount() const
{
    return m_currentModel->rowCount();
}

void ProxyModel::setModel(AbstractItemModel *model)
{
    if(m_currentModel == model)
        return;

    m_showedIndexes.clear();
    std::strncpy(m_filterWord, "\0", 1);

    m_currentModel = model;
}

AbstractItemModel *ProxyModel::model() const
{
    return m_currentModel;
}

void ProxyModel::setFilter(const char *filterWord)
{
    std::strncpy(m_filterWord, filterWord, 100);
}

void ProxyModel::setFilterColumn(int column)
{
    if(m_sortColumn == column)
        return;
    m_sortColumn = column;
}

bool ProxyModel::filter(const char* data) const
{
    if(std::strncmp(m_filterWord, "\0", 1) == 0
            || m_sortColumn == -1)
        return true;

    if(std::strncmp(data, m_filterWord, 100) == 0)
        return true;

    return false;
}
