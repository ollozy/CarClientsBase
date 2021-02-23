#include "tableview.h"

#include "../models/abstractitemmodel.h"

#include "../delegates/abstractdelegate.h"

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

    for(int i = 0; i < columnCount; ++i) {
        for(int j = 0; j < rowCount; ++j) {
            ModelIndex index(i, j);
            delegate()->setCurrentIndex(index);
            if(selectedItems().contains(index))
                delegate()->drawSelected();
            else
                delegate()->draw();
        }
    }
}

void TableView::selectItem(int row, int column)
{
    if(row == 0 || column == 0)
        return;

    AbstractItemView::selectItem(row, column);
}
