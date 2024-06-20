#ifndef LOSESCENE_HPP
#define LOSESCENE_HPP

#include "Engine/IScene.hpp"

class LoseScene final : public Engine::IScene {
private:

public:
	explicit LoseScene() = default;
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
};

#endif // LOSESCENE_HPP
