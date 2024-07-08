#include "AnimateEntity.h"

AnimateEntity::AnimateEntity(short x, short y) : BaseEntity(x, y)
{
	turned = false;
}

AnimateEntity::~AnimateEntity()
{
}

bool AnimateEntity::getTurned()
{
	return turned;
}

void AnimateEntity::setTurned(bool turned)
{
	this->turned = turned;
}
