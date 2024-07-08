#include "Map.h"

Map::Map()
{
	this->momentPlay = MomentPlay::Afternoon;
	inventory = new Inventory();
	hud = new HUD();
	farm = new Farm();
	questionGenerator = new QuestionGenerator();
	stoped = false;
	moneyGoal = 0;
}

Map::~Map()
{
	delete inventory;
	delete hud;
	delete farm;
	delete questionGenerator;
}

void Map::paintEverything(Graphics^ g)
{
	paintBackground(g);

	farm->paintEverything(g, momentPlay);
	hud->paintInfo(g, momentPlay, farm->getFarmer()->getMoney());
	inventory->paintItems(g);
	questionGenerator->paintExercise(g, farm->getGarden()->getIdxsAvailables());

	if (*hud->getSeconds() == 8) hud->talkFarmerAllied(R"(Se acerca la noche, ¡los 
animales vienen!)");
	if (*hud->getSeconds() == 12)
	{
		momentPlay = MomentPlay::Night;
		hud->talkFarmerAllied(R"(Ten cuidado, utiliza tu 
linterna para espantarlos)");
		farm->changeNight();
	}

	// TODO: El jugador perdió la semilla
	if (questionGenerator->timeFinished() && questionGenerator->getVisible()) {
		questionGenerator->finish();
		Item* item = inventory->getItem(inventory->getIdxItemSelected());

		if (item->getCount() - 1 <= 0) inventory->removeItem(inventory->getIdxItemSelected());
		else item->setCount(item->getCount() - 1);
	}
}

void Map::moveEverything(Graphics^ g, Direction direction)
{
	farm->moveEverything(g, direction);
}

void Map::moveEverything(Graphics^ g)
{
	farm->moveEverything(g, momentPlay);
}

void Map::paintBackground(Graphics^ g)
{
	Bitmap^ bg = gcnew Bitmap((momentPlay == MomentPlay::Afternoon) ? BACKGROUND_GAME_AFTERNOON : BACKGROUND_GAME_NIGHT);

	Rectangle* mold = new Rectangle(0, 0, bg->Width, bg->Height);
	Rectangle* zoom = new Rectangle(0, 0, g->VisibleClipBounds.Width, g->VisibleClipBounds.Height);

	g->DrawImage(bg, *zoom, *mold, GraphicsUnit::Pixel);

	delete bg;
	delete zoom;
	delete mold;
}

void Map::stopEverythingAfterKeyUp()
{
	farm->stopEverythingAfterKeyUp();
}

void Map::initialize(Graphics^ g, string namePlayer, Difficult difficult)
{
	moneyGoal = difficult == Normal ? 200 : 300;
	Rectangle* farmSpace = new Rectangle(0, 100, g->VisibleClipBounds.Width, (g->VisibleClipBounds.Height * 16 / 26) - 10);
	farm->initialize(g, farmSpace, difficult);

	hud->talkFarmerAllied("Hola, " + namePlayer + (namePlayer.size() > 5 ? R"(. Bienve-
nido a tu nueva granja.)" : R"(. Bienvenido a
tu nueva granja.)"));

	hud->initialize(difficult);
	questionGenerator->initialize(farmSpace);
}

void Map::handleClick(Graphics^ g, Point point)
{
	ShopVegetable* shopVegetableClicked = farm->checkClickedShopVegetable(point);

	// TODO: Validar si se hace click a un shop vegetable
	if (shopVegetableClicked != nullptr) {
		if (farm->getFarmer()->getMoney() - shopVegetableClicked->getSeed()->getPrice() >= 0) {
			Item* item = inventory->getItemFromName(shopVegetableClicked->getSeed()->getEntity()->getName(), shopVegetableClicked->getSeed()->getType());

			if (item != nullptr) {
				item->setCount(item->getCount() + 1);
			}
			else {
				Seed* seed = new Seed;
				*seed = *shopVegetableClicked->getSeed();

				Vegetable* vegetable = shopVegetableClicked->getSeed()->getVegetable()->clone();

				seed->setVegetable(vegetable);
				seed->setCount(1);

				inventory->addItem(seed);
				item = seed;
			}

			farm->getFarmer()->setMoney(
				farm->getFarmer()->getMoney() - item->getPrice()
			);
		}
		return;
	}

	short itemIndexChoosed = inventory->handleClickChooseItem(point);

	// TODO: Items
	if (itemIndexChoosed >= 0) {
		Item* itemChoosed = inventory->getItem(itemIndexChoosed);

		if (itemChoosed->getType() == "seed" && !questionGenerator->getVisible()) {
			questionGenerator->showExercise(farm->getGarden()->getIdxsAvailables());
			hud->talkFarmerAllied(R"(Dale click a la respuesta
correcta para plantar.)");
		}

		if (itemChoosed->getType() == "powerItem") {
			PowerItem* powerItem = dynamic_cast<PowerItem*>(itemChoosed);

			if (powerItem->getEntity()->getName() == "Perro") {
				PowerItem* dogItem = dynamic_cast<PowerItem*>(powerItem);
				dogItem = dogItem != nullptr ? dogItem->clone() : nullptr;

				Animal* dog = dynamic_cast<Animal*>(dogItem->getEntity());

				farm->positionAnimal(dog);
				farm->addDog(dog);
			}
			else if (powerItem->getEntity()->getName() == "Espantapájaros") {
				Scarecrow* scarecrow = dynamic_cast<Scarecrow*>(powerItem);
				farm->setScarecrow(scarecrow);
			}

			if (powerItem->getCount() - 1 <= 0) inventory->removeItem(itemIndexChoosed);
			else powerItem->setCount(powerItem->getCount() - 1);
		}
		return;
	}

	// TODO: Validar la respuesta de la maceta
	short idxPot = questionGenerator->chooseAlternative(point);

	if (idxPot >= 0) {
		bool valided = questionGenerator->validAnswer();
		if (!valided) {
			questionGenerator->setFontSize(15.0);
			questionGenerator->setProvisionalMessage("Respuesta incorrecta, ten cuidado:(");
			return;
		}

		Item* itemSelected = inventory->getItem(inventory->getIdxItemSelected());

		Vegetable* vegetable = dynamic_cast<Vegetable*>(itemSelected->getEntity());

		vegetable = vegetable->clone();

		questionGenerator->finish();
		farm->sowPlant(idxPot, vegetable);

		if (itemSelected->getCount() - 1 <= 0) inventory->removeItem(inventory->getIdxItemSelected());
		else itemSelected->setCount(itemSelected->getCount() - 1);
		return;
	}

	// TODO: Verificar si se ha presionado una planta para devolver el cultivo
	Harvest* harvest = farm->checkClickedHarvest(point);

	if (harvest != nullptr) {
		Item* harvestExisted = inventory->getItemFromName(harvest->getEntity()->getName(), harvest->getType());

		if (harvestExisted != nullptr) {
			harvestExisted->setCount(harvestExisted->getCount() + 1);
		}
		else {
			harvest->setCount(1);
			inventory->addItem(harvest);
		}
		return;
	}

	// TODO: Verificar si se ha hecho click a un power item

	PowerItem* powerItem = farm->checkClickShop(g, point);

	if (powerItem != nullptr) {
		Item* itemExists = inventory->getItemFromName(powerItem->getEntity()->getName(), powerItem->getType());
		if (itemExists != nullptr) itemExists->setCount(itemExists->getCount() + 1);
		else {
			PowerItem* powerItemClone = powerItem->clone();
			powerItemClone->setCount(1);
			inventory->addItem(powerItemClone);
		}
	}
}

void Map::checkActionAfterKeyUp(ActionFarmer actionFarmer)
{
	farm->checkActionFarmer(actionFarmer);
}

void Map::handleActionFarmer(ActionFarmer actionFarmer)
{
	if (!questionGenerator->getVisible()) {
		bool action = farm->handleActionFarmer(actionFarmer);
		if (action) {
			if (actionFarmer == ActionFarmer::KeyForSale) {
				short cash = inventory->getCashFromType("harvest");
				inventory->removeFromType("harvest");

				farm->getFarmer()->setMoney(farm->getFarmer()->getMoney() + cash);
			}
			if (ActionFarmer::KeyForBuy == actionFarmer) {
				if (stoped) play();
				else stop();
			}
		}
	}
}

void Map::stop()
{
	stoped = true;
	farm->stop();
	hud->stop();
	inventory->stop();
}

void Map::play()
{
	stoped = false;
	farm->play();
	hud->play();
	inventory->play();
}

bool Map::checkWin()
{
	return hud->checkTimeFinish() && farm->getFarmer()->getMoney() > moneyGoal;
}

bool Map::checkLose() {
	bool cases = (farm->getFarmer()->getMoney() <= 0 && inventory->getAmountFromType("seed") <= 0
		&& inventory->getAmountFromType("harvest") <= 0) || hud->checkTimeFinish() && farm->getFarmer()->getMoney() <= moneyGoal;

	return cases;
}

Farm* Map::getFarm()
{
	return farm;
}
