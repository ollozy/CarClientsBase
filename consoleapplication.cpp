#include "consoleapplication.h"

#include "models/viewmodels/abstractitemmodel.h"
#include "models/viewmodels/clientsviewmodel.h"
#include "models/viewmodels/carsviewmodel.h"
#include "models/viewmodels/rentinfoviewmodel.h"

#include "models/datamodels/carsmodel.h"
#include "models/datamodels/clientsmodel.h"
#include "models/datamodels/rentinfomodel.h"

#include "views/listview.h"

#include "delegates/listdelegate.h"

#include <limits>
#include <iomanip>
#include <iostream>
#include <fstream>

ConsoleApplication::ConsoleApplication()
    : m_carsModel(new CarsModel)
    , m_clientsModel(new ClientsModel)
    , m_rentInfoModel(new RentInfoModel)
    , m_carsViewModel(new CarsViewModel)
    , m_clientsViewModel(new ClientsViewModel)
    , m_rentInfoViewModel(new RentInfoViewModel)
    , m_listView(new ListView)
    , m_listDelegate(new ListDelegate)
    , m_currentModelType(NoModel)
    , m_userInputState(false)
    , m_showHintPanel(true)
    , m_exit(false)
{
    m_listView->setDelegate(m_listDelegate);

    m_carsViewModel->initHeader();
    m_clientsViewModel->initHeader();
    m_rentInfoViewModel->initHeader();

    m_clientsModel->setViewModel(m_clientsViewModel);
    m_carsModel->setViewModel(m_carsViewModel);
    m_rentInfoModel->setViewModel(m_rentInfoViewModel);
}

ConsoleApplication::~ConsoleApplication()
{
    delete m_listDelegate;
    delete m_listView;
    delete m_rentInfoViewModel;
    delete m_clientsViewModel;
    delete m_carsViewModel;
    delete m_rentInfoModel;
    delete m_clientsModel;
    delete m_carsModel;
}

void ConsoleApplication::load(const char *carFile, const char *clientFile, const char *rentFile)
{
    std::fstream fs;
    fs.open(carFile, std::ios_base::in);
    if(fs.is_open()) {
        char num[app_global::car::numberMaxLen];
        char brand[app_global::car::brandMaxLen];
        char color[app_global::car::colorMaxLen];
        int year = -1;
        bool available = false;
        while (!fs.eof()) {
            fs.getline(num, app_global::car::numberMaxLen, '|');
            fs.getline(brand, app_global::car::brandMaxLen, '|');
            fs.getline(color, app_global::car::colorMaxLen, '|');
            fs >> year >> available;
            fs.ignore(1, '\n');
            if(!checkCarNumber(num))
                continue;
            Car newCar(num, brand, color, year, available);
            m_carsModel->setData(newCar);
        }
    }
    fs.close();
    fs.clear();

    fs.open(clientFile, std::ios_base::in);
    if(fs.is_open()) {
        char license[app_global::client::licenseMaxLen];
        char name[app_global::client::nameMaxLen];
        char passport[app_global::client::passportMaxLen];
        char address[app_global::client::addressMaxLen];
        while (!fs.eof()) {
            fs.getline(license, app_global::client::licenseMaxLen, '|');
            fs.getline(name, app_global::client::nameMaxLen, '|');
            fs.getline(passport, app_global::client::passportMaxLen, '|');
            fs.getline(address, app_global::client::addressMaxLen, '\n');
            if(!checkClientLicense(license))
                continue;
            Client newClient(license, name, passport, address);
            m_clientsModel->setData(newClient);
        }
    }
    fs.close();
    fs.clear();

    fs.open(rentFile, std::ios_base::in);
    if(fs.is_open()) {
        char carData[app_global::car::numberMaxLen];
        char clientData[app_global::client::licenseMaxLen];
        char issueData[app_global::dateLen];
        char returnDate[app_global::dateLen];
        while (!fs.eof()) {
            fs.getline(carData, app_global::car::numberMaxLen, '|');
            fs.getline(clientData, app_global::client::licenseMaxLen, '|');
            fs.getline(issueData, app_global::dateLen, '|');
            fs.getline(returnDate, app_global::dateLen, '\n');
            if(!checkClientLicense(clientData) || !checkCarNumber(carData))
                continue;
            RentInfo rent(clientData, carData, issueData, returnDate);
            m_rentInfoModel->setData(rent);
        }
    }
    fs.close();
    fs.clear();
}

void ConsoleApplication::exec()
{
    setlocale(LC_ALL, "");
    while (!m_exit) {
        update();
        int command = -1;
        (std::cin >> command).get();
        if(!std::cin) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        switchCommand(command);
    }
}

void ConsoleApplication::switchCommand(int command)
{
    switch(command) {
    case Exit:
        m_exit = true;
        break;

    case SelectNext:
        m_listView->selectNext();
        break;
    case SelectPrevious:
        m_listView->selectPrevious();
        break;
    case Unselect:
        m_listView->clearSelection();
        break;

    case ShowHint:
        m_showHintPanel = true;
        break;
    case HideHint:
        m_showHintPanel = false;
        break;
    case HideTables:
        showModel(NoModel);
        break;

    case ShowAllCars:
        showModel(CarsModelType);
        break;
    case AppendCar:
        showModel(CarsModelType);
        appendCar();
        break;
    case RemoveCar:
        showModel(CarsModelType);
        removeCar();
        break;
    case ClearCars:
        showModel(CarsModelType);
        clearCars();
        break;
    case FilterCar:
        showModel(CarsModelType);
        filterCar();
        break;
    case FindCar:
        showModel(CarsModelType);
        findCar();
        break;
    case SendToRepair:
        showModel(CarsModelType);
        setCarAvailable(false);
        break;
    case ReturnFromRepair:
        showModel(CarsModelType);
        setCarAvailable(true);
        break;

    case ShowAllClients:
        showModel(ClientsModelType);
        break;
    case AppendClient:
        showModel(ClientsModelType);
        appendClient();
        break;
    case RemoveClient:
        showModel(ClientsModelType);
        removeClient();
        break;
    case ClearClients:
        showModel(ClientsModelType);
        clearClients();
        break;
    case FilterClients:
        showModel(ClientsModelType);
        filterClient();
        break;
    case FindClient:
        showModel(ClientsModelType);
        findClient();
        break;

    case ShowRentInfo:
        showModel(RentInfoModelType);
        break;
    case IssueCar:
        showModel(RentInfoModelType);
        issueCar();
        break;
    case ReturnCar:
        showModel(RentInfoModelType);
        returnCar();
        break;

    case ClearAllFilters:
        clearFilters();
        break;
    default:
        break;
    }
}

void ConsoleApplication::showHintPanel()
{
    showUserOutput("\rПоказать все имеющиеся автомобили ", 61, ShowAllCars);
    showUserOutput("Добавить новый автомобиль ", 60, AppendCar);

    if(m_currentModelType == CarsModelType) {
        showUserOutput("Удалить сведения об автомобиле ", 60, RemoveCar);
        showUserOutput("Очистить данные об автомобилях ", 60, ClearCars);
        showUserOutput("Найти автомобить по гос. номеру ", 60, FindCar);
        showUserOutput("Отправить автомобиль в ремонт ", 60, SendToRepair);
        showUserOutput("Вернуть автомобиль из ремента ", 60, ReturnFromRepair);
        showUserOutput("Добавить фильтр ", 60, FilterCar);

    }
    std::cout << std::endl;

    showUserOutput("Показать всех зарегистрированных клиентов ", 60, ShowAllClients);
    showUserOutput("Зарегистрировать нового клиента ", 60, AppendClient);

    if(m_currentModelType == ClientsModelType) {
        showUserOutput("Снять клиента с обслуживания ", 60, RemoveClient);
        showUserOutput("Очистить данные о клиентах ", 60, ClearClients);
        showUserOutput("Найти клиента по номеру водительского удостоверения ", 60, FindClient);
        showUserOutput("Добавить фильтр ", 60, FilterClients);

    }
    std::cout << std::endl;

    showUserOutput("Показать информацию об аренде ", 60, ShowRentInfo);
    showUserOutput("Выдать автомобить в аренду ", 60, IssueCar);

    if(m_currentModelType == RentInfoModelType)
        showUserOutput("Вернуть автомобить из аренты ", 60, ReturnCar);
    std::cout << std::endl;

    if(m_currentModelType != NoModel)
        showUserOutput("Сбросить все фильтры ", 60, ClearAllFilters);
    std::cout << std::endl;
}

void ConsoleApplication::showMainPanel()
{
    if(!m_showHintPanel)
        showUserOutput("\rПоказать комманды ", 61, ShowHint);
    else
        showUserOutput("Скрыть комманды ", 60, HideHint);
    if(m_currentModelType != NoModel)
        showUserOutput("Скрыть таблицу ", 60, HideTables);

    showUserOutput("Выход ", 60, Exit);

    std::cout << std::endl;
    std::cout << "\ruser:~> ";
}

void ConsoleApplication::showNavigationPanel()
{
    if(m_currentModelType == NoModel)
        return;

    showUserOutput("\rПредыдущая строка ", 61, SelectNext);
    showUserOutput("Следующая строка ", 60, SelectPrevious);
    showUserOutput("Снять выделение ", 60, Unselect);

    std::cout << std::endl;
}

void ConsoleApplication::showModel(CurrentModelType type)
{
    m_currentModelType = type;
    AbstractItemModel *model = modelByType(type);
    if(!model) {
        m_listView->setModel(nullptr);
        return;
    }

    if(m_listView->model() != model) {
        m_listDelegate->setFieldWidth(app_global::numberOfLetters(model->headerData().data()));
        m_listView->setModel(model);
    }
}

void ConsoleApplication::appendCar()
{
    m_userInputState = true;
    update();

    char numb[app_global::car::numberMaxLen];
    char brand[app_global::car::brandMaxLen];
    char color[app_global::car::colorMaxLen];
    int year = 0;

    std::cout << std::endl;

    if(!getUserInput("Номер автомобиля: ", 60, numb, app_global::car::numberMaxLen)) {
        m_userInputState = false;
        return;
    }
    while (!checkCarNumber(numb)) {
        std::cout << "Неверный формат. Повторите ввод\n";
        if(!getUserInput("Номер автомобиля: ", 60, numb, app_global::car::numberMaxLen)) {
            m_userInputState = false;
            return;
        }
    }
    if(!getUserInput("Марка автомобиля: ", 60, brand, app_global::car::brandMaxLen)) {
        m_userInputState = false;
        return;
    }
    if(!getUserInput("Цвет автомобиля: ", 60, color, app_global::car::colorMaxLen)) {
        m_userInputState = false;
        return;
    }
    getUserInput("Год выпуска автомобиля: ", 60, year);

    Car newCar(numb, brand, color, year);
    m_carsModel->setData(newCar);

    m_userInputState = false;
}

void ConsoleApplication::appendClient()
{
    m_userInputState = true;
    update();

    char license[app_global::client::licenseMaxLen];
    char name[app_global::client::nameMaxLen];
    char passport[app_global::client::passportMaxLen];
    char address[app_global::client::addressMaxLen];

    std::cout << std::endl;

    if(!getUserInput("Номер водительского  удостоверения: ", 60, license, app_global::client::licenseMaxLen)) {
        m_userInputState = false;
        return;
    }
    while(!checkClientLicense(license)) {
        std::cout << "Неверный формат. Повторите ввод\n";
        if(!getUserInput("Номер водительского удостоверения: ", 60, license, app_global::client::licenseMaxLen)) {
            m_userInputState = false;
            return;
        }
    }
    if(!getUserInput("ФИО клиента: ", 60, name, app_global::client::nameMaxLen)) {
        m_userInputState = false;
        return;
    }
    if(!getUserInput("Паспортные данные: ", 60, passport, app_global::client::passportMaxLen)) {
        m_userInputState = false;
        return;
    }
    if(!getUserInput("Адрес: ", 60, address, app_global::client::addressMaxLen)) {
        m_userInputState = false;
        return;
    }

    Client newClient(license, name, passport, address);
    m_clientsModel->setData(newClient);

    m_userInputState = false;
}

bool ConsoleApplication::removeCar()
{
    if(m_listView->selectedItems().isEmpty())
        return true;

    m_userInputState = true;
    update();

    int rowForDel = m_listView->selectedItems().begin()->row();
    CStringData deleteData = m_carsViewModel->data(ModelIndex(rowForDel, CarsModel::Number));
    if(carIsRented(deleteData.data())) {
        showEscapeMsg("Невозможно снять с регистрации выданный в аренду автомобиль");
        m_userInputState = false;
        return false;
    }
    m_carsModel->removeData(deleteData);
    if(rowForDel > m_carsViewModel->rowCount())
        m_listView->clearSelection();

    m_userInputState = false;
    return true;
}

bool ConsoleApplication::removeClient()
{
    if(m_listView->selectedItems().isEmpty())
        return true;

    m_userInputState = true;
    update();

    int rowForDel = m_listView->selectedItems().begin()->row();
    CStringData deleteData = m_clientsViewModel->data(ModelIndex(rowForDel, ClientsModel::License));
    if(clientHasCar(deleteData.data())) {
        showEscapeMsg("Невозможно снять с регистрации клиента имеющего арендованные автомобили");
        m_userInputState = false;
        return false;
    }
    m_clientsModel->removeData(deleteData);
    if(rowForDel > m_clientsViewModel->rowCount())
        m_listView->clearSelection();

    m_userInputState = false;
    return true;
}

void ConsoleApplication::findCar()
{
    m_userInputState = true;
    update();

    char key[app_global::client::licenseMaxLen] = "\0";
    std::cout << "Введите гос. номер автомобиля для поиска\n";
    if(!getUserInput("Гос. номер автомобиля: ", 60, key, app_global::car::numberMaxLen)) {
        m_userInputState = false;
        return;
    }
    if(!checkCarNumber(key)) {
        std::cout << "Неверный формат. Повторите ввод: \n";
        if(!getUserInput("Гос. номер автомобиля: ", 60, key, app_global::car::numberMaxLen)) {
            m_userInputState = false;
            return;
        }
    }
    std::cout << std::endl;

    Car foundCar = m_carsModel->getData(CStringData(key, app_global::car::numberMaxLen));
    if(!checkCarNumber(foundCar.number()))
        std::cout << "Автомобиля с таким гос. номером не зарегестрирован\n";
    else {
        std::cout << "Найден автомобиль\n";
        showUserOutput("Гос. номер автомобиля ", 60, foundCar.number());
        showUserOutput("Марка автомобиля ", 60, foundCar.brand());
        showUserOutput("Цвет автомобиля ", 60, foundCar.color());
        showUserOutput("Год выпуска автомобиля ", 60, foundCar.year());
        std::cout << std::endl;

        if(!carIsRented(foundCar.number())) {
            showEscapeMsg("Автомобиль не арендован");
            m_userInputState = false;
            return;
        }
        LinkList<RentInfo> rents = m_rentInfoModel->getData(CStringData(foundCar.number(),
                                                                        app_global::car::numberMaxLen),
                                                            RentInfoModel::CarRole);
        for(LinkList<RentInfo>::iterator iter = rents.begin(); iter != rents.end(); ++iter) {
            if(std::strlen(iter->returnDate()) != 0 || !checkCarNumber(foundCar.number()))
                continue;

            Client foundClient = m_clientsModel->getData(CStringData(iter->clientData(),
                                                                     app_global::client::licenseMaxLen));
            if(!checkClientLicense(foundClient.license()))
                continue;

            showUserOutput("Номер водительского удостоверения клиента ", 60, foundClient.license());
            showUserOutput("ФИО ", 60, foundClient.name());
        }
    }

    showEscapeMsg("\n");
    m_userInputState = false;
}

void ConsoleApplication::findClient()
{
    m_userInputState = true;
    update();

    char key[app_global::client::licenseMaxLen] = "\0";
    std::cout << "Введите номер водительского удостоверения для поиска\n";
    if(!getUserInput("Номер водительского удостоверения: ", 60, key, app_global::client::licenseMaxLen)) {
        m_userInputState = false;
        return;
    }
    if(!checkClientLicense(key)) {
        std::cout << "Неверный формат. Повторите ввод: \n";
        if(!getUserInput("Номер водительского удостоверения: ", 60, key, app_global::client::licenseMaxLen)) {
            m_userInputState = false;
            return;
        }
    }
    std::cout << std::endl;

    Client foundClient = m_clientsModel->getData(CStringData(key, app_global::client::licenseMaxLen));
    if(!checkClientLicense(foundClient.license()))
        std::cout << "Клиент с таким номером водительского удостоверения не зарегистирован\n";
    else {
        std::cout << "Найден клиент\n";
        showUserOutput("Номер водительского удостоверения ", 60, foundClient.license());
        showUserOutput("ФИО ", 60, foundClient.name());
        showUserOutput("Паспортные данные ", 60, foundClient.passport());
        showUserOutput("Адрес ", 60, foundClient.address());
        std::cout << std::endl;

        if(!clientHasCar(foundClient.license())) {
            showEscapeMsg("Клиент не имеет арендованых автомобилей");
            m_userInputState = false;
            return;
        }

        LinkList<RentInfo> rents = m_rentInfoModel->getData(CStringData(foundClient.license(),
                                                                        app_global::client::licenseMaxLen),
                                                            RentInfoModel::ClientRole);
        std::cout << "Клиент имеет в аренде автомобили\n";
        for(LinkList<RentInfo>::iterator iter = rents.begin(); iter != rents.end(); ++iter) {
            if(std::strlen(iter->returnDate()) != 0)
                continue;

            Car foundCar = m_carsModel->getData(CStringData(iter->carData(),
                                                            app_global::car::numberMaxLen));
            if(checkCarNumber(foundCar.number()))
                showUserOutput("Гос. номер ", 60, foundCar.number());
        }
    }

    showEscapeMsg("\n");
    m_userInputState = false;
}

void ConsoleApplication::filterCar()
{
    m_userInputState = true;
    update();

    char key[app_global::car::brandMaxLen] = "\0";
    std::cout << "Введите матрку автомобиля для фильткации результатов\n";
    if(!getUserInput("Марка автомобиля: ", 60, key, app_global::car::brandMaxLen)) {
        m_userInputState = false;
        return;
    }
    std::cout << std::endl;
    m_carsModel->filter(CStringData(key, app_global::car::brandMaxLen), CarsModel::Brand);

    m_userInputState = false;
}

void ConsoleApplication::filterClient()
{
    m_userInputState = true;
    update();

    int role = ClientsModel::UndefinedRole;

    std::cout << std::endl;
    showUserOutput("ФИО ", 60, ClientsModel::Name);
    showUserOutput("Адрес ", 60, ClientsModel::Address);
    std::cout << std::endl;
    getUserInput("Веберете колонку для фильтрации ", 60, role);

    update();

    char *key = nullptr;
    int keyLen = 0;
    switch(role) {
    case ClientsModel::Name:
        keyLen = app_global::client::nameMaxLen;
        key = new char[keyLen];
        std::cout << "Введите ФИО клиента для фильткации результатов\n";
        if(!getUserInput("ФИО клиента: ", 60, key, keyLen)) {
            m_userInputState = false;
            return;
        }
        break;
    case ClientsModel::Address:
        keyLen = app_global::client::addressMaxLen;
        key = new char[keyLen];
        std::cout << "Введите адрес клиента для фильткации результатов\n";
        if(!getUserInput("Адрес клиента: ", 60, key, keyLen)) {
            m_userInputState = false;
            return;
        }
        break;
    default:
        m_userInputState = false;
        return;;
    }

    m_clientsModel->filter(CStringData(key, keyLen), role);
    delete [] key;

    m_userInputState = false;
}

void ConsoleApplication::clearCars()
{
    m_userInputState = true;
    update();

    m_listView->clearSelection();
    m_listView->selectNext();
    while(m_listView->selectedItems().begin()->row() < m_carsViewModel->rowCount()) {
        if(!removeCar())
            m_listView->selectNext();
        update();
        if(m_listView->selectedItems().isEmpty())
            break;
    }

    m_userInputState = false;
}

void ConsoleApplication::clearClients()
{
    m_userInputState = true;
    update();

    m_listView->clearSelection();
    m_listView->selectNext();
    while(m_listView->selectedItems().begin()->row() < m_carsViewModel->rowCount()) {
        if(!removeClient())
            m_listView->selectNext();
        update();
        if(m_listView->selectedItems().isEmpty())
            break;
    }

    m_userInputState = false;
}

void ConsoleApplication::setCarAvailable(bool available)
{
    if(m_listView->selectedItems().isEmpty())
        return;

    m_userInputState = true;
    update();

    int selectedRow = m_listView->selectedItems().begin()->row();
    CStringData number = m_carsViewModel->data(ModelIndex(selectedRow, CarsModel::Number));
    bool isCarAvailable = m_carsModel->getData(number).available();

    if(!m_carsModel->hasData(number))
        showEscapeMsg("Автомобиль с таким номером не зарегистрирован");
    else if(carIsRented(number.data()))
        showEscapeMsg("Данный автомобиль арендован");
    else if(available && isCarAvailable)
        showEscapeMsg("Нозможно вернуть из ремонта автомобиль доступный для аренды");
    else if(!available && !isCarAvailable)
        showEscapeMsg("Нозможно отправить в ремонт автомобиль уже находящийся в ремонте");
    else
        m_carsModel->setAvailable(number, available);

    m_userInputState = false;
}

void ConsoleApplication::issueCar()
{
    m_userInputState = true;

    char carKey[app_global::car::numberMaxLen] = "\0";
    char clientKey[app_global::client::licenseMaxLen] = "\0";
    char issueDate[app_global::client::licenseMaxLen] = "\0";

    showModel(CarsModelType);
    update();
    if(!getUserInput("Гос. номер автомобиля: ", 60, carKey, app_global::car::numberMaxLen)) {
        m_userInputState = false;
        return;
    }
    while(!m_carsModel->hasData(CStringData(carKey, app_global::car::numberMaxLen))) {
        std::cout << "Автомобиль с таким гос номером не зарегистрирован. Повторите ввод\n";
        if(!getUserInput("Гос. номер автомобиля: ", 60, carKey, app_global::car::numberMaxLen)) {
            m_userInputState = false;
            return;
        }
    }
    if(!m_carsModel->getData(CStringData(carKey, app_global::car::numberMaxLen)).available()) {
        update();
        showEscapeMsg("Данные автомобиль не доступен для аренды");
        m_userInputState = false;
        return;
    }


    showModel(ClientsModelType);
    update();
    if(!getUserInput("Номер водительского удостоверения: ", 60, clientKey, app_global::client::licenseMaxLen)) {
        m_userInputState = false;
        return;
    }
    while(!m_clientsModel->hasData(CStringData(clientKey, app_global::client::licenseMaxLen))){
        std::cout << "Клиент с таким номером водительского удостоверения не зарегистрирован. Повторите ввод\n";
        if(!getUserInput("Номер водительского удостоверения: ", 60, clientKey, app_global::client::licenseMaxLen)) {
            m_userInputState = false;
            return;
        }
    }

    showModel(RentInfoModelType);
    update();
    if(!getUserInput("Дата выдачи: ", 60, issueDate, app_global::dateLen)) {
        m_userInputState = false;
        return;
    }

    RentInfo rent(clientKey, carKey, issueDate);
    m_rentInfoModel->setData(rent);
    m_carsModel->setAvailable(CStringData(carKey, app_global::car::numberMaxLen), false);

    m_userInputState = false;
}

void ConsoleApplication::returnCar()
{
    m_userInputState = true;
    update();

    char carKey[app_global::car::numberMaxLen] = "\0";
    char returnDate[app_global::dateLen] = "\0";

    if(!getUserInput("Гос. номер автомобиля: ", 60, carKey, app_global::car::numberMaxLen)) {
        m_userInputState = false;
        return;
    }
    while(!m_carsModel->hasData(CStringData(carKey, app_global::car::numberMaxLen))
          || !m_rentInfoModel->hasData(CStringData(carKey, app_global::car::numberMaxLen), RentInfoModel::CarRole)) {
        std::cout << "Автомобиль с таким гос номером не выдавался в аренду. Повторите ввод\n";
        if(!getUserInput("Гос. номер автомобиля: ", 60, carKey, app_global::car::numberMaxLen)) {
            m_userInputState = false;
            return;
        }
    }
    if(!getUserInput("Дата возврата автомобиля: ", 60, returnDate, app_global::dateLen)) {
        m_userInputState = false;
        return;
    }
    LinkList<RentInfo> rents = m_rentInfoModel->getData(CStringData(carKey, app_global::car::numberMaxLen), RentInfoModel::CarRole);
    for(LinkList<RentInfo>::iterator iter = rents.begin(); iter != rents.end(); ++iter) {
        if(std::strlen(iter->returnDate()) != 0)
            continue;
        m_carsModel->setAvailable(CStringData(iter->carData(), app_global::car::numberMaxLen), true);
        iter->setReturnDate(returnDate);
        m_rentInfoModel->removeData(CStringData(carKey, app_global::car::numberMaxLen));
        m_rentInfoModel->setData(*iter);
    }

    m_userInputState = false;
}

void ConsoleApplication::clearFilters()
{
    switch (m_currentModelType) {
    case CarsModelType:
        m_carsModel->filter(CStringData(), CarsModel::UndefinedRole);
        break;
    case ClientsModelType:
        m_clientsModel->filter(CStringData(), ClientsModel::UndefinedRole);
        break;
    default:
        break;
    }
}

void ConsoleApplication::update()
{
    app_global::clearConsole();
    if(m_currentModelType != NoModel) {
        m_listView->update();
        std::cout << std::endl;
    }
    if(!m_userInputState) {
        if(m_showHintPanel)
            showHintPanel();
        showNavigationPanel();
        showMainPanel();
    }
}

bool ConsoleApplication::checkClientLicense(const char *key)
{
    if(app_global::numberOfLetters(key) != 12)
        return false;

    const char *keyPtr = key;
    for(int i = 0; i < 12; ++i) {
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
            break;
        }
        case 2:
        case 5:
            if(*keyPtr++ != ' ')
                return false;
            break;
        default:
            std::cout << "wrong char number\n";
            return false;
        }
    }
    return true;
}

bool ConsoleApplication::checkCarNumber(const char *key)
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

bool ConsoleApplication::getUserInput(const char *title, int titleMaxLen, char *storage, int maxStoreLen)
{
    std::cout.setf(std::ios_base::left, std::ios_base::adjustfield);
    std::cout << title
              << std::setw(app_global::realFilledStringSize("(Enter для выхода) ", titleMaxLen - app_global::numberOfLetters(title)))
              << std::setfill('_') << "(Enter для выхода) " << " ";
    std::cin.getline(storage, maxStoreLen, '\n');
    if(!std::cin){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cout.unsetf(std::ios_base::adjustfield);
    if(std::strlen(storage) == 0)
        return false;

    return true;
}

bool ConsoleApplication::getUserInput(const char *title, int titleMaxLen, int &storage)
{
    std::cout.setf(std::ios_base::left, std::ios_base::adjustfield);
    std::cout << std::setw(app_global::realFilledStringSize(title, titleMaxLen))
              << std::setfill('_') << title << " ";
    (std::cin >> storage).get();
    while(!std::cin) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Введено некорректное значение. Повторите ввод (0 для выхода): ";
        (std::cin >> storage).get();
        if(storage == 0)
            return false;
    }
    return true;
}

void ConsoleApplication::showUserOutput(const char *title, int titleMaxLen, const char *data)
{
    std::cout.setf(std::ios_base::left, std::ios_base::adjustfield);
    std::cout << std::setw(app_global::realFilledStringSize(title, titleMaxLen))
              << std::setfill('_') << title << ' ' << data << '\n';
    std::cout.unsetf(std::ios_base::adjustfield);
}

void ConsoleApplication::showUserOutput(const char *title, int titleMaxLen, int data)
{
    std::cout.setf(std::ios_base::left, std::ios_base::adjustfield);
    std::cout << std::setw(app_global::realFilledStringSize(title, titleMaxLen))
              << std::setfill('_') << title << ' ' << data << '\n';
    std::cout.unsetf(std::ios_base::adjustfield);
}

void ConsoleApplication::showEscapeMsg(const char *msg)
{
    std::cout << msg << std::endl << std::endl << "(Enter для выхода)";
    std::cin.get();
}

bool ConsoleApplication::carIsRented(const char *number)
{
    bool rented = false;
    if(!checkCarNumber(number))
        return rented;
    if(!m_carsModel->hasData(CStringData(number, app_global::car::numberMaxLen)))
        return rented;
    if(!m_rentInfoModel->hasData(CStringData(number, app_global::car::numberMaxLen),
                                 RentInfoModel::CarRole))
        return rented;

    Car foundCar = m_carsModel->getData(CStringData(number, app_global::car::numberMaxLen));
    if(!foundCar.available()) {

        LinkList<RentInfo> rents = m_rentInfoModel->getData(CStringData(number, app_global::car::numberMaxLen),
                                                            RentInfoModel::CarRole);
        if(rents.isEmpty())
            return rented;

        for(LinkList<RentInfo>::iterator iter = rents.begin(); iter != rents.end(); ++iter) {
            if(std::strlen(iter->returnDate()) == 0)
                rented = true;
        }
    }
    return rented;
}

bool ConsoleApplication::clientHasCar(const char *number)
{
    bool hasRent = false;
    if(!checkClientLicense(number))
        return hasRent;
    if(!m_clientsModel->hasData(CStringData(number, app_global::client::licenseMaxLen)))
        return hasRent;
    if(!m_rentInfoModel->hasData(CStringData(number, app_global::client::licenseMaxLen),
                                 RentInfoModel::ClientRole))
        return hasRent;
    LinkList<RentInfo> rents = m_rentInfoModel->getData(CStringData(number, app_global::client::licenseMaxLen),
                                                        RentInfoModel::ClientRole);
    if(!rents.isEmpty())
        hasRent = true;

    return hasRent;
}

AbstractItemModel *ConsoleApplication::modelByType(ConsoleApplication::CurrentModelType type)
{
    switch (type) {
    case NoModel:
        return nullptr;
    case CarsModelType:
        return m_carsViewModel;
    case ClientsModelType:
        return m_clientsViewModel;
    case RentInfoModelType:
        return m_rentInfoViewModel;
        break;
    default:
        return nullptr;
    }
}
