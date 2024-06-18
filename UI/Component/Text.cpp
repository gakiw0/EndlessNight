#include <functional>
#include <memory>
#include <iostream>

#include "Engine/Collider.hpp"
#include "Engine/GameEngine.hpp"
#include "Image.hpp"
#include "Text.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"

namespace Engine
{
	TextButton::TextButton(std::string img, std::string imgIn, float x, float y, float w, float h, float anchorX, float anchorY) : Image(img, x, y, w, h, anchorX, anchorY), imgOut(Resources::GetInstance().GetBitmap(img)), imgIn(Resources::GetInstance().GetBitmap(imgIn))
	{
		Point mouse = GameEngine::GetInstance().GetMousePosition();
		mouseIn = Collider::IsPointInBitmap(Point((mouse.x - Position.x) * GetBitmapWidth() / Size.x + Anchor.x * GetBitmapWidth(), (mouse.y - Position.y) * GetBitmapHeight() / Size.y + Anchor.y * GetBitmapHeight()), bmp);
		if (!mouseIn || !Enabled)
			bmp = imgOut;
		// else if(clicked) bmp = this->imgIn;
		else
			bmp = this->imgIn;
	}

	void TextButton::OnMouseDown(int button, int mx, int my)
	{
		if ((button & 1) && mouseIn && Enabled)
		{
			clicked = true;
			bmp = this->imgIn;
			// mouseIn = Collider::IsPointInBitmap(Point((mx - Position.x) * GetBitmapWidth() / Size.x + Anchor.x * GetBitmapWidth(), (my - Position.y) * GetBitmapHeight() / Size.y + Anchor.y * GetBitmapHeight()), bmp);
			// if (!mouseIn || !Enabled) bmp = imgOut;
			// else if(clicked) bmp = this->imgIn;
			// else bmp = this->imgIn;
			// std::cout << "lol" << std::endl;
		}
		else
		{
			clicked = false;
			bmp = imgOut;
		}
	}
	void TextButton::OnMouseMove(int mx, int my)
	{
		mouseIn = Collider::IsPointInBitmap(Point((mx - Position.x) * GetBitmapWidth() / Size.x + Anchor.x * GetBitmapWidth(), (my - Position.y) * GetBitmapHeight() / Size.y + Anchor.y * GetBitmapHeight()), bmp);
		if (!clicked  && !mouseIn || !Enabled)
			bmp = imgOut;
		
		else 
		{
			bmp = imgIn;
		}
	}
}