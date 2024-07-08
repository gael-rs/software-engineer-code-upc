#include "CustomInput.h"

CustomInput::CustomInput(float fontSize, string text, bool inScreen) : CustomUi(fontSize, inScreen)
{
	this->text = text;
	this->focus = false;
	this->oldText = text;
	this->lettersToDelete = 0;
}

CustomInput::CustomInput(short x, short y, short width, short height, float fontSize, string text, bool inScreen) : CustomUi(x, y, width, height, fontSize, inScreen)
{
	this->text = text;
	this->oldText = text;
	this->lettersToDelete = 0;
	this->focus = false;
}

CustomInput::~CustomInput()
{
}

SizeF^ CustomInput::getSizeText(Graphics^ g, Font^ font, String^ textParsed)
{
	return g->MeasureString(textParsed, font);
}

String^ CustomInput::getStringFromText(Graphics^ g, Font^ font)
{
	string* textTemp = new string;
	*textTemp = this->text + (focus ? "|": "");

	String^ textParsed = gcnew String(textTemp->c_str());

	SizeF^ textSize = getSizeText(g, font, textParsed);

	if (textSize->Width > width) {
		do {
			textParsed = gcnew String(textTemp->c_str());
			if (text.size() > oldText.size()) lettersToDelete++;
			else if (lettersToDelete > 0) lettersToDelete--;
			textParsed = textParsed->Remove(0, lettersToDelete);
			textSize = getSizeText(g, font, textParsed);
		} while (textSize->Width > width);
		oldText = text;
	}
	else {
		lettersToDelete = 0;
		oldText = text;
	}

	delete textTemp;
	delete textSize;
	return textParsed;
}

void CustomInput::paint(Graphics^ g)
{
	Font^ font = getFont(fontSize);

	g->DrawString(getStringFromText(g, font), font, Brushes::White, x, y);

}

string CustomInput::getText()
{
	return text;
}

void CustomInput::setText(string text)
{
	this->text = text;
}

bool CustomInput::getFocus()
{
	return focus;
}

void CustomInput::setFocus(bool focus)
{
	this->focus = focus;
}
