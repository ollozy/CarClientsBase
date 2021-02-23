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
    std::cout << model()->data(currentIndex()).data();
}
