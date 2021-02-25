#include "listdelegate.h"

#include "../models/abstractitemmodel.h"

#include "../app_core/cstringdata.h"

#include <iostream>
#include <iomanip>
#include <cstring>

ListDelegate::ListDelegate()
    : AbstractDelegate()
{

}

ListDelegate::~ListDelegate()
{

}

void ListDelegate::drawHorizontalBoard(bool selected)
{
    std::cout.setf(std::ios_base::left, std::ios_base::adjustfield);
    char board = selected ? '=' : '-';
    std::cout.fill(board);
    std::cout.width(fieldWidth() + 3);

    std::cout << "  ";
    std::cout.fill(' ');
    std::cout.unsetf(std::ios_base::adjustfield);
}

void ListDelegate::drawVerticalBorad(bool selected)
{
    std::cout << (selected ? " ! " : " | ");
}

void ListDelegate::drawData()
{
    std::cout << model()->data(currentIndex()).data();
}

void ListDelegate::drawNextLine()
{
    std::cout << std::endl;
}
