#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include "abstractitemview.h"

class TableView : public AbstractItemView
{
public:
    TableView();
    ~TableView();

public:
    virtual void update() override;
    virtual void selectItem(int row, int column) override;
};

#endif // TABLEVIEW_H
