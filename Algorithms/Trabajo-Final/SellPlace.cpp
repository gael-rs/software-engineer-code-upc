#include "SellPlace.h"

SellPlace::SellPlace() : StaticEntity()
{
}

SellPlace::~SellPlace()
{
}

void SellPlace::paint(Graphics^ g)
{
	Bitmap^ sellPlace = gcnew Bitmap(SELL_PLACE_PATH);

	width = sellPlace->Width;
	height = sellPlace->Height;

	Rectangle* mold = new Rectangle(0,0, width, height);

	width *= 1.25;
	height *= 1.25;

	Rectangle* zoom = new Rectangle(x, y, width, height);

	g->DrawImage(sellPlace, *zoom, *mold, GraphicsUnit::Pixel);

	delete sellPlace;
	delete mold;
	delete zoom;
}

bool SellPlace::collisionAction(BaseEntity* entity)
{
	bool collision = false;
	Rectangle* spaceAction = new Rectangle(x, y, width * 1.5, height);

	collision = spaceAction->IntersectsWith(*entity->getRectangle());

	return collision;
}