#include "rentinfomodel.h"

#include "../app_core/cstringdata.h"

#include <cstring>

RentInfoModel::RentInfoModel()
    : AbstractItemModel()
    , m_data()
{

}

RentInfoModel::~RentInfoModel()
{

}

void RentInfoModel::initHeader()
{
    setHeaderSize(1);
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

    setHeaderData(CStringData(header, 600), 0);
}

CStringData RentInfoModel::data(const ModelIndex &index) const
{
    if(m_data.size() < index.row() - 1
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
        return CStringData(m_data[realRow].clientData(), app_global::client::licenseLen);
    case 2:
        return CStringData(m_data[realRow].carData(), app_global::car::numberMaxLen);
    case 3:
        return CStringData(m_data[realRow].issueDate(), app_global::dateLen);
    case 4:
        return CStringData(m_data[realRow].returnDate(), app_global::dateLen);
    default:
        return CStringData();
    }
    return CStringData();
}

void RentInfoModel::setData(const CStringData &, const ModelIndex &)
{

}

void RentInfoModel::clearModel()
{
    m_data.clear();
}

int RentInfoModel::columnCount() const
{
    return 5;
}

int RentInfoModel::rowCount() const
{
    return m_data.size() + 1;
}

void RentInfoModel::removeRow(int row)
{
    LinkList<RentInfo>::iterator iter = m_data.begin();
    for(int i = 0; i < row; ++i, ++iter);
    m_data.erase(iter);
}

void RentInfoModel::insertRow(const RentInfo &info)
{
    m_data.append(info);
    sort();
}

RentInfo RentInfoModel::mapClient(const Client &client)
{
    int foundRow = find(client.license(), app_global::client::licenseLen, 2);
    return foundRow < 0 ? RentInfo() : m_data[foundRow];
}

RentInfo RentInfoModel::mapCar(const Car &car)
{
    int foundRow = find(car.number(), app_global::car::numberMaxLen, 3);
    return foundRow < 0 ? RentInfo() : m_data[foundRow];
}

void RentInfoModel::sort()
{

}

int RentInfoModel::find(const char *key, int keyLen, int col)
{
    for(int row = 0; row < m_data.size(); ++row) {
        CStringData rentKey = data(ModelIndex(row + 1, col));
        if(std::strncmp(key, rentKey.data(), keyLen))
            return row;
    }
    return -1;
}
