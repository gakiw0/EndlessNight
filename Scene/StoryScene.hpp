#ifndef STORYSCENE_HPP
#define STORYSCENE_HPP

#include "Engine/IScene.hpp"
#include "UI/Component/Label.hpp"
#include <vector>
#include <string>
#include "Engine/AudioHelper.hpp"
#include <allegro5/allegro_audio.h>

class StoryScene : public Engine::IScene {
public:
    StoryScene(); 
    void Initialize() override;
    void Update(float deltaTime) override;
    void Draw() const override;
    void Terminate() override;

private:
    ALLEGRO_SAMPLE_ID bgmId;
    std::vector<std::string> lines;
    size_t currentLineIndex; 
    float textAlpha;      
    float fadeSpeed;     
    bool fadingIn;        
    float timeElapsed;    // To track time for automatic transition
    Engine::Label* currentLabel;
};

#endif // STORYSCENE_H