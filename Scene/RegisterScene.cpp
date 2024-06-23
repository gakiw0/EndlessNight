#include <fstream>
#include <algorithm>
#include <iostream>
#include <filesystem>

#include "RegisterScene.hpp"
#include "Engine/GameEngine.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "UI/Component/TextInput.hpp"
#include "Engine/User.hpp"

using namespace std;

void RegisterScene::Initialize()
{
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    Engine::ImageButton *btn;

    ReadUserData();

    AddNewObject(new Engine::Label("USER ID", "onesize.ttf", 80, halfW, halfH / 2, 255, 255, 255, 255, 0.5, 0.5));
    AddNewObject(new Engine::Label("PASSWORD", "onesize.ttf", 80, halfW, h - halfH, 255, 255, 255, 255, 0.5, 0.5));

    inputID = new Engine::TextInput("onesize.ttf", 60, halfW, halfH * 3 / 4, 600, 80, 255, 255, 255, 255, 0, 255, 255, 255, 0.5, 0.5);
    AddNewControlObject(inputID);
    inputPass = new Engine::TextInput("onesize.ttf", 60, halfW, h - halfH * 3 / 4, 600, 80, 255, 255, 255, 255, 0, 255, 255, 255, 0.5, 0.5);
    AddNewControlObject(inputPass);

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 200, h - halfH / 2 - 20, 400, 100);
    btn->SetOnClickCallback(std::bind(&RegisterScene::RegisterOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("REGISTER", "onesize.ttf", 48, halfW, h - halfH / 2 + 30, 0, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", 50, 50, 200, 100);
    btn->SetOnClickCallback(std::bind(&RegisterScene::BackOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Back", "onesize.ttf", 48, 150, 100, 0, 0, 0, 255, 0.5, 0.5));
}
void RegisterScene::Terminate()
{
    IScene::Terminate();
}

void RegisterScene::BackOnClick(int stage)
{
    Engine::GameEngine::GetInstance().ChangeScene("loginOrRegister");
}

void RegisterScene::ReadUserData()
{
    ifstream fin("../Resource/userDatas.txt");
    string line;

    while (getline(fin, line))
    {
        size_t pos = line.find(' ');

        User data;
        data.setName(line.substr(0, pos));
        data.setPassword(line.substr(pos + 1));

        UserIDs.push_back(data.getName());
    }
    fin.close();
}

void RegisterScene::RegisterOnClick(int stage)
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

        // エラーメッセージ用のラベルを作成し、表示
        errorLabel = new Engine::Label("Type your USER ID", "onesize.ttf", 40, halfW, h - halfH / 4, 255, 0, 0, 255, 0.5, 0.5);
        AddNewObject(errorLabel);
    }
    else if (inputPass->GetText() == "")
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
        errorLabel = new Engine::Label("Type your Password", "onesize.ttf", 40, halfW, h - halfH / 4, 255, 0, 0, 255, 0.5, 0.5);
        AddNewObject(errorLabel);
    }
    else
    {
        User::getInstance().setName(inputID->GetText());
        User::getInstance().setPassword(inputPass->GetText());
        if (find(UserIDs.begin(), UserIDs.end(), User::getInstance().getName()) == UserIDs.end())
        {
            std::ofstream writingFile;
            writingFile.open("../Resource/userDatas.txt", ios::app);
            writingFile << User::getInstance().getName() << " " << User::getInstance().getPassword() << endl;
            writingFile.close();

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
            errorLabel = new Engine::Label("This userID has already been used.", "onesize.ttf", 40, halfW, h - halfH / 4, 255, 0, 0, 255, 0.5, 0.5);
            AddNewObject(errorLabel);
        }
    }
}