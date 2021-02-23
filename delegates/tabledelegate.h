#ifndef TABLEDELEGATE_H
#define TABLEDELEGATE_H

#include "abstractdelegate.h"

class TableDelegate : public AbstractDelegate
{
public:
    TableDelegate();
    ~TableDelegate();

    virtual void draw() override;
    virtual void drawSelected() override;

private:
    void drawHorizontalBoard();
    void drawVerticalBorad();
    void drawSelectedHorizontalBoard();
    void drawSelectedVerticalBoard();
    void drawData();
};

#endif // TABLEDELEGATE_H
