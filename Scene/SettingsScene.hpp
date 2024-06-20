#ifndef SettingsScene_HPP
#define SettingsScene_HPP

#include <allegro5/allegro_audio.h>
#include <memory>
#include <map> 
#include "Engine/GameEngine.hpp"
#include "Engine/IScene.hpp"
#include "UI/Component/Text.hpp"

class SettingsScene final : public Engine::IScene {
private:
    std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;
public:
    explicit SettingsScene() = default;
    void Initialize() override;
    void Terminate() override;
    void PlayOnClick(int stage);
    void BackOnClick(int stage);
    void BGMSlideOnValueChanged(float value);
    void SFXSlideOnValueChanged(float value);
    void Update(float deltaTime) override;
    Engine::TextButton *up;
    Engine::TextButton *down;
    Engine::TextButton *left;
    Engine::TextButton *right;
    Engine::Label *upLabel;
    Engine::Label *downLabel;
    Engine::Label *leftLabel;
    Engine::Label *rightLabel;
    std::string upKey;
    std::string downKey;
    std::string leftKey;
    std::string rightKey;

    // Key mapping functionality
    void RebindKeyOnClick(const std::string& action); 
    void HandleInput(ALLEGRO_EVENT& event); 
    void OnMouseDown(int button, int mx, int my) override;
	void OnMouseMove(int mx, int my) override;
	void OnMouseUp(int button, int mx, int my) override;
    void OnKeyDown(int keyCode) override;
    
    std::map<std::string, int> customKeyMappings;
    
    bool isRebindingKey = false;
    std::string actionBeingRebound; 
};

#endif // SettingsScene_HPP
