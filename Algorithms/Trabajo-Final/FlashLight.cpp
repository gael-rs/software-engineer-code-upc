#include "FlashLight.h"

FlashLight::FlashLight()
{
	this->isOn = false;
	this->direction = Direction::Right;
}

FlashLight::~FlashLight()
{
}

void FlashLight::on()
{
	isOn = false;
}

void FlashLight::off()
{
	isOn = false;
}

bool FlashLight::getStatusOn()
{
	return isOn;
}

void FlashLight::toogleStatus()
{
	this->isOn = !isOn;
}

void FlashLight::paint(Graphics^ g)
{
	Bitmap^ flashLight = gcnew Bitmap(LIGHT_PATH);
	width = flashLight->Width;
	height = flashLight->Height;

	Rectangle* mold = new Rectangle(0, 0, width, height);

	width *= 0.75;
	height *= 0.75;

	Rectangle* zoom = new Rectangle(x, y, width, height);

	if (direction == Direction::Left) flashLight->RotateFlip(
		RotateFlipType::RotateNoneFlipX
	);

	if(direction == Direction::Up) flashLight->RotateFlip(
		RotateFlipType::Rotate90FlipY
	);
	
	if(direction == Direction::Down) flashLight->RotateFlip(
		RotateFlipType::Rotate270FlipY
	);

	g->DrawImage(flashLight, *zoom, *mold, GraphicsUnit::Pixel);

	delete flashLight;
	delete mold;
	delete zoom;
}

void FlashLight::setDirection(Direction direction)
{
	this->direction = direction;
}
