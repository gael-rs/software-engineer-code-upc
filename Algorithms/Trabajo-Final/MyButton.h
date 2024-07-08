#pragma once
#include "Utilities.h"

ref class MyButton : public Windows::Forms::Button
{
private:


public:
	MyButton();
	MyButton(int x, int y);
	~MyButton();
	void OnPaint(Windows::Forms::PaintEventArgs^ e) override;
};
