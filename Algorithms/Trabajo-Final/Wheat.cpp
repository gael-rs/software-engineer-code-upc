#include "Wheat.h"

Wheat::Wheat() : Vegetable()
{
	name = "wheat";
	price = 7;
	growthInterval = 7;
	timeToBeEaten = 6;
	salePrice = 14;
}

Wheat::~Wheat()
{
}

void Wheat::paintSeed(Graphics^ g)
{
	Bitmap^ wheat = gcnew Bitmap(WHEAT_SEED);
	width = wheat->Width;
	height = wheat->Height;

	Rectangle* mold = new Rectangle(0, 0, width, height);
	Rectangle* zoom = new Rectangle(x, y, width, height);

	g->DrawImage(wheat, *zoom, *mold, GraphicsUnit::Pixel);

	delete wheat;
	delete mold;
	delete zoom;
}

void Wheat::paintPlant(Graphics^ g)
{
	Bitmap^ wheat = gcnew Bitmap(WHEAT_PLANT);
	width = wheat->Width / 3;
	height = wheat->Height;

	Rectangle* mold = new Rectangle(column * width, row * height, width, height);
	Rectangle* zoom = new Rectangle(x, y, g->VisibleClipBounds.Width * 2 / 40,
		g->VisibleClipBounds.Height * 2 / 31);

	width = zoom->Width;
	height = zoom->Height;

	g->DrawImage(wheat, *zoom, *mold, GraphicsUnit::Pixel);

	delete wheat;
	delete mold;
	delete zoom;
}

void Wheat::paintHarvest(Graphics^ g)
{
	bool change = width < 0;

	Bitmap^ wheat = gcnew Bitmap(WHEAT_HARVEST);
	width = wheat->Width;
	height = wheat->Height;

	Rectangle* mold = new Rectangle(0, 0, width, height);

	if (!change) {
		width *= 0.75;
		height *= 0.75;
	}

	Rectangle* zoom = new Rectangle(x, y, width, height);


	g->DrawImage(wheat, *zoom, *mold, GraphicsUnit::Pixel);

	delete wheat;
	delete mold;
	delete zoom;
}

Rectangle* Wheat::getMeasuresHarvest()
{
	Bitmap^ wheat = gcnew Bitmap(WHEAT_HARVEST);

	Rectangle* rectangle = new Rectangle(x, y, wheat->Width * 0.75, wheat->Height * 0.9);

	delete wheat;
	return rectangle;
}

Wheat* Wheat::clone()
{
	return new Wheat(*this);
}
