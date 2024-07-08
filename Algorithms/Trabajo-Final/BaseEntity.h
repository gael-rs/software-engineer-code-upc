#pragma once
#include "Utilities.h"

class BaseEntity
{
protected:
	short x, y, dx, dy, width, height, column, row;
	string name;

public:
	BaseEntity(short x = 0, short y = 0, short dx = 0, short dy = 0, short width = 0, short height = 0, short column = 0, short row = 0);
	~BaseEntity();
	short getX();
	short getY();
	short getDx();
	short getDy();
	short getWidth();
	short getHeight();
	short getColumn();
	short getRow();
	string getName();

	void setX(short x);
	void setY(short y);
	void setDx(short dx);
	void setDy(short dy);
	void setWidth(short width);
	void setHeight(short height);
	void setColumn(short column);
	void setRow(short row);

	virtual Rectangle* getRectangle();
	bool collision(BaseEntity* BaseEntity);
	virtual void paint(Graphics^ g) {};
	virtual void paint(Graphics^ g, Bitmap^ image) {};
};

