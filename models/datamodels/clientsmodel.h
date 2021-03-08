#ifndef CLIENTSMODEL_H
#define CLIENTSMODEL_H

#include "../../global.h"
#include "../../items.h"

#include "../../app_core/cstringdata.h"
#include "../../app_core/searchtree.h"

class ClientsViewModel;

class ClientsModel
{
public:
    enum ClientRoles {
        UndefinedRole = -1,
        License = 1,
        Name,
        PassportData,
        Address
    };

    ClientsModel();
    ~ClientsModel();

    void setData(const Client &data);

    Client getData(const CStringData &key) const;

    bool hasData(const CStringData &key) const;

    void removeData(const CStringData &key);

    void clearData();

    void filter(const CStringData &key, int role);

    void setViewModel(ClientsViewModel *model);

private:
    void notifyViewModel(const LinkList<Client> &newStorage) const;

private:
    Tree<Client, app_global::client::licenseMaxLen> m_currentStorage;
    ClientsViewModel *m_viewModel;
};

#endif // CLIENTSMODEL_H
