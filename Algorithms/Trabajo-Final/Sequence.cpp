#include "Sequence.h"

Sequence::Sequence(short columns, short rows, string srcBitmap, float scale, Position position)
{
	this->srcBitmap = new char[srcBitmap.size()];
	strcpy(this->srcBitmap, srcBitmap.c_str());
	this->columns = columns;
	this->rows = rows;
	this->scale = scale;
	this->play = false;
	this->loop = true;
	this->isFinished = false;
	this->position = position;
}

Sequence::~Sequence()
{
	delete srcBitmap;
}


void Sequence::paint(Graphics^ g)
{
	if (play) {
		String^ src = gcnew String(srcBitmap);
		Bitmap^ bitMap = gcnew Bitmap(src);

		width = bitMap->Width / columns;
		height = bitMap->Height / rows;

		if (position == Position::CenterY) {
			y = (g->VisibleClipBounds.Height - height) / 2;
		}
		else if (position == Position::CenterX) {
			x = (g->VisibleClipBounds.Width - width) / 2;
		}
		else  if (position == Position::CenterXY) {
			x = (g->VisibleClipBounds.Width - width) / 2;
			y = (g->VisibleClipBounds.Height - height) / 2;
		}

		Rectangle* form = new Rectangle(width * column, height * row, width, height);
		Rectangle* zoom = new Rectangle(x, y, width * scale, height * scale);

		g->DrawImage(bitMap, *zoom, *form, GraphicsUnit::Pixel);


		if (!isFinished) {
			if (column == columns - 1 && rows - 1 > 0) {
				if (row == rows - 1) {
					isFinished = true;

					delete bitMap;
					delete form;
					delete zoom;
					delete src;
					return;
				}
				row = ((row + 1) % (rows));
			}

			column = ((column + 1) % (columns));	
		}

		delete bitMap;
		delete form;
		delete zoom;
		delete src;
	}
}

short Sequence::getColumns()
{
	return columns;
}

void Sequence::setColumns(short columns)
{
	this->columns = columns;
}

short Sequence::getRows()
{
	return rows;
}

void Sequence::setRows(short columns)
{
	this->columns = columns;
}

bool Sequence::getPlay()
{
	return play;
}

void Sequence::setPlay(bool play) {
	this->play = play;
}

float Sequence::getScale()
{
	return scale;
}

void Sequence::setScale(float scale) {
	this->scale = scale;
}

bool Sequence::getLoop()
{
	return loop;
}

void Sequence::setLoop(bool loop) {
	this->loop = loop;
}

void Sequence::setSrcBitMap(string srcBitMap)
{
	this->srcBitmap = new char[srcBitMap.size()];
	strcpy(this->srcBitmap, srcBitMap.c_str());
}

bool Sequence::getIsFinished()
{
	return isFinished;
}
