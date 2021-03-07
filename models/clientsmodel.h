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

    virtual void initHeader() override;

    virtual CStringData data(const ModelIndex &index) const override;
    virtual void setData(const CStringData &data, const ModelIndex &index) override;

    virtual void clearModel() override;
    virtual int columnCount() const override;
    virtual int rowCount() const override;
    virtual void removeRow(int row) override;

    void insertRow(const Client &car);
    Client dataByKey(const char *key);

private:
    Tree<Client, app_global::client::licenseLen> m_currentStorage;
    LinkList<Client> m_showList;
};

#endif // CLIENTSMODEL_H
