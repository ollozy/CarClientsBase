#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "./views/listview.h"
#include "./models/carsmodel.h"
#include "./delegates/listdelegate.h"

class MainWindow
{
    enum consoleCommands {
        Exit = 0,

        PreviousLine,
        NextLine,
        UnselectLine,

        ShowHint,
        HideHint,
        EnableNavigation,
        DisableNavigation,

        ShowAllCars,
        InsertNewCar,
        EraseCar,

        ShowAllClients,
        InsertNewClient,
        EraseClient,

        ShowRentInfo,
        InsertRentInfo,
        EraseRentInfo,

        UserCommand = 100
    };

public:
    MainWindow();
    ~MainWindow();

    void open();
    void update();

private:
    bool switchCommand(const int &command);
    void showStaticInfo();
    void showHint();
    void showNavigation();

    void appendCar();
    void eraseCar();

    void appendClient();
    void eraseClient();

    void appendRentInfo();
    void eraseRentInfo();

private:
    int m_command;

    bool m_exit;
    bool m_showHint;
    bool m_showNavigation;
    bool m_showStaticInfo;

    ListView *m_list;
    ListDelegate *m_delegate;
    CarsModel *m_carModel;

    AbstractItemView *m_lastView;
};

#endif // MAINWINDOW_H
