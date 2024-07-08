#pragma once
#include "Shop.h"
#include "ShopVegetable.h"
#include "SellPlace.h"
#include "Garden.h"
#include "Wall.h"
#include "Farmer.h"
#include "ListAnimals.h"
#include "Wheat.h"
#include "Pumpkin.h"
#include "Tomato.h"


class Farm
{
private:
	Shop* shop;
	ShopVegetable** shopsVegetables;
	SellPlace* sellPlace;
	Garden* garden;
	Wall* wall;
	Farmer* farmer;
	ListAnimals* listAnimals;
	Rectangle* space;
	Scarecrow* scarescrow;
	bool stoped;

public:
	Farm();
	~Farm();
	void paintEverything(Graphics^ g, MomentPlay momentPlay);
	void moveEverything(Graphics^ g, Direction direction);
	BaseEntity* checkCollision(BaseEntity* baseEntity);
	void moveEverything(Graphics^ g, MomentPlay momentPlay);
	void stopEverythingAfterKeyUp();
	Farmer* getFarmer();
	Garden* getGarden();
	void sowPlant(short idxPlant, Vegetable* vegetable);
	Rectangle* getSpace();
	void setSpace(Rectangle* space);
	void fillGarden(Rectangle* space);
	void positionAnimal(Animal* animal);
	Harvest* checkClickedHarvest(Point point);
	void fillWall(Rectangle* space);
	void changeNight();
	void initialize(Graphics^ g, Rectangle* space, Difficult difficult);
	void checkActionFarmer(ActionFarmer actionFarmer);
	bool handleActionFarmer(ActionFarmer actionFarmer);
	ShopVegetable* checkClickedShopVegetable(Point point);
	PowerItem* checkClickShop(Graphics^ g, Point point);
	void checkSpaceActionFarmer();
	void stop();
	void play();
	ListAnimals* getListAnimals();
	Scarecrow* getScarecrow();
	void setScarecrow(Scarecrow* scarecrow);
	void addDog(Animal* animal);
};
