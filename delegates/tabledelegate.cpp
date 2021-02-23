#include "tabledelegate.h"

#include "../models/abstractitemmodel.h"

#include "../app_core/cstringdata.h"

#include <iostream>

TableDelegate::TableDelegate()
    : AbstractDelegate()
{

}

TableDelegate::~TableDelegate()
{

}

void TableDelegate::draw()
{
    drawHorizontalBoard();
    drawVerticalBorad();
    drawData();
    drawVerticalBorad();
    std::cout << '\n';
    drawHorizontalBoard();
}

void TableDelegate::drawSelected()
{
    drawSelectedHorizontalBoard();
    drawSelectedVerticalBoard();
    drawData();
    drawSelectedVerticalBoard();
    std::cout << '\n';
    drawSelectedHorizontalBoard();
}

void TableDelegate::drawHorizontalBoard()
{
    if(model()->data(currentIndex()).isEmpty())
        return;

    int dataSize = model()->data(currentIndex()).length();
    for(int i = 1; i < dataSize - 1; ++i) {
        std::cout << '-';
    }
    std::cout << '\n';
}

void TableDelegate::drawVerticalBorad()
{
    std::cout << " | ";
}

void TableDelegate::drawSelectedHorizontalBoard()
{
    if(model()->data(currentIndex()).isEmpty())
        return;

    int dataSize = model()->data(currentIndex()).length();
    for(int i = 1; i < dataSize - 1; ++i) {
        std::cout << '=';
    }
    std::cout << '\n';
}

void TableDelegate::drawSelectedVerticalBoard()
{
    std::cout << " || ";
}

void TableDelegate::drawData()
{
    if(model()->data(currentIndex()).isEmpty())
        std::cout << ' ';
    else
        std::cout << model()->data(currentIndex()).data();
}
