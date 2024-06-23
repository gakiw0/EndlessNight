#include <fstream>
#include <algorithm>

#include "LoginScene.hpp"
#include "Engine/GameEngine.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "UI/Component/TextInput.hpp"

#include <iostream>

using namespace std;

void LoginScene::Initialize()
{
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    Engine::ImageButton *btn;
    Engine::ImageButton *btn1;

    ReadUserData();

    AddNewObject(new Engine::Label("USER ID", "pirulen.ttf", 80, halfW, halfH / 2, 255, 255, 255, 255, 0.5, 0.5));
    AddNewObject(new Engine::Label("PASSWORD", "pirulen.ttf", 80, halfW, h - halfH, 255, 255, 255, 255, 0.5, 0.5));

    inputID = new Engine::TextInput("pirulen.ttf", 60, halfW, halfH * 3 / 4, 600, 80, 255, 255, 255, 255, 0, 255, 255, 255, 0.5, 0.5);
    AddNewControlObject(inputID);
    inputPass = new Engine::TextInput("pirulen.ttf", 60, halfW, h - halfH * 3 / 4, 600, 80, 255, 255, 255, 255, 0, 255, 255, 255, 0.5, 0.5);
    AddNewControlObject(inputPass);

    btn = new Engine::ImageButton("settings/backbutton1.png", "settings/backbutton2.png", halfW - 200, h - halfH / 2 - 20, 400, 100);
    btn->SetOnClickCallback(std::bind(&LoginScene::LoginOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("LOGIN", "pirulen.ttf", 48, halfW, h - halfH / 2 + 30, 255, 255, 255, 255, 0.5, 0.5));


    btn1 = new Engine::ImageButton("settings/backbutton1.png", "settings/backbutton2.png", w - 10, h - 80, 192, 64, 1, 0);;
    btn1->SetOnClickCallback(std::bind(&LoginScene::BackOnClick, this, 1));
    AddNewControlObject(btn1);
    AddNewObject(new Engine::Label("Back", "pirulen.ttf", 24, w - 105, h - 50, 255, 255, 255, 255, 0.5, 0.5));
}
void LoginScene::Terminate()
{
    UserDatas.clear();
    IScene::Terminate();
}

void LoginScene::BackOnClick(int stage)
{
    Engine::GameEngine::GetInstance().ChangeScene("loginOrRegister");
}

void LoginScene::ReadUserData()
{
    ifstream fin("../Resource/userDatas.txt");
    string line;

    while (getline(fin, line))
    {
        size_t pos = line.find(' ');

        User data;
        data.setName(line.substr(0, pos));
        data.setPassword(line.substr(pos + 1));

        UserDatas.push_back(data);
    }
    fin.close();
}

void LoginScene::LoginOnClick(int stage)
{
    if (inputID->GetText() == "")
    {
        if (errorLabel)
        {
            RemoveObject(errorLabel->GetObjectIterator());
        }
        int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
        int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
        int halfW = w / 2;
        int halfH = h / 2;

        errorLabel = new Engine::Label("Type your USER ID", "pirulen.ttf", 40, halfW, h - halfH / 4, 255, 0, 0, 255, 0.5, 0.5);
        AddNewObject(errorLabel);
    }
    else if (inputPass->GetText() == "")
    {
        int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
        int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
        int halfW = w / 2;
        int halfH = h / 2;

        errorLabel = new Engine::Label("Type your Password", "pirulen.ttf", 40, halfW, h - halfH / 4, 255, 0, 0, 255, 0.5, 0.5);
        AddNewObject(errorLabel);
    }
    else
    {
        User::getInstance().setName(inputID->GetText());
        User::getInstance().setPassword(inputPass->GetText());

        if (find(UserDatas.begin(), UserDatas.end(), User::getInstance()) != UserDatas.end())
        {
            Engine::GameEngine::GetInstance().ChangeScene("start");
        }
        else
        {
            if (errorLabel)
            {
                RemoveObject(errorLabel->GetObjectIterator());
            }
            int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
            int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
            int halfW = w / 2;
            int halfH = h / 2;

            // エラーメッセージ用のラベルを作成し、表示
            errorLabel = new Engine::Label("User cannot be found,", "pirulen.ttf", 40, halfW, h - halfH / 4, 255, 0, 0, 255, 0.5, 0.5);
            AddNewObject(errorLabel);
        }
    }
}