#include "GamePresenter.h"

GamePresenter::GamePresenter()
{
	buttonBack = new CustomButton("Volver al menú", BUTTON_PATH);

	gameInitiliazer = new GameInitializer();
	gameInitiliazer->setButtonBack(buttonBack);

	gapButtonMenu = 10;
	isShowedMenu = isShowedInstruccions = isShowedCredits = isShowedInitialGame = isShowedExit = false;

	buttons = new CustomButton * [4];
	buttons[0] = new CustomButton("Jugar", BUTTON_PATH);
	buttons[1] = new CustomButton("Instrucciones", BUTTON_PATH);
	buttons[2] = new CustomButton("Créditos", BUTTON_PATH);
	buttons[3] = new CustomButton("Salir", BUTTON_PATH);


	sequencesInstructions = new Sequence * [4];
	sequencesCredits = new Sequence * [3];

	for (short i = 0; i < 4; i++) sequencesInstructions[i] = nullptr;
	for (short i = 0; i < 3; i++) sequencesCredits[i] = nullptr;

	sequenceExit = new Sequence(3, 11, EXIT_ANIMATION_PATH, 1, Position::CenterY);

}

GamePresenter::~GamePresenter()
{
	delete[] buttons;
	delete buttonBack;
	delete gameInitiliazer;
	delete[] sequencesInstructions;
	delete[] sequenceExit;
	delete[] sequencesCredits;
}

void GamePresenter::showLogo(Graphics^ g)
{
	Bitmap^ bgLogo = gcnew Bitmap(BACKGROUND_LOGO_PATH);
	Bitmap^ logo = gcnew Bitmap(LOGO_PATH);


	g->DrawImage(bgLogo, 0, 0);

	g->DrawImage(logo, short((g->VisibleClipBounds.Width - logo->Width) / 2), short((g->VisibleClipBounds.Height - logo->Height) / 2));

	delete bgLogo;
	delete logo;
}

void GamePresenter::showCredits(Graphics^ g)
{
	buttonBack->setX(g->VisibleClipBounds.Width / 2 - buttonBack->getWidth() / 2);
	buttonBack->setY(g->VisibleClipBounds.Height - 100);

	isShowedCredits = true;
	isShowedInstruccions = false;

	for (short i = 0; i < 4; i++) buttons[i]->setInScreen(false);

	Bitmap^ bgCredits = gcnew Bitmap(BACKGROUND_CREDITS_PATH);

	Font^ font = getFont(30.5);
	String^ text = "Créditos";
	SizeF^ textSize = g->MeasureString(text, font);

	Rectangle* mold = new Rectangle(0, 0, bgCredits->Width, bgCredits->Height);
	Rectangle* zoom = new Rectangle(0, 0, g->VisibleClipBounds.Width, g->VisibleClipBounds.Height);

	g->DrawImage(bgCredits, *zoom, *mold, GraphicsUnit::Pixel);

	g->DrawString(text, font, Brushes::Black,
		(g->VisibleClipBounds.Width - textSize->Width) / 2,
		30);

	font = getFont(19.5);

	string* pathsCredits[3] = { new string(GAEL_ANIMATION_PATH) , new string(ALEJANDRO_ANIMATION_PATH), new string(MARIA_FE_ANIMATION_PATH) };
	string* namesCredits[3] = { new string("Gael Rivera"), new string("Alejandro Oroncoy"), new string("Maria Fe Bojorquez") };
	int* codesCredits[3] = { new int(202312222), new int(202313397), new int(202313071) };

	Point* point;

	short* height = new short;
	*height = 144;

	for (int i = 0; i < 3; i++) {
		if (sequencesCredits[i] == nullptr) {
			sequencesCredits[i] = new Sequence(4, 1, *pathsCredits[i], 1);
			sequencesCredits[i]->setX(i * (g->VisibleClipBounds.Width / 3) + (g->VisibleClipBounds.Width / 6) - 100);
			sequencesCredits[i]->setY(g->VisibleClipBounds.Height / 2 - *height);
			sequencesCredits[i]->setPlay(true);
		}
		else {
			sequencesCredits[i]->setPlay(true);
		}


		text = gcnew String(namesCredits[i]->c_str());
		textSize = g->MeasureString(text, font);

		point = new Point(i * (g->VisibleClipBounds.Width / 3) + (g->VisibleClipBounds.Width / 6) - textSize->Width / 2,
			sequencesCredits[i]->getY() + *height + textSize->Height + 10);

		g->DrawString(text, font, Brushes::Black, *point);

		point->Y += 10 + textSize->Height;

		text = gcnew String("U" + *codesCredits[i]);
		textSize = g->MeasureString(text, font);

		point->X = i * (g->VisibleClipBounds.Width / 3) + (g->VisibleClipBounds.Width / 6) - textSize->Width / 2;

		g->DrawString(text, font, Brushes::Black, *point);
	}


	buttonBack->paint(g, true);

	delete bgCredits;
	delete text;
	delete height;
	delete point;
	delete font;
	delete textSize;
}

void GamePresenter::showMenu(Graphics^ g)
{
	isShowedInstruccions = false;
	isShowedCredits = false;
	isShowedMenu = true;

	Bitmap^ bgMenu = gcnew Bitmap(BACKGROUND_PATH);

	Rectangle* mold = new Rectangle(0, 0, bgMenu->Width, bgMenu->Height);
	Rectangle* zoom = new Rectangle(0, 0, g->VisibleClipBounds.Width, g->VisibleClipBounds.Height);

	g->DrawImage(bgMenu, *zoom, *mold, GraphicsUnit::Pixel);

	showTitle(g);

	for (int i = 0; i < 3; i++) {
		if (sequencesCredits[i] != nullptr)	sequencesCredits[i]->setPlay(false);
	}
	for (int i = 0; i < 4; i++) {
		buttons[i]->setInScreen(true);
		buttons[i]->setClicked(false);
		buttons[i]->setHovered(false);
		buttons[i]->paint(g);
	}

	delete bgMenu;
	delete mold;
	delete zoom;
}

void GamePresenter::showExit(Graphics^ g)
{
	// TODO: Show exit
	Bitmap^ bgExit = gcnew Bitmap(BACKGROUND_EXIT_PATH);

	Rectangle* mold = new Rectangle(0, 0, bgExit->Width, bgExit->Height);
	Rectangle* zoom = new Rectangle(0, 0, g->VisibleClipBounds.Width, g->VisibleClipBounds.Height);

	g->DrawImage(bgExit, *zoom, *mold, GraphicsUnit::Pixel);

	if (!sequenceExit->getPlay()) {
		sequenceExit->setLoop(false);
		sequenceExit->setPlay(true);
	}

	for (int i = 0; i < 4; i++) buttons[i]->setInScreen(false);

	delete bgExit;
	delete mold;
	delete zoom;
}

void GamePresenter::showTitle(Graphics^ g)
{
	Bitmap^ title = gcnew Bitmap(TITLE_PATH);

	g->DrawImage(title, int((g->VisibleClipBounds.Width - title->Width) / 2), 60);
}


void GamePresenter::showInstruccions(Graphics^ g)
{
	buttonBack->setX(g->VisibleClipBounds.Width / 2 - buttonBack->getWidth() / 2);
	buttonBack->setY(g->VisibleClipBounds.Height - 100);

	Bitmap^ bgInstruccions = gcnew Bitmap(BACKGROUND_INSTRUCTIONS_PATH);

	g->DrawImage(bgInstruccions, 0, 0);

	Font^ font = getFont(21.5);
	String^ title = "I N S T R U C C I O N E S";
	SizeF^ text = g->MeasureString(title, font);

	g->DrawString(title, font, Brushes::Black,
		(g->VisibleClipBounds.Width - text->Width) / 2,
		30);

	string bitMapInstruccionPath = "";

	font = getFont(14.2);


	for (int i = 0; i < 4; i++) buttons[i]->setInScreen(false);

	for (int i = 0; i < 4; i++) {
		Point pointInstruccion = Point(
			(g->VisibleClipBounds.Width / 2) * i -
			(g->VisibleClipBounds.Width) * (i > 1),
			100 + (g->VisibleClipBounds.Height / 2) * (i > 1) - (i > 1) * 100
		);

		String^ textInstruccion = "";

		SizeF^ textInstrucctionSize = nullptr;

		if (i == 0) {
			bitMapInstruccionPath = INSTRUCTIONS_MOVE_FARMER_PATH;

			textInstruccion = R"(Mueve a tu granjero con A,W,S,D)";
		}

		if (i == 1) {
			bitMapInstruccionPath = FARMER_KEYS_PATH;
			textInstruccion = R"(Compra lo necesario para sobrevivir a la 
noche y ¡hacer crecer tu granja!)";
		}
		if (i == 2) {
			bitMapInstruccionPath = ENEMIGES_PATH;
			textInstruccion = R"(Ten cuidado, los enemigos aparecen
desde la derecha de tu pantalla)";
		}
		if (i == 3) {
			bitMapInstruccionPath = FARMER_HUD;
			textInstruccion = R"(¡Consigue ganar el mayor dinero posible
y sobrevivir cada noche!)";
		}

		textInstrucctionSize = g->MeasureString(textInstruccion, font);
		g->DrawString(textInstruccion, font, Brushes::Black, pointInstruccion.X + 5, pointInstruccion.Y);

		if (textInstrucctionSize != nullptr)
			pointInstruccion.Y += textInstrucctionSize->Height + 20;

		if (sequencesInstructions[i] == nullptr) {
			sequencesInstructions[i] = new Sequence((i == 0)* 28 + (i == 1)*8 + (i == 2)*16 + (i == 3)*7);
			sequencesInstructions[i]->setX(pointInstruccion.X + 50);
			sequencesInstructions[i]->setY(pointInstruccion.Y);
			sequencesInstructions[i]->setPlay(true);
			sequencesInstructions[i]->setSrcBitMap(bitMapInstruccionPath);
		}
		else {
			sequencesInstructions[i]->setPlay(true);
		}

		delete textInstruccion;
		delete textInstrucctionSize;
	}

	buttonBack->setInScreen(true);
	buttonBack->paint(g, true);

	delete bgInstruccions;
	delete font;
	delete title;
	delete text;
}

void GamePresenter::showGameInitializer(Graphics^ g)
{
	// TODO: Initializer
	for (int i = 0; i < 4; i++) buttons[i]->setInScreen(false);

	buttonBack->setInScreen(true);
	gameInitiliazer->chooseConfigurator(g);
}

void GamePresenter::showMessageExit(Graphics^ g)
{
	Font^ font = getFont(25.5);
	String^ message = gcnew String(R"(
Adiós, 
granjero)");

	g->DrawString(message, font, Brushes::Black,
		g->VisibleClipBounds.Width / 2 + 60,
		g->VisibleClipBounds.Height / 2 - 150
	);

	delete font;
	delete message;
}

void GamePresenter::initializeButtons(Graphics^ g)
{
	Bitmap^ btnBackgroundImage = gcnew Bitmap(BUTTON_PATH);

	short x = g->VisibleClipBounds.Width - short(btnBackgroundImage->Width / 6) - 150,
		y = (g->VisibleClipBounds.Height) / 2 - short(btnBackgroundImage->Height);

	for (short i = 0; i < 4; i++) {
		buttons[i]->setX(x);
		buttons[i]->setY(y + i * (btnBackgroundImage->Height + gapButtonMenu));
		buttons[i]->setWidth(btnBackgroundImage->Width / 3);
		buttons[i]->setHeight(btnBackgroundImage->Height);
	}

	buttonBack->setX(g->VisibleClipBounds.Width / 2 - btnBackgroundImage->Width / 6);
	buttonBack->setY(g->VisibleClipBounds.Height - 100);
	buttonBack->setWidth(btnBackgroundImage->Width / 3);
	buttonBack->setHeight(btnBackgroundImage->Height);

	gameInitiliazer->initializeButtons(g, btnBackgroundImage);

	delete btnBackgroundImage;
}

bool GamePresenter::chooseButton(Graphics^ g, Point pointClicked)
{
	for (short i = 0; i < 4; i++) {

		if (!buttons[i]->getInScreen()) return  false;
		bool isBtnClicked = buttons[i]->getRectangle()->Contains(pointClicked);

		if (isBtnClicked) {
			buttons[i]->click(g);

			isShowedMenu = false;
			switch (i + 1)
			{
			case 1:
				isShowedInitialGame = true;
				isShowedInstruccions = false;
				isShowedExit = false;
				isShowedCredits = false;
				showGameInitializer(g);
				break;
			case 2:
				isShowedInstruccions = true;
				isShowedCredits = false;

				break;
			case 3:
				isShowedInstruccions = false;
				isShowedCredits = true;
				buttonBack->setInScreen(true);

				showCredits(g);

				break;
			case 4:
				isShowedExit = true;
				isShowedInstruccions = false;
				isShowedCredits = false;

				break;
			default:
				break;
			}

			return true;
		}
	}
	return false;
}

bool GamePresenter::hoverButton(Graphics^ g, Point pointClicked)
{

	for (int i = 0; i < 4; i++) {
		if (buttons[i]->getInScreen()) {
			bool isBtnHovered = buttons[i]->getRectangle()->Contains(pointClicked);

			if (isBtnHovered) {
				buttons[i]->hover(g);
				return true;
			}

			if (buttons[i]->getHovered()) {
				buttons[i]->setHovered(false);
				buttons[i]->paint(g);
			};
		}
	}

	bool isBtnHovered = hoverButtonBack(g, pointClicked);

	return isBtnHovered;
}

bool GamePresenter::hoverButtonBack(Graphics^ g, Point pointClicked) {
	bool isBtnHovered = false;
	if (buttonBack->getInScreen() && buttonBack->getEnabled()) {
		isBtnHovered = buttonBack->getRectangle()->Contains(pointClicked);
		if (isBtnHovered) buttonBack->hover(g);
		else if (buttonBack->getHovered()) {
			buttonBack->setHovered(false);
			buttonBack->paint(g);
		}
	}
	return isBtnHovered;
}

bool GamePresenter::clickButtonBack(Graphics^ g, Point pointClicked)
{
	if (buttonBack->getInScreen() && buttonBack->getEnabled()) {
		bool isBtnClicked = buttonBack->getRectangle()->Contains(pointClicked);

		if (isBtnClicked) {
			buttonBack->click(g);
			isShowedInitialGame = false;
			isShowedInstruccions = false;
			isShowedExit = false;
			isShowedCredits = false;
			isShowedMenu = true;
			buttonBack->setInScreen(false);
			buttonBack->setHovered(false);
			buttonBack->setClicked(false);
			for (short i = 0; i < 4; i++) {
				if (sequencesInstructions[i] != nullptr) sequencesInstructions[i]->setPlay(false);
			}
			for (short i = 0; i < 3; i++) {
				if (sequencesCredits[i] != nullptr) sequencesCredits[i]->setPlay(false);
			}
			return true;
		}
	}
	return false;
}

void GamePresenter::paintSequences(Graphics^ g)
{
	for (short i = 0; i < 4; i++) {
		if (sequencesInstructions[i] != nullptr && sequencesInstructions[i]->getPlay()) {
			sequencesInstructions[i]->paint(g);
		}
	}

	for (short i = 0; i < 3; i++) {
		if (sequencesCredits[i] != nullptr && sequencesCredits[i]->getPlay()) {
			sequencesCredits[i]->paint(g);
		}
	}
	sequenceExit->paint(g);
}

Sequence* GamePresenter::getSequenceExit()
{
	return sequenceExit;
}

GameInitializer* GamePresenter::getGameInitializer()
{
	return gameInitiliazer;
}


bool GamePresenter::getIsShowedMenu()
{
	return isShowedMenu;
}

void GamePresenter::setIsShowedMenu(bool isShowedMenu)
{
	this->isShowedMenu = isShowedMenu;
}


bool GamePresenter::getIsShowedInstruccions()
{
	return isShowedInstruccions;
}

void GamePresenter::setIsShowedInstruccions(bool isShowedInstruccions)
{
	this->isShowedInstruccions = isShowedInstruccions;
}

bool GamePresenter::getIsShowedCredits()
{
	return isShowedCredits;
}

void GamePresenter::setIsShowedCredits(bool isShowedCredits)
{
	this->isShowedCredits = isShowedCredits;
}

bool GamePresenter::getIsShowedExit()
{
	return isShowedExit;
}

void GamePresenter::setIsShowedExit(bool isShowedExit)
{
	this->isShowedExit = isShowedExit;
}

bool GamePresenter::getIsShowedInitialGame()
{
	return isShowedInitialGame;
}

void GamePresenter::setIsShowedInitialGame(bool isShowedInitialGame)
{
	this->isShowedInitialGame = isShowedInitialGame;
}

