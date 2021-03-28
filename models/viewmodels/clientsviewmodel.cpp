#include "clientsviewmodel.h"

#include "../../app_core/cstringdata.h"

#include <cstring>

ClientsViewModel::ClientsViewModel()
    : AbstractItemModel()
    , m_showList()
{

}

ClientsViewModel::~ClientsViewModel()
{

}

void ClientsViewModel::initHeader()
{
    char n[100] = "N";
    char licence[100] = "Номер удостоверения";
    char name[100] = "ФИО";
    char passport[100] = "Паспортные данные";
    char address[100] = "Адрес";
    char header[600] = "\0";
    std::strncat(header, n, 100);
    for(int i = 0; i < 3 - app_global::numberOfLetters(n); ++i)
        std::strncat(header, " ", 1);
    std::strncat(header, " | ", 3);
    std::strncat(header, licence, 100);
    for(int i = 0; i < 45 - app_global::numberOfLetters(licence); ++i)
        std::strncat(header, " ", 1);
    std::strncat(header, " | ", 3);
    std::strncat(header, name, 100);
    for(int i = 0; i < 45 - app_global::numberOfLetters(name); ++i)
        std::strncat(header, " ", 1);
    std::strncat(header, " | ", 3);
    std::strncat(header, passport, 100);
    for(int i = 0; i < 45 - app_global::numberOfLetters(passport); ++i)
        std::strncat(header, " ", 1);
    std::strncat(header, " | ", 3);
    std::strncat(header, address, 100);
    for(int i = 0; i < 45 - app_global::numberOfLetters(address); ++i)
        std::strncat(header, " ", 1);

    setHeaderData(CStringData(header, 600));
}

CStringData ClientsViewModel::data(const ModelIndex &index) const
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
        return CStringData(m_showList[realRow].license(), app_global::client::licenseMaxLen);
    case 2:
        return CStringData(m_showList[realRow].name(), app_global::client::nameMaxLen);
    case 3:
        return CStringData(m_showList[realRow].passport(), app_global::client::passportMaxLen);
    case 4:
        return CStringData(m_showList[realRow].address(), app_global::client::addressMaxLen);
    default:
        return CStringData();
    }
    return CStringData();
}

int ClientsViewModel::columnCount() const
{
    return 5;
}

int ClientsViewModel::rowCount() const
{
    return m_showList.size() + 1;
}

void ClientsViewModel::update(const LinkList<Client> &newStorage)
{
    m_showList = newStorage;
}
