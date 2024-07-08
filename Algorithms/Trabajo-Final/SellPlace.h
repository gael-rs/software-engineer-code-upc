#pragma once
#include "StaticEntity.h"

class SellPlace : public StaticEntity
{
private:


public:
	SellPlace();
	~SellPlace();
	void paint(Graphics^ g);
	bool collisionAction(BaseEntity* entity);
};


