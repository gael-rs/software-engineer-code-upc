#pragma once
#include "Item.h"
#include "PowerItem.h"

class Inventory
{
private:
	vector<Item*>* items;
	short idxItemSelected;
	bool stoped;

public:
	Inventory();
	~Inventory();
	void addItem(Item* item);
	void paintItems(Graphics^ g);
	void removeItem(short pos);
	Item* getItemFromName(string name, string type = "");
	Item* getItem(short pos);
	short handleClickChooseItem(Point point);
	short getAmountFromType(string type);
	short getIdxItemSelected();
	void removeFromType(string type);
	short getCashFromType(string type);
	void play();
	void stop();
};
