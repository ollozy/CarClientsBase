#ifndef RENTINFOVIEWMODEL_H
#define RENTINFOVIEWMODEL_H

#include "abstractitemmodel.h"

#include "../../app_core/linklist.h"
#include "../../items.h"

class RentInfoViewModel : public AbstractItemModel
{
public:
    RentInfoViewModel();
    ~RentInfoViewModel();

    virtual void initHeader() override;
    virtual CStringData data(const ModelIndex &index) const override;
    virtual int columnCount() const override;
    virtual int rowCount() const override;

    void update(const LinkList<RentInfo> &newStorage);

private:
    LinkList<RentInfo> m_showList;
};

#endif // RENTINFOVIEWMODEL_H
