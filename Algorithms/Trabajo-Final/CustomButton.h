#pragma once
#include "CustomUi.h"

class CustomButton: public CustomUi
{
private:
	char* text;
	char* bgButton;
	bool hovered, clicked;
	float scale;

public:
	CustomButton(string text, string bgButton = "", float fontSize = 15.5);
	~CustomButton();
	void paint(Graphics^ g, bool force = false);
	void hover(Graphics^ g, bool withSound = false, bool force = false);
	void click(Graphics^ g, bool withSound = true);
	bool getHovered();
	void setHovered(bool hovered);
	bool getClicked();
	void setClicked(bool clicked);
	float getScale();
	void setScale(float scale);
};

