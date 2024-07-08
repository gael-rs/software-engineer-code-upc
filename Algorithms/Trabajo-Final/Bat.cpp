#include "Bat.h"

Bat::Bat(short x, short y) : Animal(x, y)
{
}

Bat::~Bat()
{
}

void Bat::paint(Graphics^ g)
{
	Bitmap^ bat = gcnew Bitmap(BAT_SPRITESHEET);

	width = bat->Width / 8;
	height = bat->Height / 1;

	Rectangle* mold = new Rectangle(column * width, row * height, width, height);
	Rectangle* zoom = new Rectangle(x, y - 1, width / 2, height / 2);

	if (turned) bat->RotateFlip(RotateFlipType::RotateNoneFlipX);

	g->DrawImage(bat, *zoom, *mold, GraphicsUnit::Pixel);

	if (!stoped) column = ((column + 1) % 8);

	delete zoom;
	delete mold;
	delete bat;
}

void Bat::eat()
{
	Animal::eat();
	if (!stoped) {
		row = 0;
		x += dx / 2;
	}
}

