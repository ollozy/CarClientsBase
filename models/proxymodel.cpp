#include "proxymodel.h"

#include "../app_core/cstringdata.h"

#include <cstring>

ProxyModel::ProxyModel()
    : m_currentModel(nullptr)
    , m_showedIndexes()
    , m_filterColumn(-1)
    , m_filterWord("\0")
{

}

CStringData ProxyModel::data(const ModelIndex &index) const
{
    if(!m_currentModel)
        return CStringData();

    filter();
    ModelIndex proxyIndex = mapToSource(index);
    if(!proxyIndex.isValid())
        return CStringData();

    return m_currentModel->data(proxyIndex);
}

void ProxyModel::setData(const CStringData &data, const ModelIndex &index)
{
    if(!m_currentModel)
        return;

    m_currentModel->setData(data, index);
}

void ProxyModel::clearModel()
{
    if(!m_currentModel)
        return;

    m_currentModel->clearModel();
}

void ProxyModel::insertColumn(int column)
{
    if(!m_currentModel)
        return;

    m_currentModel->insertColumn(column);
}

void ProxyModel::removeColumn(int column)
{
    if(!m_currentModel)
        return;

    m_currentModel->removeColumn(column);
}

int ProxyModel::columnCount() const
{
    if(!m_currentModel)
        return -1;

    return m_currentModel->columnCount();
}

void ProxyModel::insertRow(int row)
{
    if(!m_currentModel)
        return;

    m_currentModel->insertRow(row);
}

void ProxyModel::removeRow(int row)
{
    if(!m_currentModel)
        return;

    ModelIndex sourceIndex = mapToSource(ModelIndex(row, 0));
    if(!sourceIndex.isValid())
        return;

    m_currentModel->removeRow(sourceIndex.row());
}

int ProxyModel::rowCount() const
{
    if(!m_currentModel)
        return -1;

    return m_currentModel->rowCount();
}

void ProxyModel::setModel(AbstractItemModel *model)
{
    if(m_currentModel == model)
        return;

    m_currentModel = model;
    clearFilter();
}

AbstractItemModel *ProxyModel::model() const
{
    return m_currentModel;
}

void ProxyModel::setFilter(const char *filterWord)
{
    std::strncpy(m_filterWord, filterWord, 100);
    filter();
}

void ProxyModel::clearFilter()
{
    setFilter("\0");
}

void ProxyModel::setFilterColumn(int column)
{
    if(m_filterColumn == column)
        return;
    m_filterColumn = column;
}

void ProxyModel::filter() const
{
    if(!m_currentModel)
        return;

    initProxy();

    if(std::strncmp(m_filterWord, "\0", 1) == 0
            || m_filterColumn == -1)
        return;

    int row = 0;
    for(LinkList<ModelIndex>::iterator iter = m_showedIndexes.begin();
        row < m_currentModel->rowCount() && iter != m_showedIndexes.end(); ++row) {
        ModelIndex filterIndex(row, m_filterColumn);
        for(int col = 0; col < m_currentModel->columnCount() && iter != m_showedIndexes.end(); ++col) {
            if(!textSearch(m_currentModel->data(filterIndex).data(), m_filterWord)) {
                if(row == 0) {
                    ++iter;
                    continue;
                }
                iter = m_showedIndexes.erase(iter);
            }
            else
                ++iter;
        }

    }
}

void ProxyModel::initProxy() const
{
    if(!m_currentModel)
        return;

    m_showedIndexes.clear();
    for(int i = 0; i < m_currentModel->rowCount(); ++i)
        for(int j = 0; j < m_currentModel->columnCount(); ++j) {
            ModelIndex index(i, j);
            m_showedIndexes.append(index);
        }
}

ModelIndex ProxyModel::mapToSource(const ModelIndex &proxyIndex) const
{
    if(!m_currentModel)
        return ModelIndex();

    int row = 0;
    for(LinkList<ModelIndex>::iterator iter = m_showedIndexes.begin();
        row < m_currentModel->rowCount() && iter != m_showedIndexes.end(); ++row) {
        for(int col = 0; col < m_currentModel->columnCount() && iter != m_showedIndexes.end(); ++col) {
            ModelIndex index(row, col);
            if(index == proxyIndex)
                return *iter;
            else ++iter;
        }
    }
    return ModelIndex();
}

ModelIndex ProxyModel::mapToProxy(const ModelIndex &index) const
{
    if(!m_currentModel)
        return ModelIndex();

    int row = 0;
    for(LinkList<ModelIndex>::iterator iter = m_showedIndexes.begin();
        row < m_currentModel->rowCount() && iter != m_showedIndexes.end(); ++row) {
        for(int col = 0; col < m_currentModel->columnCount() && iter != m_showedIndexes.end(); ++col) {
            ModelIndex ind = index;
            if(ind == *iter)
                return ModelIndex(row, col);
        }
    }
    return ModelIndex();
}

bool ProxyModel::textSearch(const char *data, const char *key) const
{
    int dataLen = std::strlen(data);
    int keyLen = std::strlen(key);

    if(keyLen > dataLen)
        return false;

    else if(keyLen == dataLen)
        return std::strncmp(data, key, dataLen) == 0;

    const char *dataPtr = data;
    for(int i = 0; i < dataLen - keyLen; ++i, ++dataPtr) {
        if(std::strncmp(dataPtr, key, keyLen) == 0)
            return true;
    }
    return false;
}
