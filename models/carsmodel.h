#ifndef CARSMODEL_H
#define CARSMODEL_H

#include "abstractitemmodel.h"

#include "../app_core/hash.h"
#include "../app_core/linklist.h"

#include "../global.h"
#include "../items.h"

class CarsModel : public AbstractItemModel
{
public:
    CarsModel();
    ~CarsModel();

    virtual CStringData data(const ModelIndex &index) const override;
    virtual void setData(const CStringData &data, const ModelIndex &index) override;
    virtual void insertColumn(int column) override;
    virtual void removeColumn(int column) override;
    virtual int columnCount() const override;
    virtual int rowCount() const override;
    virtual void removeRow(int row) override;

    void insertRow(const Car &value);

private:
    virtual void insertRow(int row) override;

private:
    Hash<Car, app_global::car::numberLen> m_currentStorage;
    LinkList<Car> m_showList;
};

#endif // CARSMODEL_H
