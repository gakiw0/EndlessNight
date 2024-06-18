#ifndef WINSCENE_HPP
#define WINSCENE_HPP
#include <allegro5/allegro_audio.h>
#include "Engine/IScene.hpp"
#include "UI/Component/Text.hpp"


class WinScene final : public Engine::IScene {
private:
	float ticks;
	ALLEGRO_SAMPLE_ID bgmId;
	//std::shared_ptr<ALLEGRO_FONT> scoreFont;
	std::string playerName; // To store the entered name
   bool drawTextInputBox{false}; // Flag to control text input visibility
	bool active = false;
	Engine::Label* playerNameLabel;
	Engine::Label* scoreLabel;
	bool clicked = false;
	Engine::TextButton *input;
	int tempscore;
public:
	
	explicit WinScene() = default;
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void BackOnClick(int stage);
	
	void markScore();
	void Draw() const override;
	void SaveScoreToFile(const std::string& name, int score);
	void OnMouseDown(int button, int mx, int my) override;
	void OnMouseMove(int mx, int my) override;
	void OnMouseUp(int button, int mx, int my) override;
	void OnKeyDown(int keyCode) override;
	std::list<int> keyStrokes;
	void TextClick();
	std::string GetCurrentDateTime();
};

#endif // WINSCENE_HPP
