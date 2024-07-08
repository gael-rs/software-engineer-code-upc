#include "Pumpkin.h"

Pumpkin::Pumpkin() : Vegetable()
{
	name = "pumpkin";
	price = 9;
	growthInterval = 8;
	timeToBeEaten = 6;
	salePrice = 18;
}

Pumpkin::~Pumpkin()
{
}

void Pumpkin::paintSeed(Graphics^ g)
{
	Bitmap^ pumpkin = gcnew Bitmap(PUMPKIN_SEED);
	width = pumpkin->Width;
	height = pumpkin->Height;

	Rectangle* mold = new Rectangle(0, 0, width, height);
	Rectangle* zoom = new Rectangle(x, y, width, height);

	g->DrawImage(pumpkin, *zoom, *mold, GraphicsUnit::Pixel);

	delete pumpkin;
	delete mold;
	delete zoom;
}

void Pumpkin::paintPlant(Graphics^ g)
{
	Bitmap^ pumpkin = gcnew Bitmap(PUMPKIN_PLANT);
	width = pumpkin->Width / 3;
	height = pumpkin->Height;

	Rectangle* mold = new Rectangle(column * width, row * height, width, height);
	Rectangle* zoom = new Rectangle(x, y + 5, g->VisibleClipBounds.Width * 2 / 40,
		g->VisibleClipBounds.Height * 2 / 31);

	width = zoom->Width;
	height = zoom->Height;

	g->DrawImage(pumpkin, *zoom, *mold, GraphicsUnit::Pixel);

	delete pumpkin;
	delete mold;
	delete zoom;
}

void Pumpkin::paintHarvest(Graphics^ g)
{
	Bitmap^ pumpkin = gcnew Bitmap(PUMPKIN_HARVEST);
	width = pumpkin->Width;
	height = pumpkin->Height;

	Rectangle* mold = new Rectangle(0, 0, width, height);
	Rectangle* zoom = new Rectangle(x, y, width, height);

	g->DrawImage(pumpkin, *zoom, *mold, GraphicsUnit::Pixel);

	delete pumpkin;
	delete mold;
	delete zoom;
}

Pumpkin* Pumpkin::clone()
{
	return new Pumpkin(*this);
}