#ifndef HASH_H
#define HASH_H

#include <cstring>
#include <cmath>

#include "global.h"
#include "linklist.h"

template<typename Val, int KeyLen>
class Hash
{
    static const int minHashFunc;
    static const int maxHashFunc;
    static const int linearStep;
    static const int initCapacity;

    union key_helper {
        char c[KeyLen];
        int n;
    };

    struct Data {
        explicit Data(Val val = Val())
            : m_data(val)
            , m_key(new char[KeyLen])
            , m_empty(true)
            , m_deleted(false) {}
        ~Data() { delete [] m_key; }
        Val m_data;
        char* m_key;
        bool m_empty;
        bool m_deleted;
    };

public:
    Hash()
        : m_size(0)
        , m_capacity(initCapacity)
        , m_multiCoef(static_cast<int>(m_capacity / (maxHashFunc - minHashFunc)))
        , m_elements(new Data[m_capacity]) {}
    ~Hash() { delete[] m_elements; }

    void insert(const char* key, const Val& value);
    void erase(const char* key);

    void clear();
    Val &operator[](const char* key);
    const Val &operator[](const char *key) const;


    LinkList<char *> keys() const;
    LinkList<Val> values() const;
    const char *key(const Val &val) const;
    bool hasKey(const char *key) const;

    int size() const;
    int capacity() const;

private:
    void resize(int newSize);
    int hashFunction(const char* key) const;
    void linearTesting(int tryNum, int& seg) const;

private:
    int m_size;
    int m_capacity;
    int m_multiCoef;

    Data* m_elements;
};

template<typename Val, int KeyLen>
const int Hash<Val, KeyLen>::minHashFunc = 240;
template<typename Val, int KeyLen>
const int Hash<Val, KeyLen>::maxHashFunc = 357;
template<typename Val, int KeyLen>
const int Hash<Val, KeyLen>::linearStep = 2;
template<typename Val, int KeyLen>
const int Hash<Val, KeyLen>::initCapacity = 500;

template<typename Val, int KeyLen>
void Hash<Val, KeyLen>::insert(const char *key, const Val &value)
{
    if(m_size > m_capacity * 0.8)
        resize(static_cast<int>(m_capacity * 1.5));
    int seg = hashFunction(key);
    for(int i = 0; seg < m_capacity; ++i) {
        if(m_elements[seg].m_empty || m_elements[seg].m_deleted) {
            m_elements[seg].m_data = value;
            std::strncpy(m_elements[seg].m_key, key, KeyLen);
            m_elements[seg].m_deleted = false;
            m_elements[seg].m_empty = false;
            ++m_size;
            return;
        }
        else if(std::strncmp(m_elements[seg].m_key, key, KeyLen) == 0) {
            m_elements[seg].m_data = value;
            return;
        }
        else
            linearTesting(i, seg);
    }
    resize(static_cast<int>(m_capacity * 1.5));
    insert(key, value);
}

template<typename Val, int KeyLen>
void Hash<Val, KeyLen>::erase(const char *key)
{
    int seg = hashFunction(key);
    for(int i = 0; seg < m_capacity; ++i) {
        if(std::strncmp(key, m_elements[seg].m_key, KeyLen) == 0) {
            m_elements[seg].m_deleted = true;
            --m_size;
            return;
        }
        else
            linearTesting(i, seg);
    }
}

template<typename Val, int KeyLen>
void Hash<Val, KeyLen>::clear()
{
    m_capacity = initCapacity;
    delete[] m_elements;
    m_elements = new Data[m_capacity];
    m_multiCoef = static_cast<int>(m_capacity / (maxHashFunc - minHashFunc));
}

template<typename Val, int KeyLen>
Val &Hash<Val, KeyLen>::operator[](const char *key)
{
    assert(hasKey(key));

    int seg = hashFunction(key);
    for (int i = 0; seg < m_capacity; ++i) {
        if (std::strncmp(m_elements[seg].m_key, key, KeyLen) == 0)
            return m_elements[seg].m_data;
        else {
            linearTesting(i, seg);
            continue;
        }
    }
    return m_elements[0].m_data;
}

template<typename Val, int KeyLen>
const Val &Hash<Val, KeyLen>::operator[](const char *key) const
{
    assert(hasKey(key));

    int seg = hashFunction(key);
    for (int i = 0; seg < m_capacity; ++i) {
        if (std::strncmp(m_elements[seg].m_key, key, KeyLen) == 0)
            return m_elements[seg].m_data;
        else {
            linearTesting(i, seg);
            continue;
        }
    }
    return m_elements[0].m_data;
}

template<typename Val, int KeyLen>
LinkList<char *> Hash<Val, KeyLen>::keys() const
{
    LinkList<char *> keyList;
    for(int i = 0; i < m_capacity; ++i) {
        if(!m_elements[i].m_empty && !m_elements[i].m_deleted)
            keyList.append(m_elements[i].m_key);
    }
    return keyList;
}

template<typename Val, int KeyLen>
LinkList<Val> Hash<Val, KeyLen>::values() const
{
    LinkList<Val> keyList;
    for(int i = 0; i < m_capacity; ++i) {
        if(!m_elements[i].m_empty && !m_elements[i].m_deleted) {
            keyList.append(m_elements[i].m_data);
        }
    }
    return keyList;
}

template<typename Val, int KeyLen>
const char *Hash<Val, KeyLen>::key(const Val &val) const
{
    for(int i = 0; i < m_capacity; ++i) {
        if(val == m_elements[i].m_data)
            return m_elements[i].m_key;
    }
    return "\0";
}

template<typename Val, int KeyLen>
bool Hash<Val, KeyLen>::hasKey(const char *key) const
{
    int seg = hashFunction(key);
    for(int i = 0; seg < m_capacity; ++i) {
        if(m_elements[i].m_empty || m_elements[i].m_deleted)
            continue;
        else if(std::strncmp(key, m_elements[seg].m_key, KeyLen) == 0)
            return true;
        else
            linearTesting(i, seg);
    }
    return false;
}

template<typename Val, int KeyLen>
int Hash<Val, KeyLen>::size() const
{
    return m_size;
}

template<typename Val, int KeyLen>
int Hash<Val, KeyLen>::capacity() const
{
    return m_capacity;
}

template<typename Val, int KeyLen>
void Hash<Val, KeyLen>::resize(int newSize)
{
    Data *temp = new Data[newSize];
    for(int i = 0; i < m_capacity; ++i) {
        std::strncpy(temp[i].m_key, m_elements[i].m_key, KeyLen);
        temp[i].m_data = m_elements[i].m_data;
    }
    delete[] m_elements;
    m_elements = new Data[newSize]{Data()};
    m_capacity = newSize;
    m_size = 0;
    for(int i = 0; i < newSize; ++i) {
        if(!m_elements[i].m_empty && !m_elements[i].m_deleted) {
            insert(temp[i].m_key, temp[i].m_data);
        }
    }
    delete[] temp;
}

template<typename Val, int KeyLen>
int Hash<Val, KeyLen>::hashFunction(const char *key) const
{
    int seg = 0;
    key_helper helper;
    std::strncpy(helper.c, key, KeyLen);
    for(int i = 0; i < KeyLen; ++i) {
        seg += helper.n;
    }
    return std::abs(((seg - minHashFunc) * m_multiCoef) % m_capacity);
}

template<typename Val, int KeyLen>
void Hash<Val, KeyLen>::linearTesting(int tryNum, int &seg) const
{
    seg += linearStep * tryNum + tryNum % 2 + 1;
}

#endif // HASH_H
