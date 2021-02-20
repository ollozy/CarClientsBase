#ifndef HASH_H
#define HASH_H

#include <cstring>

#include "global.h"
#include "linklist.h"

#ifdef QT_DEBUG
#include <QFile>
#include <QDebug>
#endif

using appGlobal::uint;


template<typename Val, uint KeyLen>
class Hash
{
    static char deletedSegment[KeyLen];
    static char emptySegment[KeyLen];
    static const uint minHashFunc;
    static const uint maxHashFunc;
    static const uint linearStep;
    static const uint initCapacity;

    union key_helper {
        char c[KeyLen];
        uint n;
    };

    struct Data {
        explicit Data(Val val = Val())
            : m_data(val),
              m_key(new char[KeyLen])
        { std::strncpy(m_key, emptySegment, KeyLen); }
        ~Data() { delete[] m_key; }
        Val m_data;
        char* m_key;
#ifdef QT_DEBUG
        uchar m_cellCall = 0;
#endif
    };

public:
    Hash()
        : m_size(0)
        , m_capacity(initCapacity)
        , m_multiCoef(static_cast<uint>(m_capacity / (maxHashFunc - minHashFunc)))
        , m_elements(new Data[m_capacity]) {
        for(uint i = 0; i < KeyLen - 1; ++i) {
            emptySegment[i] = ' ';
            deletedSegment[i] = '*';
        }
        emptySegment[KeyLen] = deletedSegment[KeyLen] = '\0';
    }
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

    uint size() const;
    uint capacity() const;

#ifdef QT_DEBUG
    bool getTestFile(const char *fileName) {
        QFile testFile(fileName);
        if(!testFile.open(QIODevice::WriteOnly))
            qDebug() << "cannot open file" << fileName << "for write";
        QTextStream stream(&testFile);
        for (uint i = 0; i < m_capacity; ++i)
            stream << QString::number(m_elements[i].m_cellCall) << '\n';
        testFile.close();
        return true;
    }
#endif

private:
    void resize(uint newSize);
    uint hashFunction(const char* key) const;
    void linearTesting(uint tryNum, uint& seg) const;

private:
    uint m_size;
    uint m_capacity;
    uint m_multiCoef;

    Data* m_elements;
};

template<typename Val, uint KeyLen>
char Hash<Val, KeyLen>::deletedSegment[KeyLen];
template<typename Val, uint KeyLen>
char Hash<Val, KeyLen>::emptySegment[KeyLen];
template<typename Val, uint KeyLen>
const uint Hash<Val, KeyLen>::minHashFunc = 240;
template<typename Val, uint KeyLen>
const uint Hash<Val, KeyLen>::maxHashFunc = 357;
template<typename Val, uint KeyLen>
const uint Hash<Val, KeyLen>::linearStep = 2;
template<typename Val, uint KeyLen>
const uint Hash<Val, KeyLen>::initCapacity = 500;

template<typename Val, uint KeyLen>
void Hash<Val, KeyLen>::insert(const char *key, const Val &value)
{
    if(m_size > m_capacity * 0.8)
        resize(static_cast<uint>(m_capacity * 1.5));
    uint seg = hashFunction(key);
    for(uint i = 0; seg < m_capacity; ++i) {
        if(std::strncmp(m_elements[seg].m_key, key, KeyLen) == 0) {
            m_elements[seg].m_data = value;
            return;
        }
        else if(std::strncmp(m_elements[seg].m_key, deletedSegment, KeyLen) == 0 ||
                std::strncmp(m_elements[seg].m_key, emptySegment, KeyLen) == 0) {
            m_elements[seg].m_data = value;
            std::strncpy(m_elements[seg].m_key, key, KeyLen);
            ++m_size;
            return;
        }
        else
            linearTesting(i, seg);
    }
    resize(static_cast<uint>(m_capacity * 1.5));
    insert(key, value);
}

template<typename Val, uint KeyLen>
void Hash<Val, KeyLen>::erase(const char *key)
{
    uint seg = hashFunction(key);
    for(uint i = 0; seg < m_capacity; ++i) {
        if(std::strncmp(key, m_elements[seg].m_key, KeyLen) == 0) {
            std::strncpy(m_elements[seg].m_key, deletedSegment, KeyLen);
            --m_size;
            return;
        }
        else
            linearTesting(i, seg);
    }
}

template<typename Val, uint KeyLen>
void Hash<Val, KeyLen>::clear()
{
    for(uint seg = 0; seg < m_capacity; ++seg) {
        if(std::strncmp(m_elements[seg].m_key, deletedSegment, KeyLen) != 0
                && std::strncmp(m_elements[seg].m_key, emptySegment, KeyLen) != 0) {
            std::strncmp(m_elements[seg].m_key, deletedSegment, KeyLen);
            --m_size;
        }
    }
    m_capacity = initCapacity;
    delete[] m_elements;
    m_elements = new Data[m_capacity];
    m_multiCoef = static_cast<uint>(m_capacity / (maxHashFunc - minHashFunc));
}

template<typename Val, uint KeyLen>
Val &Hash<Val, KeyLen>::operator[](const char *key)
{
    uint seg = hashFunction(key);
    for (uint i = 0; seg < m_capacity; ++i) {
        if (std::strncmp(m_elements[seg].m_key, key, KeyLen) == 0)
            return m_elements[seg].m_data;
        else {
            linearTesting(i, seg);
            continue;
        }
    }
    Q_ASSERT_X(false, "Hash<Val, KeyLen>::operator[]", "access to hash with out of range key");
    return m_elements[0].m_data;
}

template<typename Val, uint KeyLen>
const Val &Hash<Val, KeyLen>::operator[](const char *key) const
{
    return operator[](key);
}

template<typename Val, uint KeyLen>
LinkList<char *> Hash<Val, KeyLen>::keys() const
{
    LinkList<char *> keyList;
    for(uint i = 0; i < m_capacity; ++i) {
        if(std::strncmp(m_elements[i].m_key, emptySegment, KeyLen) != 0
                && std::strncmp(m_elements[i].m_key, deletedSegment, KeyLen) != 0) {
            keyList.append(m_elements[i].m_key);
        }
    }
    return keyList;
}

template<typename Val, uint KeyLen>
LinkList<Val> Hash<Val, KeyLen>::values() const
{
    LinkList<Val> keyList;
    for(uint i = 0; i < m_capacity; ++i) {
        if(std::strncmp(m_elements[i].m_key, emptySegment, KeyLen) != 0
                && std::strncmp(m_elements[i].m_key, deletedSegment, KeyLen) != 0) {
            keyList.append(m_elements[i].m_data);
        }
    }
    return keyList;
}

template<typename Val, uint KeyLen>
const char *Hash<Val, KeyLen>::key(const Val &val) const
{
    for(uint i = 0; i < m_capacity; ++i) {
        if(val == m_elements[i].m_data)
            return m_elements[i].m_key;
    }
    return "\0";
}

template<typename Val, uint KeyLen>
bool Hash<Val, KeyLen>::hasKey(const char *key) const
{
    uint seg = hashFunction(key);
    for(uint i = 0; seg < m_capacity; ++i) {
        if(std::strncmp(key, m_elements[seg].m_key, KeyLen) == 0)
            return true;
        else
            linearTesting(i, seg);
    }
    return false;
}

template<typename Val, uint KeyLen>
uint Hash<Val, KeyLen>::size() const
{
    return m_size;
}

template<typename Val, uint KeyLen>
uint Hash<Val, KeyLen>::capacity() const
{
    return m_capacity;
}

template<typename Val, uint KeyLen>
void Hash<Val, KeyLen>::resize(uint newSize)
{
    Data *temp = new Data[newSize];
    for(uint i = 0; i < m_capacity; ++i) {
        std::strncpy(temp[i].m_key, m_elements[i].m_key, KeyLen);
        temp[i].m_data = m_elements[i].m_data;
    }
    delete[] m_elements;
    m_elements = new Data[newSize]{Data()};
    m_capacity = newSize;
    m_size = 0;
    for(uint i = 0; i < newSize; ++i) {
        if(std::strncmp(temp[i].m_key, deletedSegment, KeyLen) != 0
                && std::strncmp(temp[i].m_key, emptySegment, KeyLen) != 0) {
            insert(temp[i].m_key, temp[i].m_data);
        }
    }
    delete[] temp;
}

template<typename Val, uint KeyLen>
uint Hash<Val, KeyLen>::hashFunction(const char *key) const
{
    uint seg = 0;
    key_helper helper;
    std::strncpy(helper.c, key, KeyLen);
    for(uint i = 0; i < KeyLen; ++i) {
        seg += helper.n;
    }
    return ((seg - minHashFunc) * m_multiCoef) % m_capacity;
}

template<typename Val, uint KeyLen>
void Hash<Val, KeyLen>::linearTesting(uint tryNum, uint &seg) const
{
    seg += linearStep * tryNum + tryNum % 2 + 1;
}

#endif // HASH_H
