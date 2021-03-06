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
    , m_rentInfoModel(nullptr)
    , m_list(new ListView)
    , m_delegate(new ListDelegate)
    , m_proxy(new ProxyModel)
    , m_lastView(nullptr)
{
    m_list->setDelegate(m_delegate);
    m_list->setModel(m_proxy);
    m_carModel->initHeader();
    m_clientsModel->initHeader();
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
        findCar();
        break;

    case ShowAllClients:
        showView(ClientModel);
        break;
    case AppendClient:
        showView(ClientModel);
        appendClient();
        break;
    case FindClient:
        findClient();
        break;


        //    case ShowRentInfo:
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
    if(!m_showHintPanel)
        std::cout << std::setw(app_global::realFilledStringSize("Показать комманды ", 61))
                  << std::setfill('_') << "\rПоказать комманды " << ' ' << ShowHint << '\n';
    else
        std::cout << std::setw(app_global::realFilledStringSize("Скрыть комманды ", 60))
                  << std::setfill('_') << "Скрыть комманды " << ' ' << HideHint << '\n';
    if(m_lastView != nullptr) {
        std::cout << std::setw(app_global::realFilledStringSize("Скрыть таблицу ", 60))
                  << std::setfill('_') << "Скрыть таблицу " << ' ' << HideAllInfo << '\n';
    }
    std::cout << std::setw(app_global::realFilledStringSize("Выход ", 60))
              << std::setfill('_') <<  "Выход " << ' ' << Exit << '\n';
    std::cout.unsetf(std::ios_base::adjustfield);
    std::cout << std::endl;
    std::cout << "\ruser:~> ";
}

void MainWindow::hintPanel()
{
    std::cout.setf(std::ios_base::left, std::ios_base::adjustfield);
    std::cout << std::setw(app_global::realFilledStringSize("Показать все имеющиеся автомобили ", 61))
              << std::setfill('_') << "\rПоказать все имеющиеся автомобили " << ' ' << ShowAllCars << '\n';
    std::cout << std::setw(app_global::realFilledStringSize("Добавить новый автомобиль ", 60))
              << std::setfill('_') << "Добавить новый автомобиль " << ' ' << AppendCar << '\n';
    if(m_currentModel == CarModel) {
        std::cout << std::setw(app_global::realFilledStringSize("Удалить сведения об автомобиле ", 60))
                  << std::setfill('_') << "Удалить сведения об автомобиле " << ' ' << RemoveLine << '\n';
        std::cout << std::setw(app_global::realFilledStringSize("Очистить данные об автомобилях ", 60))
                  << std::setfill('_') << "Очистить данные об автомобилях " << ' ' << ClearAll << '\n';
        std::cout << std::setw(app_global::realFilledStringSize("Найти автомобить по гос. номеру ", 60))
                  << std::setfill('_') << "Найти автомобить по гос. номеру " << ' ' << FindCar << '\n';
    }
    std::cout << std::endl;
    std::cout << std::setw(app_global::realFilledStringSize("Показать всех зарегистрированных клиентов ", 60))
              << std::setfill('_') << "Показать всех зарегистрированных клиентов " << ' ' << ShowAllClients << '\n';
    std::cout << std::setw(app_global::realFilledStringSize("Зарегистрировать нового клиента ", 60))
              << std::setfill('_') << "Зарегистрировать нового клиента " << ' ' << AppendClient << '\n';
    if(m_currentModel == ClientModel) {
        std::cout << std::setw(app_global::realFilledStringSize("Снять клиента с обслуживания ", 60))
                  << std::setfill('_') << "Снять клиента с обслуживания " << ' ' << RemoveLine << '\n';
        std::cout << std::setw(app_global::realFilledStringSize("Очистить данные о клиентах ", 60))
                  << std::setfill('_') << "Очистить данные о клиентах " << ' ' << ClearAll << '\n';
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

    std::cout.setf(std::ios_base::left, std::ios_base::adjustfield);
    std::cout << std::setw(app_global::realFilledStringSize("Предыдущая строка ", 60))
              << std::setfill('_') << "Предыдущая строка " << ' ' << PreviousLine << '\n';
    std::cout << std::setw(app_global::realFilledStringSize("Следующая строка ", 61))
              << std::setfill('_') << "\rСледующая строка " << ' ' << NextLine << '\n';
    std::cout << std::setw(app_global::realFilledStringSize("Снять выделение ", 60))
              << std::setfill('_') << "Снять выделение " << ' ' << UnselectLine << '\n';
    std::cout << std::setw(app_global::realFilledStringSize("Фильтровать ", 60))
              << std::setfill('_') << "Фильтровать " << ' ' << Filter << '\n';
    std::cout << std::setw(app_global::realFilledStringSize("Очистить фильтр ", 60))
              << std::setfill('_') << "Очистить фильтр " << ' ' << ClearFilter << '\n';
    std::cout.unsetf(std::ios_base::adjustfield);
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
        m_proxy->setFilterColumn(2);
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

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout.setf(std::ios_base::left, std::ios_base::adjustfield);
    std::cout << std::setw(app_global::realFilledStringSize("Номер автомобиля: ", 30))
              << std::setfill('_') << "Номер автомобиля: " << " ";
    std::cin.getline(numb, app_global::car::numberMaxLen, '\n');
    while(!checkCarNumber(numb)) {
        if(!std::cin) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout << "Неверный формат. Повторите ввод (Enter для выхода): \n";
        std::cout << std::setw(app_global::realFilledStringSize("Номер автомобиля: ", 30))
                  << std::setfill('_') << "Номер автомобиля: " << " ";
        std::cin.getline(numb, app_global::client::licenseLen, '\n');
        if(std::strlen(numb) == 0) {
            m_userInputState = false;
            return;
        }
    }
    std::cin.sync();

    std::cout << std::setw(app_global::realFilledStringSize("Марка автомобиля: ", 30))
              << std::setfill('_') << "Марка автомобиля: " << " ";
    std::cin.getline(brand, app_global::car::brandMaxLen, '\n');
    if(!std::cin){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << std::setw(app_global::realFilledStringSize("Цвет автомобиля: ", 30))
              << std::setfill('_') << "Цвет автомобиля: " << " ";
    std::cin.getline(color, app_global::car::colorMaxLen, '\n');
    if(!std::cin){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << std::setw(app_global::realFilledStringSize("Год выпуска автомобиля: ", 30))
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

void MainWindow::findCar()
{    
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    char key[app_global::car::numberMaxLen] = "\0";
    std::cout << "Введите номер автомобиля для поиска: ";
    std::cin.getline(key, app_global::car::numberMaxLen, '\n');
    if(!checkCarNumber(key)) {
        if(!std::cin) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout << "Неверный формат. Повторите ввод (Enter для выхода): " << std::endl;
        std::cin.getline(key, app_global::client::licenseLen, '\n');
        if(std::strlen(key) == 0)
            return;
    }
    std::cout << std::endl;
    Car foundCar = m_carModel->getByKey(key);
    if(!checkCarNumber(foundCar.number())) {
        std::cout << "Автомобиль с таким номером не зарегистрирован\n";
    }
    else {
        std::cout.setf(std::ios_base::left, std::ios_base::adjustfield);
        std::cout << "Найден автомобиль:\n";
        std::cout << std::setw(app_global::realFilledStringSize("Государственный регистрационный номер: ", 61))
                  << std::setfill('_') << "\rГосударственный регистрационный номер: " << foundCar.number() << '\n';
        std::cout << std::setw(app_global::realFilledStringSize("Цвет: ", 60))
                  << std::setfill('_') << "Цвет: " << foundCar.brand() << '\n';
        std::cout << std::setw(app_global::realFilledStringSize("Марка: ", 60))
                  << std::setfill('_') << "Марка: " << foundCar.color() << '\n';
        std::cout << std::setw(app_global::realFilledStringSize("Год выпуска: ", 60))
                  << std::setfill('_') << "Год выпуска: " << foundCar.year() << '\n';
        std::cout << std::endl;
        if(foundCar.available()) {
            RentInfo rentInfo; //= m_rentInfoModel->mapClientByCar(foundCar.number());
            Client foundClinet = m_clientsModel->getByKey(rentInfo.clientData());
            std::cout << "Автомобиль выдан клиенту: \n";
            std::cout << std::setw(app_global::realFilledStringSize("ФИО: ", 60))
                      << std::setfill('_') << "ФИО: " << foundClinet.name() << '\n';
            std::cout << std::setw(app_global::realFilledStringSize("Номер водительского удостоверения: ", 60))
                      << std::setfill('_') << "Номер водительского удостоверения: " << foundClinet.license() << '\n';
        }
        std::cout.unsetf(std::ios_base::adjustfield);
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

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout.setf(std::ios_base::left, std::ios_base::adjustfield);
    std::cout << std::setw(app_global::realFilledStringSize("Номер удостоверения: ", 30))
              << std::setfill('_') << "Номер удостоверения: " << " ";
    std::cin.getline(license, app_global::client::licenseLen, '\n');
    if(!checkClientLicense(license)) {
        if(!std::cin) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout << "Неверный формат. Повторите ввод (Enter для выхода): " << std::endl;
        std::cin.getline(license, app_global::client::licenseLen, '\n');
        if(std::strlen(license) == 0) {
            m_userInputState = false;
            return;
        }
    }

    std::cout << std::setw(app_global::realFilledStringSize("ФИО клиента: ", 30))
              << std::setfill('_') << "ФИО клиента: " << " ";
    std::cin.getline(name, app_global::client::nameMaxLen, '\n');
    if(!std::cin){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << std::setw(app_global::realFilledStringSize("Паспортные данные: ", 30))
              << std::setfill('_') << "Паспортные данные: " << " ";
    std::cin.getline(passport, app_global::client::addressMaxLen, '\n');
    if(!std::cin){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << std::setw(app_global::realFilledStringSize("Адрес: ", 30))
              << std::setfill('_') << "Адрес: " << " ";
    std::cin.getline(address, app_global::client::addressMaxLen, '\n');
    if(!std::cin){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout.unsetf(std::ios_base::adjustfield);

    Client newClient(license, name, passport, address);
    m_clientsModel->insertRow(newClient);

    m_userInputState = false;
}

void MainWindow::findClient()
{
    char key[app_global::client::licenseLen] = "\0";
    std::cout << "Введите номер водительского удостоверения для поиска: ";
    std::cin.getline(key, app_global::client::licenseLen, '\n');
    m_clientsModel->getByKey(key);
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

bool MainWindow::checkCarNumber(const char *key) const
{
    /* Государственный регистрационный номер – строка формата
            * «ANNNAA-NN», где N –цифра; A – буква из следующего множества:
            * А, В, Е, К, М, Н, О, Р, С, Т, У, Х; */
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
    /* – Номер водительского удостоверения – строка формата «0R 1R 2  3A 4A 5  6N 7N 8N 9N 10N 11N»,
    * где RR – код региона (цифры); AA – серия (буквы из следующего множества: А, В, Е, К, М, Н, О, Р, С, Т, У, Х); NNNNNN –
    * порядковый номер удостоверения (цифры). Код, серия и номер отделяются друг от друга пробелами; */

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
