#ifndef TANKANIM_HPP
#define TANKANIM_HPP
#include "Enemy.hpp"
#include "Engine/Sprite.hpp"
#include "Engine/Point.hpp"

class TankAnim : public Enemy {
private:
	Sprite head;
	float targetRotation;
   
	//bool rotateHead;
public:
	TankAnim(int x, int y);
	void Draw() const override;
	void Update(float deltaTime) override;
	//void EnableHeadRotation(bool enable); 
   Engine::Point targetPosition; 
};
#endif // TANKANIM_HPP
