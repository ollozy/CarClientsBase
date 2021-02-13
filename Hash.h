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
    Val &operator[](const char* key);
    const Val &operator[](const char *key) const;


    void keys() const;
    const char *key(const Val &val) const;
    bool hasKey(const char *key) const;

    int size() const;
    int capacity() const;

private:
    void resize(uint newSize);
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

template<uint KeyLen, typename Val>
void Hash<KeyLen, Val>::clear()
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

template<uint KeyLen, typename Val>
Val &Hash<KeyLen, Val>::operator[](const char *key)
{
    uint seg = hashFunction(key);
    for (uint i = 0; seg < m_capacity; ++i) {
        if (std::strncmp(m_elements[seg].m_key, key, KeyLen) == 0)
            return m_elements[seg].m_val;
        else {
            linearTesting(i, seg);
            continue;
        }
    }
    Q_ASSERT_X(false, "Hash<KeyLen, Val>::operator[]", "access to hash with out of range key");
    return m_elements[0].m_val;
}

template<uint KeyLen, typename Val>
const Val &Hash<KeyLen, Val>::operator[](const char *key) const
{
    return operator[](key);
}
}
const char *Hash<KeyLen, Val>::key(const Val &val) const
{
    for(int i = 0; i < m_capacity; ++i) {
        if(val == m_elements[i].m_val)
            return m_elements[i].m_key;
    }
    return "\0";
}

template<uint KeyLen, typename Val>
bool Hash<KeyLen, Val>::hasKey(const char *key) const
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

template<uint KeyLen, typename Val>
int Hash<KeyLen, Val>::size() const
{
    return m_size;
}

template<uint KeyLen, typename Val>
int Hash<KeyLen, Val>::capacity() const
{
    return m_capacity;
}

template<uint KeyLen, typename Val>
void Hash<KeyLen, Val>::resize(uint newSize)
{
    Data *temp = new Data[newSize];
    for(uint i = 0; i < m_capacity; ++i) {
        std::strncpy(temp[i].m_key, m_elements[i].m_key, KeyLen);
        temp[i].m_val = m_elements[i].m_val;
    }
    delete[] m_elements;
    m_elements = new Data[newSize];
    m_capacity = newSize;
    m_size = 0;
    for(uint i = 0; i < newSize; ++i) {
        if(std::strncmp(temp[i].m_key, deletedSegment, KeyLen) != 0
                && std::strncmp(temp[i].m_key, emptySegment, KeyLen) != 0) {
            insert(temp[i].m_key, temp[i].m_val);
        }
    }
    delete[] temp;
}

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
