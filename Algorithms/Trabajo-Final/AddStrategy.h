#pragma once
#include "MathOperationStrategy.h"

class AddStrategy: public MathOperationStrategy
{
public:
	AddStrategy();
	~AddStrategy();
	short operate(short number1, short number2);
};