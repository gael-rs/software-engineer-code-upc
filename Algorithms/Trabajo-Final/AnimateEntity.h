#pragma once
#include "BaseEntity.h"

class AnimateEntity : public BaseEntity
{
protected:
	bool turned; 

public:
	AnimateEntity(short x = 0, short y = 0);
	~AnimateEntity();
	bool getTurned();
	void setTurned(bool turned);
	virtual void move() {};
};


