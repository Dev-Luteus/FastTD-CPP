#ifndef CELL_H
#define CELL_H

class Cell
{
    private:
    int x { 0 };
    int y { 0 };
    int id { 0 };
    static constexpr int CELL_SIZE { 32 };

    public:
    [[nodiscard]] int getX() const;
    void setX(int value);

    [[nodiscard]] int getY() const;
    void setY(int value);
};

#endif //CELL_H
