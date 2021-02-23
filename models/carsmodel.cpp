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

void CarsModel::initHeader()
{
    setHeaderSize(6);
    setHeaderData(CStringData("N", 2), 0);
    setHeaderData(CStringData("Гос. номер", 100), 1);
    setHeaderData(CStringData("Марка", app_global::car::brandMaxLen), 2);
    setHeaderData(CStringData("Цвет", app_global::car::colorMaxLen), 3);
    setHeaderData(CStringData("Год выпуска", 100), 4);
    setHeaderData(CStringData("Доступет", 100), 5);
}

CStringData CarsModel::data(const ModelIndex &index) const
{
    if(m_showList.size() < index.row()
            || !index.isValid())
        return CStringData();

    int realRow = index.row() - 1;
    if(realRow < 0)
        return headerData(index.column());

    switch (index.column()) {
    case 0:
        return  CStringData(index.row());
    case 1:
        return CStringData(m_showList[realRow].number(), app_global::car::numberLen);
    case 2:
        return CStringData(m_showList[realRow].brand(), app_global::car::brandMaxLen);
    case 3:
        return CStringData(m_showList[realRow].color(), app_global::car::colorMaxLen);
    case 4:
        return CStringData(m_showList[realRow].year());
    case 5:
        if(m_showList[realRow].available())
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

    int realRow = index.row() - 1;
    if(realRow < 0)
        return;

    switch (index.column()) {
    case 1: {
        Car &editingData = m_showList[realRow];
        editingData.setNumber(data.data());
        break;
    }
    case 2: {
        Car &editingData = m_showList[realRow];
        editingData.setBrand(data.data());
        break;
    }
    case 3: {
        Car &editingData = m_showList[realRow];
        editingData.setColor(data.data());
        break;
    }
    case 4: {
        Car &editingData = m_showList[realRow];
        editingData.setYear(std::atoi(data.data()));
        break;
    }
    case 5: {
        Car &editingData = m_showList[realRow];
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
    return 6;
}

int CarsModel::rowCount() const
{
    return m_showList.size() + 1;
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
