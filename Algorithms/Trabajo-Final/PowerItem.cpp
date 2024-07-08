#include "PowerItem.h"

PowerItem::PowerItem() : Item()
{
	scale = 1.0;
	type = "powerItem";
	button = new CustomButton("Comprar", BUTTON_PATH, 11.0);
	coinAnimate = new Sequence(7, 1, COIN_ANIMATE_PATH);
}

PowerItem::~PowerItem()
{
	delete coinAnimate;
}

void PowerItem::paintItem(Graphics^ g)
{
	Item::paint(g);
}

void PowerItem::paintPreview(Graphics^ g, short moneyFarmer)
{
	coinAnimate->setPlay(true);

	const short GAP = 10;
	short* heightTotal = new short;
	BaseEntity* entity = getEntity();
	*heightTotal = entity->getHeight();

	string* name = new string;
	*name = entity->getName();

	Font^ font = getFont(12.5);

	String^ nameText = gcnew String(name->c_str());
	String^ priceText = Convert::ToString(price);

	SizeF^ textSize = g->MeasureString(nameText, font);

	*heightTotal += GAP + textSize->Height;

	g->DrawString(nameText, font, Brushes::WhiteSmoke, entity->getX() + (entity->getWidth() - textSize->Width) / 2,
		entity->getY() + entity->getHeight() + GAP);
	
	textSize = g->MeasureString(priceText, font);

	// Coin Animate
	coinAnimate->setX(entity->getX() + (entity->getWidth() - (textSize->Width + 12 + 5)) / 2);
	coinAnimate->setY(entity->getY() + *heightTotal + GAP);

	coinAnimate->paint(g);
	
	g->DrawString(priceText, font, Brushes::WhiteSmoke, 
		entity->getX() + (entity->getWidth() - textSize->Width) / 2 + 5,
		entity->getY() + *heightTotal + GAP);

	*heightTotal += GAP + coinAnimate->getHeight();

	// Button
	button->setEnabled(price <= moneyFarmer);
	button->setScale(0.6);
	button->setInScreen(true);
	button->setX(entity->getX() + entity->getWidth() / 2 - 193 * button->getScale() / 2);
	button->setY(entity->getY() + *heightTotal + GAP);

	*heightTotal += GAP + button->getHeight();
	
	button->paint(g);


	// Complete
	entity->setY(
		(g->VisibleClipBounds.Height - *heightTotal) / 2
	);


	delete nameText;
	delete font;
	delete textSize;
	delete name;
	delete heightTotal;
	delete priceText;
}

short PowerItem::getPrice()
{
	return price;
}

void PowerItem::setPrice(short price)
{
	this->price = price;
}

float PowerItem::getScale()
{
	return scale;
}

void PowerItem::setScale(float scale)
{
	this->scale = scale;
}

CustomButton* PowerItem::getButton()
{
	return button;
}

BaseEntity* PowerItem::getEntity()
{
	return getEntityPowerItem();
}

PowerItem* PowerItem::clone()
{
	return new PowerItem(*this);
}
