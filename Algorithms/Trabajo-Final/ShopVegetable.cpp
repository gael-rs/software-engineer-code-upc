#include "ShopVegetable.h"

ShopVegetable::ShopVegetable(Vegetable* vegetable)
{
	seed = new Seed(vegetable);
}

ShopVegetable::~ShopVegetable()
{
	delete seed;
}

Seed* ShopVegetable::getSeed()
{
	return seed;
}

bool ShopVegetable::collisionPoint(Point point)
{
	return getRectangle()->Contains(point);
}

void ShopVegetable::paint(Graphics^ g) 
{
	Bitmap^ shop = gcnew Bitmap(SHOP_VEGETABLE_PATH);
	width = shop->Width;
	height = shop->Height;

	Rectangle* mold = new Rectangle(0,0, width, height);

	width *= 1.25;
	height *= 1.25;

	Rectangle* zoom = new Rectangle(x, y, width, height);

	g->DrawImage(shop, *zoom, *mold, GraphicsUnit::Pixel);

	Rectangle* measures = seed->getVegetable()->getMeasuresHarvest();

	seed->getVegetable()->setX(
		x + (width / 2) - (measures != nullptr ? measures->Width / 2 : 16)
	);

	seed->getVegetable()->setY(
		y + height - (measures != nullptr ? measures->Height : 32)
	);

	seed->getVegetable()->paintHarvest(g);

	delete shop;
	delete mold;
	delete zoom;
}
