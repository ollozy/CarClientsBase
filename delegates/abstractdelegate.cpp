#include "abstractdelegate.h"

AbstractDelegate::AbstractDelegate()
    : m_model(nullptr)
    , m_currentIndex()
    , m_fieldWidth(0)
{

}

AbstractDelegate::~AbstractDelegate()
{

}

const ModelIndex &AbstractDelegate::currentIndex() const
{
    return m_currentIndex;
}

void AbstractDelegate::setCurrentIndex(const ModelIndex &index)
{
    if(m_currentIndex == index)
        return;
    m_currentIndex = index;
}

AbstractItemModel *AbstractDelegate::model() const
{
    return m_model;
}

void AbstractDelegate::setModel(AbstractItemModel *model)
{
    if(m_model == model)
        return;

    m_model = model;
}

int AbstractDelegate::fieldWidth() const
{
    return m_fieldWidth;
}

void AbstractDelegate::setFieldWidth(int fieldWidth)
{
    m_fieldWidth = fieldWidth;
}
