#ifndef ABSTRACTITEMVIEW_H
#define ABSTRACTITEMVIEW_H

#include "../app_core/modelindex.h"

#include "../app_core/linklist.h"

class AbstractItemModel;
class AbstractDelegate;

class AbstractItemView
{
public:
    AbstractItemView();
    virtual ~AbstractItemView();

    virtual void update() = 0;

    virtual void editItem(const char *newData, int dataLen);
    virtual void selectItem(int row, int column);
    virtual void selectRow(int row);
    virtual void selectColumn(int column);

    AbstractDelegate *delegate() const;
    void setDelegate(AbstractDelegate *delegate);

    AbstractItemModel *model() const;
    void setModel(AbstractItemModel *model);

    const LinkList<ModelIndex> &selectedItems() const;
    void clearSelection();

private:
    AbstractItemModel *m_model;
    AbstractDelegate *m_delegate;

    LinkList<ModelIndex> m_selectedItems;
};

#endif // ABSTRACTITEMVIEW_H
