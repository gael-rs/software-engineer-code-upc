#include "Mole.h"

Mole::Mole(short x, short y) : Animal(x, y)
{
	makingHole = comingOutTheHole = false;
}

Mole::~Mole()
{
}

void Mole::paint(Graphics^ g)
{
	Bitmap^ mole = gcnew Bitmap(MOLE_SPRITESHEET);

	width = mole->Width / 5;
	height = mole->Height / 6;

	Rectangle* mold = new Rectangle(column * width, row * height, width, height);
	Rectangle* zoom = new Rectangle(x, y, width, height);

	if (turned) mole->RotateFlip(RotateFlipType::RotateNoneFlipX);

	g->DrawImage(mole, *zoom, *mold, GraphicsUnit::Pixel);

	if (!stoped) {
		if (makingHole) {
			if (column == 4) row++;
			column = ((column + 1) % 5);

			if (row == 3 && column == 3) column = 1;
		}
		else if (comingOutTheHole) {
			if (column == 4) row++;
			column = ((column + 1) % 5);

			if (row == 4 && column == 3) comingOutTheHole = false;
		}
		else if (eating) {
			if (column == 4) row++;
			column = ((column + 1) % 5);

			if (row == 5 && column == 2) {
				column = 4;
				row = 4;
			};
		}
		else {
			row = 0;
			column = ((column + 1) % 5);
		}
	}


	delete zoom;
	delete mold;
	delete mole;
}

bool Mole::getMakingHole()
{
	return makingHole;
}

void Mole::setMakingHole(bool makingHole)
{
	this->makingHole = makingHole;
}

void Mole::makeHole()
{
	if (makingHole) return;
	makingHole = true;
	column = 0;
	row = 1;
}

bool Mole::actionForCollisionWall()
{
	makeHole();
	return false;
}

Rectangle* Mole::getRectangle()
{
	short x = this->x + dx - width;
	if (!eated) {
		if (makingHole) x = this->x + dx;
		if (comingOutTheHole) x = this->x + dx;
		if (eating) x = this->x;
		if (objective < 0) x = this->x;
	}
	else {
		x = this->x + dx + width;
	}

	return new Rectangle(x, y, width, height);
}

void Mole::eat()
{
	if (!stoped) {
		if (!comingOutTheHole && !eating) {
			makingHole = false;
			comingOutTheHole = true;
			eating = true;
			column = 2;
			row = 3;
		}
		if (!comingOutTheHole && eating && dx != 0) {
			column = 4;
			row = 4;
			dx = 0;
		}
	}
}

