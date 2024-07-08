#include "Scarecrow.h"

Scarecrow::Scarecrow()
{
	price = 20;
	name = "Espantapájaros";
	// Dura 25s
}

Scarecrow::~Scarecrow()
{
}

void Scarecrow::paint(Graphics^ g)
{
	Bitmap^ scarecrow = gcnew Bitmap(SCARECROW_PATH);

	width = scarecrow->Width / 4;
	height = scarecrow->Height;
	
	Rectangle* mold = new Rectangle(column * width, height * row, width, height);

	width *= scale;
	height *= scale;

	Rectangle* zoom = new Rectangle(x, y, width, height);

	g->DrawImage(scarecrow, *zoom, *mold, GraphicsUnit::Pixel);

	column = (column + 1) % 4;

	delete scarecrow;
	delete mold;
	delete zoom;
}

void Scarecrow::paintPreview(Graphics^ g, short moneyFarmer)
{
	paint(g);
	PowerItem::paintPreview(g, moneyFarmer);
}

BaseEntity* Scarecrow::getEntityPowerItem()
{
	return this;
}

void Scarecrow::paintItem(Graphics^ g)
{
	scale = 0.85;
	column = 1;
	Bitmap^ scarecrow = gcnew Bitmap(SCARECROW_PATH);

	width = scarecrow->Width / 4;
	height = scarecrow->Height;

	Rectangle* mold = new Rectangle(column * width, height * row, width, height);

	width *= scale;
	height *= scale;

	Rectangle* zoom = new Rectangle(x + 3, y, width, height);

	g->DrawImage(scarecrow, *zoom, *mold, GraphicsUnit::Pixel);

	PowerItem::paintItem(g);

	delete scarecrow;
	delete mold;
	delete zoom;
}

PowerItem* Scarecrow::clone()
{
	return new Scarecrow(*this);
}

