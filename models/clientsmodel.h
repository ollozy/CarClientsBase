#ifndef CLIENTSMODEL_H
#define CLIENTSMODEL_H

#include "abstractitemmodel.h"

#include "../app_core/searchtree.h"
#include "../app_core/linklist.h"

#include "../items.h"

class ClientsModel : public AbstractItemModel
{
public:
    ClientsModel();
    ~ClientsModel();

    void initHeader();

    virtual CStringData data(const ModelIndex &index) const override;
    virtual void setData(const CStringData &data, const ModelIndex &index) override;

    virtual void clearModel() override;

    virtual void insertColumn(int column) override;
    virtual void removeColumn(int column) override;
    virtual int columnCount() const override;

    virtual void insertRow(int row) override;
    virtual void removeRow(int row) override;
    virtual int rowCount() const override;

    void insertRow(const Client &car);

    Client &getByKey(const char *key);

private:
    Tree<Client, app_global::client::licenseLen> m_currentStorage;
    LinkList<Client> m_showList;
};

#endif // CLIENTSMODEL_H
