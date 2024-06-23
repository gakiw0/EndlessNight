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

public:
    explicit RegisterScene() = default;
    void Initialize() override;
    void Terminate() override;
    void ReadUserData();
    void RegisterOnClick(int stage);
    void BackOnClick(int stage);
};

#endif // REGISTERSCENE
