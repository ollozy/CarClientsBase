#ifndef TABLEDELEGATE_H
#define TABLEDELEGATE_H

#include "abstractdelegate.h"

class TableDelegate : public AbstractDelegate
{
public:
    TableDelegate();
    ~TableDelegate();

    virtual void drawHorizontalBoard(bool selected) override;
    virtual void drawVerticalBorad(bool selected) override;
    virtual void drawData() override;
    virtual void drawNextLine() override;

private:
    void drawUtfFixedData(const char *data);
    int realStringLen(const char *data);
};

#endif // TABLEDELEGATE_H
