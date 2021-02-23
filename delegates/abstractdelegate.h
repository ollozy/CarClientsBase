#ifndef ABSTRACTDELEGATE_H
#define ABSTRACTDELEGATE_H

#include "../app_core/modelindex.h"

class AbstractItemModel;

class AbstractDelegate
{
public:
    AbstractDelegate();
    virtual ~AbstractDelegate();

    virtual void draw() = 0;
    virtual void drawSelected() = 0;

    const ModelIndex &currentIndex() const;
    void setCurrentIndex(const ModelIndex &index);

    AbstractItemModel *model() const;
    void setModel(AbstractItemModel *model);

    int fieldWidth() const;
    void setFieldWidth(int fieldWidth);

private:
    AbstractItemModel *m_model;

    ModelIndex m_currentIndex;

    int m_fieldWidth;
};

#endif // ABSTRACTDELEGATE_H
