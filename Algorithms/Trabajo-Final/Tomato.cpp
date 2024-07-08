#include "Tomato.h"

Tomato::Tomato() : Vegetable()
{
	name = "tomato";
	price = 5;
	growthInterval = 5;
	timeToBeEaten = 5;
	salePrice = 10;
}

Tomato::~Tomato()
{
}

void Tomato::paintSeed(Graphics^ g)
{
	Bitmap^ tomato = gcnew Bitmap(TOMATO_SEED);
	width = tomato->Width;
	height = tomato->Height;

	Rectangle* mold = new Rectangle(0, 0, width, height);
	Rectangle* zoom = new Rectangle(x, y, width, height);

	g->DrawImage(tomato, *zoom, *mold, GraphicsUnit::Pixel);

	delete tomato;
	delete mold;
	delete zoom;
}

void Tomato::paintPlant(Graphics^ g)
{
	Bitmap^ tomato = gcnew Bitmap(TOMATO_PLANT);
	width = tomato->Width / 3;
	height = tomato->Height;

	Rectangle* mold = new Rectangle(column * width, row * height, width, height);
	Rectangle* zoom = new Rectangle(x, y, g->VisibleClipBounds.Width * 2 / 40,
		g->VisibleClipBounds.Height * 2 / 31);

	width = zoom->Width;
	height = zoom->Height;

	g->DrawImage(tomato, *zoom, *mold, GraphicsUnit::Pixel);

	delete tomato;
	delete mold;
	delete zoom;
}

void Tomato::paintHarvest(Graphics^ g)
{
	Bitmap^ tomato = gcnew Bitmap(TOMATO_HARVEST);
	width = tomato->Width;
	height = tomato->Height;

	Rectangle* mold = new Rectangle(0, 0, width, height);
	Rectangle* zoom = new Rectangle(x, y, width, height);

	g->DrawImage(tomato, *zoom, *mold, GraphicsUnit::Pixel);

	delete tomato;
	delete mold;
	delete zoom;
}

Tomato* Tomato::clone()
{
	return new Tomato(*this);
}
