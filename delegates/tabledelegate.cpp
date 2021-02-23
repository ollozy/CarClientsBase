#include "tabledelegate.h"

#include "../models/abstractitemmodel.h"

#include "../app_core/cstringdata.h"

#include <iostream>
#include <iomanip>
#include <cstring>

TableDelegate::TableDelegate()
    : AbstractDelegate()
{

}

TableDelegate::~TableDelegate()
{

}

void TableDelegate::drawHorizontalBoard(bool selected)
{
    std::cout.setf(std::ios_base::left, std::ios_base::adjustfield);
    char board = selected ? '=' : '-';
    std::cout.fill(board);
    std::cout.width(fieldWidth() + 3);

    std::cout << "  ";
    std::cout.fill(' ');
    std::cout.unsetf(std::ios_base::adjustfield);
}

void TableDelegate::drawVerticalBorad(bool selected)
{
    std::cout << (selected ? " ! " : " | ");
}

void TableDelegate::drawData()
{
    if(model()->data(currentIndex()).isEmpty())
        std::cout << ' ';
    else
        drawUtfFixedData(model()->data(currentIndex()).data());
}

void TableDelegate::drawNextLine()
{
    std::cout << std::endl;
}

void TableDelegate::drawUtfFixedData(const char *data)
{
    std::cout.setf(std::ios_base::left, std::ios_base::adjustfield);
    std::cout << std::setw(realStringLen(data)) << data;
    std::cout.unsetf(std::ios_base::adjustfield);
}

int TableDelegate::realStringLen(const char *data)
{
    uint strlen = 0;
    for(uint i = 0; data[i] != '\0'; ++i) {
        if(i % 2 == 0
                || std::isalnum(data[i])
                || std::ispunct(data[i])
                || std::isspace(data[i]))
            strlen += 1;
    }
    return std::strlen(data) + fieldWidth() - strlen;
}
