#include "mainwindow.h"

#include "./app_core/cstringdata.h"
#include "./app_core/linklist.h"

#include "./views/listview.h"

#include "./delegates/listdelegate.h"

#include "./models/carsmodel.h"
#include "./models/clientsmodel.h"
#include "./models/rentinfomodel.h"
#include "./models/proxymodel.h"

#include <limits>
#include <iomanip>
#include <iostream>

MainWindow::MainWindow()
    : m_command(-1)
    , m_currentModel(NoModel)
    , m_exit(false)
    , m_showHintPanel(true)
    , m_userInputState(false)
    , m_carModel(new CarsModel)
    , m_clientsModel(new ClientsModel)
    , m_rentInfoModel(new RentInfoModel)
    , m_list(new ListView)
    , m_delegate(new ListDelegate)
    , m_proxy(new ProxyModel)
    , m_lastView(nullptr)
{
    m_list->setDelegate(m_delegate);
    m_list->setModel(m_proxy);
    m_carModel->initHeader();
    m_clientsModel->initHeader();
    m_rentInfoModel->initHeader();
}

MainWindow::~MainWindow()
{
    delete m_list;
    delete m_delegate;
    delete m_proxy;
    delete m_carModel;
    delete m_clientsModel;
    delete m_carModel;
}

void MainWindow::open()
{
    setlocale(LC_ALL, "");
    while (!m_exit) {
        update();

        (std::cin >> m_command).get();
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
    app_global::clearConsole();
    if(m_lastView) {
        m_lastView->update();
        std::cout << std::endl;
    }
    if(!m_userInputState) {
        if(m_showHintPanel)
            hintPanel();
        navigationPanel();
        mainPanel();
    }
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
    case RemoveLine:
        removeRow();
        break;
    case ClearAll:
        clear();
        break;

    case ShowHint:
        m_showHintPanel = true;
        break;
    case HideHint:
        m_showHintPanel = false;
        break;

    case HideAllInfo:
        showView(NoModel);
        break;

    case ShowAllCars:
        showView(CarModel);
        break;
    case AppendCar:
        showView(CarModel);
        appendCar();
        break;
    case FindCar:
        showView(CarModel);
        findCar();
        break;
    case RepairCar:
        showView(CarModel);
        setCarAvailable(false);
        break;
    case ReturnRepairingCar:
        showView(CarModel);
        setCarAvailable(true);
        break;

    case ShowAllClients:
        showView(ClientModel);
        break;
    case AppendClient:
        showView(ClientModel);
        appendClient();
        break;
    case FindClient:
        showView(ClientModel);
        findClient();
        break;

    case ShowRentInfo:
        showView(RentModel);
        break;
    case IssueCar:
        showView(RentModel);
        issueCar();
        break;
    case ReturnCar:
        showView(RentModel);
        returnCar();
        break;
    default:
        break;
    }
}

void MainWindow::mainPanel()
{
    if(!m_showHintPanel)
        showLine("\rПоказать комманды ", 61, ShowHint);
    else
        showLine("Скрыть комманды ", 60, HideHint);
    if(m_lastView != nullptr)
        showLine("Скрыть таблицу ", 60, HideAllInfo);

    showLine("Выход ", 60, Exit);

    std::cout << std::endl;
    std::cout << "\ruser:~> ";
}

void MainWindow::hintPanel()
{
    showLine("\rПоказать все имеющиеся автомобили ", 61, ShowAllCars);
    showLine("Добавить новый автомобиль ", 60, AppendCar);

    if(m_currentModel == CarModel) {
        showLine("Удалить сведения об автомобиле ", 60, RemoveLine);
        showLine("Очистить данные об автомобилях ", 60, ClearAll);
        showLine("Найти автомобить по гос. номеру ", 60, FindCar);
        showLine("Отправить автомобиль в ремонт ", 60, RepairCar);
        showLine("Вернуть автомобиль из ремента ", 60, ReturnRepairingCar);
    }
    std::cout << std::endl;

    showLine("Показать всех зарегистрированных клиентов ", 60, ShowAllClients);
    showLine("Зарегистрировать нового клиента ", 60, AppendClient);

    if(m_currentModel == ClientModel) {
        showLine("Снять клиента с обслуживания ", 60, RemoveLine);
        showLine("Очистить данные о клиентах ", 60, ClearAll);
        showLine("Найти клиента по номеру водительского удостоверения ", 60, FindCar);
    }
    std::cout << std::endl;

    showLine("Показать информацию об аренде ", 60, ShowRentInfo);
    showLine("Выдать автомобить в аренду ", 60, IssueCar);

    if(m_currentModel == RentModel) {
        showLine("Вернуть автомобить из аренты ", 60, ReturnCar);
    }


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
    if(m_currentModel == NoModel)
        return;

    showLine("\rПредыдущая строка ", 61, PreviousLine);
    showLine("Следующая строка ", 60, NextLine);
    showLine("Снять выделение ", 60, UnselectLine);
    showLine("Фильтровать ", 60, Filter);
    showLine("Очистить фильтр ", 60, ClearFilter);

    std::cout << std::endl;
}

void MainWindow::showView(ModelType type)
{
    m_currentModel = type;
    AbstractItemModel *model = modelByType(type);
    if(!model) {
        m_lastView = nullptr;
        m_proxy->setModel(nullptr);
        return;
    }

    m_lastView = m_list;
    if(m_proxy->model() != model){
        m_delegate->setFieldWidth(app_global::numberOfLetters(model->headerData(0).data()));
        m_proxy->setModel(model);
    }
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

    getUserInput("Номер автомобиля: ", 30, numb, app_global::car::numberMaxLen);
    while (!checkCarNumber(numb)) {
        std::cout << "Неверный формат. Повторите ввод (Enter для выхода): \n";
        getUserInput("Номер автомобиля: ", 30, numb, app_global::car::numberMaxLen);
        if(std::strlen(numb) == 0)
            return;
    }
    getUserInput("Марка автомобиля: ", 30, brand, app_global::car::brandMaxLen);
    getUserInput("Цвет автомобиля: ", 30, color, app_global::car::colorMaxLen);
    getUserInput("Год выпуска автомобиля: ", 30, year);

    Car newCar(numb, brand, color, year);
    m_carModel->insertRow(newCar);

    m_userInputState = false;
}

void MainWindow::findCar()
{
    char key[app_global::car::numberMaxLen] = "\0";
    std::cout << "Введите номер автомобиля для поиска\n";
    getUserInput("Номер автомобиля: ", 60, key, app_global::car::numberMaxLen);
    if(!checkCarNumber(key)) {
        std::cout << "Неверный формат. Повторите ввод (Enter для выхода): \n";
        getUserInput("Номер автомобиля: ", 60, key, app_global::car::numberMaxLen);
        if(std::strlen(key) == 0)
            return;
    }
    std::cout << std::endl;

    Car foundCar = m_carModel->dataByKey(key);

    if(!checkCarNumber(foundCar.number()))
        std::cout << "Автомобиль с таким номером не зарегистрирован\n";
    else {
        std::cout << "Найден автомобиль:\n";
        showLine("Гос. номер: ", 60, foundCar.number());
        showLine("Марка: ", 60, foundCar.brand());
        showLine("Цвет: ", 60, foundCar.color());
        showLine("Год выпуска: ", 60, foundCar.year());
        std::cout << std::endl;

        if(foundCar.available()) {
            RentInfo rentInfo; //= m_rentInfoModel->mapClientByCar(foundCar.number());
            Client foundClient = m_clientsModel->dataByKey(rentInfo.clientData());
            std::cout << "Автомобиль выдан клиенту\n";
            showLine("Номер водительского удостоверения: ", 60, foundClient.license());
            showLine("ФИО: ", 60, foundClient.name());
        }
        else
            std::cout << "Автомобиль с таким гос. номером доступен для аренды\n";
    }
    std::cout << "(Enter для выхода)";
    std::cout << std::endl;
    std::cin.get();
}

void MainWindow::appendClient()
{
    m_userInputState = true;

    m_lastView = m_list;
    update();

    char license[app_global::client::licenseLen];
    char name[app_global::client::nameMaxLen];
    char passport[app_global::client::passportMaxLen];
    char address[app_global::client::addressMaxLen];

    std::cout << std::endl;

    getUserInput("Номер удостоверения: ", 30, license, app_global::client::licenseLen);
    while(!checkClientLicense(license)) {
        std::cout << "Неверный формат. Повторите ввод (Enter для выхода): \n";
        getUserInput("Номер водительского удостоверения: ", 30, license, app_global::client::licenseLen);
        if(std::strlen(license) == 0)
            return;
    }
    getUserInput("ФИО клиента: ", 30, name, app_global::client::nameMaxLen);
    getUserInput("Паспортные данные: ", 30, passport, app_global::client::passportMaxLen);
    getUserInput("Адрес: ", 30, address, app_global::client::addressMaxLen);

    Client newClient(license, name, passport, address);
    m_clientsModel->insertRow(newClient);

    m_userInputState = false;
}

void MainWindow::findClient()
{
    char key[app_global::car::numberMaxLen] = "\0";
    std::cout << "Введите номер водительского удостоверения для поиска\n";
    getUserInput("Номер водительского удостоверения: ", 60, key, app_global::client::licenseLen);
    if(!checkCarNumber(key)) {
        std::cout << "Неверный формат. Повторите ввод (Enter для выхода): \n";
        getUserInput("Номер водительского удостоверения: ", 60, key, app_global::client::licenseLen);
        if(std::strlen(key) == 0)
            return;
    }
    std::cout << std::endl;

    Client foundClient = m_clientsModel->dataByKey(key);

    if(!checkCarNumber(foundClient.license()))
        std::cout << "Клиент с таким удостоверения не зарегистрирован\n";
    else {
        std::cout << "Найден клиент:\n";
        showLine("Номер водительского удостоверения: ", 60, foundClient.license());
        showLine("ФИО клиента: ", 30, foundClient.name());
        showLine("Паспортные данные: ", 30, foundClient.passport());
        showLine("Адрес: ", 30, foundClient.address());
        std::cout << std::endl;

        RentInfo info;
        Car rentedCar = m_carModel->dataByKey(info.carData());

        if(checkCarNumber(rentedCar.number()) && !rentedCar.available()) {
            std::cout << "Клиенту выдан автомобиль\n";
            showLine("Гос. номер: ", 60, rentedCar.number());
        }
        else
            std::cout << "Клиенту не было выдано в аренду ни одного автомобиля\n";
    }
    std::cout << "(Enter для выхода)";
    std::cout << std::endl;
    std::cin.get();
}

void MainWindow::filter()
{
    char keyWord[100] = "\0";


    std::cout << "Введите слово для фильтра: ";
    std::cin.getline(keyWord, 100);

    m_proxy->setFilter(keyWord, 2);
}

void MainWindow::clearFilter()
{
    m_proxy->clearFilter();
}

void MainWindow::removeRow()
{
    if(!m_proxy->model()
            || m_list->selectedItems().isEmpty())
        return;

    showView(m_currentModel);

    int rowForDel = m_list->selectedItems().begin()->row();
    m_proxy->removeRow(rowForDel);
    int selectedRow = m_list->selectedItems().begin()->row();
    if(selectedRow > m_proxy->rowCount())
        m_list->clearSelection();
}

void MainWindow::clear()
{
    if(!m_proxy->model())
        return;

    showView(m_currentModel);

    m_proxy->clearModel();
    m_list->clearSelection();
}

void MainWindow::setCarAvailable(bool available)
{
    if(m_proxy->model() != m_carModel || !m_lastView)
        return;

    ModelIndex selectedIndex = m_lastView->selectedItems().begin();
    CStringData selectedNum = m_proxy->data(ModelIndex(selectedIndex.row(), 1));
    if(selectedNum.isEmpty())
        return;

    Car selectedCar = m_carModel->dataByKey(selectedNum.data());
    if(selectedCar.available() == available)
        return;

    selectedCar.setAvailable(available);
    m_carModel->insertRow(selectedCar);
}

void MainWindow::issueCar()
{

}

void MainWindow::returnCar()
{

}

bool MainWindow::checkCarNumber(const char *key) const
{
    if(app_global::numberOfLetters(key) != 9)
        return false;

    const char *keyPtr = key;
    for(int i = 0; i < 9; ++i) {
        switch (i) {
        case 0:
        case 4:
        case 5: {
            char simbol[2] = "\0";
            simbol[0] = *keyPtr++;
            simbol[1] = *keyPtr++;
            if((simbol[0] == "А"[0] && simbol[1] == "А"[1])
                    || (simbol[0] == "В"[0] && simbol[1] == "В"[1])
                    || (simbol[0] == "Е"[0] && simbol[1] == "Е"[1])
                    || (simbol[0] == "К"[0] && simbol[1] == "К"[1])
                    || (simbol[0] == "М"[0] && simbol[1] == "М"[1])
                    || (simbol[0] == "Н"[0] && simbol[1] == "Н"[1])
                    || (simbol[0] == "О"[0] && simbol[1] == "О"[1])
                    || (simbol[0] == "Р"[0] && simbol[1] == "Р"[1])
                    || (simbol[0] == "С"[0] && simbol[1] == "С"[1])
                    || (simbol[0] == "Т"[0] && simbol[1] == "Т"[1])
                    || (simbol[0] == "У"[0] && simbol[1] == "У"[1])
                    || (simbol[0] == "Х"[0] && simbol[1] == "Х"[1]))
                break;
            return false;
        }
        case 1:
        case 2:
        case 3:
        case 7:
        case 8: {
            int simbolCode = static_cast<int>(*keyPtr++);
            if(simbolCode < 48 || simbolCode > 57)
                return false;
            break;
        }
        case 6:
            if(*keyPtr++ != '-')
                return false;
            break;
        default:
            std::cout << "wrong char number\n";
            return false;
        }
    }
    return true;
}

bool MainWindow::checkClientLicense(const char *key) const
{
    if(app_global::numberOfLetters(key) != 9)
        return false;

    const char *keyPtr = key;
    for(int i = 0; i < 9; ++i) {
        switch (i) {
        case 3:
        case 4:{
            char simbol[2] = "\0";
            simbol[0] = *keyPtr++;
            simbol[1] = *keyPtr++;
            if((simbol[0] == "А"[0] && simbol[1] == "А"[1])
                    || (simbol[0] == "В"[0] && simbol[1] == "В"[1])
                    || (simbol[0] == "Е"[0] && simbol[1] == "Е"[1])
                    || (simbol[0] == "К"[0] && simbol[1] == "К"[1])
                    || (simbol[0] == "М"[0] && simbol[1] == "М"[1])
                    || (simbol[0] == "Н"[0] && simbol[1] == "Н"[1])
                    || (simbol[0] == "О"[0] && simbol[1] == "О"[1])
                    || (simbol[0] == "Р"[0] && simbol[1] == "Р"[1])
                    || (simbol[0] == "С"[0] && simbol[1] == "С"[1])
                    || (simbol[0] == "Т"[0] && simbol[1] == "Т"[1])
                    || (simbol[0] == "У"[0] && simbol[1] == "У"[1])
                    || (simbol[0] == "Х"[0] && simbol[1] == "Х"[1]))
                break;
            return false;
        }
        case 0:
        case 1:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:{
            int simbolCode = static_cast<int>(*keyPtr++);
            if(simbolCode < 48 || simbolCode > 57)
                return false;
        }
        case 2:
        case 5:
            if(*keyPtr++ != ' ')
                return false;
        default:
            std::cout << "wrong char number\n";
            return false;
        }
    }
    return true;
}

void MainWindow::getUserInput(const char *title, int fieldWidth, int &storage)
{
    std::cout.setf(std::ios_base::left, std::ios_base::adjustfield);
    std::cout << std::setw(app_global::realFilledStringSize(title, fieldWidth))
              << std::setfill('_') << title << " ";
    std::cin >> storage;
    while(!std::cin) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Введено некорректное значение. Повторите ввод (0 для выхода): ";
        std::cin >> storage;
        if(storage == 0)
            break;
    }
}

void MainWindow::getUserInput(const char *title, int fieldWidth, char *storage, int storageLen)
{
    std::cout.setf(std::ios_base::left, std::ios_base::adjustfield);
    std::cout << std::setw(app_global::realFilledStringSize(title, fieldWidth))
              << std::setfill('_') << title << " ";
    std::cin.getline(storage, storageLen, '\n');
    if(!std::cin){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cout.unsetf(std::ios_base::adjustfield);
}

void MainWindow::showLine(const char *title, int fieldWidth, const char *data)
{
    std::cout.setf(std::ios_base::left, std::ios_base::adjustfield);
    std::cout << std::setw(app_global::realFilledStringSize(title, fieldWidth))
              << std::setfill('_') << title << ' ' << data << '\n';
    std::cout.unsetf(std::ios_base::adjustfield);
}

void MainWindow::showLine(const char *title, int fieldWidth, int data)
{
    std::cout.setf(std::ios_base::left, std::ios_base::adjustfield);
    std::cout << std::setw(app_global::realFilledStringSize(title, fieldWidth))
              << std::setfill('_') << title << ' ' << data << '\n';
    std::cout.unsetf(std::ios_base::adjustfield);
}

AbstractItemModel *MainWindow::modelByType(ModelType type)
{
    switch (type) {
    case NoModel:
        return nullptr;
    case CarModel:
        return m_carModel;
    case ClientModel:
        return m_clientsModel;
    case RentModel:
        return m_rentInfoModel;
        break;
    default:
        return nullptr;
    }
}
