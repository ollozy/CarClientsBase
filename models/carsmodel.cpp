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

    if(index.column() != 0)
        return CStringData();

    int realRow = index.row() - 1;
    if(realRow == 0)
        return headerData(index.column());

    char header[600] = "\0";
    char n[3] = "\0";
    char year[100] = "\0";
    {
        std::stringstream stream(n);
        stream << index.row() + 1;
    }
    {
        std::stringstream stream(year);
        stream << m_showList[index.row()].year();
    }

    std::strncat(header, n, 3);
    for(int i = 0; i < 25 - app_global::numberOfLetters(n); ++i)
        std::strncat(header, " ", 1);
    std::strncat(header, " | ", 3);

    const char *field = m_showList[index.row()].number();
    std::strncat(header, field, 100);
    for(int i = 0; i < 25 - app_global::numberOfLetters(field); ++i)
        std::strncat(header, " ", 1);
    std::strncat(header, " | ", 3);

    field = m_showList[index.row()].brand();
    std::strncat(header, field, 100);
    for(int i = 0; i < 25 - app_global::numberOfLetters(field); ++i)
        std::strncat(header, " ", 1);
    std::strncat(header, " | ", 3);

    field = m_showList[index.row()].color();
    std::strncat(header, field, 100);
    for(int i = 0; i < 25 - app_global::numberOfLetters(field); ++i)
        std::strncat(header, " ", 1);
    std::strncat(header, " | ", 3);

    std::strncat(header, year, 100);
    for(int i = 0; i < 25 - app_global::numberOfLetters(year); ++i)
        std::strncat(header, " ", 1);
    std::strncat(header, " | ", 3);

    if(m_showList[index.row()].available()) {
        std::strncat(header, "Да", 100);
        for(int i = 0; i < 25 - app_global::numberOfLetters("Да"); ++i)
            std::strncat(header, " ", 1);
    }
    else {
        std::strncat(header, "Нет", 100);
        for(int i = 0; i < 25 - app_global::numberOfLetters("Нет"); ++i)
            std::strncat(header, " ", 1);
    }
    return CStringData(header, 600);
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
