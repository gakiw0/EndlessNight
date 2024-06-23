#ifndef LOGINSCENE_HPP
#define LOGINSCENE_HPP

#include <memory>
#include <string>
#include <vector>
#include "Engine/IScene.hpp"
#include "UI/Component/Label.hpp"
#include "UI/Component/TextInput.hpp"
#include "Engine/User.hpp"
#include "Engine/AutoScroller.hpp"
#include "UI/Component/ImageButton.hpp"


class LoginScene final : public Engine::IScene
{
private:
    std::vector<User> UserDatas;
    Engine::TextInput *inputID;
    Engine::TextInput *inputPass;
    Engine::Label *errorLabel;
    Engine::ImageButton *btn;
    Engine::ImageButton *btn1;
    Engine::Label *login;
    Engine::Label *back;
    Engine::Label *userId;
    Engine::Label *password;
    AutoScroller* background;
public:
    explicit LoginScene() = default;
    void Initialize() override;
    void Update(float deltaTime) override;
    void Draw() const override;
    void Terminate() override;
    void LoginOnClick(int stage);
    void ReadUserData();
    void BackOnClick(int stage);
    
};

#endif // LOGINSCENE_HPP
