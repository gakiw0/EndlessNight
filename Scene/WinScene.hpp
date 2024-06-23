#ifndef WINSCENE_HPP
#define WINSCENE_HPP
#include <allegro5/allegro_audio.h>
#include "Engine/IScene.hpp"


class WinScene final : public Engine::IScene {
private:
	ALLEGRO_SAMPLE_ID bgmId;
	float ticks;
	//std::shared_ptr<ALLEGRO_FONT> scoreFont;
	Engine::Label* playerNameLabel;
	Engine::Label* scoreLabel;
	int tempscore;
	int finalScore;
public:
	
	explicit WinScene() = default;
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void BackOnClick(int stage);
	
	void Draw() const override;
	void OnMouseDown(int button, int mx, int my) override;
	void OnMouseMove(int mx, int my) override;
	void OnMouseUp(int button, int mx, int my) override;
};

#endif // WINSCENE_HPP
