#include "Hash.h"
#include <cmath>

void Hash::insert(const char* key, const int& value)
{
    //Если превышен максимальный размер таблицы, изменить ее размер 
    //Такая реализация не гарантирует, что пара ключ-значение попадут в таблицу
    //if (m_size > m_capacity * 0.4) resize();
    
    //Вызвать хеш-функцию
    unsigned int seg = hashFunction(key);
    //Пока полученный сегмент не за пределами таблицы
    for (int i = 0; seg < m_capacity; ++i) {
        //Подсчет количества обращений к сегменту
        ++m_elements[seg].m_segCalcCount;
        //Если элемент имеет такой же ключ как передаваемый в функцию
        if (!std::strcmp(m_elements[seg].m_key, key)) {
            //Изменить значение по данному адресу
            m_elements[seg].m_val = value;
            return;
        }
        //Если элемент по полученному адресу пуст или удален
        else if (!std::strcmp(m_elements[seg].m_key, deletedSegment) ||
            !std::strcmp(m_elements[seg].m_key, emptySegment)) {
            //Вставить новый элемент в таблицу
            m_elements[seg].m_val = value;
            std::strcpy(m_elements[seg].m_key, key);
            ++m_size;
            return;
        }
        else
            //Вызвать функцию квадратичного опробования для получения нового адреса
            quadTesting(i, seg);
    }
    //Полученный сегмент за пределами таблицы
    //Рекурсивно изменять фактический размер таблицы, пока ключ не будет вставлен в таблицу
    //Это гарантирует, что ключ будет вставлен в таблицу
    resize();
    insert(key, value);
}

//В этой функции нельзя использовать operator[] для поиска элемента по ключю
//Так как при отсутствии ключа в таблице функция все равно передаст значение
//а ключи для сравнения она не возвращаяет (хотя и можно реализовать такую фукнцию, но это
//усложнит код. Так проще и нагляднее
bool Hash::erase(const char* key)
{
    //Вызвать хеш функцию
    unsigned int seg = hashFunction(key);
    //Пока полученный сегмент не за пределами таблицы
    for (int i = 0; seg < m_capacity; ++i) {
        //Если ключ по полученному сегменту равен ключу переданому в функцию
        if (!std::strcmp(key, m_elements[seg].m_key)) {
            //пометить его как удаленный
            std::strcpy(m_elements[seg].m_key, deletedSegment);
            m_elements[seg].m_segCalcCount = 0;
            --m_size;
            return true;
        }
        else
            //Вызвать функцию квадратичного опробывания
            quadTesting(i, seg);
    }
    //Полученный сегмент за пределами таблицы. 
    //Данного элемента нет в таблице
    return false;
}

bool Hash::erase(const unsigned int seg)
{
    //Если сегмент за пределами таблицы - операция имеет неопределенное поведение
    if (seg >= m_capacity) {
        std::cout << "Попытка обращения к несуществующему сегменту\n";
        return false;
    }
    //Если элемент по сегменту уже удален - операция не имеет смысла
    else if (!std::strcmp(m_elements[seg].m_key, deletedSegment) ||
        !std::strcmp(m_elements[seg].m_key, emptySegment)) {
        return false;
    }
    //Иначе, помечием элемент по сегменту как удаленный
    return erase(m_elements[seg].m_key);
}

void Hash::clear()
{
    //Как в erase только для всех сегментов таблицы
    for (unsigned int i = 0; i < m_capacity; ++i) {
        if (std::strcmp(m_elements[i].m_key, deletedSegment) && 
            std::strcmp(m_elements[i].m_key, emptySegment)) {
            std::strcpy(m_elements[i].m_key, deletedSegment);
            m_elements[i].m_segCalcCount = 0;
            --m_size;
        }
    }
    //Вернуть размер таблици в исходное состояние
    //Иначе после каждой очистки insert начнет раздувать размер таблицы
    m_capacity = 3000;
    delete[] m_elements;
    m_elements = new Data[m_capacity];
    m_multiCoef = static_cast<unsigned int>(m_capacity / 102);
}

int Hash::operator[](const char* key) const
{    
    //Вызвать хеш-функцию
    unsigned int seg = hashFunction(key);
    //Пока полученный сегмент не за пределами таблицы
    for (int i = 0; seg < m_capacity; ++i) {
        //Если по сегменту лежит тот же ключ, что и передаваемый в функцию
        if (!std::strcmp(m_elements[seg].m_key, key)) {
            //Вернуть значение
            return m_elements[seg].m_val;
        }
        //Если элемент по полученному сегменту пуст или удален
        else {
            //Вызвать функцию квадратичного опроддования для получения нового адреса
            quadTesting(i, seg);
            continue;
        }
    }
    //Полученный сегмент за пределами таблицы.
    //Такого ключа в таблице нет
    //! Можно сделать out of range, но такой задачи нет
    std::cout << "Ключ " << key << " не найден\n";
    return m_elements[0].m_val;
}

int Hash::operator[](const unsigned int seg) const
{
    //Если сегмент за пределами таблицы - операция имеет неопределенное поведение
    //! Можно сделать out of range, но такой задачи нет
    if (seg > m_capacity) {
        std::cout << "обращение к несуществующему сегменту хеш-таблицы\n";
        return m_elements[0].m_val;
    }

    return m_elements[seg].m_val;
}

void Hash::keys(char(*keysStorage)[7]) const
{
    //Копирует все ключи, не помеченные как удаленные или пустые в keysStorage
    for (unsigned int i = 0, j = 0; i < m_capacity; ++i) {
        if (std::strcmp(m_elements[i].m_key, emptySegment) &&
            std::strcmp(m_elements[i].m_key, deletedSegment)) {
            std::strcpy(keysStorage[j], m_elements[i].m_key);
            ++j;
        }
    }
}

bool Hash::hasKey(const char* key) const
{
    for (unsigned int i = 0; i < m_capacity; ++i)
        if (!std::strcmp(key, m_elements[i].m_key))
            return true;
  
    return false;
}

bool Hash::testDataFile(const char* fileName) const
{
    //Записывает в файл количество обращений к каждому сегменту
    std::ofstream ofs;
    ofs.open(fileName);
    if (!ofs.is_open()) {
        ofs.clear();
        return false;
    }
    for (unsigned int i = 0; i < m_capacity; ++i)
        ofs << m_elements[i].m_segCalcCount << '\n';
    ofs.close();
    return true;
}

void Hash::resize(unsigned int size)
{
    unsigned int newCapacity = static_cast<unsigned int>(m_capacity * 1.5);

    //Создается временное хранилище элементов таблицы
    //все ее элементы копируются в это хранилище
    Data* temp = new Data[newCapacity];
    for (unsigned int i = 0; i < m_capacity; ++i) {
        std::strcpy(temp[i].m_key, m_elements[i].m_key);
        temp[i].m_val = m_elements[i].m_val;
    }
    //Удаляется массив таблицы и создается новый нового размера
    delete[] m_elements;
    m_elements = new Data[newCapacity];
    //обычная вставка в получившийся массив
    //из временного хранилища. Иначе потеряются ключи
    m_capacity = newCapacity;
    m_size = 0;
    for (unsigned int i = 0; i < newCapacity; ++i) {
        if (std::strcmp(temp[i].m_key, deletedSegment) &&
            std::strcmp(temp[i].m_key, emptySegment))
            insert(temp[i].m_key, temp[i].m_val);
    }
    delete[] temp;
}

unsigned int Hash::hashFunction(const char* key) const
{
    unsigned int seg = 0;
    //для каждого символа ключа
    for (int i = 0; key[i] != '\0'; ++i)
        //прибавить код символа в 3 степени к общей сумме
        seg += static_cast<unsigned int>(std::pow(key[i], 3));
    return ((seg - 339) * m_multiCoef) % (m_capacity);
}
