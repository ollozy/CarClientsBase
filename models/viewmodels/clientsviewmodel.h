#ifndef CLIENTSVIEWMODEL_H
#define CLIENTSVIEWMODEL_H

#include "abstractitemmodel.h"

#include "../../app_core/linklist.h"

#include "../../items.h"

class ClientsViewModel : public AbstractItemModel
{
public:
    ClientsViewModel();
    ~ClientsViewModel();

    virtual void initHeader() override;

    virtual CStringData data(const ModelIndex &index) const override;

    virtual int columnCount() const override;
    virtual int rowCount() const override;

    void update(const LinkList<Client> &newStorage);

private:
    LinkList<Client> m_showList;
};

#endif // CLIENTSVIEWMODEL_H
