#include <functional>
#include <memory>
#include <iostream>

#include "Engine/Collider.hpp"
#include "Engine/GameEngine.hpp"
#include "Image.hpp"
#include "Pause.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"
#include "Scene/PlayScene.hpp"

namespace Engine
{
   PauseButton::PauseButton(std::string img, std::string imgIn, float x, float y, float w, float h, float anchorX, float anchorY) : Image(img, x, y, w, h, anchorX, anchorY), imgOut(Resources::GetInstance().GetBitmap(img)), imgIn(Resources::GetInstance().GetBitmap(imgIn))
   {
      Point mouse = GameEngine::GetInstance().GetMousePosition();
      mouseIn = Collider::IsPointInBitmap(Point((mouse.x - Position.x) * GetBitmapWidth() / Size.x + Anchor.x * GetBitmapWidth(), (mouse.y - Position.y) * GetBitmapHeight() / Size.y + Anchor.y * GetBitmapHeight()), bmp);
      if (!mouseIn || !Enabled)
         bmp = imgOut;
      // else if(clicked) bmp = this->imgIn;
      else
         bmp = this->imgIn;
   }

   void PauseButton::OnMouseDown(int button, int mx, int my)
   {
      if ((button & 1) && mouseIn && Enabled)
      {
         clicked = !clicked;
         if(clicked) bmp = this->imgIn;
         else bmp = imgOut;
         getPlayScene()->PauseGame();

         // mouseIn = Collider::IsPointInBitmap(Point((mx - Position.x) * GetBitmapWidth() / Size.x + Anchor.x * GetBitmapWidth(), (my - Position.y) * GetBitmapHeight() / Size.y + Anchor.y * GetBitmapHeight()), bmp);
         // if (!mouseIn || !Enabled) bmp = imgOut;
         // else if(clicked) bmp = this->imgIn;
         // else bmp = this->imgIn;
         // std::cout << "lol" << std::endl;
      }
      else
      {
         //clicked = false;
         // if(clicked) bmp = this->imgIn;
         // else bmp = imgOut;
         //bmp = imgOut;
         //getPlayScene()->PauseGame();
      }
   }
   void PauseButton::OnMouseMove(int mx, int my)
   {
      mouseIn = Collider::IsPointInBitmap(Point((mx - Position.x) * GetBitmapWidth() / Size.x + Anchor.x * GetBitmapWidth(), (my - Position.y) * GetBitmapHeight() / Size.y + Anchor.y * GetBitmapHeight()), bmp);
      // if (!clicked && !mouseIn || !Enabled)
      //    bmp = imgOut;

      // else
      // {
      //    bmp = imgIn;
      // }
      if (!clicked && !mouseIn || !Enabled) bmp = imgOut;
      else if(clicked && !mouseIn || !Enabled) bmp = imgIn;
      //else if(clicked && mouseIn || Enabled) bmp = imgOut;
      else if(!clicked && mouseIn || Enabled) bmp = imgIn;
      //else if(clicked && mouseIn || Enabled) bmp = imgOut;
		else bmp = imgIn;
   }

   PlayScene *PauseButton::getPlayScene()
   {
      return dynamic_cast<PlayScene *>(Engine::GameEngine::GetInstance().GetActiveScene());
   }
}
