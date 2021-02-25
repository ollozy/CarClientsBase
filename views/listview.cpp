#include "listview.h"

#include "../models/abstractitemmodel.h"

#include "../delegates/abstractdelegate.h"

#include <iostream>

ListView::ListView()
    : AbstractItemView()
{

}

ListView::~ListView()
{

}

void ListView::update()
{
    int rowCount = model()->rowCount();

    bool needBoard = false;
    for(int i = 0; i < rowCount * 2; ++i) {
        if(i % 2 == 0)
            needBoard = true;
        else
            needBoard = false;

        ModelIndex index(i, 0);
        delegate()->setCurrentIndex(index);
        bool isSelected = selectedItems().contains(index)
                || selectedItems().contains(ModelIndex(i - 1, 0))
                || selectedItems().contains(ModelIndex(i + 1, 0));

        if(needBoard)
            delegate()->drawHorizontalBoard(isSelected);
        else {
            delegate()->drawVerticalBorad(isSelected);
            delegate()->drawData();
            delegate()->drawVerticalBorad(isSelected);
        }

        delegate()->drawNextLine();
    }
    delegate()->drawHorizontalBoard(false);
    delegate()->drawNextLine();

}

void ListView::selectItem(int row, int column)
{
    if(row == 0 || column == 0)
        return;

    AbstractItemView::selectItem(row, column);
}
