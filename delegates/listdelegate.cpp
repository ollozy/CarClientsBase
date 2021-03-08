#include "listdelegate.h"

#include "../models/viewmodels/carsviewmodel.h"
#include "../items.h"

#include "../app_core/cstringdata.h"

#include "../global.h"

#include <iostream>
#include <iomanip>
#include <cmath>
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

    std::cout << "\r  ";
    std::cout.fill(' ');
    std::cout.unsetf(std::ios_base::adjustfield);
}

void ListDelegate::drawVerticalBorad(bool selected)
{
    std::cout << (selected ? " # " : " | ");
}

void ListDelegate::drawData()
{
    if(currentIndex().row() == 0) {
        std::cout << model()->data(currentIndex()).data();
        return;
    }

    CStringData data = model()->data(currentIndex());
    char dataPresentation[100] = "\0";
    if(currentIndex().column() == 0) {
        std::strncat(dataPresentation, data.data(), 3);
        for(int i = 0; i < 3 - app_global::numberOfLetters(data.data()); ++i)
            std::strncat(dataPresentation, " ", 1);
    }
    else {
        std::strncat(dataPresentation, data.data(), app_global::realFilledStringSize(data.data(), 45));
        for(int i = 0; i < 45 - app_global::numberOfLetters(data.data()); ++i)
            std::strncat(dataPresentation, " ", 1);
    }
    std::cout << dataPresentation;
}

void ListDelegate::drawNextLine()
{
    std::cout << std::endl;
}
