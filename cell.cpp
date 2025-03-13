#include "cell.h"

int Cell::getX() const
{
    return x;
}

void Cell::setX(int const value) // Just set the value, don't modify it
{
    x = value;
}

int Cell::getY() const
{
    return y;
}

void Cell::setY(int const value)
{
    y = value;
}