#include "listview.h"

#include "../models/viewmodels/abstractitemmodel.h"

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
    int columtCount = model()->columnCount();

    bool needBoard = false;
    for(int i = 0; i < rowCount * 2; ++i) {
        if(i % 2 == 0)
            needBoard = true;
        else
            needBoard = false;

        ModelIndex index(i / 2, 0);
        bool selectVertical = selectedItems().contains(index);
        bool selectHorizontal = selectedItems().contains(index)
                || selectedItems().contains(ModelIndex(index.row() - 1, 0));

        if(needBoard)
            delegate()->drawHorizontalBoard(selectHorizontal);
        else {
            delegate()->drawVerticalBorad(selectVertical);
            if(index.row() == 0) {
                delegate()->setCurrentIndex(index);
                delegate()->drawData();
                delegate()->drawVerticalBorad(selectVertical);
            }
            else {
                for(int j = 0; j < columtCount; ++j) {
                    delegate()->setCurrentIndex(ModelIndex(index.row(), j));
                    delegate()->drawData();
                    delegate()->drawVerticalBorad(selectVertical);
                }
            }
        }
        delegate()->drawNextLine();
    }
    delegate()->drawHorizontalBoard(selectedItems().contains(ModelIndex(rowCount - 1, 0)));
    delegate()->drawNextLine();
}

void ListView::selectItem(int row, int column)
{
    if(!model())
        return;

    if(row == 0)
        return;

    if(!(row < model()->rowCount())) {
        clearSelection();
        return;
    }

    clearSelection();
    AbstractItemView::selectItem(row, column);
}

void ListView::selectNext()
{
    if(!model())
        return;

    if(selectedItems().isEmpty()) {
        selectItem(1, 0);
        return;
    }
    else if(selectedItems().size() > 1)
        return;
    selectItem(selectedItems().begin()->row() + 1, 0);
}

void ListView::selectPrevious()
{
    if(!model())
        return;

    if(selectedItems().isEmpty()) {
        selectItem(model()->rowCount() - 1, 0);
        return;
    }
    else if(selectedItems().size() > 1)
        return;
    selectItem(selectedItems().begin()->row() - 1, 0);
}
