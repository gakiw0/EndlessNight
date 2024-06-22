#include <allegro5/allegro_audio.h>
#include <functional>
#include <memory>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Image.hpp"
#include "UI/Component/Label.hpp"
#include "PlayScene.hpp"
#include "UI/Component/Slider.hpp"
#include "SettingsScene.hpp"

void SettingsScene::Initialize()
{
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;

    upKey = Engine::GameEngine::GetInstance().GetKey("MoveUp");
    downKey = Engine::GameEngine::GetInstance().GetKey("MoveDown");
    leftKey = Engine::GameEngine::GetInstance().GetKey("MoveLeft");
    rightKey = Engine::GameEngine::GetInstance().GetKey("MoveRight");

    Engine::Image *stoneWall;
    stoneWall = new Engine::Image("settings/stoneboard.png", 50, 50, w - 100, h - 100);
    AddNewObject(stoneWall);

    AddNewObject(
        new Engine::Label("Settings", "pirulen.ttf", 48, halfW, 120, 255, 255, 255, 255, 0.5,
                          0.5));

    Engine::ImageButton *music;
    music = new Engine::ImageButton("settings/music.png", "settings/music.png", halfW - 144, 250 - 48 + 16, 64, 64);
    AddNewControlObject(music);

    Slider *sliderBGM, *sliderSFX;
    sliderBGM = new Slider(40 + halfW - 95, 250, 190, 4);
    sliderBGM->SetOnValueChangedCallback(
        std::bind(&SettingsScene::BGMSlideOnValueChanged, this, std::placeholders::_1));
    AddNewControlObject(sliderBGM);
    // AddNewObject(
    //     new Engine::Label("BGM: ", "pirulen.ttf", 28, 40 + halfW - 60 - 95, halfH - 50, 255, 255, 255, 255, 0.5,
    //                       0.5));
    // sliderSFX = new Slider(40 + halfW - 95, halfH + 50 - 2, 190, 4);
    // sliderSFX->SetOnValueChangedCallback(
    //     std::bind(&SettingsScene::SFXSlideOnValueChanged, this, std::placeholders::_1));
    // AddNewControlObject(sliderSFX);
    // AddNewObject(
    //     new Engine::Label("SFX: ", "pirulen.ttf", 28, 40 + halfW - 60 - 95, halfH + 50, 255, 255, 255, 255, 0.5,
    //                       0.5));

    Engine::ImageButton *btn;
    btn = new Engine::ImageButton("settings/backbutton1.png", "settings/backbutton2.png", halfW - 144, halfH + 216, 288, 96);
    btn->SetOnClickCallback(std::bind(&SettingsScene::BackOnClick, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW, halfH + 216 + 48, 255, 255, 255, 255, 0.5, 0.5));

    up = new Engine::TextButton("stage-select/border.png", "stage-select/border.png", halfW - 248, halfH - 48, 96, 96);
    AddNewControlObject(up);
    upLabel = new Engine::Label(upKey, "pirulen.ttf", 36, halfW - 248 + 48, halfH, 255, 255, 255, 255, 0.5, 0.5);
    AddNewObject(upLabel);
    Engine::ImageButton *upborder = new Engine::ImageButton("settings/backbutton1.png", "settings/backbutton1.png", w/4 - 144, halfH - 48, 288, 96);
    AddNewObject(upborder);
    AddNewObject(
        new Engine::Label("UP", "pirulen.ttf", 36, halfW - 248 - 152, halfH, 255, 255, 255, 255, 0.5,
                          0.5));

    down = new Engine::TextButton("stage-select/border.png", "stage-select/border.png", halfW + 248 - 96, halfH - 48, 96, 96);
    AddNewControlObject(down);
    downLabel = new Engine::Label(downKey, "pirulen.ttf", 36, halfW + 248 - 48, halfH, 255, 255, 255, 255, 0.5, 0.5);
    AddNewObject(downLabel);
    Engine::ImageButton *downborder = new Engine::ImageButton("settings/backbutton1.png", "settings/backbutton1.png", 3 * w/4 - 144, halfH - 48, 288, 96);
    AddNewObject(downborder);
    AddNewObject(
        new Engine::Label("DOWN", "pirulen.ttf", 36, halfW + 248 + 152, halfH, 255, 255, 255, 255, 0.5,
                          0.5));


    left = new Engine::TextButton("stage-select/border.png", "stage-select/border.png", halfW - 248, halfH + 96, 96, 96);
    AddNewControlObject(left);
    leftLabel = new Engine::Label(leftKey, "pirulen.ttf", 36, halfW - 248 + 48, halfH + 150 - 6, 255, 255, 255, 255, 0.5, 0.5);
    AddNewObject(leftLabel);
    Engine::ImageButton *leftborder = new Engine::ImageButton("settings/backbutton1.png", "settings/backbutton1.png", w/4 - 144, halfH + 96, 288, 96);
    AddNewObject(leftborder);
    AddNewObject(
        new Engine::Label("LEFT", "pirulen.ttf", 36, halfW - 248 - 152, halfH + 150 - 6, 255, 255, 255, 255, 0.5,
                          0.5));


    right = new Engine::TextButton("stage-select/border.png", "stage-select/border.png", halfW + 248 - 96, halfH + 96, 96, 96);
    AddNewControlObject(right);
    rightLabel = new Engine::Label(rightKey, "pirulen.ttf", 36, halfW + 248 - 48, halfH + 150 - 6, 255, 255, 255, 255, 0.5, 0.5);
    AddNewObject(rightLabel);
    Engine::ImageButton *rightborder = new Engine::ImageButton("settings/backbutton1.png", "settings/backbutton1.png",3 * w/4 - 144, halfH + 96, 288, 96);
    AddNewObject(rightborder);
    AddNewObject(
        new Engine::Label("RIGHT", "pirulen.ttf", 36, halfW + 248 + 152, halfH + 150 - 6, 255, 255, 255, 255, 0.5,
                          0.5));


    // Not safe if release resource while playing, however we only free while change scene, so it's fine.
    bgmInstance = AudioHelper::PlaySample("select.ogg", true, AudioHelper::BGMVolume);
    sliderBGM->SetValue(AudioHelper::BGMVolume);
    sliderBGM->SetValue(AudioHelper::SFXVolume);
}

void SettingsScene::Terminate()
{
    AudioHelper::StopSample(bgmInstance);
    bgmInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
    IScene::Terminate();
}

void SettingsScene::Update(float deltaTime)
{
    upLabel->isBlinking = up->clicked;
    downLabel->isBlinking = down->clicked;
    leftLabel->isBlinking = left->clicked;
    rightLabel->isBlinking = right->clicked;

    Engine::Label *labels[] = {upLabel, downLabel, leftLabel, rightLabel};

    for (auto &label : labels)
    {
        if (label->isBlinking)
        {
            label->blinkTimer += deltaTime;
            if (label->blinkTimer >= 0.4f)
            {
                label->blinkTimer = 0.0f;
                label->Visible = !label->Visible;
            }
        }
        else
        {
            label->Visible = true; // Ensure label is visible when not blinking
        }
    }
}

void SettingsScene::PlayOnClick(int stage)
{
    // PlayScene *scene = dynamic_cast<PlayScene *>(Engine::GameEngine::GetInstance().GetScene("play"));
    // scene->MapId = stage;
    // Engine::GameEngine::GetInstance().ChangeScene("play");
}

void SettingsScene::BGMSlideOnValueChanged(float value)
{
    AudioHelper::ChangeSampleVolume(bgmInstance, value);
    AudioHelper::BGMVolume = value;
    AudioHelper::SFXVolume = value;
}

void SettingsScene::SFXSlideOnValueChanged(float value)
{
    // AudioHelper::SFXVolume = value;
}

void SettingsScene::BackOnClick(int stage)
{

    Engine::GameEngine::GetInstance().ChangeScene("start");
}

void SettingsScene::RebindKeyOnClick(const std::string &action)
{

    isRebindingKey = true;
    actionBeingRebound = action;
    // You might want to update the UI here to indicate that the game is waiting
    // for a key press (e.g., change the button text to "Press Key").
}

void SettingsScene::OnKeyDown(int keyCode)
{
    IScene::OnKeyDown(keyCode);

    if (up->clicked)
    {
        Engine::GameEngine::GetInstance().SetKeyMapping("MoveUp", ALLEGRO_KEY_UNKNOWN);
        if (keyCode >= ALLEGRO_KEY_A && keyCode <= ALLEGRO_KEY_Z && !IsKeyInUse(keyCode))
        {
            
            Engine::GameEngine::GetInstance().SetKeyMapping("MoveUp", keyCode);
            upKey = Engine::GameEngine::GetInstance().GetKey("MoveUp");
            upLabel->Text = upKey;
            up->clicked = !up->clicked;
        }
    }
    if (down->clicked)
    {
        Engine::GameEngine::GetInstance().SetKeyMapping("MoveDown", ALLEGRO_KEY_UNKNOWN);
        if (keyCode >= ALLEGRO_KEY_A && keyCode <= ALLEGRO_KEY_Z && !IsKeyInUse(keyCode))
        {
            Engine::GameEngine::GetInstance().SetKeyMapping("MoveDown", keyCode);
            downKey = Engine::GameEngine::GetInstance().GetKey("MoveDown");
            downLabel->Text = downKey;
            down->clicked = !down->clicked;
        }
    }
    if (left->clicked)
    {
        Engine::GameEngine::GetInstance().SetKeyMapping("MoveLeft", ALLEGRO_KEY_UNKNOWN);
        if (keyCode >= ALLEGRO_KEY_A && keyCode <= ALLEGRO_KEY_Z && !IsKeyInUse(keyCode))
        {
            Engine::GameEngine::GetInstance().SetKeyMapping("MoveLeft", keyCode);
            leftKey = Engine::GameEngine::GetInstance().GetKey("MoveLeft");
            leftLabel->Text = leftKey;
            left->clicked = !left->clicked;
        }
    }
    if (right->clicked)
    {
        Engine::GameEngine::GetInstance().SetKeyMapping("MoveRight", ALLEGRO_KEY_UNKNOWN);
        if (keyCode >= ALLEGRO_KEY_A && keyCode <= ALLEGRO_KEY_Z && !IsKeyInUse(keyCode))
        {
            Engine::GameEngine::GetInstance().SetKeyMapping("MoveRight", keyCode);
            rightKey = Engine::GameEngine::GetInstance().GetKey("MoveRight");
            rightLabel->Text = rightKey;
            right->clicked = !right->clicked;
        }
        // std::cout << keyName << std::endl;
    }
}

void SettingsScene::OnMouseDown(int button, int mx, int my)
{
    IScene::OnMouseDown(button, mx, my);
}

void SettingsScene::OnMouseMove(int mx, int my)
{
    IScene::OnMouseMove(mx, my);
}

void SettingsScene::OnMouseUp(int button, int mx, int my)
{
    IScene::OnMouseUp(button, mx, my);
}

bool SettingsScene::IsKeyInUse(int keyCode)
{
    // Check if the keyCode is already assigned to any other action

    return (keyCode == Engine::GameEngine::GetInstance().GetKeyMapping("MoveUp") ||
            keyCode == Engine::GameEngine::GetInstance().GetKeyMapping("MoveDown") ||
            keyCode == Engine::GameEngine::GetInstance().GetKeyMapping("MoveLeft") ||
            keyCode == Engine::GameEngine::GetInstance().GetKeyMapping("MoveRight"));
}