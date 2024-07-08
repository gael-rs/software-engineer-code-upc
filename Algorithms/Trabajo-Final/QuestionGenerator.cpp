#include "QuestionGenerator.h"

QuestionGenerator::QuestionGenerator() {
	exercise = new Exercise();
	userAnswer = 0, fontSize = 22.5;
	visible = false, visibleAlternatives = false;
	alternativesSpace = new Rectangle * [16];
	alternatives = new short* [16];
	provisionalMessage = "";
}

QuestionGenerator::~QuestionGenerator() {
	delete exercise;
	delete alternativesSpace;
	delete alternatives;
}

void QuestionGenerator::showExercise(vector<short>* idxsAvailables) {
	provisionalMessage = "";
	fontSize = 22.5;
	visible = true;
	visibleAlternatives = true;
	timeStart = clock();
	exercise->generateRandomNumbers();
	exercise->generateRandomOperation();
	generateAlternatives(idxsAvailables);
}

Exercise* QuestionGenerator::getExercise()
{
	return this->exercise;
}

bool QuestionGenerator::validAnswer()
{
	bool valid = this->exercise->validAnswer(userAnswer);
	return valid;
}

void QuestionGenerator::showAlternatives(Graphics^ g, vector<short>* idxsAvailables)
{
	Bitmap^ buttle = gcnew Bitmap(BUBBLE_PATH);
	Font^ font = getFont(7.9);
	String^ alternative = "";
	SizeF^ alternativeSizeF;

	short width = buttle->Width, height = buttle->Height;

	Rectangle* mold = new Rectangle(0, 0, width, height);

	for (short i = 0; i < 16; i++)
	{
		if (alternatives[i] != nullptr) {
			alternativesSpace[i]->Width = width;
			alternativesSpace[i]->Height = height;

			alternative = Convert::ToString(*alternatives[i]);
			alternativeSizeF = g->MeasureString(alternative, font);

			Brush^ brush = gcnew SolidBrush(Color::FromArgb(18, 18, 18));

			g->DrawImage(buttle, *alternativesSpace[i], *mold, GraphicsUnit::Pixel);
			g->DrawString(alternative, font, brush, alternativesSpace[i]->X +
				(width - alternativeSizeF->Width) / 2, alternativesSpace[i]->Y + (height -
					alternativeSizeF->Height) / 2);
		}

	}

	delete buttle;
	delete mold;
	delete font;
	delete alternativeSizeF;
	delete alternative;
}

void QuestionGenerator::paintExercise(Graphics^ g, vector<short>* idxsAvailables)
{
	if (visible) {
		short* a = new short;
		*a = exercise->getNumber1();
		short* b = new short;
		*b = exercise->getNumber2();
		string* operation = new string;
		*operation = exercise->getOperation();
		Font^ font = getFont(fontSize);

		String^ exerciseString = provisionalMessage.size() > 0 ? gcnew String(provisionalMessage.c_str()) : "¿Cúanto es " + Convert::ToString(*a) +
			gcnew String(operation->c_str())
			+ Convert::ToString(*b) + "?";

		SizeF^ exerciseStringSize = g->MeasureString(exerciseString, font);

		g->DrawString(exerciseString, font, Brushes::WhiteSmoke,
			g->VisibleClipBounds.Width * 18 / 40 + g->VisibleClipBounds.Width * 21 / 80 - exerciseStringSize->Width / 2,
			g->VisibleClipBounds.Height * 25 / 31 + g->VisibleClipBounds.Height * 5 / 62 - exerciseStringSize->Height / 2);

		paintBarTime(g);

		fontSize = 22.5;
		provisionalMessage = "";

		delete a;
		delete b;
		delete operation;
		delete exerciseString;
		delete font;
		delete exerciseStringSize;
	}

	if (visibleAlternatives) showAlternatives(g, idxsAvailables);

	checkTime();
}

void QuestionGenerator::initialize(Rectangle* space)
{
	Point* point = new Point;
	for (short i = 0; i < 16; i++) {
		point->X = space->X + space->Width * 1 / 4 + space->Width * 2 / 40 * (i % 4) + (i % 4) * space->Width * 2 / 40 + 2;
		point->Y = space->Y + space->Height * 2 / 16
			+ trunc(i / 4) * space->Height * 2 / 16 + trunc(i / 4) * space->Height * 1.5 / 16 - 16;
		alternativesSpace[i] = new Rectangle(point->X, point->Y, 32, 32);
	}

	delete point;
}

void QuestionGenerator::generateAlternatives(vector<short>* idxsAvailables)
{
	short indexCorrect = rand() % 16;
	bool indexChecked = false;

	for (short i = 0; i < idxsAvailables->size(); i++) {
		if (idxsAvailables->at(i) == indexCorrect) {
			indexChecked = true;
			break;
		}
	}

	if (!indexChecked) return generateAlternatives(idxsAvailables);

	for (short i = 0; i < 16; i++) {
		indexChecked = false;
		for (short j = 0; j < idxsAvailables->size(); j++) {
			if (idxsAvailables->at(j) == i) {
				indexChecked = true;
				break;
			}
		}
		if (indexChecked) {
			alternatives[i] = new short;
			*alternatives[i] = i == indexCorrect ? exercise->results() : exercise->getMathOperationBehavior()->operate(
				(rand() % 13), (rand() % 13)
			);
		}
		else alternatives[i] = nullptr;
	}
}

short QuestionGenerator::chooseAlternative(Point point)
{
	if (visibleAlternatives) {
		for (short i = 0; i < 16; i++) {
			if (alternativesSpace[i]->Contains(point)) {
				userAnswer = *alternatives[i];
				return i;
			}
		}
	}

	return -1;
}

void QuestionGenerator::setProvisionalMessage(string provisionalMessage)
{
	this->provisionalMessage = provisionalMessage;
}

void QuestionGenerator::paintBarTime(Graphics^ g)
{
	short* seconds = getSeconds();
	Bitmap^ barTime = gcnew Bitmap(BAR_TIME_MATHEMATICS_PATH);

	Rectangle* mold = new Rectangle(*seconds * (barTime->Width / 8), 0, barTime->Width / 8, barTime->Height);
	Rectangle* zoom = new Rectangle(g->VisibleClipBounds.Width * 18 / 40 + g->VisibleClipBounds.Width * 21 / 80 - barTime->Width / 16,
		g->VisibleClipBounds.Height * 25 / 31 + g->VisibleClipBounds.Height * 5 / 31 - barTime->Height - g->VisibleClipBounds.Height * 1 / 62, barTime->Width / 8, barTime->Height);

	g->DrawImage(barTime, *zoom, *mold, GraphicsUnit::Pixel);

	delete barTime;
	delete seconds;
	delete mold;
	delete zoom;
}

short* QuestionGenerator::getSeconds()
{
	short* seconds = new short;
	*seconds = (clock() - timeStart) / CLOCKS_PER_SEC;
	return seconds;
}

void QuestionGenerator::checkTime()
{
	short* seconds = getSeconds();

	if (*seconds == 8) {
		visibleAlternatives = false;
		provisionalMessage = "Se acabó el tiempo :(";
	}
	delete seconds;
}

bool QuestionGenerator::getVisible()
{
	return visible;
}

short QuestionGenerator::getFontSize()
{
	return fontSize;
}

void QuestionGenerator::setFontSize(short fontSize)
{
	this->fontSize = fontSize;
}

bool QuestionGenerator::timeFinished()
{
	short* seconds = getSeconds();
	if (*seconds == 9) return true;
	delete seconds;
	return false;
}

void QuestionGenerator::setVisible(bool visible)
{
	this->visible = visible;
}

void QuestionGenerator::finish()
{
	visible = false;
	visibleAlternatives = false;
}
