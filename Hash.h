#ifndef HASH_H
#define HASH_H

#include <QObject>

#include <cstring>

#ifdef QT_DEBUG
#include <QFile>
#include <QDebug>
#endif


class LinkList;

template<uint KeyLen, typename Val>
class Hash
{
    using uint = unsigned int;

    static const char deletedSegment[KeyLen];
    static const char emptySegment[KeyLen];
    static const uint minHashFunc;
    static const uint maxHashFunc;
    static const uint linearStep;
    static const uint initCapacity;

    union key_helper {
        char c[KeyLen];
        uint n;
    };

    struct Data {
        explicit Data(Val val = Val()) noexcept
            : m_val(val),
              m_key(new char[KeyLen])
        { std::strncpy(m_key, emptySegment, KeyLen); }
        ~Data() { delete[] m_key; }
        Val m_val;
        char* m_key;
    };

public:
    Hash()
        : m_size(0)
        , m_capacity(initCapacity)
        , m_multiCoef(static_cast<uint>(m_capacity / (maxHashFunc - minHashFunc)))
        , m_elements(new Data[m_capacity]) {}
    ~Hash() { delete[] m_elements; }

    void insert(const char* key, const Val& value);
    void erase(const char* key);

    void clear();
    int operator[](const char* key) const;

    void keys(char(*keysStorage)[KeyLen]) const;
    bool hasKey(const char* key) const;

    int size() const;
    int capacity() const;

private:
    void resize(unsigned int size = 0);
    uint hashFunction(const char* key) const;
    void linearTesting(int tryNum, unsigned int& seg) const;

private:
    uint m_size;
    uint m_capacity;
    uint m_multiCoef;

    Data* m_elements;
};

template<uint KeyLen, typename Val>
const char Hash<KeyLen, Val>::deletedSegment[KeyLen] = "*****\0";
template<uint KeyLen, typename Val>
const char Hash<KeyLen, Val>::emptySegment[KeyLen] = "     \0";
template<uint KeyLen, typename Val>
const uint Hash<KeyLen, Val>::minHashFunc = 240;
template<uint KeyLen, typename Val>
const uint Hash<KeyLen, Val>::maxHashFunc = 357;
template<uint KeyLen, typename Val>
const uint Hash<KeyLen, Val>::linearStep = 2;
template<uint KeyLen, typename Val>
const uint Hash<KeyLen, Val>::initCapacity = 500;

template<uint KeyLen, typename Val>
void Hash<KeyLen, Val>::insert(const char *key, const Val &value)
{
    if(m_size > m_capacity * 0.4)
        resize();
    uint seg = hashFunction(key);
    for(uint i = seg; seg < m_capacity; ++i) {
        if(std::strcmp(m_elements[seg].m_key, key) == 0) {
            *m_elements[seg].m_val = value;
            return;
        }
        else if(std::strcmp(m_elements[seg].m_key, deletedSegment) == 0 ||
                std::strcmp(m_elements[seg].m_key, emptySegment) == 0) {
            m_elements[seg].m_val = new Val(value);
            std::strncpy(m_elements[seg].m_key, KeyLen, key);
            ++m_size;
            return;
        }
        else
            linearTesting(i, seg);
    }
    resize();
    insert(key, value);
}

template<int KeyLen, typename Val>
void Hash<KeyLen, Val>::erase(const char *key)
{
    uint seg = hashFunction(key);
    for(uint i = 0; seg < m_capacity; ++i) {
        if(std::strcmp(key, m_elements[seg].m_key) == 0) {
            std::strncpy(m_elements[seg].m_key, KeyLen, deletedSegment);
            delete m_elements[seg].m_val;
            --m_size;
            return;
        }
        else
            linearTesting(i, seg);
    }
}

template<int KeyLen, typename Val>
void Hash<KeyLen, Val>::clear()
{
    for(uint seg = 0; seg < m_capacity; ++seg) {
        if(std::strcmp(m_elements[seg].m_key, deletedSegment) != 0
                && std::strcmp(m_elements[seg].m_key, emptySegment) != 0) {
            std::strcmp(m_elements[seg].m_key, deletedSegment);
            delete m_elements[seg].m_val;
            --m_size;
        }
    }
    m_capacity = 3000;
    delete[] m_elements;
    m_elements = new Data[m_capacity]{Val()};
    m_multiCoef = m_capacity / 102;

template<uint KeyLen, typename Val>
unsigned int Hash<KeyLen, Val>::hashFunction(const char *key) const
{
    uint seg = 0;
    key_helper helper;
    std::strncpy(helper.c, key, KeyLen);
    for(uint i = 0; i < KeyLen; ++i) {
        seg += helper.n;
    }
    return ((seg - minHashFunc) * m_multiCoef) % m_capacity;
}

template<uint KeyLen, typename Val>
void Hash<KeyLen, Val>::linearTesting(int tryNum, unsigned int &seg) const
{
    seg += linearStep * tryNum + tryNum % 2 + 1;
}

#endif // HASH_H
