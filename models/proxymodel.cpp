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

ProxyModel::~ProxyModel()
{

}

CStringData ProxyModel::data(const ModelIndex &index) const
{
    if(!m_currentModel)
        return CStringData();

    //    filter();
    if(index.row() == 0)
        return m_currentModel->data(index);

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

int ProxyModel::rowCount() const
{
    if(!m_currentModel)
        return -1;

    return m_currentModel->rowCount();
}

int ProxyModel::columnCount() const
{
    if(!m_currentModel)
        return -1;

    return m_currentModel->columnCount();
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

void ProxyModel::setFilter(const char *filterWord, int column)
{
    m_filterColumn = column;
    std::strncpy(m_filterWord, filterWord, 100);
    filter();
}

void ProxyModel::clearFilter()
{
    setFilter("\0");
}

void ProxyModel::filter() const
{
    if(!m_currentModel)
        return;

    if(std::strncmp(m_filterWord, "\0", 1) == 0
            || m_filterColumn == -1)
        return;

    m_showedIndexes.clear();

    for(int i = 1; i < m_currentModel->rowCount(); ++i) {
        bool rowNeedAppend = textSearch(m_currentModel->data(ModelIndex(i, m_filterColumn)).data());
        for(int j = 0; j < m_currentModel->columnCount() && rowNeedAppend; ++j) {
            ModelIndex index(i, j);
            m_showedIndexes.append(index);
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

    if(m_filterColumn == -1
            || std::strncmp(m_filterWord, "\0", 1) == 0)
        return proxyIndex;

    LinkList<ModelIndex>::iterator iter = m_showedIndexes.begin();
    for(int row = 1; row < m_currentModel->rowCount() && iter != m_showedIndexes.end(); ++row) {
        for(int col = 0; col < m_currentModel->columnCount() && iter != m_showedIndexes.end(); ++col) {
            ModelIndex index(row, col);
            if(index == proxyIndex)
                return *iter;
            else ++iter;
        }
    }
    return ModelIndex();
}

ModelIndex ProxyModel::mapToProxy(const ModelIndex &sourceIndex) const
{
    if(!m_currentModel)
        return ModelIndex();

    if(m_filterColumn == -1
            || std::strncmp(m_filterWord, "\0", 1) == 0)
        return sourceIndex;

    LinkList<ModelIndex>::iterator iter = m_showedIndexes.begin();
    for(int row = 0; row < m_currentModel->rowCount() && iter != m_showedIndexes.end(); ++row) {
        for(int col = 0; col < m_currentModel->columnCount() && iter != m_showedIndexes.end(); ++col) {
            ModelIndex ind = sourceIndex;
            if(ind == *iter)
                return ModelIndex(row, col);
        }
    }
    return ModelIndex();
}

bool ProxyModel::textSearch(const char *data) const
{
    int dataLen = std::strlen(data);
    int keyLen = std::strlen(m_filterWord);

    if(keyLen > dataLen)
        return false;

    else if(keyLen == dataLen)
        return std::strncmp(data, m_filterWord, dataLen) == 0;

    const char *dataPtr = data;
    for(int i = 0; i < dataLen - keyLen; ++i, ++dataPtr) {
        if(std::strncmp(dataPtr, m_filterWord, keyLen) == 0)
            return true;
    }
    return false;
}

void ProxyModel::initHeader()
{
    m_currentModel->initHeader();
}
