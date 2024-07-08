#include "Racoon.h"


Racoon::Racoon(short x, short y) : Animal(x, y)
{
}

Racoon::~Racoon()
{
}

void Racoon::paint(Graphics^ g)
{
	Bitmap^ raccon = gcnew Bitmap(RACCOON_SPRITESHEET);

	width = raccon->Width / 3;
	height = raccon->Height / 2;

	Rectangle* mold = new Rectangle(column * width, row * height, width, height);
	Rectangle* zoom = new Rectangle(x, y, width, height);

	if (turned) raccon->RotateFlip(RotateFlipType::RotateNoneFlipX);

	g->DrawImage(raccon, *zoom, *mold, GraphicsUnit::Pixel);

	row = eating ? 1 : 0;

	if (!stoped) column = ((column + 1) % 3);

	delete zoom;
	delete mold;
	delete raccon;
}

void Racoon::eat()
{
	Animal::eat();
	if (!stoped) {
		row = 1;
	}
}
