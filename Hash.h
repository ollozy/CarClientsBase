#ifndef HASH_H
#define HASH_H

#include <cstring>

template<int KeyLen, typename Val>
class Hash
{    
    static const char deletedSegment[KeyLen] = "*****\0";
    static const char emptySegment[KeyLen] = "     \0";

    struct Data {
        Data() : m_val(0), m_key(new char[KeyLen]) { std::strncpy(m_key, KeyLen, emptySegment); }
        ~Data() { delete[] m_key; delete m_val; }
        Val *m_val;
        char* m_key;
    };

    using uint = unsigned int;

public:
    Hash()
        : m_size(0)
        , m_capacity(3000)
        , m_multiCoef(m_capacity / 102)
        , m_elements(new Data[m_capacity]) {}
    ~Hash() { delete[] m_elements; }

    void insert(const char* key, const Val& value);
    bool erase(const char* key);

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

#endif // HASH_H
