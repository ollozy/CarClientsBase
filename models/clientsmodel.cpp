#include "clientsmodel.h"

#include "../app_core/cstringdata.h"

#include <cstdlib>
#include <sstream>

ClientsModel::ClientsModel()
    : AbstractItemModel()
    , m_currentStorage()
    , m_showList()
{

}

ClientsModel::~ClientsModel()
{

}

void ClientsModel::initHeader()
{
    setHeaderSize(1);
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
    for(int i = 0; i < 25 - app_global::numberOfLetters(licence); ++i)
        std::strncat(header, " ", 1);
    std::strncat(header, " | ", 3);
    std::strncat(header, name, 100);
    for(int i = 0; i < 25 - app_global::numberOfLetters(name); ++i)
        std::strncat(header, " ", 1);
    std::strncat(header, " | ", 3);
    std::strncat(header, passport, 100);
    for(int i = 0; i < 25 - app_global::numberOfLetters(passport); ++i)
        std::strncat(header, " ", 1);
    std::strncat(header, " | ", 3);
    std::strncat(header, address, 100);
    for(int i = 0; i < 25 - app_global::numberOfLetters(address); ++i)
        std::strncat(header, " ", 1);

    setHeaderData(CStringData(header, 600), 0);
}

CStringData ClientsModel::data(const ModelIndex &index) const
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
        return CStringData(m_showList[realRow].license(), app_global::client::licenseLen);
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

void ClientsModel::setData(const CStringData &data, const ModelIndex &index)
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

void ClientsModel::insertColumn(int column)
{
    (void)column;
}

void ClientsModel::removeColumn(int column)
{
    (void)column;
}

int ClientsModel::columnCount() const
{
    return 5;
}

int ClientsModel::rowCount() const
{
    return m_showList.size() + 1;
}

void ClientsModel::insertRow(int row)
{
    (void)row;
}

void ClientsModel::insertRow(const Client &client)
{
    m_currentStorage.insert(client.license(), client);
    m_showList = m_currentStorage.values();
}

Client ClientsModel::getByKey(const char *key)
{
    if(m_currentStorage.hasKey(key))
        return m_currentStorage[key];
    return Client();
}

void ClientsModel::clearModel()
{
    m_currentStorage.clear();
    m_showList = m_currentStorage.values();
}

void ClientsModel::removeRow(int row)
{
    if(m_showList.size() < row)
        return;

    Client &removedVal = m_showList[row - 1];
    m_currentStorage.erase(removedVal.license());
    m_showList = m_currentStorage.values();
}
