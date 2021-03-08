#include "carsmodel.h"

#include "../viewmodels/carsviewmodel.h"

CarsModel::CarsModel()
    : m_currentStorage()
    , m_viewModel(nullptr)
{

}

CarsModel::~CarsModel()
{

}

void CarsModel::setData(const Car &data)
{
    m_currentStorage.insert(data.number(), data);
    notifyViewModel(m_currentStorage.values());
}

Car CarsModel::getData(const CStringData &key) const
{
    if(!m_currentStorage.hasKey(key.data()))
        return Car();

    return m_currentStorage[key.data()];
}

bool CarsModel::hasData(const CStringData &key) const
{
    return m_currentStorage.hasKey(key.data());
}

void CarsModel::removeData(const CStringData &key)
{
    if(!m_currentStorage.hasKey(key.data()))
        return;

    m_currentStorage.erase(key.data());

    notifyViewModel(m_currentStorage.values());
}

void CarsModel::clearData()
{
    m_currentStorage.clear();
    notifyViewModel(m_currentStorage.values());
}

void CarsModel::filter(const CStringData &key, int role) const
{
    (void)key;
    LinkList<Car> storage;
    switch (role) {
    case Brand: {
        LinkList<Car> cars = m_currentStorage.values();
        LinkList<Car>::iterator iter = cars.begin();
        while(iter != cars.end()) {
            iter = app_global::find_if(iter, cars.end(), [&](const Car &left) {
                return std::strncmp(left.brand(), key.data(), app_global::car::brandMaxLen) == 0;
            });
            if(iter != cars.end())
                storage.append(*iter++);
        }
        break;
    }
    case UndefinedRole:
        storage = m_currentStorage.values();
        break;
    default:
        return;
    }

    notifyViewModel(storage);
}

void CarsModel::setAvailable(const CStringData &key, bool available)
{
    if(!m_currentStorage.hasKey(key.data()))
        return;

    m_currentStorage[key.data()].setAvailable(available);

    notifyViewModel(m_currentStorage.values());
}

void CarsModel::setViewModel(CarsViewModel *model)
{
    m_viewModel = model;
    notifyViewModel(m_currentStorage.values());
}

void CarsModel::notifyViewModel(const LinkList<Car> &newStorage) const
{
    if(m_viewModel)
        m_viewModel->update(newStorage);
}
