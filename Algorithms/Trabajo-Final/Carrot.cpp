#include "Carrot.h"

Carrot::Carrot() : Vegetable()
{
	name = "carrot";
	price = 3;
	growthInterval = 4;
	timeToBeEaten = 5;
	salePrice = 6;
}

Carrot::~Carrot()
{
}

void Carrot::paintSeed(Graphics^ g)
{
	Bitmap^ carrot = gcnew Bitmap(CARROT_SEED);
	width = carrot->Width;
	height = carrot->Height;

	Rectangle* mold = new Rectangle(0, 0, width, height);
	Rectangle* zoom = new Rectangle(x, y, width, height);

	g->DrawImage(carrot, *zoom, *mold, GraphicsUnit::Pixel);

	delete carrot;
	delete mold;
	delete zoom;
}

void Carrot::paintPlant(Graphics^ g)
{
	Bitmap^ carrot = gcnew Bitmap(CARROT_PLANT);
	width = carrot->Width / 3;
	height = carrot->Height;

	Rectangle* mold = new Rectangle(column * width, row * height, width, height);
	Rectangle* zoom = new Rectangle(x, y, g->VisibleClipBounds.Width * 2 / 40,
		g->VisibleClipBounds.Height * 2 / 31);

	width = zoom->Width;
	height = zoom->Height;

	g->DrawImage(carrot, *zoom, *mold, GraphicsUnit::Pixel);

	delete carrot;
	delete mold;
	delete zoom;
}

void Carrot::paintHarvest(Graphics^ g)
{
	Bitmap^ carrot = gcnew Bitmap(CARROT_HARVEST);
	width = carrot->Width;
	height = carrot->Height;

	Rectangle* mold = new Rectangle(0, 0, width, height);
	Rectangle* zoom = new Rectangle(x, y, width, height);

	g->DrawImage(carrot, *zoom, *mold, GraphicsUnit::Pixel);

	delete carrot;
	delete mold;
	delete zoom;
}

Carrot* Carrot::clone()
{
	return new Carrot(*this);
}