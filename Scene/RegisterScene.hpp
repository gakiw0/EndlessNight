#ifndef REGISTERSCENE
#define REGISTERSCENE

#include <memory>
#include <string>
#include <vector>
#include "Engine/IScene.hpp"
#include "UI/Component/Label.hpp"
#include "UI/Component/TextInput.hpp"
#include "Scene/LoginScene.hpp"

class RegisterScene final : public Engine::IScene
{
private:
    std::vector<std::string> UserIDs;
    Engine::TextInput *inputID;
    Engine::TextInput *inputPass;
    Engine::Label *errorLabel;
    Engine::ImageButton *btn;
    Engine::ImageButton *btn1;
    Engine::Label *registerLabel;
    Engine::Label *back;
    Engine::Label *userId;
    Engine::Label *password;
    AutoScroller *background;

public:
    explicit RegisterScene() = default;
    void Initialize() override;
    void Terminate() override;
    void Update(float deltaTime) override;
    void Draw() const override;
    void ReadUserData();
    void RegisterOnClick(int stage);
    void BackOnClick(int stage);
};

#endif // REGISTERSCENE
