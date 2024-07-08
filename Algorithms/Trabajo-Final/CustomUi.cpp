#include "CustomUi.h"

CustomUi::CustomUi(short x, short y, short width, short height, float fontSize, bool inScreen): StaticEntity(x, y, width, height)
{
	this->inScreen = inScreen;
	this->fontSize = fontSize;
	this->enabled = true;
}

CustomUi::CustomUi(float fontSize, bool inScreen)
{
	this->inScreen = inScreen;
	this->fontSize = fontSize;
}

CustomUi::~CustomUi()
{
}

bool CustomUi::getInScreen()
{
	return inScreen;
}

void CustomUi::setInScreen(bool inScreen)
{
	this->inScreen = inScreen;
}

bool CustomUi::getEnabled()
{
	return enabled;
}

void CustomUi::setEnabled(bool enabled)
{
	this->enabled = enabled;
}

float CustomUi::getFontSize()
{
	return fontSize;
}

void CustomUi::setFontSize(float fontSize)
{
	this->fontSize = fontSize;
}
