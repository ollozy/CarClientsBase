#include "mainwindow.h"

#include "./app_core/cstringdata.h"

#include <limits>
#include <iomanip>
#include <iostream>

MainWindow::MainWindow()
    : m_command(-1)
    , m_exit(false)
    , m_showHint(true)
    , m_list(new ListView)
    , m_delegate(new ListDelegate)
    , m_carModel(new CarsModel)
{
    m_list->setDelegate(m_delegate);
    m_list->setModel(m_carModel);
    m_carModel->initHeader();
    m_delegate->setFieldWidth(app_global::numberOfLetters(m_carModel->headerData(0).data()));
    m_list->selectRow(-1);
}

MainWindow::~MainWindow()
{

}

void MainWindow::open()
{
    setlocale(LC_ALL, "");
    while (!m_exit) {
        update();

        std::cin >> m_command;
        if(!std::cin) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        m_exit = switchCommand(m_command);
    }
}

void MainWindow::update()
{
    system("clear");
    m_list->update();
    if(m_showHint)
        showHint();
    std::cout << "\ruser:~> ";
}

bool MainWindow::switchCommand(const int &command)
{
    switch (command) {
    case ShowHint:
        m_showHint = true;
        return false;
    case HideHint:
        m_showHint = false;
        return false;
    case ShowAllCars:
        return false;
    case ShowAllClients:
        return false;
    case ShowRentInfo:
        return false;
    case InsertNewCar:
        return false;
    case InsertNewClient:
        return false;
    case InsertRentInfo:
        return false;
    case Exit:
        return true;
    default:
        return false;
    }
}

void MainWindow::showHint()
{
    std::cout.setf(std::ios_base::left);
    std::cout << std::setw(50) << std::setfill('_') << "Show hint " << ' ' << ShowHint << '\n';
    std::cout << std::setw(50) << std::setfill('_') << "Hide hint " << ' ' << HideHint << '\n';
    std::cout << std::setw(50) << std::setfill('_') << "Show all cars " << ' ' << ShowAllCars << '\n';
    std::cout << std::setw(50) << std::setfill('_') << "Show all clients " << ' ' << ShowAllClients << '\n';
    std::cout << std::setw(50) << std::setfill('_') << "Show rent info " << ' ' << ShowRentInfo << '\n';
    std::cout << std::setw(50) << std::setfill('_') << "Insert new car " << ' ' << InsertNewCar << '\n';
    std::cout << std::setw(50) << std::setfill('_') << "Insert new client " << ' ' << InsertNewClient << '\n';
    std::cout << std::setw(50) << std::setfill('_') << "Insert rent info " << ' ' << InsertRentInfo << '\n';
    std::cout << std::setw(50) << std::setfill('_') <<  "Exit " << ' ' << Exit << '\n';
    std::cout << std::endl;
}
