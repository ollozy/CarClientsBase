#include "rentinfomodel.h"

#include "../viewmodels/rentinfoviewmodel.h"

RentInfoModel::RentInfoModel()
    : m_currentStorage()
    , m_viewModel(nullptr)
{

}

RentInfoModel::~RentInfoModel()
{

}

void RentInfoModel::setData(const RentInfo &data)
{
    m_currentStorage.append(data);
    app_global::sort(m_currentStorage, m_currentStorage.begin(), --m_currentStorage.end(),
                     [&](const RentInfo &left, const RentInfo &right){
        return (std::strncmp(left.carData(), right.carData(), app_global::car::numberMaxLen));
    });
    notifyViewModel(m_currentStorage);
}

LinkList<RentInfo> RentInfoModel::getData(const CStringData &key, int keyRole) const
{
    LinkList<RentInfo> storage;

    LinkList<RentInfo>::iterator iter = m_currentStorage.begin();
    while(iter != m_currentStorage.end()) {
        iter = app_global::find_if(iter, m_currentStorage.end(), [&](const RentInfo &info) {
            switch (keyRole) {
            case CarRole:
                return std::strncmp(info.carData(), key.data(), key.length()) == 0;
            case ClientRole:
                return std::strncmp(info.clientData(), key.data(), key.length()) == 0;
            case IssueDateRole:
                return false;
            case ReturnDateRole:
                return false;
            default:
                return false;
            }
            return false;
        });
        if(iter != m_currentStorage.end())
            storage.append(*iter++);
    }

    return storage;
}

bool RentInfoModel::hasData(const CStringData &key, int keyRole) const
{
    LinkList<RentInfo>::iterator iter = app_global::find_if(m_currentStorage.begin(), m_currentStorage.end(), [&](const RentInfo &info) {
        switch (keyRole) {
        case CarRole:
            return std::strncmp(info.carData(), key.data(), key.length()) == 0;
        case ClientRole:
            return std::strncmp(info.clientData(), key.data(), key.length()) == 0;
        case IssueDateRole:
            return std::strncmp(info.issueDate(), key.data(), key.length()) == 0;
        case ReturnDateRole:
            return std::strncmp(info.returnDate(), key.data(), key.length()) == 0;
        default:
            return false;
        }
        return false;
    });

    if(iter != m_currentStorage.end())
        return true;

    return false;
}

void RentInfoModel::removeData(const CStringData &carKey)
{
    LinkList<RentInfo>::iterator iter = app_global::find_if(m_currentStorage.begin(), m_currentStorage.end(), [&](const RentInfo &info) {
        return std::strncmp(info.carData(), carKey.data(), carKey.length()) == 0;
    });
    if(iter == m_currentStorage.end())
        return;

    m_currentStorage.erase(iter);
}

void RentInfoModel::clearData()
{
    m_currentStorage.clear();
    notifyViewModel(m_currentStorage);
}

void RentInfoModel::filter(const CStringData &key, int role)
{
    (void)key;
    (void)role;
}

void RentInfoModel::setViewModel(RentInfoViewModel *model)
{
    m_viewModel = model;
}

void RentInfoModel::notifyViewModel(const LinkList<RentInfo> &newStorage)
{
    if(m_viewModel)
        m_viewModel->update(newStorage);
}
