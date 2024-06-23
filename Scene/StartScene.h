#ifndef INC_ENDLESS_NIGHTS_STARTSCENE_H
#define INC_ENDLESS_NIGHTS_STARTSCENE_H

#include <allegro5/allegro_audio.h>
#include <memory>
#include <vector>

#include "Engine/IScene.hpp"
#include "Engine/Sprite.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "UI/Component/Image.hpp"
#include "Engine/AutoScroller.hpp"

class StartScene final : public Engine::IScene {
private:
    std::vector<std::shared_ptr<Engine::Image>> zombieFrames; // Vector to store zombie animation frames
    std::shared_ptr<Engine::ImageButton> btnStart;
    std::shared_ptr<Engine::Label> title;
    int currentFrame; // Current frame of animation
    float animationTime; // Time accumulator for animation
    float frameDuration;

public:
    explicit StartScene() = default;
    void Initialize() override;
    void Update(float deltaTime) override;
    void Draw() const override;
    void Terminate() override;
    void PlayOnClick(int stage);
    void SettingsOnClick(int stage);
    void ScoreBoardOnClick(int stage);
    void OnMouseDown(int button, int mx, int my) override;
    void LogoutOnClick(int stage);
    Engine::ImageButton *btn;
    Engine::ImageButton *btn1;
    Engine::ImageButton *btn2;
    Engine::ImageButton *btn3;
    Engine::Label *play;
    Engine::Label *logout;
    Engine::Image *border;
    Engine::Image *title1;
    AutoScroller* background;
    AutoScroller* depthground;
};

#endif // INC_ENDLESS_NIGHTS_STARTSCENE_H
