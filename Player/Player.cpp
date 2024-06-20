#include "Player.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"
#include "Scene/PlayScene.hpp"

#include <string>

using namespace std;

Player::Player(float x, float y, int hp)
    : Engine::Sprite("PixelArt/RightLeftWalk/pixil-frame-0.png", x, y, 0, 0, 0.5f, 0.5f, 0, 0, 0, 255, 255, 255, 255, 2.0f, 2.0f), hp(hp), frame(0), elapsedTime(0), timeSinceLastShot(0), shootCooldown(0.5f)
{
    Anchor = Engine::Point(0.5f, 0.5f);
    CollisionRadius = 40;

    // Initialize the list of image paths for different directions
    rightLeftWalkImages = {
        "PixelArt/RightLeftWalk/pixil-frame-1.png",
        "PixelArt/RightLeftWalk/pixil-frame-2.png"};

    upWalkImages = {
        "PixelArt/UpWalk/pixil-frame-0.png",
        "PixelArt/UpWalk/pixil-frame-1.png",
        "PixelArt/UpWalk/pixil-frame-2.png"};

    downWalkImages = {
        "PixelArt/DownWalk/pixil-frame-1.png",
        "PixelArt/DownWalk/pixil-frame-2.png"};

    // Use right-left walk images as the default
    imagePath = rightLeftWalkImages;
}

PlayScene *Player::getPlayScene()
{
    return dynamic_cast<PlayScene *>(Engine::GameEngine::GetInstance().GetActiveScene());
}

void Player::Update(float deltaTime)
{
    Engine::GameEngine &gameEngine = Engine::GameEngine::GetInstance();
    Velocity.x = 0;
    Velocity.y = 0;
    bool moving = false;

    // Define radians for each direction using Allegro's constants
    float newRotation = fakeRotation; // Use existing fakeRotation from the Sprite class.

    // WASD key movements for straight directions only
    if (gameEngine.IsKeyDown(Engine::GameEngine::GetInstance().GetKeyMapping("MoveUp")))
    {
        newRotation = 3 * ALLEGRO_PI / 2; // Up (W)
        Velocity.y -= speed;
        moving = true;
        imagePath = upWalkImages;
        bmp = Engine::Resources::GetInstance().GetBitmap(imagePath[frame]);
    }
    else if (gameEngine.IsKeyDown(Engine::GameEngine::GetInstance().GetKeyMapping("MoveDown")))
    {
        newRotation = ALLEGRO_PI / 2; // Down (S)
        Velocity.y += speed;
        moving = true;
        imagePath = downWalkImages;
        bmp = Engine::Resources::GetInstance().GetBitmap(imagePath[frame]);
    }
    else if (gameEngine.IsKeyDown(Engine::GameEngine::GetInstance().GetKeyMapping("MoveLeft")))
    {
        newRotation = ALLEGRO_PI; // Left (A)
        Velocity.x -= speed;
        moving = true;
        imagePath = rightLeftWalkImages;
        bmp = Engine::Resources::GetInstance().GetBitmap(imagePath[frame]);
        scaleX = abs(scaleX);
    }
    else if (gameEngine.IsKeyDown(Engine::GameEngine::GetInstance().GetKeyMapping("MoveRight")))
    {
        newRotation = 0; // Right (D)
        Velocity.x += speed;
        moving = true;
        imagePath = rightLeftWalkImages;
        bmp = Engine::Resources::GetInstance().GetBitmap(imagePath[frame]);
        scaleX = -abs(scaleX);
    }

    // Set the new rotation to the Player's fakeRotation (radians)
    fakeRotation = newRotation;

    // Update animation frame based on elapsed time
    if (moving)
    {
        elapsedTime += deltaTime;
        if (elapsedTime >= frameDuration)
        {
            // Toggle between specific frames for up-walk animation
            if (imagePath == upWalkImages)
            {
                frame = (frame == 1) ? 2 : 1;
            }
            else
            {
                frame = (frame + 1) % imagePath.size();
            }
            bmp = Engine::Resources::GetInstance().GetBitmap(imagePath[frame]);
            elapsedTime = 0; // Reset elapsed time
        }
    }
    else
    {
        if (fakeRotation < ALLEGRO_PI / 4 || fakeRotation >= 7 * ALLEGRO_PI / 4)
        {
            bmp = Engine::Resources::GetInstance().GetBitmap("PixelArt/RightLeftWalk/pixil-frame-0.png"); // Facing right
        }
        else if (fakeRotation >= ALLEGRO_PI / 4 && fakeRotation < 3 * ALLEGRO_PI / 4)
        {
            bmp = Engine::Resources::GetInstance().GetBitmap("PixelArt/DownWalk/pixil-frame-0.png"); // Facing down
        }
        else if (fakeRotation >= 3 * ALLEGRO_PI / 4 && fakeRotation < 5 * ALLEGRO_PI / 4)
        {
            bmp = Engine::Resources::GetInstance().GetBitmap("PixelArt/RightLeftWalk/pixil-frame-0.png"); // Facing left
        }
        else if (fakeRotation >= 5 * ALLEGRO_PI / 4 && fakeRotation < 7 * ALLEGRO_PI / 4)
        {
            bmp = Engine::Resources::GetInstance().GetBitmap("PixelArt/UpWalk/pixil-frame-0.png"); // Facing up
        }
        elapsedTime = frameDuration;
    }

    timeSinceLastShot += deltaTime;
    if (gameEngine.IsKeyDown(ALLEGRO_KEY_SPACE) && timeSinceLastShot >= shootCooldown)
    {
        Shoot();
        timeSinceLastShot = 0; // Reset the timer after shooting
    }

    Engine::Sprite::Update(deltaTime);
}

void Player::TakeDamage(int damage)
{
    hp -= damage;
    if(hp <= 0)
    {
        Engine::GameEngine::GetInstance().ChangeScene("lose");
    }
}

int Player::GetHealth() const
{
    return hp;
}

float Player::GetSpeed() const
{
    return speed;
}

void Player::Shoot()
{
    // Create a new bullet and set its direction based on the player's current rotation
    Bullet *bullet = new Bullet(Position.x, Position.y, fakeRotation, 500);
    getPlayScene()->BulletGroup->AddNewObject(bullet);
}
