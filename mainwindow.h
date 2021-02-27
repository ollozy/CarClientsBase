#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "./views/listview.h"

#include "./models/carsmodel.h"
#include "./models/proxymodel.h"

#include "./delegates/listdelegate.h"

class MainWindow
{
    enum ConsoleCommand {
        Exit = 0,

        PreviousLine,
        NextLine,
        UnselectLine,
        Filter,
        ClearFilter,

        ShowHint,
        HideHint,

        HideAllInfo,

        ShowAllCars,
        AppendCar,
        RemoveCar,
        ClearCars,
        FindCar,

        ShowAllClients,
        InsertNewClient,
        EraseClient,
        ClearClients,
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
        RentInfoModel
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
    void hideAllView();

    void appendCar();
    void removeCar();
    void clearCar();
    void findCar();

    void filter();
    void clearFilter();

private:
    int m_command;
    ModelType m_currentModel;

    bool m_exit;
    bool m_showHintPanel;
    bool m_showNavigationPanel;
    bool m_showMainPanel;
    bool m_userInputState;

    ListView *m_list;
    ListDelegate *m_delegate;
    CarsModel *m_carModel;

    ProxyModel *m_proxy;
    AbstractItemView *m_lastView;
};

#endif // MAINWINDOW_H
