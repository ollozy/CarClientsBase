#include "mainwindow.h"

#include "./app_core/cstringdata.h"
#include "./app_core/linklist.h"

#include <limits>
#include <iomanip>
#include <iostream>

MainWindow::MainWindow()
    : m_command(-1)
    , m_currentModel(NoModel)
    , m_exit(false)
    , m_showHintPanel(true)
    , m_showNavigationPanel(false)
    , m_showMainPanel(true)
    , m_userInputState(false)
    , m_list(new ListView)
    , m_delegate(new ListDelegate)
    , m_carModel(new CarsModel)
    , m_proxy(new ProxyModel)
    , m_lastView(nullptr)
{
    m_list->setDelegate(m_delegate);
    m_list->setModel(m_proxy);
    m_carModel->initHeader();
    m_delegate->setFieldWidth(app_global::numberOfLetters(m_carModel->headerData(0).data()));
}

MainWindow::~MainWindow()
{
    delete m_list;
    delete m_delegate;
    delete m_carModel;
    delete m_proxy;
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
        switchCommand(m_command);
    }
}

void MainWindow::update()
{
    system("clear");
    if(m_lastView) {
        m_lastView->update();
        std::cout << std::endl;
    }
    if(m_userInputState)
        return;
    if(m_showHintPanel)
        hintPanel();
    if(m_showNavigationPanel)
        navigationPanel();
    if(m_showMainPanel)
        mainPanel();
}

void MainWindow::switchCommand(const int &command)
{
    switch (command) {
    case Exit:
        m_exit = true;
        break;

    case NextLine:
        m_list->selectNext();
        break;
    case PreviousLine:
        m_list->selectPrevious();
        break;
    case UnselectLine:
        m_list->clearSelection();
        break;
    case Filter:
        filter();
        break;
    case ClearFilter:
        clearFilter();
        break;

    case ShowHint:
        m_showHintPanel = true;
        break;
    case HideHint:
        m_showHintPanel = false;
        break;

    case HideAllInfo:
        hideAllView();
        break;

    case ShowAllCars:
        showView(CarModel);
        break;
    case RemoveCar:
        showView(CarModel);
        removeCar();
        break;
    case AppendCar:
        showView(CarModel);
        appendCar();
        break;
    case ClearCars:
        clearCar();
        break;
    case FindCar:
        findCar();
        break;

        //    case ShowAllClients:
        //        break;
        //    case ShowRentInfo:
        //        break;
        //    case InsertNewClient:
        //        break;
        //    case IssueCar:
        //        break;
        //    case EraseClient:
        //        break;
        //    case ReturnCar:
        //        break;
    default:
        break;
    }
}

void MainWindow::mainPanel()
{
    std::cout.setf(std::ios_base::left, std::ios_base::adjustfield);
    std::cout << std::setw(app_global::realStringSize("Показать комманды ", 61))
              << std::setfill('_') << "\rПоказать комманды " << ' ' << ShowHint << '\n';
    std::cout << std::setw(app_global::realStringSize("Скрыть комманды ", 60))
              << std::setfill('_') << "Скрыть комманды " << ' ' << HideHint << '\n';
    if(m_lastView != nullptr) {
        std::cout << std::setw(app_global::realStringSize("Скрыть таблицу ", 60))
                  << std::setfill('_') << "Скрыть таблицу " << ' ' << HideAllInfo << '\n';
    }
    std::cout << std::setw(app_global::realStringSize("Выход ", 60))
              << std::setfill('_') <<  "Выход " << ' ' << Exit << '\n';
    std::cout.unsetf(std::ios_base::adjustfield);
    std::cout << std::endl;
    std::cout << "\ruser:~> ";
}

void MainWindow::hintPanel()
{
    std::cout.setf(std::ios_base::left, std::ios_base::adjustfield);
    std::cout << std::setw(app_global::realStringSize("Показать все имеющиеся автомобили ", 61))
              << std::setfill('_') << "\rПоказать все имеющиеся автомобили " << ' ' << ShowAllCars << '\n';
    std::cout << std::setw(app_global::realStringSize("Добавить новый автомобиль ", 60))
              << std::setfill('_') << "Добавить новый автомобиль " << ' ' << AppendCar << '\n';
    std::cout << std::setw(app_global::realStringSize("Удалить сведения об автомобиле ", 60))
              << std::setfill('_') << "Удалить сведения об автомобиле " << ' ' << RemoveCar << '\n';
    std::cout << std::setw(app_global::realStringSize("Очистить данные об автомобилях ", 60))
              << std::setfill('_') << "Очистить данные об автомобилях " << ' ' << ClearCars << '\n';
    std::cout << std::setw(app_global::realStringSize("Найти автомобить по гос. номеру ", 60))
              << std::setfill('_') << "Найти автомобить по гос. номеру " << ' ' << FindCar << '\n';

    //    std::cout << std::setw(app_global::realStringSize("Вывести на экран всех клиентов ", 60))
    //              << std::setfill('_') << "Показать всех зарегистрированных клиентов " << ' ' << ShowAllClients << '\n';
    //    std::cout << std::setw(app_global::realStringSize("Добавить нового клиента ", 60))
    //              << std::setfill('_') << "Зарегистрировать нового клиента " << ' ' << InsertNewClient << '\n';
    //    std::cout << std::setw(app_global::realStringSize("Удалить клиента ", 60))
    //              << std::setfill('_') << "Снять клиента с обслуживания " << ' ' << EraseClient << '\n';

    //    std::cout << std::setw(app_global::realStringSize("Вывести на экран данные об аренде ", 60))
    //              << std::setfill('_') << "Вывести на экран данные об аренде " << ' ' << ShowRentInfo << '\n';
    //    std::cout << std::setw(app_global::realStringSize("Добавить данные об аренде ", 60))
    //              << std::setfill('_') << "Добавить данные об аренде " << ' ' << IssueCar << '\n';
    //    std::cout << std::setw(app_global::realStringSize("Удалить данные об аренде ", 60))
    //              << std::setfill('_') << "Удалить данные об аренде " << ' ' << ReturnCar << '\n';
    std::cout.unsetf(std::ios_base::adjustfield);
    std::cout << std::endl;
}

void MainWindow::navigationPanel()
{
    std::cout.setf(std::ios_base::left, std::ios_base::adjustfield);
    std::cout << std::setw(app_global::realStringSize("Предыдущая строка ", 60))
              << std::setfill('_') << "Предыдущая строка " << ' ' << PreviousLine << '\n';
    std::cout << std::setw(app_global::realStringSize("Следующая строка ", 61))
              << std::setfill('_') << "\rСледующая строка " << ' ' << NextLine << '\n';
    std::cout << std::setw(app_global::realStringSize("Снять выделение ", 60))
              << std::setfill('_') << "Снять выделение " << ' ' << UnselectLine << '\n';
    std::cout << std::setw(app_global::realStringSize("Фильтровать ", 60))
              << std::setfill('_') << "Фильтровать " << ' ' << Filter << '\n';
    std::cout << std::setw(app_global::realStringSize("Очистить фильтр ", 60))
              << std::setfill('_') << "Очистить фильтр " << ' ' << ClearFilter << '\n';
    std::cout.unsetf(std::ios_base::adjustfield);
    std::cout << std::endl;
}

void MainWindow::showView(ModelType type)
{
    m_currentModel = type;
    switch(type)  {
    case NoModel:
        m_lastView = nullptr;
        m_proxy->setModel(nullptr);
        m_showNavigationPanel = false;
        break;
    case CarModel:
        m_lastView = m_list;
        if(m_proxy->model() != m_carModel){
            m_proxy->setModel(m_carModel);
            m_proxy->setFilterColumn(2);
        }
        m_showNavigationPanel = true;
        break;
    case ClientModel:
        m_lastView = nullptr;
        m_proxy->setModel(nullptr);
        m_showNavigationPanel = false;
        break;
    case RentInfoModel:
        m_lastView = nullptr;
        m_proxy->setModel(nullptr);
        m_showNavigationPanel = false;
        break;
    default:
        m_lastView = nullptr;
        m_proxy->setModel(nullptr);
        m_showNavigationPanel = false;
        break;
    }
}

void MainWindow::hideAllView()
{
    m_lastView = nullptr;
    m_showNavigationPanel = false;
}

void MainWindow::appendCar()
{
    m_userInputState = true;

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
    std::cin.getline(numb, app_global::car::numberMaxLen, '\n');
    if(!(app_global::numberOfLetters(numb) > 0)) {
        std::cout << "\nНекорректный гос номер. Enter для продолжения\n";
        while(std::cin.peek() != '\n') std::cin.get();
        m_userInputState = false;
        return;
    }
    std::cout << std::setw(app_global::realStringSize("Марка автомобиля: ", 30))
              << std::setfill('_') << "Марка автомобиля: " << " ";
    std::cin.getline(brand, app_global::car::brandMaxLen, '\n');
    std::cout << std::setw(app_global::realStringSize("Цвет автомобиля: ", 30))
              << std::setfill('_') << "Цвет автомобиля: " << " ";
    std::cin.getline(color, app_global::car::colorMaxLen, '\n');
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

    m_userInputState = false;
}

void MainWindow::removeCar()
{
    if(!m_list->selectedItems().isEmpty()) {
        int rowForDel = m_list->selectedItems().begin()->row();
        m_carModel->removeRow(rowForDel - 1);
        int selectedRow = m_list->selectedItems().begin()->row();
        if(selectedRow > m_carModel->rowCount() - 1)
            m_list->clearSelection();
    }
}

void MainWindow::clearCar()
{
    m_proxy->clearModel();
    m_list->clearSelection();
}

void MainWindow::findCar()
{
    char numb[app_global::car::numberMaxLen];
    std::cout << "Введите гос. номер автомобиля для поиска: ";
    std::cin.getline(numb, app_global::car::numberMaxLen, '\n');
    if(!(app_global::numberOfLetters(numb) > 0)) {
        std::cout << "\nНекорректный гос номер. Enter для продолжения\n";
        while(std::cin.peek() != '\n') std::cin.get();
        m_userInputState = false;
        return;
    }


}

void MainWindow::filter()
{
    char keyWord[100] = "\0";

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Введите слово для фильтра: ";
    std::cin.getline(keyWord, 100);

    m_proxy->setFilter(keyWord);
}

void MainWindow::clearFilter()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    m_proxy->setFilter("\0");
}
