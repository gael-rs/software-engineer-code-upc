#pragma once
#include "CustomUi.h"

class CustomInput : public CustomUi
{
private:
	string text, oldText;
	short lettersToDelete;
	bool focus;

public:
	CustomInput(float fontSize = 10.5, string text = "", bool inScreen = false);
	CustomInput(short x, short y, short width = 0, short height = 0, float fontSize = 10.5, string text = "", bool inScreen = false);
	~CustomInput();
	SizeF^ getSizeText(Graphics^ g, Font^ font, String^ textParsed);
	String^ getStringFromText(Graphics^ g, Font^ font);
	void paint(Graphics^ g);
	string getText();
	void setText(string text);
	bool getFocus();
	void setFocus(bool focus);
};
