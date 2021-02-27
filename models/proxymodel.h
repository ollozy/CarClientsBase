#ifndef PROXYMODEL_H
#define PROXYMODEL_H

#include "abstractitemmodel.h"

#include "../app_core/linklist.h"

class ProxyModel : public AbstractItemModel
{
public:
    ProxyModel();

    virtual CStringData data(const ModelIndex &index) const override;
    virtual void setData(const CStringData &data, const ModelIndex &index) override;
    virtual void clearModel() override;
    virtual void insertColumn(int column) override;
    virtual void removeColumn(int column) override;
    virtual int columnCount() const override;
    virtual void insertRow(int row) override;
    virtual void removeRow(int row) override;
    virtual int rowCount() const override;

    void setModel(AbstractItemModel *model);
    AbstractItemModel *model() const;

    void setFilter(const char *filterWord);
    void clearFilter();
    void setFilterColumn(int column);

private:
    void filter() const;
    void initProxy() const;
    ModelIndex mapToSource(const ModelIndex &proxyIndex) const;
    ModelIndex mapToProxy(const ModelIndex &index) const;

private:
    AbstractItemModel *m_currentModel;

    mutable LinkList<ModelIndex> m_showedIndexes;

    int m_filterColumn;
    char m_filterWord[100];
};

#endif // PROXYMODEL_H
