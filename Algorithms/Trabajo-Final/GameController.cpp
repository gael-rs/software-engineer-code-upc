#include "GameController.h"

GameController::GameController()
{
	this->namePlayer = "";
	this->difficult = 0;
	runned = false;
	levelNormal = new LevelController(Difficult::Normal);
	levelHard = new LevelController(Difficult::Hard);
}

GameController::~GameController()
{
	delete levelNormal;
	delete levelHard;
}

void GameController::startLevel(Graphics^ g, string namePlayer, short difficult)
{
	this->namePlayer = namePlayer;
	this->difficult = difficult;
	getLevel()->start(g, namePlayer);
	runned = true;
}

void GameController::showGame(Graphics^ g)
{
	LevelController* level = getLevel();

	level->moveLevel(g);
	level->paintLevel(g);
}

void GameController::handleDirection(Graphics^ g, Direction direction)
{
	LevelController* level = getLevel();

	level->moveLevel(g, direction);
}

void GameController::handleKeyUp(ActionFarmer actionFarmer)
{
	LevelController* level = getLevel();

	level->handleKeyUp(actionFarmer);
}

void GameController::handleClick(Graphics^ g, Point point)
{
	LevelController* level = getLevel();

	level->handleClick(g, point);
}

void GameController::handleActionFarmer(ActionFarmer actionFarmer)
{
	LevelController* level = getLevel();

	level->handleActionFarmer(actionFarmer);
}

LevelController* GameController::getLevel()
{
	if (difficult == 0) return levelNormal;
	return levelHard;
}

bool GameController::getRunned() {
	return runned;
}

void GameController::setButtonBack(CustomButton* buttonBack)
{
	this->buttonBack = buttonBack;
	getLevel()->setButtonBack(buttonBack);
}

CustomButton* GameController::getButtonBack()
{
	return buttonBack;
}
