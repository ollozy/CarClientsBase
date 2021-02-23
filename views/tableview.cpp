#include "tableview.h"

#include "../models/abstractitemmodel.h"

#include "../delegates/abstractdelegate.h"

#include <iostream>

TableView::TableView()
    : AbstractItemView()
{

}

TableView::~TableView()
{

}

void TableView::update()
{
    int columnCount = model()->columnCount();
    int rowCount = model()->rowCount();

    bool needBoard = false;
    bool noNeedBoard = false;
    int realRow = 0;
    for(int i = realRow; i < rowCount + 2; ++i) {
        if(i == 2 || i == 0)
            needBoard = true;
        for(int j = 0; j < columnCount; ++j) {
            ModelIndex index(realRow, j);

            bool isSelected = selectedItems().contains(index);

            if(j == 0)
                delegate()->setFieldWidth(2);
            else
                delegate()->setFieldWidth(20);

            if(needBoard) {
                delegate()->drawHorizontalBoard(isSelected);
                continue;
            }

            delegate()->setCurrentIndex(index);
            delegate()->drawVerticalBorad(isSelected);
            delegate()->drawData();
        }
        if(!needBoard)
            delegate()->drawVerticalBorad(selectedItems().contains(ModelIndex(i, columnCount - 1)));
        else {
            --realRow;
            needBoard = false;
            noNeedBoard = true;
        }
        ++realRow;
        std::cout << std::endl;
    }
}

void TableView::selectItem(int row, int column)
{
    if(row == 0 || column == 0)
        return;

    AbstractItemView::selectItem(row, column);
}
