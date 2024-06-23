#ifndef LOGINSCENE_HPP
#define LOGINSCENE_HPP

#include "Engine/IScene.hpp"
#include "Engine/GameEngine.hpp"
#include "UI/Component/Label.hpp"
#include "UI/Component/TextInput.hpp"
#include "Firebase/FirebaseAuth.hpp"

class LoginScene : public Engine::IScene
{
private:
    Engine::TextInput *inputID;
    Engine::TextInput *inputPass;
    Engine::Label *errorLabel = nullptr;
    FirebaseAuth FirebaseAuth;
    void LoginOnClick(int stage);
    void BackOnClick(int stage);
    void ShowErrorMessage(const std::string &message);

public:
    explicit LoginScene() : FirebaseAuth() {}
    void Initialize() override;
    void Terminate() override;
};

#endif // LOGINSCENE_HPP
