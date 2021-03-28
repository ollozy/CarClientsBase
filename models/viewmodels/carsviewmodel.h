#ifndef CARSVIEWMODEL_H
#define CARSVIEWMODEL_H

#include "abstractitemmodel.h"

#include "../../app_core/linklist.h"

#include "../../items.h"

class CarsViewModel : public AbstractItemModel
{
public:
    CarsViewModel();
    ~CarsViewModel();

    virtual void initHeader() override;

    virtual CStringData data(const ModelIndex &index) const override;

    virtual int columnCount() const override;
    virtual int rowCount() const override;

    void update(const LinkList<Car> &newStorage);

private:
    LinkList<Car> m_showList;
};

#endif // CARSVIEWMODEL_H
