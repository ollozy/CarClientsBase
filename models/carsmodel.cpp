#include "carsmodel.h"

#include "../app_core/cstringdata.h"

#include <cstdlib>

CarsModel::CarsModel()
    : AbstractItemModel()
    , m_currentStorage()
    , m_showList()
{

}

CarsModel::~CarsModel()
{

}

CStringData CarsModel::data(const ModelIndex &index) const
{
    if(m_showList.isEmpty()
            || m_showList.size() < index.row()
            || !index.isValid())
        return CStringData();

    switch (index.column()) {
    case 0:
        return CStringData(m_showList[index.row()].number(), app_global::car::numberLen);
    case 1:
        return CStringData(m_showList[index.row()].brand(), app_global::car::brandMaxLen);
    case 2:
        return CStringData(m_showList[index.row()].color(), app_global::car::colorMaxLen);
    case 3:
        return CStringData(m_showList[index.row()].year());
    case 4:
        if(m_showList[index.row()].available())
            return CStringData("Да", 3);
        return CStringData("Нет", 4);
    }
    return CStringData();
}

void CarsModel::setData(const CStringData &data, const ModelIndex &index)
{
    if(data.isEmpty()
            || m_showList.size() < index.row()
            || !index.isValid())
        return;

    switch (index.column()) {
    case 0: {
        Car &editingData = m_showList[index.row()];
        editingData.setNumber(data.data());
        break;
    }
    case 1: {
        Car &editingData = m_showList[index.row()];
        editingData.setBrand(data.data());
        break;
    }
    case 2: {
        Car &editingData = m_showList[index.row()];
        editingData.setColor(data.data());
        break;
    }
    case 3: {
        Car &editingData = m_showList[index.row()];
        editingData.setYear(std::atoi(data.data()));
        break;
    }
    case 4: {
        Car &editingData = m_showList[index.row()];
        if(std::strncmp(data.data(), "Да", 3))
            editingData.setAvailable(true);
        else
            editingData.setAvailable(false);
    }
    }
}

void CarsModel::insertColumn(int column)
{
    (void)column;
}

void CarsModel::removeColumn(int column)
{
    (void)column;
}

int CarsModel::columnCount() const
{
    return 5;
}

int CarsModel::rowCount() const
{
    m_showList.size();
}

void CarsModel::insertRow(const Car &value)
{
    m_currentStorage.insert(value.number(), value);
    m_showList = m_currentStorage.values();
}

void CarsModel::removeRow(int row)
{
    if(m_showList.size() < row)
        return;

    Car &removedVal = m_showList[row];
    m_currentStorage.erase(removedVal.number());
    m_showList = m_currentStorage.values();
}

void CarsModel::insertRow(int row)
{
    (void)row;
}
