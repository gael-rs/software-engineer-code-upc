#include "Farm.h"

Farm::Farm()
{
	space = nullptr;
	scarescrow = nullptr;
	// Agregación
	shop = new Shop();
	// Agregación
	sellPlace = new SellPlace();
	// Composición
	garden = new Garden();
	// Composición
	wall = new Wall();
	// Agregación
	farmer = new Farmer();
	// Agregación
	listAnimals = new ListAnimals();

	shopsVegetables = new ShopVegetable * [4];

	stoped = false;
}

Farm::~Farm()
{
	delete space;
	delete shop;
	delete garden;
	delete farmer;
	delete listAnimals;
	delete wall;
	delete shopsVegetables;
}

void Farm::paintEverything(Graphics^ g, MomentPlay momentPlay)
{
	for (short i = 0; i < 4; i++)
	{
		shopsVegetables[i]->paint(g);
	}
	if (!stoped) garden->paintAllGarden(g);
	sellPlace->paint(g);
	wall->paintFences(g);
	if (momentPlay == MomentPlay::Night) {
		listAnimals->paintAnimals(g);
	}
	farmer->paint(g);
	shop->paint(g, farmer->getMoney());
	if (!stoped) checkSpaceActionFarmer();
}

void Farm::moveEverything(Graphics^ g, Direction direction)
{
	if (!stoped) {
		Point* point = new Point(farmer->getX(), farmer->getY());

		farmer->move(space, direction);

		BaseEntity* entityCollided = checkCollision(farmer);

		if (entityCollided != nullptr) {
			farmer->setX(point->X);
			farmer->setY(point->Y);
		}
	}
}

BaseEntity* Farm::checkCollision(BaseEntity* entity)
{
	Fence* fence = wall->collisionFence(entity);
	if (fence != nullptr) return fence;
	return nullptr;
}

void Farm::moveEverything(Graphics^ g, MomentPlay momentPlay)
{
	if (!stoped) {
		if (momentPlay == MomentPlay::Night) listAnimals->moveAnimals(g, space);

		if (farmer->getFlashLight()->getStatusOn()) {
			Animal* animalCollided = listAnimals->collisionAnimal(farmer->getFlashLight());
			if (animalCollided != nullptr) {
				animalCollided->setTimeLighting(clock());
				if (animalCollided->getDx() == 0) animalCollided->setDx(4);
				else animalCollided->setDx(animalCollided->getDx() < 0 ?
					-1 * animalCollided->getDx() : animalCollided->getDx());

				animalCollided->setTurned(true);
				animalCollided->setLighted(true);
				if (animalCollided->getEating()) animalCollided->setEating(false);

			}
		}

		listAnimals->checkObjective(garden->getIdxsPlanted());

		for (short i = 0; i < listAnimals->getN(); i++)
		{
			Animal* animal = listAnimals->getAnimal(i);
			Fence* fenceCollided = wall->collisionFence(animal, animal->getObjetive() < 0);

			if (fenceCollided != nullptr) {
				if (animal->getObjetive() < 0 && animal->getName() == "Perro") {
					animal->setDx(animal->getDx() > 0 ? animal->getDx() * -1 : animal->getDx());
					animal->setTurned(true);
					return;
				}

				if (animal->getObjetive() < 0) {
					animal->setDx(animal->getDx() < 0 ?
						-1 * animal->getDx() : animal->getDx());
					animal->setTurned(true);
				}
				else {
					bool breakFence = true;
					if (fenceCollided->getColumn() + 1 < 3) breakFence = animal->actionForCollisionWall();
					if (breakFence) {
						fenceCollided->setColumn(fenceCollided->getColumn() + 1);
					}
					continue;
				}
			}

			PlatingPlace* platingPlaceObjetive = garden->getPlatingPlace(animal->getObjetive());

			if (platingPlaceObjetive != nullptr) {
				if (platingPlaceObjetive->getPlant() != nullptr && platingPlaceObjetive->collision(animal)) {
					if (!platingPlaceObjetive->getPlant()->getStartedBeEaten()) {
						platingPlaceObjetive->getPlant()->setStartedBeEaten(true);
						platingPlaceObjetive->getPlant()->setStartBeEaten(clock());
					}
					if (!animal->getLighted()) animal->eat();
					else {
						if (platingPlaceObjetive->getPlant()->getStartedBeEaten())
							platingPlaceObjetive->getPlant()->setStartedBeEaten(false);
					}
				}

				if (platingPlaceObjetive->getPlant() == nullptr && animal->getEating()) {
					animal->setEating(false);
					animal->setEated(true);
					animal->setTurned(true);
					animal->setDx(4);
				}
			}

			Dog* dog = dynamic_cast<Dog*>(animal);

			if (dog != nullptr) {
				Animal* animalCollided = listAnimals->collisionAnimal(dog);
				if (animalCollided != nullptr) {
					animalCollided->setChasedAway(true);
					dog->bark();
					if (animalCollided->getDx() < 0) {
						animalCollided->setDx(animalCollided->getDx() * -1);
						if (dog->getDx() < 0) dog->setDx(animalCollided->getDx());
						if (!animalCollided->getTurned()) animalCollided->setTurned(true);
					}
					else {
						dog->setDx(4);
					}
				}
				else {
					dog->setColumn(0);
				}
			}
		}

		if (listAnimals->getSecondsStartOfRefill() > listAnimals->getTimeOfRefill()) {
			listAnimals->fill(space);
			listAnimals->setStartOfRefill(clock());
		}
	}


}

void Farm::stopEverythingAfterKeyUp()
{
	farmer->stop();
}

Farmer* Farm::getFarmer()
{
	return farmer;
}

Garden* Farm::getGarden()
{
	return garden;
}

void Farm::sowPlant(short idxPlant, Vegetable* vegetable)
{
	garden->sow(idxPlant, vegetable);
}

Rectangle* Farm::getSpace()
{
	return space;
}

void Farm::setSpace(Rectangle* space)
{
	this->space = space;
}


void Farm::fillGarden(Rectangle* space)
{
	Point* point = new Point;

	for (short i = 0; i < 16; i++) {
		point->X = space->X + space->Width * 1 / 4 + space->Width * 2 / 40 * (i % 4) + (i % 4) * space->Width * 2 / 40;
		point->Y = space->Y + space->Height * 2 / 16
			+ trunc(i / 4) * space->Height * 2 / 16 + trunc(i / 4) * space->Height * 1.5 / 16;

		garden->addPlatingPlace(new PlatingPlace(point->X, point->Y));
	}

	delete point;
}

void Farm::positionAnimal(Animal* animal) {
	listAnimals->positionAnimal(animal, space);
}

Harvest* Farm::checkClickedHarvest(Point point)
{
	PlatingPlace* platingPlace = garden->collisionPoint(point);
	if (platingPlace != nullptr && platingPlace->getPlant() != nullptr && platingPlace->getPlant()->getVegetable()->getColumn() >= 2) {
		Harvest* harvest = platingPlace->getHarvest();
		platingPlace->removePlant();
		return harvest;
	}
	return nullptr;
}

void Farm::fillWall(Rectangle* space)
{
	Point* point = new Point(space->X + space->Width * 3 / 4);

	for (short i = 0; i < 5; i++) {
		point->Y = space->Y + space->Height * 3.49 / 16 * i;
		Fence* fence = new Fence(point->X, point->Y, space->Height * 3.49 / 16);
		if (i == 4) fence->setColumn(3);
		wall->addFence(fence);
	}

	delete point;
}

void Farm::changeNight()
{
	listAnimals->setStartOfRefill(clock());
}

void Farm::initialize(Graphics^ g, Rectangle* space, Difficult difficult)
{
	// Inicializando las entidades para el inicio del juego
	this->space = space;
	farmer->setMoney(difficult == Difficult::Hard ? 15 : 25);

	farmer->setX(space->X + 48 * 1.25 + 16 + 8);
	farmer->setY(space->Y);

	farmer->getFlashLight()->setX(
		farmer->getX() + 40
	);

	farmer->getFlashLight()->setY(
		farmer->getY() + 10
	);

	while (listAnimals->getN() <= 0) {
		listAnimals->fill(space);
	}

	if (garden->getN() <= 0) {
		fillGarden(space);
	}

	if (wall->getN() <= 0) {
		fillWall(space);
	}

	shopsVegetables[0] = new ShopVegetable(new Carrot());
	shopsVegetables[1] = new ShopVegetable(new Wheat());
	shopsVegetables[2] = new ShopVegetable(new Pumpkin());
	shopsVegetables[3] = new ShopVegetable(new Tomato());

	for (short i = 0; i < 4; i++)
	{
		shopsVegetables[i]->setY(space->Y + 48 * 1.25 * (1 + i));
		shopsVegetables[i]->setX(space->X + 16);
	}

	sellPlace->setX(space->X + 16);
	sellPlace->setY(space->Y);

	shop->setY(space->Y + 48 * 1.25 * 5);
	shop->setX(space->X + 16);
	shop->initialize(difficult);

}

void Farm::checkActionFarmer(ActionFarmer actionFarmer)
{
	if (actionFarmer == ActionFarmer::PlayFlashLight) {
		farmer->getFlashLight()->toogleStatus();
		farmer->changeStatusFlashLight();
	}
}

bool Farm::handleActionFarmer(ActionFarmer actionFarmer)
{
	if (actionFarmer == ActionFarmer::KeyForSale && farmer->getSequenceKeySale()->getPlay()) return true;
	else if (actionFarmer == ActionFarmer::KeyForBuy && farmer->getSequenceKeyBuy()->getPlay()) {
		shop->toggle();
		return true;
	}
	return false;
}


ShopVegetable* Farm::checkClickedShopVegetable(Point point)
{
	// TODO: Make a collision point width shop vegetable
	for (short i = 0; i < 4; i++) {
		if (shopsVegetables[i]->collisionPoint(point)) return shopsVegetables[i];
	}
	return nullptr;
}

PowerItem* Farm::checkClickShop(Graphics^ g, Point point)
{
	PowerItem* powerItem = shop->handleClick(g, point);
	if (powerItem != nullptr) {
		farmer->setMoney(farmer->getMoney() - powerItem->getPrice());
		return powerItem;
	}
	return nullptr;
}

void Farm::checkSpaceActionFarmer()
{
	bool collidedShop = shop->collisionAction(farmer);
	bool collidedSellPlace = sellPlace->collisionAction(farmer);

	if (collidedShop || collidedSellPlace) {
		farmer->getSequenceKeySale()->setX(farmer->getX() + farmer->getWidth() / 2 - 16 * 0.6);
		farmer->getSequenceKeySale()->setY(farmer->getY() - 18);

		farmer->getSequenceKeyBuy()->setX(farmer->getX() + farmer->getWidth() / 2 - 16 * 0.6);
		farmer->getSequenceKeyBuy()->setY(farmer->getY() - 18);
	}

	if (collidedShop) {
		farmer->action(ActionFarmer::KeyForBuy);
		return;
	}

	if (collidedSellPlace) {
		farmer->action(ActionFarmer::KeyForSale);
		return;
	}

	farmer->action(ActionFarmer::Nothing);
}

void Farm::stop()
{
	stoped = true;
	listAnimals->stopEverything();
}

void Farm::play()
{
	stoped = false;
	listAnimals->playEverything();
}

ListAnimals* Farm::getListAnimals()
{
	return listAnimals;
}

Scarecrow* Farm::getScarecrow()
{
	return scarescrow;
}

void Farm::setScarecrow(Scarecrow* scarecrow)
{
	this->scarescrow = scarecrow;
}

void Farm::addDog(Animal* animal)
{
	listAnimals->addAnimal(animal);
}
