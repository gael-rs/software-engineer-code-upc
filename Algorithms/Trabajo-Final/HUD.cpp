#include "HUD.h"

HUD::HUD()
{
	time = -1, timePaused = 0, timeStartPaused = 0, timeActual = 0;
	sequenceFarmerAllied = new Sequence(2, 1, FARMER_ALLIED_PATH);
	sequenceFarmerAllied->setPlay(true);
	messageFarmerAllied = "";
	stoped = false;
}

HUD::~HUD()
{
	delete sequenceFarmerAllied;
}

clock_t HUD::getTime()
{
	return time;
}


short* HUD::getSeconds()
{
	short* seconds = new short;
	*seconds = (clock() - time) / CLOCKS_PER_SEC;
	*seconds = *seconds % 60;
	return seconds;
}

short* HUD::getMinutes()
{
	short* minutes = new short;
	*minutes = trunc((clock() - time) / CLOCKS_PER_SEC * 60);
	return minutes;
}

bool HUD::checkTimeFinish()
{
	return timeOfPlay - timeActual >= timeOfPlay;
}

void HUD::setTime(clock_t time)
{
	this->time = time;
}

void HUD::paintInfo(Graphics^ g, MomentPlay momentPlay, short money)
{
	paintTime(g);
	paintIndicator(g, momentPlay);
	paintFarmerAllied(g);
	paintMoney(g, money);
}


void HUD::paintTime(Graphics^ g)
{
	if (time == -1) time = clock();

	Font^ font = getFont(20);
	short* seconds = new short;

	timeActual = stoped ? timeActual : (timeOfPlay - ((clock() - timePaused) - time));

	*seconds = short(timeActual / CLOCKS_PER_SEC);
	short* minutes = new short;
	*minutes = trunc(*seconds / 60);
	*seconds = *seconds % 60;

	String^ timeString = (*minutes < 10 ? "0" : "") + Convert::ToString(*minutes) + ": " + (*seconds < 10 ? "0" : "") +
		Convert::ToString(*seconds);

	SizeF^ timeStringSize = g->MeasureString(timeString, font);

	g->DrawString(timeString, font, Brushes::WhiteSmoke,
		g->VisibleClipBounds.Width * 9 / 40 + g->VisibleClipBounds.Width * 3 / 40 - timeStringSize->Width / 2,
		g->VisibleClipBounds.Height * 1 / 13 - timeStringSize->Height * 65 / 100);


	delete seconds;
	delete minutes;
	delete font;
	delete timeString;
	delete timeStringSize;

}

void HUD::paintIndicator(Graphics^ g, MomentPlay momentPlay)
{
	Bitmap^ indicator = gcnew Bitmap(
		momentPlay == MomentPlay::Afternoon ? INDICATOR_SUN_PATH : INDICATOR_MOON_PATH
	);

	Rectangle* mold = new Rectangle(0, 0, indicator->Width, indicator->Height);
	Rectangle* zoom = new Rectangle(g->VisibleClipBounds.Width * 34 / 40 + 4,
		g->VisibleClipBounds.Height * 1 / 26 + 2, indicator->Width, indicator->Height);

	g->DrawImage(indicator, *zoom, *mold, GraphicsUnit::Pixel);

	delete indicator;
	delete zoom;
	delete mold;
}

void HUD::paintFarmerAllied(Graphics^ g)
{
	sequenceFarmerAllied->setX(g->VisibleClipBounds.Width * 19 / 40);
	sequenceFarmerAllied->setY(g->VisibleClipBounds.Height * 1 / 52 - 4);
	sequenceFarmerAllied->paint(g);

	String^ message = gcnew String(messageFarmerAllied.c_str());
	Font^ font = getFont(10.25);
	SizeF^ fontSize = g->MeasureString(message, font);

	g->DrawString(message, font, Brushes::Black,
		sequenceFarmerAllied->getX() + sequenceFarmerAllied->getWidth() * 1 / 4 + 10,
		sequenceFarmerAllied->getY() + 13
	);

	delete message;
	delete font;
	delete fontSize;
}

void HUD::talkFarmerAllied(string messageFarmerAllied)
{
	this->messageFarmerAllied = messageFarmerAllied;
}

void HUD::paintMoney(Graphics^ g, short money)
{
	Bitmap^ coin = gcnew Bitmap(COIN_PATH);

	Rectangle* mold = new Rectangle(0, 0, coin->Width, coin->Height);
	Rectangle* zoom = new Rectangle(g->VisibleClipBounds.Width * 2 / 40,
		g->VisibleClipBounds.Height * 1 / 26 - 5, coin->Width * 1.5, coin->Height * 1.5);

	g->DrawImage(coin, *zoom, *mold, GraphicsUnit::Pixel);

	String^ moneyString = (money < 10 ? "0" : "") + Convert::ToString(money);
	Font^ font = getFont(13.5);
	SizeF^ moneyStringSize = g->MeasureString(moneyString, font);

	g->DrawString(moneyString, font, Brushes::WhiteSmoke, zoom->X + coin->Width * 1.5 - 10,
		zoom->Y + coin->Height * 1.5 / 2 - moneyStringSize->Height / 2);

	delete moneyString;
	delete font;
	delete moneyStringSize;
	delete coin;
	delete zoom;
	delete mold;
}

void HUD::play()
{
	stoped = false;
	timePaused += clock() - timeStartPaused;
}

void HUD::stop()
{
	stoped = true;
	timeStartPaused = clock();
}

void HUD::initialize(Difficult difficult)
{
	timeOfPlay = clock_t((difficult == Normal ? 1 :0.5) * 60 * CLOCKS_PER_SEC);
}
