#pragma once
#include "Animal.h"
#include "PowerItem.h"

class Dog: public Animal, public PowerItem
{
private:
	

public:
	Dog();
	~Dog();
	void paint(Graphics^ g);
	void move(Rectangle* space);
	void paintItem(Graphics^ g);
	BaseEntity* getEntityPowerItem();
	void paintPreview(Graphics^ g, short moneyFarmer);
	PowerItem* clone();
	void bark();
};
