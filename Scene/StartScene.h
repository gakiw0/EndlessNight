//
// Created by Hsuan on 2024/4/10.
//

#ifndef INC_EndlessNights_STARTSCENE_H
#define INC_EndlessNights_STARTSCENE_H

#include <allegro5/allegro_audio.h>
#include <memory>
#include "Engine/IScene.hpp"
#include "Engine/Sprite.hpp"
#include "Enemy/TankAnim.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"

class StartScene final : public Engine::IScene
{
public:
    explicit StartScene() = default;
    void Initialize() override;
    void Terminate() override;
    void PlayOnClick(int stage);
    void SettingsOnClick(int stage);
    void Update(float deltaTime) override;
    void Draw() const override;
    void OnMouseDown(int button, int mx, int my) override;
    TankAnim *tankAnim;
    Engine::ImageButton *btn;
    Engine::ImageButton *btn1;
    Engine::Label *play;
    Engine::Label *settings;
};

#endif // INC_EndlessNights_STARTSCENE_H
