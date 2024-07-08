#pragma once
#include "StaticEntity.h"

class CustomUi : public StaticEntity
{
protected:
	bool inScreen;
	float fontSize;
	bool enabled;

public:
	CustomUi(float fontSize = 0.0, bool inScreen = false);
	CustomUi(short x, short y, short width, short height, float fontSize = 0.0, bool inScreen = false);
	~CustomUi();
	virtual void hover(Graphics^ g) {};
	bool getInScreen();
	void setInScreen(bool inScreen);
	bool getEnabled();
	void setEnabled(bool enabled);
	float getFontSize();
	void setFontSize(float fontSize);
};



