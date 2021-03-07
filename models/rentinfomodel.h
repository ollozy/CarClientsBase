#ifndef RENTINFOMODEL_H
#define RENTINFOMODEL_H

#include "abstractitemmodel.h"

#include "../app_core/linklist.h"
#include "../items.h"

class RentInfoModel : public AbstractItemModel
{
public:
    RentInfoModel();
    ~RentInfoModel();

    virtual void initHeader() override;

    virtual CStringData data(const ModelIndex &index) const override;
    virtual void setData(const CStringData &data, const ModelIndex &index) override;
    virtual void clearModel() override;
    virtual int columnCount() const override;
    virtual int rowCount() const override;
    virtual void removeRow(int row) override;

    void insertRow(const RentInfo &info);

    RentInfo mapClient(const Client &client);
    RentInfo mapCar(const Car &car);

private:
    void sort();
    int find(const char *key, int keyLen, int col);

private:
    LinkList<RentInfo> m_data;
};

#endif // RENTINFOMODEL_H
