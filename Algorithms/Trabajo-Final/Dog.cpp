#include "Dog.h"

Dog::Dog()
{
	dx = 5;
	dy = 5;
	// price = 35;
	price = 10;
	name = "Perro";
	// Dura 35 segundos
}

Dog::~Dog()
{
}

void Dog::paint(Graphics^ g)
{
	Bitmap^ dog  = gcnew Bitmap(DOG_SPRITESHEET);

	width = dog->Width / 3;
	height = dog->Height / 2;

	Rectangle* mold = new Rectangle(column * width, row * height, width, height);

	width *= scale;
	height *= scale;

	Rectangle* zoom = new Rectangle(x, y, width, height);

	if (turned) dog->RotateFlip(RotateFlipType::RotateNoneFlipX);

	g->DrawImage(dog, *zoom, *mold, GraphicsUnit::Pixel);

	if(!stoped) column = ((column + 1) % 3);

	delete zoom;
	delete mold;
	delete dog;
}

void Dog::move(Rectangle* space)
{
	if (x + dx <= space->X + 48 * 1.25 + 8 || x + width + dx >= space->Width) {
		turned = !turned;
		dx *= -1;
	}

	x += dx;
}

void Dog::paintItem(Graphics^ g)
{
	scale = 1;
	column = 0;
	Bitmap^ dog = gcnew Bitmap(DOG_SPRITESHEET);

	width = dog->Width / 3;
	height = dog->Height / 2;

	Rectangle* mold = new Rectangle(column * width, row * height, width, height);

	width *= scale;
	height *= scale;

	Rectangle* zoom = new Rectangle(x, y, width, height);

	if (turned) dog->RotateFlip(RotateFlipType::RotateNoneFlipX);

	g->DrawImage(dog, *zoom, *mold, GraphicsUnit::Pixel);

	PowerItem::paintItem(g);

	delete zoom;
	delete mold;
	delete dog;
}

BaseEntity* Dog::getEntityPowerItem()
{
	return this;
}

void Dog::paintPreview(Graphics^ g, short moneyFarmer)
{
	paint(g);
	PowerItem::paintPreview(g, moneyFarmer);
}

PowerItem* Dog::clone()
{
	return new Dog(*this);
}

void Dog::bark()
{
	row = 1;
	dx = 0;
}

