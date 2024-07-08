#pragma once
#include "MathOperationStrategy.h"

class MultiplicationStrategy: public MathOperationStrategy
{
public:
	MultiplicationStrategy();
	~MultiplicationStrategy();
	short operate(short number1, short number2);
};
