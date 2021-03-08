#ifndef CARMODEL_H
#define CARMODEL_H

#include "../../items.h"
#include "../../global.h"

#include "../../app_core/hash.h"
#include "../../app_core/cstringdata.h"

class CarsViewModel;

class CarsModel
{
public:
    enum CarRoles {
        UndefinedRole = -1,
        Number = 1,
        Brand,
        Color,
        Year
    };

    CarsModel();
    ~CarsModel();

    void setData(const Car &data);

    Car getData(const CStringData &key) const;

    bool hasData(const CStringData &key) const;

    void removeData(const CStringData &key);

    void clearData();

    void filter(const CStringData &key, int role) const;

    void setAvailable(const CStringData &key, bool available);

    void setViewModel(CarsViewModel *model);

private:
    void notifyViewModel(const LinkList<Car> &newStorage) const;

private:
    Hash<Car, app_global::car::numberMaxLen> m_currentStorage;
    CarsViewModel *m_viewModel;
};

#endif // CARMODEL_H
