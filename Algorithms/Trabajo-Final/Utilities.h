#pragma once
#include "Macros.h"
#include "Enums.h"

inline Font^ getFont(float fontSize = 64.0, FontStyle fontStyle = FontStyle::Regular) {
	Drawing::Text::PrivateFontCollection^ fonts = gcnew Drawing::Text::PrivateFontCollection();

	fonts->AddFontFile(FONTS_PATH);

	Font^ font = gcnew Font(fonts->Families[0], fontSize, fontStyle);
	return font;
}