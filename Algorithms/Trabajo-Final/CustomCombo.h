#pragma once
#include "CustomUi.h"

class CustomCombo : public CustomUi
{
private:
	vector<string*>* items;
	short selected;
	bool extend;
	Rectangle* indicatorRectangle;

public:
	CustomCombo(short x, short y, short width, short height,
		float fontSize = 28.5, bool inScreen = false);
	~CustomCombo();
	void paint(Graphics^ g);
	void addItem(string* item);
	short getSelected();
	void setSelected(short selected);
	bool getExtend();
	void setExtend(bool extend);
	Rectangle* getIndicator(Graphics^ g, Point* point);
	Rectangle* getRectangleAll();
	bool click(Point point);
};


