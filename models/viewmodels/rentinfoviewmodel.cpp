#include "rentinfoviewmodel.h"

#include "../../app_core/cstringdata.h"

#include <cstring>

RentInfoViewModel::RentInfoViewModel()
    : AbstractItemModel()
    , m_showList()
{

}

RentInfoViewModel::~RentInfoViewModel()
{

}

void RentInfoViewModel::initHeader()
{
    char n[100] = "N";
    char licence[100] = "Номер водительского удостоверерния клиента";
    char number[100] = "Гос. номер автомобиля";
    char issueDate[100] = "Дата выдачи в аренду";
    char returnDate[100] = "Дата возврата";
    char header[600] = "\0";
    std::strncat(header, n, 100);
    for(int i = 0; i < 3 - app_global::numberOfLetters(n); ++i)
        std::strncat(header, " ", 1);
    std::strncat(header, " | ", 3);
    std::strncat(header, licence, 100);
    for(int i = 0; i < 45 - app_global::numberOfLetters(licence); ++i)
        std::strncat(header, " ", 1);
    std::strncat(header, " | ", 3);
    std::strncat(header, number, 100);
    for(int i = 0; i < 45 - app_global::numberOfLetters(number); ++i)
        std::strncat(header, " ", 1);
    std::strncat(header, " | ", 3);
    std::strncat(header, issueDate, 100);
    for(int i = 0; i < 45 - app_global::numberOfLetters(issueDate); ++i)
        std::strncat(header, " ", 1);
    std::strncat(header, " | ", 3);
    std::strncat(header, returnDate, 100);
    for(int i = 0; i < 45 - app_global::numberOfLetters(returnDate); ++i)
        std::strncat(header, " ", 1);

    setHeaderData(CStringData(header, 600));
}

CStringData RentInfoViewModel::data(const ModelIndex &index) const
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
        return CStringData(m_showList[realRow].clientData(), app_global::client::licenseMaxLen);
    case 2:
        return CStringData(m_showList[realRow].carData(), app_global::car::numberMaxLen);
    case 3:
        return CStringData(m_showList[realRow].issueDate(), app_global::dateLen);
    case 4:
        return CStringData(m_showList[realRow].returnDate(), app_global::dateLen);
    default:
        return CStringData();
    }
    return CStringData();
}

int RentInfoViewModel::columnCount() const
{
    return 5;
}

int RentInfoViewModel::rowCount() const
{
    return m_showList.size() + 1;
}

void RentInfoViewModel::update(const LinkList<RentInfo> &newStorage)
{
    m_showList = newStorage;
}
