#include "carsviewmodel.h"

#include "../../app_core/cstringdata.h"

#include <cstring>

CarsViewModel::CarsViewModel()
    : AbstractItemModel()
    , m_showList()
{

}

CarsViewModel::~CarsViewModel()
{

}

void CarsViewModel::initHeader()
{
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
    for(int i = 0; i < 45 - app_global::numberOfLetters(numb); ++i)
        std::strncat(header, " ", 1);
    std::strncat(header, " | ", 3);
    std::strncat(header, brand, 100);
    for(int i = 0; i < 45 - app_global::numberOfLetters(brand); ++i)
        std::strncat(header, " ", 1);
    std::strncat(header, " | ", 3);
    std::strncat(header, color, 100);
    for(int i = 0; i < 45 - app_global::numberOfLetters(color); ++i)
        std::strncat(header, " ", 1);
    std::strncat(header, " | ", 3);
    std::strncat(header, year, 100);
    for(int i = 0; i < 45 - app_global::numberOfLetters(year); ++i)
        std::strncat(header, " ", 1);
    std::strncat(header, " | ", 3);
    std::strncat(header, available, 100);
    for(int i = 0; i < 45 - app_global::numberOfLetters(available); ++i)
        std::strncat(header, " ", 1);

    setHeaderData(CStringData(header, 600));
}

CStringData CarsViewModel::data(const ModelIndex &index) const
{
    if(m_showList.size() < index.row() - 1
            || !index.isValid())
        return CStringData();

    if(index.column() > columnCount())
        return CStringData();

    int realRow = index.row() - 1;
    if(realRow < 0)
        return headerData();

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

int CarsViewModel::columnCount() const
{
    return 6;
}

int CarsViewModel::rowCount() const
{
    return m_showList.size() + 1;
}

void CarsViewModel::update(const LinkList<Car> &newStorage)
{
    m_showList = newStorage;
}
