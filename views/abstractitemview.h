#ifndef ABSTRACTITEMVIEW_H
#define ABSTRACTITEMVIEW_H

#include "../app_core/modelindex.h"

class AbstractItemModel;
class AbstractDelegate;

class AbstractItemView
{
public:
    AbstractItemView();
    virtual ~AbstractItemView();

    virtual void show() = 0;

    virtual void editItem();
    virtual void selectItem(int row, int column);
    virtual void selectRow(int row);
    virtual void selectColumn(int column);

    const ModelIndex &selectedItem() const;

    AbstractDelegate *delegate() const;
    void setDelegate(AbstractDelegate *delegate);

    AbstractItemModel *setModel() const;
    void setAbstractModel(AbstractItemModel *model);

private:
    AbstractItemModel *m_model;
    AbstractDelegate *m_delegate;

    ModelIndex m_currentIndex;
};

#endif // ABSTRACTITEMVIEW_H
