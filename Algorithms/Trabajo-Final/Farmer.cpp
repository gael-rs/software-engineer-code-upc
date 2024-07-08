#include "Farmer.h"

Farmer::Farmer(short x, short y) : AnimateEntity(x, y)
{
	scale = 0.75;
	flashLight = new FlashLight();
	row = 8;
	dx = 2;
	dy = 2;
	money = 0;
	sequenceKeySale = new Sequence(4, 1, KEY_E_PATH, 0.6);
	sequenceKeyBuy = new Sequence(4, 1, KEY_Q_PATH, 0.6);
}

Farmer::~Farmer()
{
	delete flashLight;
	delete sequenceKeyBuy;
	delete sequenceKeySale;
}

void Farmer::move(Rectangle* space, Direction direction)
{
	dx = 2;
	dy = 2;

	if (direction == Direction::Up && y - dy >= space->Y) {
		row = flashLight->getStatusOn() ? 4 : 10;
		turned = false;
		y -= dy;
		flashLight->setY(y - 28);
		flashLight->setX(x - 5);
		flashLight->setDirection(Direction::Up);
	}
	if (direction == Direction::Down && y + dy + height < space->Y + space->Height) {
		row = flashLight->getStatusOn() ? 3 : 9;
		turned = false;
		y += dy;
		flashLight->setY(y + height - 8);
		flashLight->setX(x + 10);
		flashLight->setDirection(Direction::Down);
	}
	if (direction == Direction::Left && x - dx >= space->X + 48 * 1.25 + 8) {
		row = flashLight->getStatusOn() ? 5 : 11;
		turned = true;
		x -= dx;
		flashLight->setX(x - width + 14);
		flashLight->setY(y + 8);
		flashLight->setDirection(Direction::Left);
	}
	if (direction == Direction::Right && x + dx + width < space->X + space->Width) {
		row = flashLight->getStatusOn() ? 5 : 11;
		turned = false;
		x += dx;
		flashLight->setX(x + width - 8);
		flashLight->setY(y + 8);
		flashLight->setDirection(Direction::Right);
	}



}

void Farmer::paint(Graphics^ g)
{
	Bitmap^ farmer = gcnew Bitmap(FRAMER_SPRITESHEET);
	width = farmer->Width / 4;
	height = farmer->Height / 12;

	Rectangle* mold = new Rectangle(column * width, row * height, width, height);
	width *= scale;
	height *= scale;

	Rectangle* zoom = new Rectangle(x, y, width, height);


	if (turned) farmer->RotateFlip(RotateFlipType::RotateNoneFlipX);
	g->DrawImage(farmer, *zoom, *mold, GraphicsUnit::Pixel);

	column = (column + 1) % 4;

	if (flashLight->getStatusOn()) flashLight->paint(g);

	sequenceKeySale->paint(g);
	sequenceKeyBuy->paint(g);

	delete farmer;
	delete mold;
	delete zoom;
}

void Farmer::stop()
{
	dx = 0;
	dy = 0;
	// Arriba
	if (row == 4 || row == 10) row = flashLight->getStatusOn() ? 1 : 7;
	// Abajo
	if (row == 3 || row == 9) row = flashLight->getStatusOn() ? 0 : 6;
	if (row == 11 || row == 5) {
		// Izquierda
		if (turned) row = flashLight->getStatusOn() ? 2 : 8;
		// Derecha
		else row = flashLight->getStatusOn() ? 2 : 8;
	}
}

short Farmer::getMoney()
{
	return money;
}

void Farmer::setMoney(short money)
{
	this->money = money;
}

FlashLight* Farmer::getFlashLight()
{
	return flashLight;
}

void Farmer::changeStatusFlashLight()
{
	if (row == 4 || row == 10) row = flashLight->getStatusOn() ? 4 : 10;
	if (row == 3 || row == 9) row = flashLight->getStatusOn() ? 3 : 9;
	if (row == 2 || row == 5) row = flashLight->getStatusOn() ? 2 : 5;

	if (row == 1 || row == 7) row = flashLight->getStatusOn() ? 1 : 7;
	// Abajo
	if (row == 0 || row == 6) row = flashLight->getStatusOn() ? 0 : 6;
	if (row == 2 || row == 8) {
		// Izquierda
		if (turned) row = flashLight->getStatusOn() ? 2 : 8;
		// Derecha
		else row = flashLight->getStatusOn() ? 2 : 8;
	}
}

void Farmer::action(ActionFarmer actionFarmer)
{
	sequenceKeyBuy->setPlay(false);
	sequenceKeySale->setPlay(false);

	if (ActionFarmer::KeyForBuy == actionFarmer) {
		sequenceKeyBuy->setPlay(true);
	}

	if (ActionFarmer::KeyForSale == actionFarmer) {
		sequenceKeySale->setPlay(true);
	}
}

Sequence* Farmer::getSequenceKeySale()
{
	return sequenceKeySale;
}

Sequence* Farmer::getSequenceKeyBuy()
{
	return sequenceKeyBuy;
}

void Farmer::animationLeave(Graphics^ g)
{
	y = g->VisibleClipBounds.Height - 64 * scale - g->VisibleClipBounds.Height * 3 / 26;

	if (x + dx <= (g->VisibleClipBounds.Width - width) / 2) {
		row = 11;
		x += dx;
	}
	else {
		row = 8;
		dx = 0;
	}
}

float Farmer::getScale()
{
	return scale;
}

void Farmer::setScale(float scale)
{
	this->scale = scale;
}

