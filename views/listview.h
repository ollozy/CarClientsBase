#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include "abstractitemview.h"

class ListView : public AbstractItemView
{
public:
    ListView();
    ~ListView();

public:
    virtual void update() override;
    virtual void selectItem(int row, int column) override;

    void selectNext();
    void selectPrevious();
};

#endif // TABLEVIEW_H
