#pragma once
#include "StaticEntity.h"

class Fence: public StaticEntity
{
private:
	short heightExpect;

public:
	Fence(short x = 0, short y = 0, short heightExpect = 0);
	~Fence();
	void paint(Graphics^ g);
};
