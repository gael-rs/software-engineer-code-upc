#include "Fence.h"

Fence::Fence(short x, short y, short heightExpect) : StaticEntity(x, y)
{
	this->heightExpect = heightExpect;
}

Fence::~Fence()
{
}

void Fence::paint(Graphics^ g)
{
	Bitmap^ fence = gcnew Bitmap(FENCE_PATH);

	width = fence->Width / 4;
	height = fence->Height;

	Rectangle* mold = new Rectangle(column * width, row * height, width, height);
	Rectangle* zoom = new Rectangle(x, y, g->VisibleClipBounds.Width * 1 / 40
		, heightExpect != 0 ? heightExpect : g->VisibleClipBounds.Width * 2 / 26);

	g->DrawImage(fence, *zoom, *mold, GraphicsUnit::Pixel);

	delete zoom;
	delete mold;
	delete fence;
}
