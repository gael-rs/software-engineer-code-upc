#pragma once
#include "AnimateEntity.h"
#include "FlashLight.h"
#include "Sequence.h"

class Farmer: public AnimateEntity
{
private:
	FlashLight* flashLight;
	ActionFarmer actionFarmer;
	Sequence* sequenceKeySale;
	Sequence* sequenceKeyBuy;
	float scale;
	short money; 

public:
	Farmer(short x = 0, short y = 0);
	~Farmer();
	void move(Rectangle* space, Direction direction);
	void paint(Graphics^ g);
	void stop();
	short getMoney();
	void setMoney(short money);
	FlashLight* getFlashLight();
	void changeStatusFlashLight();
	void action(ActionFarmer actionFarmer);
	Sequence* getSequenceKeySale();
	Sequence* getSequenceKeyBuy();
	void animationLeave(Graphics^ g);
	float getScale();
	void setScale(float scale);
};

