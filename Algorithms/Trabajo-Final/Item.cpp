#include "Item.h"

Item::Item(short count)
{
	this->count = count;
	this->type = "";
}

Item::~Item()
{
}

short Item::getCount()
{
	return count;
}

void Item::setCount(short count)
{
	this->count = count;
}

string Item::getType()
{
	return type;
}

void Item::paint(Graphics^ g)
{
	String^ amount = Convert::ToString(count);
	Font^ font = getFont(10.5);
	
	g->DrawString(amount, font, Brushes::WhiteSmoke, getEntity()->getX() + getEntity()->getWidth() - 8,
		getEntity()->getY() + getEntity()->getHeight() - 14
	);

	delete amount;
	delete font;
}

