#pragma once
#include "Map.h"
#include "Statistics.h"
#include "Sequence.h"

class LevelController
{
private:
	Difficult difficult;
	Map* map;
	Statistics* statistics;
	CustomButton* buttonBack;
	string namePlayer;
	bool winned, losed,finished;

public:
	LevelController(Difficult difficult);
	~LevelController();
	void paintLevel(Graphics^ g);
	void moveLevel(Graphics^ g, Direction direction);
	void moveLevel(Graphics^ g);
	void handleKeyUp(ActionFarmer actionFarmer);
	void handleClick(Graphics^ g, Point point);
	void handleActionFarmer(ActionFarmer actionFarmer);
	void start(Graphics^g, string namePlayer);
	void checkWin(Graphics^ g);
	void checkLose(Graphics^ g);
	void win(Graphics^ g);
	void lose(Graphics^ g);
	void finishBg(Graphics^ g);
	void sendMessage(Graphics^ g);
	void setButtonBack(CustomButton* buttonBack);
};

