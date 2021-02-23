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

private:
    AbstractItemModel *m_model;

    ModelIndex m_currentIndex;
};

#endif // ABSTRACTDELEGATE_H
