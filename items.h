#ifndef CLIENT_H
#define CLIENT_H

#include "global.h"

class Client
{
public:
    Client();
    Client(const char *license,
           const char *name,
           const char *passport,
           const char *address);
    Client(const Client &other);
    ~Client();

    const Client &operator=(const Client &other);

    const char *license() const;
    void setLicense(const char *license);

    const char *name() const;
    void setName(const char *name);

    const char *passport() const;
    void setPassport(const char *passport);

    const char *address() const;
    void setAddress(const char *address);

private:
    char *m_license;
    char *m_name;
    char *m_passport;
    char *m_address;
};

class Car
{
public:
    Car();
    Car(const char *number,
        const char *brand,
        const char *color,
        const int year,
        bool available = true);
    Car(const Car &other);
    ~Car();

    const Car &operator=(const Car &other);

    const char *number() const;
    void setNumber(const char *number);

    const char *brand() const;
    void setBrand(const char *brand);

    const char *color() const;
    void setColor(const char *color);

    int year() const;
    void setYear(const int &year);

    bool available() const;
    void setAvailable(bool available);

private:
    char *m_number;
    char *m_brand;
    char *m_color;
    int m_year;
    bool m_available;
};

class RentInfo
{
public:
    RentInfo();
    RentInfo(const char *clientData,
             const char *carData,
             const char *issueDate,
             const char *returnDate = "\0");
    RentInfo(const RentInfo &other);
    ~RentInfo();

    const RentInfo &operator=(const RentInfo &other);

    const char *clientData() const;
    void setClientData(const char *clientData);

    const char *carData() const;
    void setCarData(const char *carData);

    const char *returnDate() const;
    void setReturnDate(const char *returnDate);

    const char *issueDate() const;
    void setIssueDate(const char *issueDate);

private:
    char *m_clientData;
    char *m_carData;

    char *m_returnDate;
    char *m_issueDate;
};

#endif // CLIENT_H
