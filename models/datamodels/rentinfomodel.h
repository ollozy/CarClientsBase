#ifndef RENTINFOMODEL_H
#define RENTINFOMODEL_H

#include "../../items.h"
#include "../../global.h"

#include "../../app_core/hash.h"
#include "../../app_core/cstringdata.h"

class RentInfoViewModel;

class RentInfoModel
{
public:
    enum RentInfoRoles {
        UndefinedRole = -1,
        CarRole = 1,
        ClientRole,
        IssueDateRole,
        ReturnDateRole
    };

    RentInfoModel();
    ~RentInfoModel();

    void setData(const RentInfo &data);

    LinkList<RentInfo> getData(const CStringData &key, int keyRole) const;

    bool hasData(const CStringData &key, int keyRole) const;

    void removeData(const CStringData &carKey);

    void clearData();

    void filter(const CStringData &key, int role);

    void setViewModel(RentInfoViewModel *model);

private:
    void notifyViewModel(const LinkList<RentInfo> &newStorage);

private:
    LinkList<RentInfo> m_currentStorage;
    RentInfoViewModel *m_viewModel;
};

#endif // RENTINFOMODEL_H
