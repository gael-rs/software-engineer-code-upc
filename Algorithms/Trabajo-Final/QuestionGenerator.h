#pragma once
#include "StaticEntity.h"
#include "Exercise.h"

class QuestionGenerator: public StaticEntity
{
private:
	short userAnswer, fontSize;
	bool visible, visibleAlternatives;
	Exercise* exercise;
	Rectangle** alternativesSpace;
	short** alternatives;
	string provisionalMessage;
	clock_t timeStart;

public:
	QuestionGenerator();
	~QuestionGenerator();
	void showExercise(vector<short>* idxsAvailables);
	Exercise* getExercise();
	bool validAnswer();
	void showAlternatives(Graphics^ g, vector<short>* idxsAvailables);
	void paintExercise(Graphics^ g, vector<short>* idxsAvailables);
	void initialize(Rectangle* space);
	void generateAlternatives(vector<short>* idxsAvailables);
	short chooseAlternative(Point point);
	void setProvisionalMessage(string provisionalMessage);
	void paintBarTime(Graphics^ g);
	short* getSeconds();
	void checkTime();
	bool getVisible();
	short getFontSize();
	void setFontSize(short fontSize);
	bool timeFinished();
	void setVisible(bool visible);
	void finish();
};


