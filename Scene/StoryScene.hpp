#ifndef STORYSCENE_HPP
#define STORYSCENE_HPP

#include "Engine/IScene.hpp"
#include "UI/Component/Label.hpp"
#include <vector>
#include <string>

class StoryScene : public Engine::IScene {
public:
    StoryScene(const std::vector<std::string>& storyLines); 
    void Initialize() override;
    void Update(float deltaTime) override;
    void Draw() const override;
    void Terminate() override;

private:
    std::vector<std::string> lines;
    size_t currentLineIndex; 
    float textAlpha;      
    float fadeSpeed;     
    bool fadingIn;        
    float timeElapsed;    // To track time for automatic transition
    Engine::Label* currentLabel;
};

#endif // STORYSCENE_H