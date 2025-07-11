#include "Player.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Collider.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/AudioHelper.hpp"
#include <iostream>

#include <string>

using namespace std;

Player::Player(float x, float y, int hp)
    : Engine::Sprite("PixelArt/RightLeftWalk/pixil-frame-0.png", x, y, 0, 0, 0.5f, 0.5f, 0, 0, 0, 255, 255, 255, 255), maxhp(75), hp(hp), bulletDmg(50), frame(0), elapsedTime(0), timeSinceLastShot(0), shootCooldown(0.5f), speedUpDuration(5.0f), sinceSpeedUpStart(5.1f)
{
    speed = initialSpeed = 200.0f;
    Anchor = Engine::Point(0.5f, 0.5f);
    CollisionRadius = 10;
    moving = movingU = movingD = movingL = movingR = false;
    scaleX = -abs(scaleX);

    // Initialize the list of image paths for different directions
    rightLeftWalkImages = {
        "PixelArt/RightLeftWalk/pixil-frame-0.png",
        "PixelArt/RightLeftWalk/pixil-frame-1.png",
        "PixelArt/RightLeftWalk/pixil-frame-2.png"};

    upWalkImages = {
        "PixelArt/UpWalk/pixil-frame-0.png",
        "PixelArt/UpWalk/pixil-frame-1.png",
        "PixelArt/UpWalk/pixil-frame-2.png"};

    downWalkImages = {
        "PixelArt/DownWalk/pixil-frame-0.png",
        "PixelArt/DownWalk/pixil-frame-1.png",
        "PixelArt/DownWalk/pixil-frame-2.png"};

    for (auto imgPath : rightLeftWalkImages)
        bmp = Engine::Resources::GetInstance().GetBitmap(imgPath);
    for (auto imgPath : upWalkImages)
        bmp = Engine::Resources::GetInstance().GetBitmap(imgPath);
    for (auto imgPath : downWalkImages)
        bmp = Engine::Resources::GetInstance().GetBitmap(imgPath);

    // Use right-left walk images as the default
    imagePath = rightLeftWalkImages;
}

PlayScene *Player::getPlayScene()
{
    return dynamic_cast<PlayScene *>(Engine::GameEngine::GetInstance().GetActiveScene());
}

void Player::Update(float deltaTime)
{
    if (sinceSpeedUpStart + deltaTime <= speedUpDuration)
        sinceSpeedUpStart += deltaTime;
    else if (sinceSpeedUpStart <= speedUpDuration && sinceSpeedUpStart + deltaTime > speedUpDuration)
    {
        sinceSpeedUpStart += deltaTime;
        Velocity.x /= speed / initialSpeed;
        Velocity.y /= speed / initialSpeed;
        speed = initialSpeed;
    }

    Engine::GameEngine &gameEngine = Engine::GameEngine::GetInstance();

    if (Velocity.x > 0)
    {
        imgRotation = 0; // Right (D)
        imagePath = rightLeftWalkImages;
        bmp = Engine::Resources::GetInstance().GetBitmap(imagePath[frame]);
        scaleX = -abs(scaleX);
    }
    else if (Velocity.x < 0)
    {
        imgRotation = ALLEGRO_PI; // Left (A)
        imagePath = rightLeftWalkImages;
        bmp = Engine::Resources::GetInstance().GetBitmap(imagePath[frame]);
        scaleX = abs(scaleX);
    }
    else if (Velocity.y > 0)
    {
        imgRotation = ALLEGRO_PI / 2; // Down (S)
        imagePath = downWalkImages;
        bmp = Engine::Resources::GetInstance().GetBitmap(imagePath[frame]);
    }
    else if (Velocity.y < 0)
    {
        imgRotation = 3 * ALLEGRO_PI / 2; // Up (W)
        imagePath = upWalkImages;
        bmp = Engine::Resources::GetInstance().GetBitmap(imagePath[frame]);
    }

    if (moving)
    {
        elapsedTime += deltaTime;
        if (elapsedTime >= frameDuration)
        {
            // Toggle between specific frames for up-walk animation
            frame = (frame == 1) ? 2 : 1;
            bmp = Engine::Resources::GetInstance().GetBitmap(imagePath[frame]);
            elapsedTime = 0; // Reset elapsed time
        }
    }
    else
    {
        frame = 0;
        if (imgRotation < ALLEGRO_PI / 4 || imgRotation >= 7 * ALLEGRO_PI / 4)
        {
            bmp = Engine::Resources::GetInstance().GetBitmap(imagePath[frame]); // Facing right
        }
        else if (imgRotation >= ALLEGRO_PI / 4 && imgRotation < 3 * ALLEGRO_PI / 4)
        {
            bmp = Engine::Resources::GetInstance().GetBitmap(imagePath[frame]); // Facing down
        }
        else if (imgRotation >= 3 * ALLEGRO_PI / 4 && imgRotation < 5 * ALLEGRO_PI / 4)
        {
            bmp = Engine::Resources::GetInstance().GetBitmap(imagePath[frame]); // Facing left
        }
        else if (imgRotation >= 5 * ALLEGRO_PI / 4 && imgRotation < 7 * ALLEGRO_PI / 4)
        {
            bmp = Engine::Resources::GetInstance().GetBitmap(imagePath[frame]); // Facing up
        }
        elapsedTime = frameDuration;
    }

    timeSinceLastShot += deltaTime;
    if (gameEngine.IsKeyDown(ALLEGRO_KEY_SPACE) && timeSinceLastShot >= shootCooldown)
    {
        Shoot();
        timeSinceLastShot = 0; // Reset the timer after shooting
    }

    HandleOverlapWithObstacle(deltaTime);
    if (Position.x + Velocity.x * deltaTime - Size.x / 2 < 0 || Position.x + Velocity.x * deltaTime + Size.x / 2 > PlayScene::GetClientSize().x)
        Velocity.x = 0;
    if (Position.y + Velocity.y * deltaTime - Size.y / 2 < 0 || Position.y + Velocity.y * deltaTime + Size.y / 2 > PlayScene::GetClientSize().y)
        Velocity.y = 0;

    Engine::Sprite::Update(deltaTime);

    // Velocity.x = 0;
    // Velocity.y = 0;
    bool moving = false;
}

void Player::TakeDamage(int damage)
{
    if (getPlayScene()->RegenState() == false)
    {
        hp -= damage;
        getPlayScene()->DestroyHeart();
    }
}

int Player::GetHealth() const
{
    return hp;
}

int Player::GetMaxHP() const
{
    return maxhp;
}

float Player::GetSpeed() const
{
    return speed;
}

void Player::Shoot()
{
    float shootRotation = imgRotation;
    int num = getPlayScene()->getScore() / 10;
    num = num * 2 + 1;

    // 角度を広げる範囲（ラジアン単位）
    float angleRange = ALLEGRO_PI / 120 * (num - 1); // ±30度

    // 角度の増加量
    float angleIncrement = angleRange != 0 ? angleRange * 2 / (num - 1) : 0;

    // 初期角度（中央から開始）
    float startAngle = shootRotation - angleRange;

    for (int i = 0; i < num; ++i)
    {
        // 各弾丸の角度を計算
        float bulletAngle = startAngle + i * angleIncrement;

        // 新しい弾丸を作成して、方向を設定
        Bullet *bullet = new Bullet(Position.x, Position.y, bulletAngle, 500, bulletDmg);
        getPlayScene()->BulletGroup->AddNewObject(bullet);
    }
    AudioHelper::PlayAudio("gun.wav");
}

void Player::HandleOverlapWithObstacle(float deltaTime)
{
    Engine::Point nextPosition;
    nextPosition.x = Position.x + Velocity.x * deltaTime;
    nextPosition.y = Position.y + Velocity.y * deltaTime;
    PlayScene *scene = getPlayScene();
    for (auto &it : scene->ObstacleGroup->GetObjects())
    {
        Image *obstacle = dynamic_cast<Image *>(it);
        if (Engine::Collider::IsRectOverlap(Position - Size / 2, Position + Size / 2, obstacle->Position - obstacle->Size / 2, obstacle->Position + obstacle->Size / 2))
        {
            Velocity.x = -abs(Velocity.x);
            Velocity.y = -abs(Velocity.y);
            return;
        }
        else if (Engine::Collider::IsRectOverlap(nextPosition - Size / 2, nextPosition + Size / 2, obstacle->Position - obstacle->Size / 2, obstacle->Position + obstacle->Size / 2))
        {
            Velocity.x = 0;
            Velocity.y = 0;
            return;
        }
    }
}

void Player::StartMove(int keyCode)
{

    if (keyCode == Engine::GameEngine::GetInstance().GetKeyMapping("MoveLeft"))
    {
        if (movingU || movingD)
            Velocity.y = 0;
        Velocity.x = -speed;
        moving = movingL = true;
    }
    else if (keyCode == Engine::GameEngine::GetInstance().GetKeyMapping("MoveRight"))
    {
        if (movingU || movingD)
            Velocity.y = 0;
        Velocity.x = speed;
        moving = movingR = true;
    }
    else if (keyCode == Engine::GameEngine::GetInstance().GetKeyMapping("MoveUp"))
    {
        if (movingL || movingR)
            Velocity.x = 0;
        Velocity.y = -speed;
        moving = movingU = true;
    }
    else if (keyCode == Engine::GameEngine::GetInstance().GetKeyMapping("MoveDown"))
    {
        if (movingL || movingR)
            Velocity.x = 0;
        Velocity.y = speed;
        moving = movingD = true;
    }
}

void Player::StopMove(int keyCode)
{
    if (keyCode == Engine::GameEngine::GetInstance().GetKeyMapping("MoveUp"))
    {
        Velocity.y = 0;
        movingU = false;
        if (movingL)
            Velocity.x = -speed;
        else if (movingR)
            Velocity.x = speed;
        else if (movingD)
            Velocity.y = -speed;
        else
        {
            moving = false;
        }
    }
    else if (keyCode == Engine::GameEngine::GetInstance().GetKeyMapping("MoveDown"))
    {
        Velocity.y = 0;
        movingD = false;
        if (movingL)
            Velocity.x = -speed;
        else if (movingR)
            Velocity.x = speed;
        else if (movingU)
            Velocity.y = speed;
        else
        {
            moving = false;
        }
    }
    else if (keyCode == Engine::GameEngine::GetInstance().GetKeyMapping("MoveLeft"))
    {
        Velocity.x = 0;
        movingL = false;
        if (movingU)
            Velocity.y = -speed;
        else if (movingD)
            Velocity.y = speed;
        else if (movingR)
            Velocity.x = speed;
        else
        {
            moving = false;
        }
    }
    else if (keyCode == Engine::GameEngine::GetInstance().GetKeyMapping("MoveRight"))
    {
        Velocity.x = 0;
        movingR = false;
        if (movingU)
            Velocity.y = -speed;
        else if (movingD)
            Velocity.y = speed;
        else if (movingL)
            Velocity.x = -speed;
        else
        {
            moving = false;
        }
    }
}

void Player::AddBulletDmg(float dmg)
{
    bulletDmg += dmg;
}

void Player::Heal(float heal)
{
    if (hp < maxhp)
    {
        hp += heal;
    }
    if (hp > maxhp)
        hp = maxhp;
}

void Player::TemporarySpeedBoost(float boost)
{
    if (sinceSpeedUpStart > speedUpDuration)
    {
        Velocity.x *= boost;
        Velocity.y *= boost;
        speed *= boost;
    }
    sinceSpeedUpStart = 0.0f;
}