#ifndef TABLEDELEGATE_H
#define TABLEDELEGATE_H

#include "abstractdelegate.h"

class ListDelegate : public AbstractDelegate
{
public:
    ListDelegate();
    ~ListDelegate();

    virtual void drawHorizontalBoard(bool selected) override;
    virtual void drawVerticalBorad(bool selected) override;
    virtual void drawData() override;
    virtual void drawNextLine() override;
};

#endif // TABLEDELEGATE_H
