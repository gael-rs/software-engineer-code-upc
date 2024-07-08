#include "Shop.h"

Shop::Shop() : StaticEntity()
{
	menuSpace = new Rectangle();
	openedMenu = false;
	powerItems = new PowerItem * [2];

	powerItems[0] = new Scarecrow();
	powerItems[1] = new Dog();
}

Shop::~Shop()
{
	delete[] powerItems;
}

void Shop::paint(Graphics^ g, short moneyFarmer)
{
	Bitmap^ shop = gcnew Bitmap(SHOP_PATH);
	width = shop->Width;
	height = shop->Height;

	Rectangle* mold = new Rectangle(0, 0, width, height);

	width *= 1.25;
	height *= 1.25;

	Rectangle* zoom = new Rectangle(x, y, width, height);

	g->DrawImage(shop, *zoom, *mold, GraphicsUnit::Pixel);

	if (openedMenu) paintMenu(g, moneyFarmer);

	delete shop;
	delete mold;
	delete zoom;
}

bool Shop::collisionAction(BaseEntity* entity)
{
	bool collision = false;
	Rectangle* spaceAction = new Rectangle(x, y, width * 1.5, height);

	collision = spaceAction->IntersectsWith(*entity->getRectangle());

	return collision;
}

void Shop::open()
{
	openedMenu = true;
}

void Shop::close()
{
	openedMenu = false;
}

void Shop::toggle()
{
	this->openedMenu = !this->openedMenu;
}

void Shop::paintMenu(Graphics^ g, short moneyFarmer)
{
	Bitmap^ menu = gcnew Bitmap(SLOT_MENU_PATH);

	short width = menu->Width;
	short height = menu->Height;

	Rectangle* mold = new Rectangle(0, 0, width, height);

	width *= 1.35;
	height *= 1.35;

	Rectangle* zoom = new Rectangle((g->VisibleClipBounds.Width - width) / 2, (g->VisibleClipBounds.Height - height) / 2 - g->VisibleClipBounds.Height * 0.8 / 16, width, height);

	Font^ font = getFont(20.5);
	String^ title = "Tiendita de power ups";
	SizeF^ titleSize = g->MeasureString(title->ToUpper(), font);

	menuSpace = zoom;

	g->DrawImage(menu, *zoom, *mold, GraphicsUnit::Pixel);

	g->DrawString(title->ToUpper(), font, Brushes::WhiteSmoke,
		zoom->X + (zoom->Width - titleSize->Width) / 2,
		zoom->Y + titleSize->Height + 5
	);

	paintPowerItems(g, moneyFarmer);

	paintMessageToUser(g);

	delete menu;
	delete mold;
	delete zoom;
	delete font;
	delete title;
	delete titleSize;
}

void Shop::paintPowerItems(Graphics^ g, short moneyFarmer)
{
	for (short i = 0; i < 2; i++)
	{
		powerItems[i]->setScale(2);

		powerItems[i]->getEntity()->setX(
			menuSpace->X + menuSpace->Width * i / 2 + menuSpace->Width * 1 / 4 - 16 * powerItems[i]->getScale()
		);

		if (powerItems[i]->getEntity()->getY() == 0) {
			powerItems[i]->getEntity()->setY(
				menuSpace->Y + menuSpace->Height / 2 - 16 * powerItems[i]->getScale()
			);
		}

		powerItems[i]->paintPreview(g, moneyFarmer);
	}

}

PowerItem* Shop::handleClick(Graphics^ g, Point point)
{
	for (short i = 0; i < 2; i++)
	{
		if (powerItems[i]->getButton()->getEnabled()) {
			bool clicked = powerItems[i]->getButton()->getRectangle()->Contains(point);
			if (clicked) {
				powerItems[i]->getButton()->click(g);
				return powerItems[i];
			}
		}
	}
	return nullptr;
}

void Shop::handleHover(Point point)
{

}

void Shop::paintMessageToUser(Graphics^ g)
{
	Font^ font = getFont(12.5);
	String^ messageToUser = gcnew String("¡Hola, granjero! Presiona 'Q' para volver.");
	SizeF^ messageToUserSize = g->MeasureString(messageToUser, font);

	g->DrawString(messageToUser, font, Brushes::WhiteSmoke,
		menuSpace->X + (menuSpace->Width - messageToUserSize->Width) / 2,
		menuSpace->Y + (menuSpace->Height - (messageToUserSize->Height + 15))
	);

	delete messageToUser;
}

void Shop::initialize(Difficult difficult)
{
	powerItems[0]->setPrice(powerItems[0]->getPrice() + (difficult == Difficult::Hard) * 5);
	powerItems[1]->setPrice(powerItems[1]->getPrice() + (difficult == Difficult::Hard) * 5);
}

