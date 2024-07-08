#include "Wall.h"

Wall::Wall()
{
	fences = new vector<Fence*>;
}

Wall::~Wall()
{
	delete fences;
}

void Wall::paintFences(Graphics^ g)
{
	for (short i = 0; i < fences->size(); i++) {
		fences->at(i)->paint(g);
	}
}

void Wall::addFence(Fence* fence)
{
	fences->push_back(fence);
}

short Wall::getN()
{
	return fences->size();
}

Fence* Wall::collisionFence(BaseEntity* entity, bool checkWithoutStatusFence)
{
	for (short i = 0; i < fences->size(); i++)
	{
		if ((checkWithoutStatusFence || fences->at(i)->getColumn() < 3) && fences->at(i)->collision(entity)) return fences->at(i);
	}

	return nullptr;
}

