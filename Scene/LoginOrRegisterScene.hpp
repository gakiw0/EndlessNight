#ifndef LOGINORREGISTERSCENE_HPP
#define LOGINORREGISTERSCENE_HPP

#include <allegro5/allegro_audio.h>
#include <memory>
#include "Engine/IScene.hpp"
#include "Engine/AutoScroller.hpp"
#include "UI/Component/Label.hpp"
#include "Engine/AudioHelper.hpp"
#include <allegro5/allegro_audio.h>

class LoginOrRegisterScene final : public Engine::IScene
{
public:
    std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;
    explicit LoginOrRegisterScene() = default;
    void Initialize() override;
    void Terminate() override;
    void LoginOnClick(int stage);
    void RegisterOnClick(int stage);
    void Update(float deltaTime) override;
    void Draw() const override;
    Engine::Image *title1;
    Engine::ImageButton *btn;
    Engine::ImageButton *btn1;
    Engine::Label *login;
    Engine::Label *register1;
    AutoScroller* background;

};

#endif //LOGINORREGISTERSCENE_HPP
