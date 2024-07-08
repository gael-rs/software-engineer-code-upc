#pragma once
#include "CustomInput.h"
#include "CustomCombo.h"
#include "CustomButton.h"
#include "GameController.h"

class GameInitializer
{
private:
	CustomInput* inputName;
	CustomCombo* combo;
	CustomButton* buttonStartGame;
	CustomButton* buttonBack;
	GameController* gameController;

public:
	GameInitializer();
	~GameInitializer();
	void chooseConfigurator(Graphics^ g);
	void handleInput(char value);
	bool focusInput(Point point);
	bool hoverInput(Point point);
	bool clickCombo(Point point);
	bool hoverCombo(Point point);
	void initializeButtons(Graphics^ g, Bitmap^ backgroundButton);
	bool clickButtonStart(Graphics^ g, Point point);
	bool hoverButtonStart(Graphics^ g, Point point);
	void setButtonBack(CustomButton* buttonBack);
	GameController* getGameController();
	bool getRunned();
};

