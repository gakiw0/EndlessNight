#include "LoginScene.hpp"
#include "Engine/GameEngine.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "UI/Component/TextInput.hpp"
#include "Engine/UserManager.hpp"

void LoginScene::Initialize()
{
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    Engine::ImageButton *btn;

    AddNewObject(new Engine::Label("USER ID", "pirulen.ttf", 80, halfW, halfH / 2, 255, 255, 255, 255, 0.5, 0.5));
    AddNewObject(new Engine::Label("PASSWORD", "pirulen.ttf", 80, halfW, h - halfH, 255, 255, 255, 255, 0.5, 0.5));

    inputID = new Engine::TextInput("pirulen.ttf", 60, halfW, halfH * 3 / 4, 600, 80, 255, 255, 255, 255, 0, 255, 255, 255, 0.5, 0.5);
    AddNewControlObject(inputID);
    inputPass = new Engine::TextInput("pirulen.ttf", 60, halfW, h - halfH * 3 / 4, 600, 80, 255, 255, 255, 255, 0, 255, 255, 255, 0.5, 0.5);
    AddNewControlObject(inputPass);

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 200, h - halfH / 2 - 20, 400, 100);
    btn->SetOnClickCallback(std::bind(&LoginScene::LoginOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("LOGIN", "pirulen.ttf", 48, halfW, h - halfH / 2 + 30, 0, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", 50, 50, 200, 100);
    btn->SetOnClickCallback(std::bind(&LoginScene::BackOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, 150, 100, 0, 0, 0, 255, 0.5, 0.5));
}

void LoginScene::Terminate()
{
    IScene::Terminate();
}

void LoginScene::BackOnClick(int stage)
{
    Engine::GameEngine::GetInstance().ChangeScene("loginOrRegister");
}

void LoginScene::ShowErrorMessage(const std::string &message)
{
    if (errorLabel)
    {
        RemoveObject(errorLabel->GetObjectIterator());
    }
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;

    errorLabel = new Engine::Label(message, "pirulen.ttf", 40, halfW, h - halfH / 4, 255, 0, 0, 255, 0.5, 0.5);
    AddNewObject(errorLabel);
}

void LoginScene::LoginOnClick(int stage)
{
    std::string email = inputID->GetText();
    std::string password = inputPass->GetText();

    if (email.empty())
    {
        ShowErrorMessage("Type your USER ID");
        return;
    }
    else if (password.empty())
    {
        ShowErrorMessage("Type your Password");
        return;
    }

    std::string response = FirebaseAuth.signIn(email, password);
    std::string idToken = UserManager::getInstance().getIdToken();

    if (!idToken.empty())
    {
        Engine::GameEngine::GetInstance().ChangeScene("start");
    }
    else
    {
        ShowErrorMessage("Invalid USER ID or Password");
    }
}
