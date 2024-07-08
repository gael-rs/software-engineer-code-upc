#pragma once
#include "AnimateEntity.h"

class Animal : public AnimateEntity
{
protected:
	bool eating, eated, crashed, lighted, stoped, chasedAway;
	short objective, columnGarden;
	clock_t timeLighting;
	clock_t timeCrashed;

public:
	Animal(short x = 0, short y = 0);
	~Animal();
	void move(Graphics^ g);
	bool getEating();
	void stop();	
	void play();
	void setEating(bool eating);
	bool getCrashed();
	void setCrashed(bool crashed);
	bool getLighted();
	void setLighted(bool lighted);
	short getObjetive();
	clock_t getTimeLighting();
	short getSecondsSinceLighting();
	short getSecondsSinceCrashed();
	short getColumnGarden();
	bool getChasedAway();
	void setChasedAway(bool chasedAway);
	void setTimeLighting(clock_t timeLighting);
	void setTimeCrashed(clock_t timeCrashed);
	void setObjective(short objective);
	void setColumnGarden(short columnGarden);
	short getEated();
	void setEated(bool eated);
	virtual bool actionForCollisionWall();
	virtual void eat();
};
