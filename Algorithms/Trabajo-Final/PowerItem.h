#pragma once
#include "Item.h"
#include "Sequence.h"
#include "CustomButton.h"

class PowerItem : public Item
{
protected:
	short price;
	float scale;
	Sequence* coinAnimate;
	CustomButton* button;

public:
	PowerItem();
	~PowerItem();
	virtual void paintItem(Graphics^ g);
	virtual void paintPreview(Graphics^ g, short moneyFarmer);
	short getPrice();
	void setPrice(short price);
	float getScale();
	void setScale(float scale);
	CustomButton* getButton(); 
	virtual BaseEntity* getEntityPowerItem() { return nullptr;  };
	BaseEntity* getEntity();
	virtual PowerItem* clone();
};

