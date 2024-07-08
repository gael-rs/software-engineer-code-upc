#include "CustomCombo.h"

CustomCombo::CustomCombo(short x, short y, short width,
	short height, float fontSize, bool inScreen) : CustomUi(x, y, width, height, fontSize, inScreen)
{
	this->items = new vector<string*>;
	this->selected = 0;
	this->extend = false;
}


CustomCombo::~CustomCombo()
{
	delete[] items;
	delete indicatorRectangle;
}

void CustomCombo::paint(Graphics^ g)
{
	Bitmap^ slotDifficult = gcnew Bitmap(SLOT_DIFFICULT_PATH);

	Font^ font = getFont(fontSize);
	String^ textParsed;
	SizeF^ textSize;

	Point* point = new Point(x, y);

	short p = 0;

	for (short i = 0; i < items->size(); i++)
	{
		if (i == selected) {
			point->Y = y;
			point->X = x;
			getIndicator(g, point);
		}
		else if (extend) {
			point->X = x;
			point->Y = y + height * (++p);
			g->DrawImage(slotDifficult, point->X, point->Y);
		}

		if ((i == selected && !extend) || extend) {
			textParsed = gcnew String(items->at(i)->c_str());
			textSize = g->MeasureString(textParsed, font);

			g->DrawString(textParsed, font, Brushes::White, point->X + 10, point->Y + height / 2 - textSize->Height / 2 + 4);
		}
	}

	delete font;
	delete textParsed;
	delete point;
	delete slotDifficult;
	delete textSize;
}

void CustomCombo::addItem(string* item)
{
	items->push_back(item);
}

short CustomCombo::getSelected()
{
	return selected;
}

void CustomCombo::setSelected(short selected)
{
	this->selected = selected;
}

bool CustomCombo::getExtend()
{
	return extend;
}

void CustomCombo::setExtend(bool extend)
{
	this->extend = extend;
}

Rectangle* CustomCombo::getIndicator(Graphics^ g, Point* point)
{
	Bitmap^ indicator = gcnew Bitmap(INDICATOR_PATH);

	Rectangle* mold = new Rectangle(0, 0, indicator->Width, indicator->Height);
	Rectangle* zoom = new Rectangle(point->X + width - indicator->Width * 3 / 4, point->Y + height / 2 - indicator->Height / 4 + 4,
		indicator->Width / 2, indicator->Height / 2);

	if (extend) indicator->RotateFlip(RotateFlipType::RotateNoneFlipY);

	g->DrawImage(indicator, *zoom, *mold, GraphicsUnit::Pixel);

	delete indicator;
	delete mold;

	return zoom;
}

Rectangle* CustomCombo::getRectangleAll()
{
	Rectangle* rectangle = new Rectangle(x, y, width, 0);

	for (short i = 0; i < items->size(); i++) {
		if (extend || i == selected) rectangle->Height += height;
	}

	return rectangle;
}

bool CustomCombo::click(Point point)
{
	Rectangle* rectangle = new Rectangle(x, y, width, height);
	bool clicked = false;
	short p = 0;

	for (short i = 0; i < items->size(); i++)
	{
		if (i == selected) {
			rectangle->Y = y;
			rectangle->X = x;
			if (rectangle->Contains(point)) {
				clicked = true;
				extend = !extend;
			}
		}
		else if (extend) {
			rectangle->X = x;
			rectangle->Y = y + height * (++p);

			if (rectangle->Contains(point)) {
				selected = i;
				clicked = true;
			}
		}
	}

	delete rectangle;

	return clicked;
}
