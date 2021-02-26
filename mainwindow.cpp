#include "mainwindow.h"

#include "./app_core/cstringdata.h"
#include "./app_core/linklist.h"

#include <limits>
#include <iomanip>
#include <iostream>

MainWindow::MainWindow()
    : m_command(-1)
    , m_exit(false)
    , m_showHint(true)
    , m_showNavigation(true)
    , m_showStaticInfo(true)
    , m_list(new ListView)
    , m_delegate(new ListDelegate)
    , m_carModel(new CarsModel)
    , m_lastView(nullptr)
{
    m_list->setDelegate(m_delegate);
    m_list->setModel(m_carModel);
    m_carModel->initHeader();
    m_delegate->setFieldWidth(app_global::numberOfLetters(m_carModel->headerData(0).data()));
    m_list->selectRow(-1);
}

MainWindow::~MainWindow()
{
    delete m_list;
    delete m_delegate;
    delete m_carModel;
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
    if(m_lastView) {
        m_lastView->update();
        std::cout << std::endl;
    }
    if(m_showHint)
        showHint();
    if(m_showNavigation)
        showNavigation();
    if(m_showStaticInfo)
        showStaticInfo();
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
        m_lastView = m_list;
        return false;
    case ShowAllClients:
        return false;
    case ShowRentInfo:
        return false;
    case InsertNewCar:
        appendCar();
        return false;
    case InsertNewClient:
        return false;
    case InsertRentInfo:
        return false;
    case EraseCar:
        eraseCar();
        return false;
    case EraseClient:
        return false;
    case EraseRentInfo:
        return false;
    case EnableNavigation:
        m_showNavigation = true;
        return false;
    case DisableNavigation:
        m_showNavigation = false;
        return false;
    case Exit:
        return true;
    case NextLine:
        m_list->selectNext();
        return false;
    case PreviousLine:
        m_list->selectPrevious();
        return false;
    case UnselectLine:
        m_list->clearSelection();
        return false;
    default:
        return false;
    }
}

void MainWindow::showStaticInfo()
{
    std::cout.setf(std::ios_base::left, std::ios_base::adjustfield);
    std::cout << std::setw(app_global::realStringSize("Показать комманды ", 61))
              << std::setfill('_') << "\rПоказать комманды " << ' ' << ShowHint << '\n';
    std::cout << std::setw(app_global::realStringSize("Скрыть комманды ", 60))
              << std::setfill('_') << "Скрыть комманды " << ' ' << HideHint << '\n';
    std::cout << std::setw(app_global::realStringSize("Показать на навигационную панель ", 60))
              << std::setfill('_') << "Показать на навигационную панель " << ' ' << EnableNavigation << '\n';
    std::cout << std::setw(app_global::realStringSize("Скрыть навигационную панель ", 60))
              << std::setfill('_') << "Скрыть навигационную панель " << ' ' << DisableNavigation << '\n';
    std::cout << std::setw(app_global::realStringSize("Выход ", 60))
              << std::setfill('_') <<  "Выход " << ' ' << Exit << '\n';
    std::cout.unsetf(std::ios_base::adjustfield);
    std::cout << std::endl;
    std::cout << "\ruser:~> ";
}

void MainWindow::showHint()
{
    std::cout.setf(std::ios_base::left, std::ios_base::adjustfield);
    std::cout << std::setw(app_global::realStringSize("Вывести на экран все зарегистрированные автомобили ", 61))
              << std::setfill('_') << "\rВывести на экран все зарегистрированные автомобили " << ' ' << ShowAllCars << '\n';
    std::cout << std::setw(app_global::realStringSize("Добавить новый автомобиль ", 60))
              << std::setfill('_') << "Добавить новый автомобиль " << ' ' << InsertNewCar << '\n';
    std::cout << std::setw(app_global::realStringSize("Удалить автомобиль ", 60))
              << std::setfill('_') << "Удалить автомобиль " << ' ' << EraseCar << '\n';
    std::cout << std::setw(app_global::realStringSize("Вывести на экран всех клиентов ", 60))
              << std::setfill('_') << "Вывести на экран всех клиентов " << ' ' << ShowAllClients << '\n';
    std::cout << std::setw(app_global::realStringSize("Добавить нового клиента ", 60))
              << std::setfill('_') << "Добавить нового клиента " << ' ' << InsertNewClient << '\n';
    std::cout << std::setw(app_global::realStringSize("Удалить клиента ", 60))
              << std::setfill('_') << "Удалить клиента " << ' ' << EraseClient << '\n';
    std::cout << std::setw(app_global::realStringSize("Вывести на экран данные об аренде ", 60))
              << std::setfill('_') << "Вывести на экран данные об аренде " << ' ' << ShowRentInfo << '\n';
    std::cout << std::setw(app_global::realStringSize("Добавить данные об аренде ", 60))
              << std::setfill('_') << "Добавить данные об аренде " << ' ' << InsertRentInfo << '\n';
    std::cout << std::setw(app_global::realStringSize("Удалить данные об аренде ", 60))
              << std::setfill('_') << "Удалить данные об аренде " << ' ' << EraseRentInfo << '\n';
    std::cout.unsetf(std::ios_base::adjustfield);
    std::cout << std::endl;
}

void MainWindow::showNavigation()
{
    std::cout.setf(std::ios_base::left, std::ios_base::adjustfield);
    std::cout << std::setw(app_global::realStringSize("Предыдущая строка ", 60))
              << std::setfill('_') << "Предыдущая строка " << ' ' << PreviousLine << '\n';
    std::cout << std::setw(app_global::realStringSize("Следующая строка ", 61))
              << std::setfill('_') << "\rСледующая строка " << ' ' << NextLine << '\n';
    std::cout << std::setw(app_global::realStringSize("Снять выделение ", 60))
              << std::setfill('_') << "Снять выделение " << ' ' << UnselectLine << '\n';
    std::cout.unsetf(std::ios_base::adjustfield);
    std::cout << std::endl;
}

void MainWindow::appendCar()
{
    bool hintStorage = m_showHint;
    bool navigationStorage = m_showNavigation;
    bool staticInfoStorage = m_showStaticInfo;

    m_showHint = false;
    m_showNavigation = false;
    m_showStaticInfo = false;

    m_lastView = m_list;
    update();

    char numb[app_global::car::numberMaxLen];
    char brand[app_global::car::brandMaxLen];
    char color[app_global::car::colorMaxLen];
    int year = 0;

    std::cout << std::endl;

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout.setf(std::ios_base::left, std::ios_base::adjustfield);
    std::cout << std::setw(app_global::realStringSize("Номер автомобиля: ", 30))
              << std::setfill('_') << "Номер автомобиля: " << " ";
    std::cin.getline(numb, app_global::car::numberMaxLen);
    std::cout << std::setw(app_global::realStringSize("Марка автомобиля: ", 30))
              << std::setfill('_') << "Марка автомобиля: " << " ";
    std::cin.getline(brand, app_global::car::brandMaxLen);
    std::cout << std::setw(app_global::realStringSize("Цвет автомобиля: ", 30))
              << std::setfill('_') << "Цвет автомобиля: " << " ";
    std::cin.getline(color, app_global::car::colorMaxLen);
    std::cout << std::setw(app_global::realStringSize("Год выпуска автомобиля: ", 30))
              << std::setfill('_') << "Год выпуска автомобиля: " << " ";
    std::cin >> year;
    while(!std::cin) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Введено некорректное значение. Повторите ввод (0 для выхода): ";
        std::cin >> year;
        if(year == 0)
            break;
    }
    std::cout.unsetf(std::ios_base::adjustfield);

    Car newCar(numb, brand, color, year);
    m_carModel->insertRow(newCar);

    m_showHint = hintStorage;
    m_showNavigation = navigationStorage;
    m_showStaticInfo = staticInfoStorage;
}

void MainWindow::eraseCar()
{
    if(!m_list->selectedItems().isEmpty()) {
        int rowForDel = m_list->selectedItems().begin()->row();
        m_carModel->removeRow(rowForDel - 1);
        int selectedRow = m_list->selectedItems().begin()->row();
        if(m_carModel->rowCount() == 0 || selectedRow > m_carModel->rowCount())
            m_list->clearSelection();
    }
}

void MainWindow::appendClient()
{

}

void MainWindow::eraseClient()
{

}

void MainWindow::appendRentInfo()
{

}

void MainWindow::eraseRentInfo()
{

}
