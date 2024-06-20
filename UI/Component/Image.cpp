#include <allegro5/allegro.h>
#include <memory>

#include "Engine/IObject.hpp"
#include "Image.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"

namespace Engine {
    Image::Image(std::string img, float x, float y, float w, float h, float anchorX, float anchorY, float scaleX, float scaleY) :
        IObject(x, y, w, h, anchorX, anchorY), scaleX(scaleX), scaleY(scaleY) {
        if (Size.x == 0 && Size.y == 0) {
            bmp = Resources::GetInstance().GetBitmap(img);
            Size.x = GetBitmapWidth();
            Size.y = GetBitmapHeight();
        }
        else if (Size.x == 0) {
            bmp = Resources::GetInstance().GetBitmap(img);
            Size.x = GetBitmapWidth() * Size.y / GetBitmapHeight();
        }
        else if (Size.y == 0) {
            bmp = Resources::GetInstance().GetBitmap(img);
            Size.y = GetBitmapHeight() * Size.x / GetBitmapWidth();
        }
        else {
            bmp = Resources::GetInstance().GetBitmap(img, Size.x, Size.y);
        }
    }

    void Image::Draw() const {
        al_draw_scaled_bitmap(bmp.get(), 0, 0, GetBitmapWidth(), GetBitmapHeight(),
            Position.x - Anchor.x * GetBitmapWidth() * scaleX, Position.y - Anchor.y * GetBitmapHeight() * scaleY,
            Size.x * scaleX, Size.y * scaleY, 0);
    }

    int Image::GetBitmapWidth() const {
        return al_get_bitmap_width(bmp.get());
    }

    int Image::GetBitmapHeight() const {
        return al_get_bitmap_height(bmp.get());
    }
}
