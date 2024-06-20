#include <fstream>
#include <sstream>
#include <string>
#include "PlayScene.hpp"
#include "Engine/GameEngine.hpp"
#include "Enemy/Enemy.hpp" // Include the Enemy header

using namespace std;

const int PlayScene::MapWidth = 20, PlayScene::MapHeight = 20;
const int PlayScene::BlockSize = 64;

PlayScene::PlayScene() {}

void PlayScene::Initialize()
{
    MapId = 2;
    w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;

    remainingTime = 10.0f;

    AddNewObject(BulletGroup = new Group());
    AddNewObject(EnemyGroup = new Group());
    AddNewObject(PlayerGroup = new Group());
    player1 = new Player(halfW, halfH, 50);
    PlayerGroup->AddNewObject(player1);
    // Initialize one Enemy at specific location
    EnemyGroup->AddNewObject(new Enemy(halfW, halfH - 100));
    timerLabel = new Engine::Label(to_string((int)remainingTime), "pirulen.ttf", 120, halfW, halfH / 3 + 50, 255, 255, 255, 255, 0.5, 0.5);
    AddNewObject(timerLabel);

    healthLabel = new Engine::Label("HP: " + to_string(player1->GetHealth()), "pirulen.ttf", 60, 0, 0, 255, 255, 255, 255, 0, 0);
    AddNewObject(healthLabel);
}

Engine::Point PlayScene::GetClientSize()
{
    return Engine::Point(Engine::GameEngine::GetInstance().GetScreenSize().x, Engine::GameEngine::GetInstance().GetScreenSize().y);
}

void PlayScene::Update(float deltaTime)
{
    IScene::Update(deltaTime);
    for (auto &enemy : EnemyGroup->GetObjects())
    {
        enemy->Update(deltaTime);
    }

    remainingTime -= deltaTime;
    static float spawnTimer = 1.0f;
    spawnTimer -= deltaTime;
    if (spawnTimer <= 0 && remainingTime > 0)
    {
        spawnTimer = 1.0f;
        int randomX = rand() % w;
        int randomY = rand() % h;
        EnemyGroup->AddNewObject(new Enemy(randomX, randomY));
    }
    if (remainingTime < 0)
    {
        Engine::GameEngine::GetInstance().ChangeScene("win");
    }
    timerLabel->Text = to_string((int)remainingTime);
    healthLabel->Text = "HP: " + to_string(player1->GetHealth());
}

void PlayScene::Draw() const
{
    IScene::Draw();
}

void PlayScene::Terminate()
{
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
            ++idx;
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
            string imagePath = "Tiles/";
            switch (mapState[i][j])
            { 
            case TILE_DIRT1:
                
                break;
            case TILE_DIRT2:
                break;
            case TILE_DIRT3:
                break;
            case TILE_DIRT4:
                break;
            case TILE_GRASS1:
                break;
            case TILE_GRASS2:
                break;
            case TILE_GRASS3:
                break;
            case TILE_BUSH:
                break;
            case TILE_TOMBSTONE:
                break;
            case TILE_POLETILE:
                break;
            case TILE_STONE:
                break;
            case TILE_BOX:
                break;
            case TILE_CAR:
                break;
            case TILE_DEBRIS:
                break;
            case TILE_LOG:
                break;
            case TILE_PATH0:
                break;
            case TILE_PATH1:
                break;
            case TILE_PATH2:
                break;
            case TILE_PATH3:
                break;
            case TILE_PATH4:
                break;
            case TILE_PATH5:
                break;
            case TILE_PATH6:
                break;
            case TILE_PATH7:
                break;
            case TILE_PATH8:
                break;
            case TILE_PATH9:
                break;
            case TILE_PATH10:
                break;
            case TILE_PATH11:
                break;
            default:
                // デフォルトの動作（必要に応じて）
                break;
            }
        }
    }
}
