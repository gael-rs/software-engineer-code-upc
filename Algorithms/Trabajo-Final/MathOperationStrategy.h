#pragma once

class MathOperationStrategy
{
private:

public:
	MathOperationStrategy();
	~MathOperationStrategy();
	virtual short operate(short number1, short number2) { return 0; };
};


