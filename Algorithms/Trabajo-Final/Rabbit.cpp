#include "Rabbit.h"

Rabbit::Rabbit(short x, short y) : Animal(x, y)
{
	turned = false;
}

Rabbit::~Rabbit()
{
}

void Rabbit::paint(Graphics^ g)
{
	Bitmap^ rabbit = gcnew Bitmap(RABBIT_SPRITESHEET);

	width = rabbit->Width / 4;
	height = rabbit->Height / 2;

	Rectangle* mold = new Rectangle(column * width, row * height, width, height);
	Rectangle* zoom = new Rectangle(x, y, width, height);

	if (turned) rabbit->RotateFlip(RotateFlipType::RotateNoneFlipX);

	g->DrawImage(rabbit, *zoom, *mold, GraphicsUnit::Pixel);

	row = eating ? 1 : 0;
	if(!stoped) column = ((column + 1) % 4);

	delete zoom;
	delete mold;
	delete rabbit;
}

void Rabbit::eat()
{
	Animal::eat();
	if(!stoped) row = 1;
}
