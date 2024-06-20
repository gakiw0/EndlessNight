#ifndef IMAGE_HPP
#define IMAGE_HPP
#include <allegro5/bitmap.h>
#include <memory>
#include <string>

#include "Engine/IObject.hpp"

namespace Engine {
    class Image : public IObject {
    public:
        std::shared_ptr<ALLEGRO_BITMAP> bmp;
        explicit Image(std::string img, float x, float y, float w = 0, float h = 0, float anchorX = 0, float anchorY = 0, float scaleX = 1.0f, float scaleY = 1.0f);
        void Draw() const override;
        int GetBitmapWidth() const;
        int GetBitmapHeight() const;

    private:
        float scaleX;
        float scaleY;
    };
}
#endif // IMAGE_HPP
