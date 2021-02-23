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

    virtual void update() = 0;

    virtual void editItem(const char *newData);
    virtual void selectItem(int row, int column);
    virtual void selectRow(int row);
    virtual void selectColumn(int column);

    ModelIndex selectedItem() const;

    AbstractDelegate *delegate() const;
    void setDelegate(AbstractDelegate *delegate);

    AbstractItemModel *model() const;
    void setModel(AbstractItemModel *model);

private:
    AbstractItemModel *m_model;
    AbstractDelegate *m_delegate;
};

#endif // ABSTRACTITEMVIEW_H
