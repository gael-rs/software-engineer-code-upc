#pragma once
#include "StaticEntity.h"
#include "Scarecrow.h"
#include "Dog.h"

class Shop : public StaticEntity
{
private:
	bool openedMenu;
	Rectangle* menuSpace;
	PowerItem** powerItems;

public:
	Shop();
	~Shop();
	void paint(Graphics^ g, short moneyFarmer);
	bool collisionAction(BaseEntity* entity);
	void open();
	void close();
	void toggle();
	void paintMenu(Graphics^ g, short moneyFarmer);
	void paintPowerItems(Graphics^ g, short moneyFarmer);
	PowerItem* handleClick(Graphics^ g, Point point);
	void handleHover(Point point);
	void paintMessageToUser(Graphics^ g);
	void initialize(Difficult difficult);
};

