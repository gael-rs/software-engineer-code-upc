#pragma once
#include "Fence.h"

class Wall
{
private:
	// Relaci�n de agregaci�n de la clase Fence con la clase Wall
	vector<Fence*>* fences;

public:
	Wall();
	~Wall();
	void paintFences(Graphics^ g);
	void addFence(Fence* fence);
	short getN();
	Fence* collisionFence(BaseEntity* entity, bool checkWithoutStatusFence = false);
};



