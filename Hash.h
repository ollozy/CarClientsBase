#ifndef HASH_H
#define HASH_H

#include <cstdlib>
#include <iostream>
#include <fstream>

const char deletedSegment[7] = "*****\0";
const char emptySegment[7] = "     \0";

class Hash
{
public:
    Hash()
        : m_elements(new Data[m_capacity])
        , m_size(0)
        , m_capacity(3000)
        , m_multiCoef(m_capacity / 102) {}
    ~Hash() { delete[] m_elements; }
    //Вставка значение value по ключу key
    void insert(const char* key, const int& value); 
    //Удаление значения по ключу key
    bool erase(const char* key); 
    //Перегруженный метод. Удаление по номеру сегмента
    bool erase(const unsigned int seg);
    //Полная очистка табилцы
    void clear();
    //Получения значения по ключу
    int operator[](const char* key) const;
    //Получение значения по сегменту
    int operator[](const unsigned int seg) const;
    //Выгружает все ключи в переданный массив
    void keys(char(*keysStorage)[7]) const;
    //Получение ключа по номеру сегмента
    char* key(const unsigned int seg) const { return m_elements[seg].m_key; }
    //Содержит ли таблица переданный ключ
    bool hasKey(const char* key) const;
    //Значащий размер таблицы
    int size() const { return m_size; }
    //Фактичекй размер таблицы
    int capacity() const { return m_capacity; }
    bool testDataFile(const char *fileName) const;

private:
    //Увеличение фактического размера таблицы
    void resize(unsigned int size = 0);
    //Хеш-функция
    unsigned int hashFunction(const char* key) const;
    //Функция квадратичного опробования
    void quadTesting(int tryNum, unsigned int& seg) const { seg += 1 * tryNum + 1 * tryNum * tryNum; }
    //Структура для хранения данных элемента hash таблицы
    struct Data {
        //стандартный конструктор
        Data() : m_val(0), m_key(new char[7]), m_segCalcCount(0) { std::strcpy(m_key, emptySegment); }
        //Чтобы небыло утечек при удалении
        ~Data() { delete[] m_key; }
        //Поля значения и ключа
        int m_val;
        char* m_key;
        unsigned int m_segCalcCount;
    };
    //Значащий размер таблицы
    unsigned int m_size;
    //Фактический размер таблицы
    unsigned int m_capacity;
    //Множитель размера таблицы
    unsigned int m_multiCoef;

    //Массив элементов
    Data* m_elements;
};

#endif // HASH_H
