#include "abstractitemview.h"

#include "../models/abstractitemmodel.h"
#include "../delegates/abstractdelegate.h"

AbstractItemView::AbstractItemView()
    : m_model(nullptr)
    , m_delegate(nullptr)
{

}

AbstractItemView::~AbstractItemView()
{

}

void AbstractItemView::editItem(const char *newData)
{
    if(!m_delegate || !m_model)
        return;

    const ModelIndex &currentIndex = m_delegate->currentIndex();

    if(!currentIndex.isValid()
            || !currentIndex.isMulti())
        return;

    m_model->setData(newData, currentIndex);
}

void AbstractItemView::selectItem(int row, int column)
{
    if(!m_delegate)
        return;

    ModelIndex selectedIndex(row, column);
    if(!selectedIndex.isValid())
        return;

    m_delegate->setCurrentIndex(selectedIndex);
    update();
}

void AbstractItemView::selectRow(int row)
{
    selectItem(row, -1);
}

void AbstractItemView::selectColumn(int column)
{
    selectItem(column, -1);
}

ModelIndex AbstractItemView::selectedItem() const
{
    return m_delegate ? m_delegate->currentIndex() : ModelIndex();
}

AbstractDelegate *AbstractItemView::delegate() const
{
    return m_delegate;
}

void AbstractItemView::setDelegate(AbstractDelegate *delegate)
{
    if(m_delegate == delegate)
        return;

    m_delegate = delegate;
}

AbstractItemModel *AbstractItemView::model() const
{
    return m_model;
}

void AbstractItemView::setModel(AbstractItemModel *model)
{
    if(m_model == model)
        return;

    m_model = model;
}
