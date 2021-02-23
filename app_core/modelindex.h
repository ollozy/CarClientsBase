#ifndef MODELINDEX_H
#define MODELINDEX_H


class ModelIndex
{
public:
    ModelIndex();
    ModelIndex(int row, int column);
    ModelIndex(const ModelIndex &other);

    const ModelIndex &operator=(const ModelIndex &other);
    bool operator==(const ModelIndex &other);
    bool operator!=(const ModelIndex &other);

    int row() const;
    void setRow(int row);

    int column() const;
    void setColunt(int column);

    //! Если row < 0, а column >= 0 или наоборот,
    //! ModelIndex указывает на все элементы в строке или столбце
    //! (смотря что >= 0)
    bool isValid() const;
    bool isMulti() const;

private:
    int m_row;
    int m_column;
};

#endif // MODELINDEX_H
