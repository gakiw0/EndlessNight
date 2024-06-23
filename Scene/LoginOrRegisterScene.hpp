#ifndef LOGINORREGISTERSCENE_HPP
#define LOGINORREGISTERSCENE_HPP

#include <allegro5/allegro_audio.h>
#include <memory>
#include "Engine/IScene.hpp"
class LoginOrRegisterScene final : public Engine::IScene
{
public:
    explicit LoginOrRegisterScene() = default;
    void Initialize() override;
    void Terminate() override;
    void LoginOnClick(int stage);
    void RegisterOnClick(int stage);
};

#endif //LOGINORREGISTERSCENE_HPP
