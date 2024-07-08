#include "Pot.h"

Pot::Pot(short x, short y): StaticEntity(x, y)
{
	planted = false;
}

Pot::~Pot()
{
}

void Pot::paint(Graphics^ g)
{
	Bitmap^ pot = gcnew Bitmap(POT_PATH);
	width = pot->Width;
	height = pot->Height;

	Rectangle* mold = new Rectangle(0, 0, width, height);

	Rectangle* zoom = new Rectangle(x, y, g->VisibleClipBounds.Width * 2 / 40, 
		g->VisibleClipBounds.Height * 2 / 31);

	width = zoom->Width;
	height = zoom->Height;

	//g->DrawRectangle(Pens::Black, *zoom);
	g->DrawImage(pot, *zoom, *mold, GraphicsUnit::Pixel);

	delete pot;
	delete mold;
	delete zoom;
}

void Pot::setPlanted(bool planted)
{
	this->planted = planted;
}

bool Pot::getPlanted()
{
	return planted;
}

Rectangle* Pot::getRectangle()
{
	return new Rectangle(x + width / 5, y + height / 3, width * 1.9 / 3, height * 1 / 2);
}
