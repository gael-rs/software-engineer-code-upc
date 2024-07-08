#include "Vegetable.h"

Vegetable::Vegetable()
{
    price = 0;
    name = "";
}

Vegetable::~Vegetable()
{
}

Vegetable* Vegetable::clone()
{
    return new Vegetable(*this);
}

short Vegetable::getPrice()
{
    return price;
}

short Vegetable::getTimeToBeEaten()
{
    return timeToBeEaten;
}

short Vegetable::getSalePrice()
{
    return salePrice;
}

short Vegetable::getGrowthInterval()
{
    return growthInterval;
}
