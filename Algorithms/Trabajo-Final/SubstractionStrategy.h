#pragma once
#include "MathOperationStrategy.h"

class SubstractionStrategy : public MathOperationStrategy
{
public:
	SubstractionStrategy();
	~SubstractionStrategy();
	short operate(short number1, short number2);
};