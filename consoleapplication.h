#ifndef COREAPPLICATION_H
#define COREAPPLICATION_H

class AbstractItemModel;
class CarsViewModel;
class ClientsViewModel;
class RentInfoViewModel;

class CarsModel;
class ClientsModel;
class RentInfoModel;

class ListView;

class ListDelegate;

class ConsoleApplication
{
    enum CurrentModelType {
        NoModel,
        CarsModelType,
        ClientsModelType,
        RentInfoModelType
    };
    enum UserCommand {
        Exit = 0,

        SelectNext,
        SelectPrevious,
        Unselect,

        ShowHint,
        HideHint,
        HideTables,

        ShowAllCars,
        AppendCar,
        RemoveCar,
        ClearCars,
        FilterCar,
        FindCar,
        SendToRepair,
        ReturnFromRepair,

        ShowAllClients,
        AppendClient,
        RemoveClient,
        ClearClients,
        FilterClients,
        FindClient,

        ShowRentInfo,
        IssueCar,
        ReturnCar,

        ClearAllFilters
    };

public:
    ConsoleApplication();
    ~ConsoleApplication();

    void load(const char *carFile, const char *clientFile, const char *rentFile);
    void exec();

private:
    void switchCommand(int command);

    void showHintPanel();
    void showMainPanel();
    void showNavigationPanel();

    void showModel(CurrentModelType type);

    void appendCar();
    void appendClient();

    bool removeCar();
    bool removeClient();

    void findCar();
    void findClient();

    void filterCar();
    void filterClient();

    void clearCars();
    void clearClients();

    void setCarAvailable(bool available);

    void issueCar();
    void returnCar();

    void clearFilters();

private:
    void update();

    bool checkClientLicense(const char *key);
    bool checkCarNumber(const char *key);

    bool getUserInput(const char *title, int titleMaxLen, char *storage, int maxStoreLen);
    bool getUserInput(const char *title, int titleMaxLen, int &storage);

    void showUserOutput(const char *title, int titleMaxLen, const char *data);
    void showUserOutput(const char *title, int titleMaxLen, int data);

    void showEscapeMsg(const char *msg);

    bool carIsRented(const char *number);
    bool clientHasCar(const char *number);

    AbstractItemModel *modelByType(CurrentModelType type);

private:
    CarsModel *m_carsModel;
    ClientsModel *m_clientsModel;
    RentInfoModel *m_rentInfoModel;

    CarsViewModel *m_carsViewModel;
    ClientsViewModel *m_clientsViewModel;
    RentInfoViewModel *m_rentInfoViewModel;

    ListView *m_listView;
    ListDelegate *m_listDelegate;

    CurrentModelType m_currentModelType;
    bool m_userInputState;
    bool m_showHintPanel;
    bool m_exit;
};

#endif // COREAPPLICATION_H
