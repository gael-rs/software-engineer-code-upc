#pragma once
#include "HUD.h"
#include "Inventory.h"
#include "Hud.h"
#include "Farm.h"
#include "QuestionGenerator.h"

class Map
{
private:
	MomentPlay momentPlay;
	Inventory* inventory;
	HUD* hud;
	Farm* farm;
	QuestionGenerator* questionGenerator;
	bool stoped;
	short moneyGoal;

public:
	Map();
	~Map();
	void paintEverything(Graphics^ g);
	void moveEverything(Graphics^ g, Direction direction);
	void moveEverything(Graphics^ g);
	void paintBackground(Graphics^ g);
	void stopEverythingAfterKeyUp();
	void initialize(Graphics^ g, string namePlayer, Difficult difficult);
	void handleClick(Graphics^ g, Point point);
	void checkActionAfterKeyUp(ActionFarmer actionFarmer);
	void handleActionFarmer(ActionFarmer actionFarmer);
	void stop();
	void play();
	bool checkWin();
	bool checkLose();
	Farm* getFarm();
};

