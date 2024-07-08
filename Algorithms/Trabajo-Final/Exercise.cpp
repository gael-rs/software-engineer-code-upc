#include "Exercise.h"

Exercise::Exercise(string operation)
{
	generateRandomOperation();
	mathOperationBehavior = nullptr;
}

Exercise::~Exercise() {}

MathOperationStrategy* Exercise::getMathOperationBehavior()
{
	return mathOperationBehavior;
}

short Exercise::results() {
	return mathOperationBehavior->operate(number1, number2);

}
bool Exercise::validAnswer(short answer) {
	return answer == results();
}

void Exercise::generateRandomNumbers() {
	this->number1 = rand() % 13;
	this->number2 = rand() % 13;
}

short Exercise::getNumber1()
{
	return this->number1;
}

short Exercise::getNumber2()
{
	return this->number2;
}

string Exercise::getOperation()
{
	return operation;
}

void Exercise::generateRandomOperation()
{
	string operations[3] = { "+", "-", "x" };
	this->operation = operations[rand() % 3];
	if (operation == "+" || operation == "suma") {
		mathOperationBehavior = new AddStrategy();
	}
	else if (operation == "-" || operation == "resta") {
		mathOperationBehavior = new SubstractionStrategy();
	}
	else if (operation == "x" || operation == "multiplicacion") {
		mathOperationBehavior = new MultiplicationStrategy();
	}
	else {
		mathOperationBehavior = new MathOperationStrategy();
	}
}
