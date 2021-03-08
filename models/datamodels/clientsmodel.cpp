#include "clientsmodel.h"

#include "../viewmodels/clientsviewmodel.h"

ClientsModel::ClientsModel()
    : m_currentStorage()
    , m_viewModel(nullptr)
{

}

ClientsModel::~ClientsModel()
{

}

void ClientsModel::setData(const Client &data)
{
    m_currentStorage.insert(data.license(), data);
    notifyViewModel(m_currentStorage.values());
}

Client ClientsModel::getData(const CStringData &key) const
{
    if(!m_currentStorage.hasKey(key.data()))
        return Client();

    return m_currentStorage[key.data()];
}

bool ClientsModel::hasData(const CStringData &key) const
{
    return m_currentStorage.hasKey(key.data());
}

void ClientsModel::removeData(const CStringData &key)
{
    if(!m_currentStorage.hasKey(key.data()))
        return;

    m_currentStorage.erase(key.data());

    notifyViewModel(m_currentStorage.values());
}

void ClientsModel::clearData()
{
    m_currentStorage.clear();
    notifyViewModel(m_currentStorage.values());
}

void ClientsModel::filter(const CStringData &key, int role)
{
    LinkList<Client> storage;
    Client searchVal;
    switch (role) {
    case Name:
        searchVal.setName(key.data());
        storage = m_currentStorage.find(searchVal, [](const Client &left, const Client &right) {
            return app_global::textSearch(left.name(), right.name());
        });
        break;
    case Address:
        searchVal.setAddress(key.data());
        storage = m_currentStorage.find(searchVal, [](const Client &left, const Client &right) {
            return app_global::textSearch(left.address(), right.address());
        });
        break;
    case UndefinedRole:
        storage = m_currentStorage.values();
        break;
    default:
        break;
    }

    notifyViewModel(storage);
}

void ClientsModel::setViewModel(ClientsViewModel *model)
{
    m_viewModel = model;
    notifyViewModel(m_currentStorage.values());
}

void ClientsModel::notifyViewModel(const LinkList<Client> &newStorage) const
{
    if(m_viewModel)
        m_viewModel->update(newStorage);
}
