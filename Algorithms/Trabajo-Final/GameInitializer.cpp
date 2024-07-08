#include "GameInitializer.h"

GameInitializer::GameInitializer()
{
	buttonBack = nullptr;
	inputName = new CustomInput(0, 0, 242, 81, 28.5);
	combo = new CustomCombo(0, 0, 242, 81, 28.5);

	buttonStartGame = new CustomButton("¡A jugar!", BUTTON_PATH);
	gameController = new GameController();

	combo->addItem(new string("Normal"));
	combo->addItem(new string("Difícil"));
}

GameInitializer::~GameInitializer()
{
	delete inputName;
	delete combo;
	delete buttonStartGame;
	delete gameController;
}

void GameInitializer::chooseConfigurator(Graphics^ g)
{
	const short ESPACIADO = 75;
	Bitmap^ bitmap = gcnew Bitmap(BACKGROUND_GAME_INITIALIZER_PATH);

	Rectangle* mold = new Rectangle(0, 0, bitmap->Width, bitmap->Height);
	Rectangle* zoom = new Rectangle(0, 0, g->VisibleClipBounds.Width, g->VisibleClipBounds.Height);

	g->DrawImage(bitmap, *zoom, *mold, GraphicsUnit::Pixel);

	Font^ font = getFont(28.5);
	String^ text = "Configuración de partida";
	SizeF^ textSize = g->MeasureString(text, font);


	g->DrawString(text, font, Brushes::White,
		(g->VisibleClipBounds.Width - textSize->Width) / 2
		, 85);


	text = "Nombre: ";
	textSize = g->MeasureString(text, font);


	Point* puntoReferencia = new Point(
		g->VisibleClipBounds.Width / 2,
		g->VisibleClipBounds.Height / 2
	);

	short* x = new short;
	*x = (puntoReferencia->X - textSize->Width * 17.5 / 10);

	g->DrawString(text, font, Brushes::White,
		*x,
		(puntoReferencia->Y - textSize->Height * 16.5 / 10)
	);

	text = "Dificultad: ";
	textSize = g->MeasureString(text, font);

	g->DrawString(text, font, Brushes::White,
		*x,
		(puntoReferencia->Y + textSize->Height * 13 / 10)
	);

	inputName->setX(
		puntoReferencia->X + inputName->getWidth() * 1 / 3
	);

	inputName->setY(
		puntoReferencia->Y - inputName->getHeight() - 5
	);

	combo->setX(inputName->getX() - 15);
	combo->setY(
		puntoReferencia->Y + combo->getHeight() - 31
	);

	buttonBack->setX(g->VisibleClipBounds.Width / 3 - buttonBack->getWidth() / 2);
	buttonBack->setY(g->VisibleClipBounds.Height - buttonBack->getHeight() - 50);

	buttonStartGame->setInScreen(true);
	buttonBack->setInScreen(true);

	inputName->paint(g);
	combo->paint(g);
	buttonStartGame->paint(g, true);
	buttonBack->paint(g);

	delete bitmap;
	delete mold;
	delete zoom;
	delete font;
	delete text;
	delete textSize;
	delete puntoReferencia;
	delete x;
}

void GameInitializer::handleInput(char value)
{
	if (inputName->getFocus()) {
		string* text = new string;
		*text = inputName->getText();

		if (value == short(ConsoleKey::Backspace)) {
			if (text->size() > 0) text->pop_back();
		}
		else *text += string(1, value);

		inputName->setText(*text);

		buttonStartGame->setEnabled(text->size() > 0);
		delete text;
	}
}

bool GameInitializer::focusInput(Point point)
{
	bool checkFocus = inputName->getRectangle()->Contains(point);
	if (checkFocus && !inputName->getFocus()) {
		inputName->setFocus(true);
		return true;
	}
	if (inputName->getFocus() && !checkFocus) {
		inputName->setFocus(false);
		return true;
	}
	return false;
}

bool GameInitializer::hoverInput(Point point)
{
	return inputName->getRectangle()->Contains(point);
}

bool GameInitializer::clickCombo(Point point)
{
	bool comboClicked = combo->click(point);
	return comboClicked;
}

bool GameInitializer::hoverCombo(Point point)
{
	return combo->getRectangleAll()->Contains(point);
}

void GameInitializer::initializeButtons(Graphics^ g, Bitmap^ backgroundButton)
{
	buttonStartGame->setX(3 * g->VisibleClipBounds.Width / 4 - backgroundButton->Width / 3);
	buttonStartGame->setY(g->VisibleClipBounds.Height - backgroundButton->Height - 50);

	buttonStartGame->setWidth(backgroundButton->Width / 3);
	buttonStartGame->setHeight(backgroundButton->Height);

	buttonStartGame->setEnabled(false);
}

bool GameInitializer::clickButtonStart(Graphics^ g, Point point)
{
	if (buttonStartGame->getInScreen() && buttonStartGame->getEnabled()) {
		bool clicked = buttonStartGame->getRectangle()->Contains(point);
		if (clicked) {
			buttonStartGame->click(g);
			buttonBack->setInScreen(false);
			buttonStartGame->setInScreen(false);
			gameController->startLevel(g, inputName->getText(), combo->getSelected());
		}
		return clicked;
	}
	return false;
}

bool GameInitializer::hoverButtonStart(Graphics^ g, Point point)
{
	bool hovered = buttonStartGame->getRectangle()->Contains(point);

	if (hovered) buttonStartGame->hover(g);
	else if (buttonStartGame->getHovered()) {
		buttonStartGame->setHovered(false);
		buttonStartGame->paint(g);
	}
	else if (buttonStartGame->getClicked()) {
		buttonStartGame->setClicked(false);
		buttonStartGame->paint(g);
	}

	return hovered;
}

void GameInitializer::setButtonBack(CustomButton* buttonBack)
{
	gameController->setButtonBack(buttonBack);
	this->buttonBack = buttonBack;
}

GameController* GameInitializer::getGameController()
{
	return gameController;
}

bool GameInitializer::getRunned()
{
	return false;
}

