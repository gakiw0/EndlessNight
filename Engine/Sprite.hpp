#ifndef SPRITE_HPP
#define SPRITE_HPP
#include <allegro5/color.h>
#include <string>

#include "UI/Component/Image.hpp"
#include "Engine/Point.hpp"

namespace Engine {
    class Sprite : public Image {
    public:
        float Rotation;
        Point Velocity;
        float scaleX, scaleY;
        ALLEGRO_COLOR Tint;
        float CollisionRadius = 0;
        explicit Sprite(std::string img, float x, float y, float w = 0, float h = 0, float anchorX = 0.5f, float anchorY = 0.5f, float rotation = 0, float vx = 0, float vy = 0, unsigned char r = 255, unsigned char g = 255, unsigned char b = 255, unsigned char a = 255, float scaleX = 1.0f, float scaleY = 1.0f);
        void Draw() const override;
        void Update(float deltaTime) override;
    };
}
#endif // SPRITE_HPP
