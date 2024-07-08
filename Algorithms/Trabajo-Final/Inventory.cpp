#include "Inventory.h"

Inventory::Inventory()
{
	items = new vector<Item*>;
	idxItemSelected = -1;
	stoped = false;
}

Inventory::~Inventory()
{
	delete[] items;
}

void Inventory::addItem(Item* item)
{
	items->push_back(item);
}

void Inventory::paintItems(Graphics^ g)
{
	Point* point = new Point();
	for (short i = 0; i < items->size(); i++) {
		point->X = g->VisibleClipBounds.Width / 80 + (i % 4) * (g->VisibleClipBounds.Width * 2 / 20) + (g->VisibleClipBounds.Width * 1 / 40) - 6;
		point->Y = g->VisibleClipBounds.Height * (25) / (31) + trunc(i / 4) * (g->VisibleClipBounds.Height * 1.5 / 32 + 32) + (g->VisibleClipBounds.Width * 1 / 40) - 13;
		
		items->at(i)->getEntity()->setX(point->X);
		items->at(i)->getEntity()->setY(point->Y);

		if (items->at(i)->getType() == "powerItem") {
			PowerItem* powerItem = dynamic_cast<PowerItem*>(items->at(i));
			powerItem->paintItem(g);
		} else items->at(i)->paint(g);
	}

	delete point;
}

void Inventory::removeItem(short pos)
{
	this->items->erase(this->items->begin() + pos);
}

Item* Inventory::getItemFromName(string name, string type)
{
	for (short i = 0; i < items->size(); i++) {
		if(name.size() > 0 &&
			items->at(i)->getEntity()->getName().size() > 0 &&
			name == items->at(i)->getEntity()->getName() && (type.size() > 0 && type == items->at(i)->getType())) return items->at(i);
	}
	return nullptr;
}

Item* Inventory::getItem(short pos)
{
	if (pos < 0) return nullptr;
	return items->at(pos);
}

short Inventory::handleClickChooseItem(Point point)
{
	if (stoped) return -1;
	for (short i = 0; i < items->size(); i++) {
		if (items->at(i)->getEntity()->getRectangle()->Contains(point)) {
			if(items->at(i)->getType() == "seed") idxItemSelected = i;
			return i;
		}
	}
	return -1;
}

short Inventory::getAmountFromType(string type)
{
	short amount = 0;
	for (short i = 0; i < items->size(); i++) {
		if (items->at(i)->getType() == type) amount++;
	}
	return amount;
}

short Inventory::getIdxItemSelected()
{
	return idxItemSelected;
}

void Inventory::removeFromType(string type)
{
	for (short i = 0; i < items->size(); i++) {
		if (items->at(i)->getType() == type) items->erase(items->begin() + i);
	}
}

short Inventory::getCashFromType(string type)
{
	short money = 0;
	for (short i = 0; i < items->size(); i++) {
		if (items->at(i)->getType() == type) money += items->at(i)->getSalePrice();
	}
	return money;
}

void Inventory::play()
{
	stoped = false;
}

void Inventory::stop()
{
	stoped = true;
}
