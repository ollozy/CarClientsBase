#include "carsmodel.h"

#include "../app_core/cstringdata.h"

#include <cstdlib>
#include <sstream>

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
    setHeaderSize(1);
    char n[100] = "N";
    char numb[100] = "Гос. номер";
    char brand[100] = "Марка";
    char color[100] = "Цвет";
    char year[100] = "Год выпуска";
    char available[100] = "Доступен";
    char header[600] = "\0";
    std::strncat(header, n, 100);
    for(int i = 0; i < 3 - app_global::numberOfLetters(n); ++i)
        std::strncat(header, " ", 1);
    std::strncat(header, " | ", 3);
    std::strncat(header, numb, 100);
    for(int i = 0; i < 25 - app_global::numberOfLetters(numb); ++i)
        std::strncat(header, " ", 1);
    std::strncat(header, " | ", 3);
    std::strncat(header, brand, 100);
    for(int i = 0; i < 25 - app_global::numberOfLetters(brand); ++i)
        std::strncat(header, " ", 1);
    std::strncat(header, " | ", 3);
    std::strncat(header, color, 100);
    for(int i = 0; i < 25 - app_global::numberOfLetters(color); ++i)
        std::strncat(header, " ", 1);
    std::strncat(header, " | ", 3);
    std::strncat(header, year, 100);
    for(int i = 0; i < 25 - app_global::numberOfLetters(year); ++i)
        std::strncat(header, " ", 1);
    std::strncat(header, " | ", 3);
    std::strncat(header, available, 100);
    for(int i = 0; i < 25 - app_global::numberOfLetters(available); ++i)
        std::strncat(header, " ", 1);

    setHeaderData(CStringData(header, 600), 0);
}

CStringData CarsModel::data(const ModelIndex &index) const
{
    if(m_showList.size() < index.row() - 1
            || !index.isValid())
        return CStringData();

    if(index.column() > columnCount())
        return CStringData();

    int realRow = index.row() - 1;
    if(realRow < 0)
        return headerData(index.column());

    switch (index.column()) {
    case 0:
        return CStringData(index.row());
    case 1:
        return CStringData(m_showList[realRow].number(), app_global::car::numberMaxLen);
    case 2:
        return CStringData(m_showList[realRow].brand(), app_global::car::brandMaxLen);
    case 3:
        return CStringData(m_showList[realRow].color(), app_global::car::colorMaxLen);
    case 4:
        return CStringData(m_showList[realRow].year());
    case 5: {
        if(m_showList[realRow].available())
            return CStringData("Да", app_global::car::availableMaxLen);
        else
            return CStringData("Нет", app_global::car::availableMaxLen);
    }
    default:
        return CStringData();
    }
    return CStringData();
}

void CarsModel::setData(const CStringData &data, const ModelIndex &index)
{
    (void)data;
    (void)index;
    //    if(data.isEmpty()
    //            || m_showList.size() < index.row()
    //            || !index.isValid())
    //        return;

    //    int realRow = index.row() - 1;
    //    if(realRow < 0)
    //        return;

    //    switch (index.column()) {
    //    case 1: {
    //        Car editingData = m_showList[realRow];
    //        m_currentStorage.erase(editingData.number());
    //        editingData.setNumber(data.data());
    //        m_currentStorage.insert(editingData.number(), editingData);
    //        m_showList = m_currentStorage.values();
    //        break;
    //    }
    //    case 2: {
    //        const char *key = m_showList[realRow].number();
    //        Car &editingData = m_currentStorage[key];
    //        editingData.setBrand(data.data());
    //        m_showList = m_currentStorage.values();
    //        break;
    //    }
    //    case 3: {
    //        const char *key = m_showList[realRow].number();
    //        Car &editingData = m_currentStorage[key];
    //        editingData.setColor(data.data());
    //        m_showList = m_currentStorage.values();
    //        break;
    //    }
    //    case 4: {
    //        const char *key = m_showList[realRow].number();
    //        Car &editingData = m_currentStorage[key];
    //        editingData.setYear(data.toInt());
    //        m_showList = m_currentStorage.values();
    //        break;
    //    }
    //    case 5: {
    //        const char *key = m_showList[realRow].number();
    //        Car &editingData = m_currentStorage[key];
    //        if(std::strncmp(data.data(), "Да", 3))
    //            editingData.setAvailable(true);
    //        else
    //            editingData.setAvailable(false);
    //        m_showList = m_currentStorage.values();
    //    }
    //    }
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

void CarsModel::insertRow(int row)
{
    (void)row;
}

void CarsModel::insertRow(const Car &car)
{
    m_currentStorage.insert(car.number(), car);
    m_showList = m_currentStorage.values();
}

void CarsModel::clearModel()
{
    m_currentStorage.clear();
    m_showList = m_currentStorage.values();
}

void CarsModel::removeRow(int row)
{
    if(row > m_showList.size())
        return;

    Car &removedVal = m_showList[row - 1];
    m_currentStorage.erase(removedVal.number());
    m_showList = m_currentStorage.values();
}
