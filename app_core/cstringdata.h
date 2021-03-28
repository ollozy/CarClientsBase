#ifndef CSTRINGDATA_H
#define CSTRINGDATA_H


class CStringData
{
public:
    CStringData();
    CStringData(const char *data, int len);
    CStringData(int data);
    CStringData(const CStringData &other);
    ~CStringData();

    const CStringData &operator=(const CStringData &other);

    int toInt() const;

    const char *data() const;
    int length() const;

    void setData(const char *data, int len);
    void setData(int data);

    bool isEmpty() const;

private:
    char *m_data;
    int m_len;
};

#endif // CSTRINGDATA_H
