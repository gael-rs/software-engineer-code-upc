#pragma once
#include "AnimateEntity.h"

class FlashLight: public AnimateEntity
{
private:
	bool isOn;
	Direction direction;

public:
	FlashLight();
	~FlashLight();
	void on();
	void off();
	bool getStatusOn();
	void toogleStatus();
	void paint(Graphics^ g);
	void setDirection(Direction direction);
};

