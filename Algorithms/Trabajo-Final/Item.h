#pragma once
#include "BaseEntity.h"

class Item
{
protected:
	short count;
	string type;

public:
	Item(short count = 0);
	~Item();
	short getCount();
	void setCount(short count);
	string getType();
	virtual void paint(Graphics^ g);
	virtual BaseEntity* getEntity() { return nullptr; }
	virtual short getPrice() { return 0; };
	virtual short getSalePrice() { return 0; };
};

