#include "BaseEntity.h"

BaseEntity::BaseEntity(short x, short y, short dx, short dy, short width, short height, short column, short row)
{
	this->x = x;
	this->y = y;
	this->dx = dx;
	this->dy = dy;
	this->width = width;
	this->height = height;
	this->column = column;
	this->row = row;
	this->name = "";
}

BaseEntity::~BaseEntity()
{
}

short BaseEntity::getX()
{
	return x;
}

short BaseEntity::getY()
{
	return y;
}

short BaseEntity::getDx()
{
	return dx;
}

short BaseEntity::getDy()
{
	return dy;
}

short BaseEntity::getWidth()
{
	return width;
}

short BaseEntity::getHeight()
{
	return height;
}

short BaseEntity::getColumn()
{
	return column;
}

short BaseEntity::getRow()
{
	return row;
}

string BaseEntity::getName()
{
	return name;
}

void BaseEntity::setX(short x)
{
	this->x = x;
}

void BaseEntity::setY(short y)
{
	this->y = y;
}

void BaseEntity::setDx(short dx)
{
	this->dx = dx;
}

void BaseEntity::setDy(short dy)
{
	this->dy = dy;
}

void BaseEntity::setWidth(short width)
{
	this->width = width;
}

void BaseEntity::setHeight(short height)
{
	this->height = height;
}

void BaseEntity::setColumn(short column)
{
	this->column = column;
}

void BaseEntity::setRow(short row)
{
	this->row = row;
}

Rectangle* BaseEntity::getRectangle()
{
	return new Rectangle(x, y, width, height);
}

bool BaseEntity::collision(BaseEntity* BaseEntity)
{
	return this->getRectangle()->IntersectsWith(*BaseEntity->getRectangle());
}

