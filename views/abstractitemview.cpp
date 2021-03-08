#include "abstractitemview.h"

#include "../models/viewmodels/abstractitemmodel.h"

#include "../delegates/abstractdelegate.h"

#include "../app_core/cstringdata.h"

AbstractItemView::AbstractItemView()
    : m_model(nullptr)
    , m_delegate(nullptr)
{

}

AbstractItemView::~AbstractItemView()
{

}

void AbstractItemView::editItem(const char *newData, int dataLen)
{
    if(!m_delegate || !m_model)
        return;

    const ModelIndex &currentIndex = m_delegate->currentIndex();

    if(!currentIndex.isValid()
            || !currentIndex.isMulti())
        return;

//    m_model->setData(CStringData(newData, dataLen), currentIndex);
}

void AbstractItemView::selectItem(int row, int column)
{
    if(!m_delegate)
        return;

    ModelIndex selectedIndex(row, column);
    if(!selectedIndex.isValid())
        return;

    m_selectedItems.append(selectedIndex);
}

void AbstractItemView::selectRow(int row)
{
    selectItem(row, -1);
}

void AbstractItemView::selectColumn(int column)
{
    selectItem(column, -1);
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
    m_delegate->setModel(m_model);
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
    m_delegate->setModel(m_model);
    m_selectedItems.clear();
}

const LinkList<ModelIndex> &AbstractItemView::selectedItems() const
{
    return m_selectedItems;
}

void AbstractItemView::clearSelection()
{
    m_selectedItems.clear();
}
