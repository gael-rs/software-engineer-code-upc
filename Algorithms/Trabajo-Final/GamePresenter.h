#pragma once
#include "GameInitializer.h"
#include "CustomButton.h"
#include "Sequence.h"

class GamePresenter
{
private:
	GameInitializer* gameInitiliazer;
	int gapButtonMenu;
	CustomButton** buttons;
	CustomButton* buttonBack;
	Sequence** sequencesInstructions;
	Sequence** sequencesCredits;
	Sequence* sequenceExit;

	bool isShowedMenu, isShowedInstruccions, isShowedCredits, isShowedExit, isShowedInitialGame;

public:
	GamePresenter();
	~GamePresenter();

	void showLogo(Graphics^ g);
	void showCredits(Graphics^ g);
	void showMenu(Graphics^ g);
	void showExit(Graphics^ g);
	void showTitle(Graphics^ g);
	void showInstruccions(Graphics^ g);
	void showGameInitializer(Graphics^ g);
	void showMessageExit(Graphics^ g);

	void initializeButtons(Graphics^ g);
	bool chooseButton(Graphics^ g, Point pointClicked);
	bool hoverButton(Graphics^ g, Point pointClicked);
	bool hoverButtonBack(Graphics^ g, Point pointClicked);
	bool clickButtonBack(Graphics^ g, Point pointClicked);

	void paintSequences(Graphics^ g);

	Sequence* getSequenceExit();
	GameInitializer* getGameInitializer();

	bool getIsShowedMenu();
	void setIsShowedMenu(bool isShowedMenu);
	bool getIsShowedInstruccions();
	void setIsShowedInstruccions(bool isShowedInstruccions);
	bool getIsShowedCredits();
	void setIsShowedCredits(bool isShowedCredits);
	bool getIsShowedExit();
	void setIsShowedExit(bool isShowedExit);
	bool getIsShowedInitialGame();
	void setIsShowedInitialGame(bool isShowedInitialGame);
};

