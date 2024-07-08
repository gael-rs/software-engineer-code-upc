#include "CustomButton.h"

CustomButton::CustomButton(string text, string bgButton, float fontSize) : CustomUi(fontSize)
{
	this->scale = 1.0;
	this->text = new char[text.size()];
	strcpy(this->text, text.c_str());

	this->bgButton = new char[bgButton.size()];
	strcpy(this->bgButton, bgButton.c_str());

	this->column = 0;
	hovered = clicked = inScreen = false;
}

CustomButton::~CustomButton()
{
	delete[] bgButton;
	delete[] text;
}

void CustomButton::paint(Graphics^ g, bool force)
{
	if (hovered) return hover(g, false, force);
	if (clicked && enabled)  return click(g, false);

	if (inScreen) {
		String^ path = gcnew String(this->bgButton);
		Bitmap^ backgroundImage = gcnew Bitmap(path);

		width = backgroundImage->Width / 3;
		height = backgroundImage->Height;

		String^ textButton = gcnew String(text);
		Font^ font = getFont(fontSize);
		SizeF^ textSize = g->MeasureString(textButton, font);

		Rectangle* cropRect = new Rectangle(0, 0, width, height);

		width *= scale;
		height *= scale;

		Rectangle* zoom = new Rectangle(x, y, width, height);

		g->DrawImage(backgroundImage, *zoom, *cropRect, GraphicsUnit::Pixel);

		g->DrawString(textButton, font, (
			enabled ? Brushes::White : gcnew SolidBrush(Color::FromArgb(191, 191, 192))
			),
			x + width / 2 - textSize->Width / 2,
			y + height / 2 - textSize->Height / 2);

		delete textButton;
		delete font;
		delete textSize;
		delete cropRect;
		delete path;
		delete backgroundImage;
	}

}

void CustomButton::hover(Graphics^ g, bool withSound, bool force)
{
	if (inScreen && (((!hovered || withSound) && enabled) || force)) {
		Media::SoundPlayer^ effectSoundHover = nullptr;
		effectSoundHover = gcnew Media::SoundPlayer(BUTTON_HOVER_SOUND_PATH);

		String^ path = gcnew String(this->bgButton);
		Bitmap^ backgroundImage = gcnew Bitmap(path);

		width = backgroundImage->Width / 3;
		height = backgroundImage->Height;

		String^ textButton = gcnew String(text);
		column = 2;
		Font^ font = getFont(fontSize);
		SizeF^ textSize = g->MeasureString(textButton, font);

		Rectangle* cropRect = new Rectangle(width * column, 0, width, height);

		width *= scale;
		height *= scale;

		Rectangle* zoom = new Rectangle(x, y, width, height);

		g->DrawImage(backgroundImage, *zoom, *cropRect, GraphicsUnit::Pixel);

		g->DrawString(textButton, font, Brushes::White,
			x + width / 2 - textSize->Width / 2,
			y + height / 2 - textSize->Height / 2);

		hovered = true;
		if (effectSoundHover != nullptr) effectSoundHover->Play();

		delete font;
		delete textSize;
		delete cropRect;
		delete zoom;
		delete textButton;
		delete path;
		delete backgroundImage;
		delete effectSoundHover;
	}
}

void CustomButton::click(Graphics^ g, bool withSound)
{
	// if (inScreen && !enabled) return paint(g);

	if (inScreen && enabled) {
		String^ textButton = gcnew String(text);
		String^ path = gcnew String(this->bgButton);
		Bitmap^ backgroundImage = gcnew Bitmap(path);

		width = backgroundImage->Width / 3;
		height = backgroundImage->Height;

		column = 1;
		clicked = true;
		Font^ font = getFont(fontSize - 2);
		Rectangle* cropRect = new Rectangle(width * column, 0, width, height);

		width *= scale;
		height *= scale;

		Rectangle* zoom = new Rectangle(getRectangle()->Location.X, getRectangle()->Location.Y, width, height);
		SizeF^ textSize = g->MeasureString(textButton, font);

		g->DrawImage(backgroundImage, *zoom, *cropRect, GraphicsUnit::Pixel);

		g->DrawString(textButton, font, Brushes::LightGray,
			x + width / 2 - textSize->Width / 2,
			y + height / 2 - textSize->Height / 2);

		if (withSound) {
			Media::SoundPlayer^ effectSoundClick = gcnew Media::SoundPlayer(BUTTON_CLICK_SOUND_PATH);
			effectSoundClick->Play();
			delete effectSoundClick;
		}

		delete font;
		delete textSize;
		delete cropRect;
		delete zoom;
		delete textButton;
		delete path;
		delete backgroundImage;
	}
}

bool CustomButton::getHovered()
{
	return hovered;
}

void CustomButton::setHovered(bool hovered) {
	this->hovered = hovered;
}

bool CustomButton::getClicked()
{
	return clicked;
}

void CustomButton::setClicked(bool clicked)
{
	this->clicked = clicked;
}

float CustomButton::getScale()
{
	return scale;
}

void CustomButton::setScale(float scale)
{
	this->scale = scale;
}

