#include "items.h"

#include <cstring>

Client::Client()
    : m_license(new char[app_global::client::licenseMaxLen])
    , m_name(new char[app_global::client::nameMaxLen])
    , m_passport(new char[app_global::client::passportMaxLen])
    , m_address(new char[app_global::client::addressMaxLen])
{
    m_license[0] = '\0';
    m_name[0] = '\0';
    m_passport[0] = '\0';
    m_address[0] = '\0';
}

Client::Client(const char *license,
               const char *name,
               const char *passport,
               const char *address)
    : m_license(new char[app_global::client::licenseMaxLen])
    , m_name(new char[app_global::client::nameMaxLen])
    , m_passport(new char[app_global::client::passportMaxLen])
    , m_address(new char[app_global::client::addressMaxLen])
{
    std::strncpy(m_license, license, app_global::client::licenseMaxLen);
    std::strncpy(m_name, name, app_global::client::nameMaxLen);
    std::strncpy(m_passport, passport, app_global::client::passportMaxLen);
    std::strncpy(m_address, address, app_global::client::addressMaxLen);
}

Client::Client(const Client &other)
    : m_license(new char[app_global::client::licenseMaxLen])
    , m_name(new char[app_global::client::nameMaxLen])
    , m_passport(new char[app_global::client::passportMaxLen])
    , m_address(new char[app_global::client::addressMaxLen])
{
    std::strncpy(m_license, other.m_license, app_global::client::licenseMaxLen);
    std::strncpy(m_name, other.m_name, app_global::client::nameMaxLen);
    std::strncpy(m_passport, other.m_passport, app_global::client::passportMaxLen);
    std::strncpy(m_address, other.m_address, app_global::client::addressMaxLen);
}

Client::~Client()
{
    delete[] m_license;
    delete[] m_name;
    delete[] m_passport;
    delete[] m_address;
}

const Client &Client::operator=(const Client &other)
{
    if(this == &other)
        return *this;

    std::strncpy(m_license, other.m_license, app_global::client::licenseMaxLen);
    std::strncpy(m_name, other.m_name, app_global::client::nameMaxLen);
    std::strncpy(m_passport, other.m_passport, app_global::client::passportMaxLen);
    std::strncpy(m_address, other.m_address, app_global::client::addressMaxLen);

    return *this;
}

const char *Client::license() const
{
    return m_license;
}

void Client::setLicense(const char *license)
{
    std::strncpy(m_license, license, app_global::client::licenseMaxLen);
}

const char *Client::name() const
{
    return m_name;
}

void Client::setName(const char *name)
{
    std::strncpy(m_name, name, app_global::client::nameMaxLen);
}

const char *Client::passport() const
{
    return m_passport;
}

void Client::setPassport(const char *passport)
{
    std::strncpy(m_passport, passport, app_global::client::passportMaxLen);
}

const char *Client::address() const
{
    return m_address;
}

void Client::setAddress(const char *address)
{
    std::strncpy(m_address, address, app_global::client::addressMaxLen);
}

Car::Car()
    : m_number(new char[app_global::car::numberMaxLen])
    , m_brand(new char[app_global::car::brandMaxLen])
    , m_color(new char[app_global::car::colorMaxLen])
    , m_year(0)
    , m_available(true)
{
    m_number[0] = '\0';
    m_brand[0] = '\0';
    m_color[0] = '\0';
}

Car::Car(const char *number,
         const char *brand,
         const char *color,
         const int year,
         bool available)
    : m_number(new char[app_global::car::numberMaxLen])
    , m_brand(new char[app_global::car::brandMaxLen])
    , m_color(new char[app_global::car::colorMaxLen])
{
    std::strncpy(m_number, number, app_global::car::numberMaxLen);
    std::strncpy(m_brand, brand, app_global::car::brandMaxLen);
    std::strncpy(m_color, color, app_global::car::colorMaxLen);

    m_year = year;
    m_available = available;
}

Car::Car(const Car &other)
    : m_number(new char[app_global::car::numberMaxLen])
    , m_brand(new char[app_global::car::brandMaxLen])
    , m_color(new char[app_global::car::colorMaxLen])
{
    std::strncpy(m_number, other.m_number, app_global::car::numberMaxLen);
    std::strncpy(m_brand, other.m_brand, app_global::car::brandMaxLen);
    std::strncpy(m_color, other.m_color, app_global::car::colorMaxLen);

    m_year = other.m_year;
    m_available = other.m_available;
}

Car::~Car()
{
    delete[] m_number;
    delete[] m_brand;
    delete[] m_color;
}

const Car &Car::operator=(const Car &other)
{
    if(this == &other)
        return *this;

    std::strncpy(m_number, other.m_number, app_global::car::numberMaxLen);
    std::strncpy(m_brand, other.m_brand, app_global::car::brandMaxLen);
    std::strncpy(m_color, other.m_color, app_global::car::colorMaxLen);

    m_year = other.m_year;
    m_available = other.m_available;

    return *this;
}

const char *Car::number() const
{
    return m_number;
}

void Car::setNumber(const char *number)
{
    std::strncpy(m_number, number, app_global::car::numberMaxLen);
}

const char *Car::brand() const
{
    return m_brand;
}

void Car::setBrand(const char *brand)
{
    std::strncpy(m_brand, brand, app_global::car::brandMaxLen);
}

const char *Car::color() const
{
    return m_color;
}

void Car::setColor(const char *color)
{
    std::strncpy(m_color, color, app_global::car::colorMaxLen);
}

int Car::year() const
{
    return m_year;
}

void Car::setYear(const int &year)
{
    m_year = year;
}

bool Car::available() const
{
    return m_available;
}

void Car::setAvailable(bool available)
{
    m_available = available;
}

RentInfo::RentInfo()
    : m_clientData(new char[app_global::client::licenseMaxLen])
    , m_carData(new char[app_global::car::numberMaxLen])
    , m_returnDate(new char[app_global::dateLen])
    , m_issueDate(new char[app_global::dateLen])
{
    m_clientData[0] = '\0';
    m_carData[0] = '\0';
    m_returnDate[0] = '\0';
    m_issueDate[0] = '\0';
}

RentInfo::RentInfo(const char *clientData,
                   const char *carData,
                   const char *issueDate,
                   const char *returnDate)
    : m_clientData(new char[app_global::client::licenseMaxLen])
    , m_carData(new char[app_global::car::numberMaxLen])
    , m_returnDate(new char[app_global::dateLen])
    , m_issueDate(new char[app_global::dateLen])
{
    std::strncpy(m_clientData, clientData, app_global::client::licenseMaxLen);
    std::strncpy(m_carData, carData, app_global::car::numberMaxLen);
    std::strncpy(m_issueDate, issueDate, app_global::dateLen);
    std::strncpy(m_returnDate, returnDate, app_global::dateLen);
}

RentInfo::RentInfo(const RentInfo &other)
    : m_clientData(new char[app_global::client::licenseMaxLen])
    , m_carData(new char[app_global::car::numberMaxLen])
    , m_returnDate(new char[app_global::dateLen])
    , m_issueDate(new char[app_global::dateLen])
{
    std::strncpy(m_clientData, other.m_clientData, app_global::client::licenseMaxLen);
    std::strncpy(m_carData, other.m_carData, app_global::car::numberMaxLen);
    std::strncpy(m_issueDate, other.m_issueDate, app_global::dateLen);
    std::strncpy(m_returnDate, other.m_returnDate, app_global::dateLen);
}

RentInfo::~RentInfo()
{
    delete[] m_clientData;
    delete[] m_carData;
    delete[] m_issueDate;
    delete[] m_returnDate;
}

const RentInfo &RentInfo::operator=(const RentInfo &other)
{
    if(this == &other)
        return *this;

    std::strncpy(m_clientData, other.m_clientData, app_global::client::licenseMaxLen);
    std::strncpy(m_carData, other.m_carData, app_global::car::numberMaxLen);
    std::strncpy(m_issueDate, other.m_issueDate, app_global::dateLen);
    std::strncpy(m_returnDate, other.m_returnDate, app_global::dateLen);

    return *this;
}

const char *RentInfo::clientData() const
{
    return m_clientData;
}

void RentInfo::setClientData(const char *clientData)
{
    std::strncpy(m_clientData, clientData, app_global::client::licenseMaxLen);
}

const char *RentInfo::carData() const
{
    return m_carData;
}

void RentInfo::setCarData(const char *carData)
{
    std::strncpy(m_carData, carData, app_global::car::numberMaxLen);
}

const char *RentInfo::returnDate() const
{
    return m_returnDate;
}

void RentInfo::setReturnDate(const char *returnDate)
{
    std::strncpy(m_returnDate, returnDate, app_global::dateLen);
}

const char *RentInfo::issueDate() const
{
    return m_issueDate;
}

void RentInfo::setIssueDate(const char *issueDate)
{
    std::strncpy(m_issueDate, issueDate, app_global::dateLen);
}
