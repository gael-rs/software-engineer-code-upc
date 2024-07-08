#pragma once
#include "Headers.h"
#include "MathOperationStrategy.h"
#include "AddStrategy.h"
#include "SubstractionStrategy.h"
#include "MultiplicationStrategy.h"


class Exercise
{
private:
	short number1;
	short number2;
	string operation;
	MathOperationStrategy* mathOperationBehavior;

public:
	Exercise(string operation = " ");
	~Exercise();
	MathOperationStrategy* getMathOperationBehavior();
	short results();
	bool validAnswer(short answer);
	void generateRandomNumbers();
	short getNumber1();
	short getNumber2();
	string getOperation();
	void generateRandomOperation();
};
