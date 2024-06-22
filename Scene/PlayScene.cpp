#include <fstream>
#include <sstream>
#include <string>
#include <random>
#include "PlayScene.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Collider.hpp"
#include "Enemy/Enemy.hpp" // Include the Enemy header
#include "Player/Player.hpp"
#include "Item/Coin.hpp"
using namespace std;

const int PlayScene::MapWidth = 30, PlayScene::MapHeight = 20;
const int PlayScene::BlockSize = 64;

int finalScore;

PlayScene::PlayScene() {}

void PlayScene::Initialize()
{
    mapState.clear();
    cameraD.x = 0;
    cameraD.y = 0;
    sw = Engine::GameEngine::GetInstance().GetScreenSize().x;
    sh = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = sw / 2;
    int halfH = sh / 2;
    cameraTopLeft = Engine::Point(sw / 2, sh / 2);
    cameraDownRight = Engine::Point(MapWidth * BlockSize - sw / 2, MapHeight * BlockSize - sh / 2);
    camera.x = sw / 2;
    camera.y = sh / 2;
    MapId = 2;

    remainingTime = 60.0f;
    finalScore = 0;
    score = 0;

    AddNewObject(BulletGroup = new Group());
    AddNewObject(EnemyGroup = new Group());
    AddNewObject(PlayerGroup = new Group());
    AddNewObject(TileMapGroup = new Group());
    AddNewObject(ObstacleGroup = new Group());
    AddNewObject(NonObstacleGroup = new Group());
    AddNewObject(LabelGroup = new Group());
    AddNewObject(ItemGroup = new Group());
    AddNewControlObject(UILife = new Group());
    ReadMap();

    ItemProbabilities.push_back(0.5); // NONE
    ItemProbabilities.push_back(0.5); // COIN

    player1 = new Player(halfW, halfH, 50);
    PlayerGroup->AddNewObject(player1);

    ConstructHeart();
    // Initialize one Enemy at specific location
    timerLabel = new Engine::Label(to_string((int)remainingTime), "pirulen.ttf", 120, halfW, halfH / 3 + 50, 255, 255, 255, 255, 0.5, 0.5);
    LabelGroup->AddNewObject(timerLabel);

    // healthLabel = new Engine::Label("HP: " + to_string(player1->GetHealth()), "pirulen.ttf", 60, 0, 0, 255, 255, 255, 255, 0, 0);
    // LabelGroup->AddNewObject(healthLabel);

    Engine::Image *coinUI;
    // coinUI = new Engine::Image("PixelArt/Coin/coin0.png", )
    std::vector<std::string> imagePaths = {
        "PixelArt/Coin/coin0.png",
        "PixelArt/Coin/coin1.png",
        "PixelArt/Coin/coin2.png",
        "PixelArt/Coin/coin3.png",
        "PixelArt/Coin/coin4.png",
        "PixelArt/Coin/coin5.png",
        "PixelArt/Coin/coin6.png",
        "PixelArt/Coin/coin7.png"};

    for (const auto &path : imagePaths)
    {
        auto img = std::make_shared<Engine::Image>(path, 9 * sw / 10, 28, 0, 0, 0.5f, 0.5f, 2.0f, 2.0f);
        coinFrames.push_back(img);
    }

    scoreLabel = new Engine::Label(to_string(score), "pirulen.ttf", 28, sw - 56, 12, 255, 255, 255, 255, 1.0, 0);
    LabelGroup->AddNewObject(scoreLabel);

    ItemGroup->AddNewObject(new Coin(halfW, halfH + 100));
}

Engine::Point PlayScene::GetClientSize()
{
    return Engine::Point(Engine::GameEngine::GetInstance().GetScreenSize().x, Engine::GameEngine::GetInstance().GetScreenSize().y);
}

void PlayScene::Update(float deltaTime)
{
    IScene::Update(deltaTime);

    animationTime += deltaTime;
    if (animationTime >= 0.1f)
    { // Change frame every frameDuration seconds
        currentFrame = (currentFrame + 1) % coinFrames.size();
        animationTime = 0.0f;
    }

    camera = camera + player1->Velocity * deltaTime;
    if ((camera.x >= cameraTopLeft.x && camera.x <= cameraDownRight.x) || (camera.y >= cameraTopLeft.y && camera.y <= cameraDownRight.y))
    {
        cameraD.x = (camera.x >= cameraTopLeft.x && camera.x <= cameraDownRight.x) ? player1->Velocity.x * deltaTime : 0.0f;
        cameraD.y = (camera.y >= cameraTopLeft.y && camera.y <= cameraDownRight.y) ? player1->Velocity.y * deltaTime : 0.0f;
        BulletGroup->MoveCamera(cameraD);
        EnemyGroup->MoveCamera(cameraD);
        ObstacleGroup->MoveCamera(cameraD);
        NonObstacleGroup->MoveCamera(cameraD);
        TileMapGroup->MoveCamera(cameraD);
        ItemGroup->MoveCamera(cameraD);
        PlayerGroup->MoveCamera(cameraD);
    }
    remainingTime -= deltaTime;
    static float spawnTimer = 1.0f;
    spawnTimer -= deltaTime;
    if (spawnTimer <= 0 && remainingTime > 0)
    {
        spawnTimer = 1.0f;
        int randomX = rand() % sw;
        int randomY = rand() % sh;
        EnemyGroup->AddNewObject(new Enemy(randomX, randomY));
    }
    if (remainingTime < 0)
    {
        Engine::GameEngine::GetInstance().ChangeScene("win");
    }
    timerLabel->Text = to_string((int)remainingTime);
    // healthLabel->Text = "HP: " + to_string(player1->GetHealth());
    scoreLabel->Text = to_string(score);
    for (auto &it : PlayerGroup->GetObjects())
    {
        Player *player = dynamic_cast<Player *>(it);
        if (player->GetHealth() > 0)
            break;
        if (it == PlayerGroup->GetObjects().back())
            Engine::GameEngine::GetInstance().ChangeScene("lose");
    }
    // ConstructHeart();
}

void PlayScene::Draw() const
{
    IScene::Draw();
    ItemGroup->Draw();
    ObstacleGroup->Draw();
    BulletGroup->Draw();
    PlayerGroup->Draw();
    EnemyGroup->Draw();
    NonObstacleGroup->Draw();
    LabelGroup->Draw();
    UILife->Draw();
    if (!coinFrames.empty())
    {
        coinFrames[currentFrame]->Draw();
    }
}

void PlayScene::OnKeyDown(int keyCode)
{
    IScene::OnKeyDown(keyCode);

    if (keyCode == Engine::GameEngine::GetInstance().GetKeyMapping("MoveUp"))
    {
        player1->StartMove(keyCode);
    }
    else if (keyCode == Engine::GameEngine::GetInstance().GetKeyMapping("MoveDown"))
    {
        player1->StartMove(keyCode);
    }
    else if (keyCode == Engine::GameEngine::GetInstance().GetKeyMapping("MoveLeft"))
    {
        player1->StartMove(keyCode);
    }
    else if (keyCode == Engine::GameEngine::GetInstance().GetKeyMapping("MoveRight"))
    {
        player1->StartMove(keyCode);
    }
}

void PlayScene::OnKeyUp(int keyCode)
{
    if (keyCode == Engine::GameEngine::GetInstance().GetKeyMapping("MoveUp"))
    {
        player1->StopMove(keyCode);
    }
    else if (keyCode == Engine::GameEngine::GetInstance().GetKeyMapping("MoveDown"))
    {
        player1->StopMove(keyCode);
    }
    else if (keyCode == Engine::GameEngine::GetInstance().GetKeyMapping("MoveLeft"))
    {
        player1->StopMove(keyCode);
    }
    else if (keyCode == Engine::GameEngine::GetInstance().GetKeyMapping("MoveRight"))
    {
        player1->StopMove(keyCode);
    }
}

void PlayScene::Terminate()
{
    heartImages.clear();
    IScene::Terminate();
}

void PlayScene::ReadMap()
{
    string filename = "Resource/map" + to_string(MapId) + ".txt";
    char c;
    mapState = vector<vector<TileType>>(MapHeight, vector<TileType>(0));
    ifstream fin(filename);
    size_t idx = 0;
    while (fin >> c && idx < MapHeight)
    {
        if (mapState[idx].size() == MapWidth)
            ++idx;
        switch (c)
        {
        case '1':
            mapState[idx].push_back(TILE_DIRT1);
            break;
        case '2':
            mapState[idx].push_back(TILE_DIRT2);
            break;
        case '3':
            mapState[idx].push_back(TILE_DIRT3);
            break;
        case '4':
            mapState[idx].push_back(TILE_DIRT4);
            break;
        case '5':
            mapState[idx].push_back(TILE_GRASS1);
            break;
        case '6':
            mapState[idx].push_back(TILE_GRASS2);
            break;
        case '7':
            mapState[idx].push_back(TILE_GRASS3);
            break;
        case '8':
            mapState[idx].push_back(TILE_BUSH);
            break;
        case 'T':
            mapState[idx].push_back(TILE_TOMBSTONE);
            break;
        case 'P':
            mapState[idx].push_back(TILE_POLETILE);
            break;
        case 's':
            mapState[idx].push_back(TILE_STONE);
            break;
        case 'b':
            mapState[idx].push_back(TILE_BOX);
            break;
        case 'c':
            mapState[idx].push_back(TILE_CAR);
            break;
        case 'd':
            mapState[idx].push_back(TILE_DEBRIS);
            break;
        case 'l':
            mapState[idx].push_back(TILE_LOG);
            break;
        case 'A':
            mapState[idx].push_back(TILE_PATH0);
            break;
        case 'B':
            mapState[idx].push_back(TILE_PATH1);
            break;
        case 'C':
            mapState[idx].push_back(TILE_PATH2);
            break;
        case 'D':
            mapState[idx].push_back(TILE_PATH3);
            break;
        case 'E':
            mapState[idx].push_back(TILE_PATH4);
            break;
        case 'F':
            mapState[idx].push_back(TILE_PATH5);
            break;
        case 'G':
            mapState[idx].push_back(TILE_PATH6);
            break;
        case 'H':
            mapState[idx].push_back(TILE_PATH7);
            break;
        case 'I':
            mapState[idx].push_back(TILE_PATH8);
            break;
        case 'J':
            mapState[idx].push_back(TILE_PATH9);
            break;
        case 'K':
            mapState[idx].push_back(TILE_PATH10);
            break;
        case 'L':
            mapState[idx].push_back(TILE_PATH11);
            break;
        case '\n':
        case '\r':
            if (static_cast<int>(mapState[idx].size()) / MapHeight != 0)
                throw ios_base::failure("Map data is corrupted.");
            break;
        default:
            throw ios_base::failure("Map data is corrupted.");
        }
    }
    fin.close();

    for (int i = 0; i < MapHeight; i++)
    {
        for (int j = 0; j < MapWidth; j++)
        {
            int positionX = j * BlockSize;
            int positionY = i * BlockSize;
            int ObjectHeight = BlockSize;
            int ObjectWidth = BlockSize;
            string mapTilePath = "Tiles/";
            string mapObstaclePath = "Tiles/";
            string mapNonObstaclePath = "Tiles/";
            switch (mapState[i][j])
            {
            case TILE_DIRT1:
                mapTilePath += "dirt1.png";
                break;
            case TILE_DIRT2:
                mapTilePath += "dirt2.png";
                break;
            case TILE_DIRT3:
                mapTilePath += "dirt3.png";
                break;
            case TILE_DIRT4:
                mapTilePath += "dirt4.png";
                break;
            case TILE_GRASS1:
                mapTilePath += "grass1.png";
                break;
            case TILE_GRASS2:
                mapTilePath += "grass2.png";
                break;
            case TILE_GRASS3:
                mapTilePath += "grass3.png";
                break;
            case TILE_BUSH:
                mapTilePath += "bush.png";
                break;
            case TILE_TOMBSTONE:
                mapTilePath += "dirt1.png";
                mapNonObstaclePath += "tombstone.png";
                break;
            case TILE_POLETILE:
                mapTilePath += "dirt1.png";
                NonObstacleGroup->AddNewObject(new Engine::Sprite(mapNonObstaclePath + "stopsign.png", positionX + ObjectWidth / 2, positionY + ObjectHeight / 2 - BlockSize, ObjectWidth, ObjectHeight));
                mapObstaclePath += "poletile.png";
                break;
            case TILE_STONE:
                mapTilePath += "dirt1.png";
                mapObstaclePath += "stone.png";
                break;
            case TILE_BOX:
                mapTilePath += "dirt1.png";
                mapObstaclePath += "boxtile.png";
                break;
            case TILE_CAR:
                mapTilePath += "dirt1.png";
                ObjectWidth *= 2;
                mapObstaclePath += "car.png";
                break;
            case TILE_DEBRIS:
                mapTilePath += "dirt1.png";
                mapObstaclePath += "debris1.png";
                break;
            case TILE_LOG:
                mapTilePath += "dirt1.png";
                mapObstaclePath += "log.png";
                break;
            case TILE_PATH0:
                mapTilePath += "path0.png";
                break;
            case TILE_PATH1:
                mapTilePath += "path1.png";
                break;
            case TILE_PATH2:
                mapTilePath += "path2.png";
                break;
            case TILE_PATH3:
                mapTilePath += "path3.png";
                break;
            case TILE_PATH4:
                mapTilePath += "path4.png";
                break;
            case TILE_PATH5:
                mapTilePath += "path5.png";
                break;
            case TILE_PATH6:
                mapTilePath += "path6.png";
                break;
            case TILE_PATH7:
                mapTilePath += "path7.png";
                break;
            case TILE_PATH8:
                mapTilePath += "path8.png";
                break;
            case TILE_PATH9:
                mapTilePath += "path9.png";
                break;
            case TILE_PATH10:
                mapTilePath += "path10.png";
                break;
            case TILE_PATH11:
                mapTilePath += "path11.png";
                break;
            default:
                break;
            }
            if (mapObstaclePath != "Tiles/")
                ObstacleGroup->AddNewObject(new Engine::Sprite(mapObstaclePath, positionX + ObjectWidth / 2, positionY + ObjectHeight / 2, ObjectWidth, ObjectHeight));
            if (mapNonObstaclePath != "Tiles/")
                NonObstacleGroup->AddNewObject(new Engine::Sprite(mapNonObstaclePath, positionX + ObjectWidth / 2, positionY + ObjectHeight / 2, ObjectWidth, ObjectHeight));
            TileMapGroup->AddNewObject(new Engine::Image(mapTilePath, positionX, positionY, BlockSize, BlockSize));
        }
    }
}

int PlayScene::generateRandomItemValue()
{
    random_device rd;
    mt19937 gen(rd());
    discrete_distribution<> dis(ItemProbabilities.begin(), ItemProbabilities.end());

    return dis(gen);
}

void PlayScene::generateItem(int index, float x, float y)
{
    switch (index)
    {
    case COIN:
        ItemGroup->AddNewObject(new Coin(x, y));
        break;
    default:
        break;
    }
}

void PlayScene::IncreaseKill()
{
    // ++score;
    // ++finalScore;
}

void PlayScene::ConstructHeart()
{
    Engine::ImageButton *lifebtn;
    int health = player1->GetHealth();
    for (int i = 0; i < health / 5; i++)
    {
        lifebtn = new Engine::ImageButton("play/heart.png", "play/heart.png", i * 48 + 4, 6, 56, 56);
        UILife->AddNewControlObject(lifebtn);
        heartImages.push_back(lifebtn);
    }
}

void PlayScene::DestroyHeart()
{
    Engine::ImageButton *lastHeart = heartImages.back();
    UILife->RemoveObject(lastHeart->GetObjectIterator());
    heartImages.pop_back();
}

void PlayScene::updateScore()
{
    ++score;
    finalScore += 50;
}
