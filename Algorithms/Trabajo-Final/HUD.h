#pragma once
#include "Sequence.h"

class HUD
{
private:
	Sequence* sequenceFarmerAllied;
	string messageFarmerAllied;
	clock_t timeOfPlay, time, timeStartPaused, timePaused, timeActual;
	bool stoped;

public:
	HUD();
	~HUD();

	clock_t getTime();
	short* getSeconds();
	short* getMinutes();
	bool checkTimeFinish();
	void setTime(clock_t time);
	void paintInfo(Graphics^ g, MomentPlay momentPlay, short money);
	void paintTime(Graphics^ g);
	void paintIndicator(Graphics^ g, MomentPlay momentPlay);
	void paintFarmerAllied(Graphics^ g);
	void talkFarmerAllied(string messageFarmerAllied);
	void paintMoney(Graphics^ g, short money);
	void play();
	void stop();
	void initialize(Difficult difficult);
};

