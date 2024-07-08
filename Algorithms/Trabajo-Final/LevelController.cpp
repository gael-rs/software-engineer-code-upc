#include "LevelController.h"

LevelController::LevelController(Difficult difficult)
{
	this->buttonBack = nullptr;
	this->namePlayer = "";
	this->difficult = difficult;
	this->winned = false;
	this->losed = false;
	this->finished = false;
	map = new Map();
	statistics = new Statistics();
}

LevelController::~LevelController()
{
	delete map;
	delete statistics;
}

void LevelController::paintLevel(Graphics^ g)
{
	if (winned || losed) {
		finishBg(g);
		if (!finished) map->getFarm()->getFarmer()->setX(0);

		map->getFarm()->getFarmer()->setDx(12);
		map->getFarm()->getFarmer()->setScale(3.0);
		map->getFarm()->getFarmer()->action(Nothing);
		map->getFarm()->getFarmer()->animationLeave(g);
		map->getFarm()->getFarmer()->paint(g);
		finished = true;
	}
	if (winned) return this->win(g);
	if (losed) return this->lose(g);

	if (!finished) {
		map->paintEverything(g);
		checkWin(g);
		checkLose(g);
	}

}

void LevelController::moveLevel(Graphics^ g, Direction direction)
{
	if (!finished) map->moveEverything(g, direction);
}

void LevelController::moveLevel(Graphics^ g)
{
	if (!finished) map->moveEverything(g);
}

void LevelController::handleKeyUp(ActionFarmer actionFarmer)
{
	if (!finished) {
		map->checkActionAfterKeyUp(actionFarmer);
		map->stopEverythingAfterKeyUp();
	}
}

void LevelController::handleClick(Graphics^ g, Point point)
{
	if (!finished) {
		map->handleClick(g, point);
	}
}

void LevelController::handleActionFarmer(ActionFarmer actionFarmer)
{
	if (!finished) {
		map->handleActionFarmer(actionFarmer);
	}
}

void LevelController::start(Graphics^ g, string namePlayer)
{
	this->namePlayer = namePlayer;
	statistics->openFile();
	map->initialize(g, namePlayer, difficult);
}

void LevelController::checkWin(Graphics^ g)
{
	bool win = map->checkWin();
	if (win) winned = true;
}

void LevelController::checkLose(Graphics^ g)
{
	bool lose = map->checkLose();
	if (lose) losed = true;
}

void LevelController::win(Graphics^ g)
{
	LevelInfo li = statistics->getLevelInfo();
	li.moneyFarmer = map->getFarm()->getFarmer()->getMoney();
	li.name = namePlayer.c_str();
	statistics->save(li);
}

void LevelController::lose(Graphics^ g)
{
	LevelInfo li = statistics->getLevelInfo();

	li.moneyFarmer = map->getFarm()->getFarmer()->getMoney();
	li.name = namePlayer.c_str();
	statistics->save(li);
}

void LevelController::finishBg(Graphics^ g)
{
	Bitmap^ bg = gcnew Bitmap(BG_GAME_FINISH);

	Rectangle* mold = new Rectangle(0, 0, bg->Width, bg->Height);
	Rectangle* zoom = new Rectangle(0, 0, g->VisibleClipBounds.Width, g->VisibleClipBounds.Height);

	g->DrawImage(bg, *zoom, *mold, GraphicsUnit::Pixel);

	sendMessage(g);

	if (buttonBack != nullptr) {
		buttonBack->setInScreen(true);
		buttonBack->setX((g->VisibleClipBounds.Width - buttonBack->getWidth()) / 2);
		buttonBack->setY((g->VisibleClipBounds.Height - buttonBack->getHeight() * 1.5));
		buttonBack->paint(g);
	}
	delete bg;
	delete zoom;
	delete mold;
}

void LevelController::sendMessage(Graphics^ g)
{
	Font^ font = getFont(85.5);
	String^ message = gcnew String(losed ? "Perdiste :(" : "¡Ganaste!");
	SizeF^ messageSize = g->MeasureString(message, font);

	g->DrawString(message, font, Brushes::WhiteSmoke,
		(g->VisibleClipBounds.Width - messageSize->Width) / 2,
		(g->VisibleClipBounds.Height * 4.8 / 31)
	);

	delete message;
	delete font;
	delete messageSize;
}

void LevelController::setButtonBack(CustomButton* buttonBack)
{

	this->buttonBack = buttonBack;
}
