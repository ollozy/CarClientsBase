#ifndef MAINWINDOW_H
#define MAINWINDOW_H

class AbstractItemModel;
class AbstractItemView;
class ListDelegate;
class ListView;
class ProxyModel;
class CarsModel;
class RentInfoModel;
class ClientsModel;

class MainWindow
{
    enum ConsoleCommand {
        Exit = 0,

        PreviousLine,
        NextLine,
        UnselectLine,

        Filter,
        ClearFilter,

        RemoveLine,
        ClearAll,

        ShowHint,
        HideHint,

        HideAllInfo,

        ShowAllCars,
        AppendCar,
        FindCar,

        ShowAllClients,
        AppendClient,
        FindClient,

        ShowRentInfo,
        IssueCar,
        ReturnCar,

        SendCarToRepair,
        ArrivalCarFromRepair,

        UserCommand = 100
    };

    enum ModelType {
        NoModel,
        CarModel,
        ClientModel,
        RentModel
    };

public:
    MainWindow();
    ~MainWindow();

    void open();
    void update();

private:
    void switchCommand(const int &command);
    void mainPanel();
    void hintPanel();
    void navigationPanel();

    void showView(ModelType type);

    void appendCar();
    void findCar();

    void appendClient();
    void findClient();

    void filter();
    void clearFilter();
    void removeRow();
    void clear();

    bool checkCarNumber(const char *key) const;
    bool checkClientLicense(const char *key) const;

    AbstractItemModel *modelByType(ModelType type);

private:
    int m_command;
    ModelType m_currentModel;

    bool m_exit;
    bool m_showHintPanel;
    bool m_userInputState;

    CarsModel *m_carModel;
    ClientsModel *m_clientsModel;
    RentInfoModel *m_rentInfoModel;

    ListView *m_list;
    ListDelegate *m_delegate;
    ProxyModel *m_proxy;

    AbstractItemView *m_lastView;
};

#endif // MAINWINDOW_H
