#include "Sprite.hpp"
#include "Engine/Resources.hpp"

namespace Engine {
    Sprite::Sprite(std::string img, float x, float y, float w, float h, float anchorX, float anchorY, float rotation, float vx, float vy, unsigned char r, unsigned char g, unsigned char b, unsigned char a, float scaleX, float scaleY) :
        Image(img, x, y, w, h, anchorX, anchorY, scaleX, scaleY),scaleX(scaleX),scaleY(scaleY), Rotation(rotation), Velocity(vx, vy), Tint(al_map_rgba(r, g, b, a)) {
    }

    void Sprite::Draw() const {
        al_draw_tinted_scaled_rotated_bitmap(bmp.get(), Tint, Anchor.x * GetBitmapWidth(), Anchor.y * GetBitmapHeight(),
			Position.x, Position.y, Size.x * scaleX / GetBitmapWidth(), Size.y * scaleY / GetBitmapHeight(), Rotation, 0);
    }

    void Sprite::Update(float deltaTime) {
        Position.x += Velocity.x * deltaTime;
        Position.y += Velocity.y * deltaTime;
    }
}
