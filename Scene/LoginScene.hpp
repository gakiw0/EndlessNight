#ifndef LOGINSCENE_HPP
#define LOGINSCENE_HPP

#include <memory>
#include <string>
#include <vector>
#include "Engine/IScene.hpp"
#include "UI/Component/Label.hpp"
#include "UI/Component/TextInput.hpp"
#include "Engine/User.hpp"


class LoginScene final : public Engine::IScene
{
private:
    std::vector<User> UserDatas;
    Engine::TextInput *inputID;
    Engine::TextInput *inputPass;
    Engine::Label *errorLabel;
public:
    explicit LoginScene() = default;
    void Initialize() override;
    void Terminate() override;
    void LoginOnClick(int stage);
    void ReadUserData();
    void BackOnClick(int stage);
};

#endif // LOGINSCENE_HPP
