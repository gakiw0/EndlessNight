#ifndef WINSCENE_HPP
#define WINSCENE_HPP

#include "Engine/IScene.hpp"

class WinScene final : public Engine::IScene {
private:

public:
	explicit WinScene() = default;
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
};

#endif // WINSCENE_HPP
