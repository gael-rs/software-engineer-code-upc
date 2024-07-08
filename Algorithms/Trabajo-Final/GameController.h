#pragma once
#include "LevelController.h"

class GameController
{
private:
	string namePlayer;
	short difficult;
	LevelController* levelNormal;
	LevelController* levelHard;
	bool runned;
	CustomButton* buttonBack;

public:
	GameController();
	~GameController();
	void startLevel(Graphics^ g, string namePlayer, short difficult);
	void showGame(Graphics^ g);
	void handleDirection(Graphics^ g, Direction direction);
	void handleKeyUp(ActionFarmer actionFarmer);
	void handleClick(Graphics^ g, Point point);
	void handleActionFarmer(ActionFarmer actionFarmer);
	LevelController* getLevel();
	bool getRunned();
	void setButtonBack(CustomButton* buttonBack);
	CustomButton* getButtonBack();
};


