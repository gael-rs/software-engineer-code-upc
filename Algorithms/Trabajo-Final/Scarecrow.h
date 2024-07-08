#pragma once
#include "PowerItem.h"
#include "StaticEntity.h"

class Scarecrow : public PowerItem, public StaticEntity
{
private:

public:
	Scarecrow();
	~Scarecrow();
	void paint(Graphics^ g);
	void paintPreview(Graphics^ g, short moneyFarmer);
	BaseEntity* getEntityPowerItem();
	void paintItem(Graphics^ g);
	PowerItem* clone();
};
