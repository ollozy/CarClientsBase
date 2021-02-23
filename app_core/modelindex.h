#ifndef MODELINDEX_H
#define MODELINDEX_H


class ModelIndex
{
public:
    ModelIndex();

    int row() const;
    void setRow(int row);

    int column() const;
    void setColunt(int column);

    bool isValid() const;

private:
    int m_row;
    int m_column;
};

#endif // MODELINDEX_H
