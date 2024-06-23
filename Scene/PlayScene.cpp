#include <fstream>
#include <sstream>
#include <string>
#include <random>
#include <chrono>
#include <filesystem>

#include "PlayScene.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Collider.hpp"
#include "Enemy/Enemy.hpp" // Include the Enemy header
#include "Player/Player.hpp"
#include "Item/Coin.hpp"
#include "Item/Heal.hpp"
#include "Item/DamageFlask.hpp"
#include "Item/SpeedFlask.hpp"
#include "Item/Light.hpp"
#include "Engine/AudioHelper.hpp"

using namespace std;

const int PlayScene::MapWidth = 35, PlayScene::MapHeight = 25;
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
    camera.x = MapWidth * BlockSize / 2;
    camera.y = MapHeight * BlockSize / 2;
    lightExpandDuration = 10.0f;
    sinceLightExpandStart = lightExpandDuration + 0.1f;

    MapId = 2;

    finalScore = 0;
    score = 0;
    isHealing = false;

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
    AddNewObject(miniMap = new MiniMap());

    ItemProbabilities.push_back(0.5); // NONE
    ItemProbabilities.push_back(0.1); // COIN
    ItemProbabilities.push_back(0.1); // HEAL
    ItemProbabilities.push_back(0.1); // DAMAGEFLASK
    ItemProbabilities.push_back(0.1); // SPEEDFLASK
    ItemProbabilities.push_back(0.1); // LIGHT

    player1 = new Player(halfW, halfH, 50);
    PlayerGroup->AddNewObject(player1);

    ConstructHeart();
    // Initialize one Enemy at specific location

    // healthLabel = new Engine::Label("HP: " + to_string(player1->GetHealth()), "onesize.ttf", 60, 0, 0, 255, 255, 255, 255, 0, 0);
    // LabelGroup->AddNewObject(healthLabel);

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
        auto img = std::make_shared<Engine::Image>(path, 9 * sw / 10, 300, 0, 0, 0.5f, 0.5f, 2.0f, 2.0f);
        coinFrames.push_back(img);
    }

    std::vector<std::string> imagePaths1 = {
        "PixelArt/Heal/heal0.png",
        "PixelArt/Heal/heal1.png",
        "PixelArt/Heal/heal2.png",
        "PixelArt/Heal/heal3.png",
        "PixelArt/Heal/heal4.png",
        "PixelArt/Heal/heal5.png",
        "PixelArt/Heal/heal6.png",
        "PixelArt/Heal/heal0.png"};

    scoreLabel = new Engine::Label(to_string(score), "onesize.ttf", 28, sw - 56, 284, 255, 255, 255, 255, 1.0, 0);
    LabelGroup->AddNewObject(scoreLabel);

    ItemGroup->AddNewObject(new Coin(halfW, halfH + 100));
    ItemGroup->AddNewObject(new Heal(halfW + 40, halfH + 100));
    ItemGroup->AddNewObject(new Heal(halfW + 140, halfH + 100));
    ItemGroup->AddNewObject(new Coin(halfW + 180, halfH + 100));
    ItemGroup->AddNewObject(new Coin(halfW + 220, halfH + 100));
    ItemGroup->AddNewObject(new Coin(halfW + 330, halfH + 100));
    ItemGroup->AddNewObject(new Coin(halfW + 440, halfH + 100));
    initialLightScale = 3.0f;
    shade = new Engine::Image("UI/dark_blur.png", sw / 2, sh / 2, 0.0, 0.0, 0.5, 0.5, initialLightScale, initialLightScale);

    bgmId = AudioHelper::PlayBGM("careening-into-danger.ogg");
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
    if (sinceLightExpandStart + deltaTime <= lightExpandDuration)
    {
        sinceLightExpandStart += deltaTime;
    }  
    else if (sinceLightExpandStart <= lightExpandDuration && sinceLightExpandStart + deltaTime > lightExpandDuration)
    {
        sinceLightExpandStart += deltaTime;
        shade->scaleX = initialLightScale;
        shade->scaleY = initialLightScale;
    }

    if (isHealing)
    {
        healAnimationTimer += deltaTime;
        if (healAnimationTimer >= 0.1f)
        {
            healAnimationTimer = 0.0f;

            // Draw the current frame
            if (healFrame < healFrames.size())
            {
                healFrames[healFrame]->Draw();
            }

            healFrame++;

            // Check if the animation is finished
            if (healFrame >= healFrames.size())
            {
                isHealing = false;  // Stop the animation after one play
                healFrames.clear(); // Clear the animation frames
            }
        }
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
    shade->Position = player1->Position;
    static float spawnTimer = 1.0f;
    spawnTimer -= deltaTime;
    if (spawnTimer <= 0)
    {
        spawnTimer = 1.0f;
        int randomX = rand() % sw;
        int randomY = rand() % sh;
        EnemyGroup->AddNewObject(new Enemy(randomX, randomY));
    }

    if (player1->GetHealth() <= 0)
    {
        User::getInstance().setScore(score * 50);
        WriteScoreBoard();
        Engine::GameEngine::GetInstance().ChangeScene("win");
        return;
    }

    // healthLabel->Text = "HP: " + to_string(player1->GetHealth());
    scoreLabel->Text = to_string(score);
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
    shade->Draw();
    miniMap->Draw();
    LabelGroup->Draw();
    UILife->Draw();
    if (!coinFrames.empty())
    {
        coinFrames[currentFrame]->Draw();
    }
    if (!healFrames.empty())
    {
        healFrames[healFrame]->Draw();
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
    AudioHelper::StopBGM(bgmId);
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
            int positionX = j * BlockSize - (MapWidth * BlockSize / 2 - cameraTopLeft.x);
            int positionY = i * BlockSize - (MapHeight * BlockSize / 2 - cameraTopLeft.y);
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
                mapTilePath += "dirt1.png";
                mapNonObstaclePath += "bush.png";
                break;
            case TILE_TOMBSTONE:
                mapTilePath += "dirt1.png";
                mapObstaclePath += "tombstone.png";
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
    case HEAL:
        ItemGroup->AddNewObject(new Heal(x, y));
        break;
    case DAMAGEFLASK:
        ItemGroup->AddNewObject(new DamageFlask(x, y));
        break;
    case SPEEDFLASK:
        ItemGroup->AddNewObject(new SpeedFlask(x, y));
        break;
    case LIGHT:
        ItemGroup->AddNewObject(new Light(x, y));
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
    int max = player1->GetMaxHP() / 5;
    int count = 1;

    for (int i = 0; i < health / 5; i++)
    {
        if (count <= 10)
        {
            lifebtn = new Engine::ImageButton("PixelArt/Heart/heart0.png", "PixelArt/Heart/heart0.png", i * 48 + 4, 6, 36, 36);
        }
        else
            lifebtn = new Engine::ImageButton("PixelArt/Heart/heart0.png", "PixelArt/Heart/heart0.png", (i) * 48 - (10 * 48) + 4, 6 + 42, 36, 36);
        count++;
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

// void PlayScene::HealAnim()
// {
//     if (!isHealing)
//     {
//         std::vector<std::string> imagePaths = {
//             "PixelArt/Heal/heal0.png",
//             "PixelArt/Heal/heal1.png",
//             "PixelArt/Heal/heal2.png",
//             "PixelArt/Heal/heal3.png",
//             "PixelArt/Heal/heal4.png",
//             "PixelArt/Heal/heal5.png",
//             "PixelArt/Heal/heal6.png",
//             "PixelArt/Heal/heal0.png"};

//         Engine::ImageButton *heartbtn;
//         int currenthealth = player1->GetHealth() / 5;
//         int max = player1->GetMaxHP() / 5;
//         int count = 1;
//         if (currenthealth <= max - 2 && currenthealth > 0)
//         {
//             for (int i = 0; i < 2; i++)
//             {

//                 if (currenthealth < 10)
//                 {
//                     for (const auto &path : imagePaths)
//                     {
//                         auto img = std::make_shared<Engine::Image>(path, (currenthealth + i) * 48 + 4, 6, 36, 36);
//                         healFrames.push_back(img);
//                     }
//                     healAnimationTimer = 0.0f;
//                     healFrame = 0;
//                     isHealing = true;
//                     heartbtn = new Engine::ImageButton("PixelArt/Heart/heart0.png", "PixelArt/Heart/heart0.png", (currenthealth + i) * 48 + 4, 6, 36, 36);
//                 }
//                 else
//                 {
//                     for (const auto &path : imagePaths)
//                     {
//                         auto img = std::make_shared<Engine::Image>(path, (currenthealth + i) * 48 - (10 * 48) + 4, 6 + 42, 36, 36);
//                         healFrames.push_back(img);
//                     }
//                     healAnimationTimer = 0.0f;
//                     healFrame = 0;
//                     isHealing = true;
//                     heartbtn = new Engine::ImageButton("PixelArt/Heart/heart0.png", "PixelArt/Heart/heart0.png", (currenthealth + i) * 48 - (10 * 48) + 4, 6 + 42, 36, 36);
//                 }
//                 UILife->AddNewControlObject(heartbtn);
//                 heartImages.push_back(heartbtn);
//             }
//         }
//         else if(currenthealth == max - 1)
//         {
//             for (const auto &path : imagePaths)
//             {
//                 auto img = std::make_shared<Engine::Image>(path, (currenthealth) * 48 - (10 * 48) + 4, 6 + 42, 36, 36);
//                 healFrames.push_back(img);
//             }
//             healAnimationTimer = 0.0f;
//             healFrame = 0;
//             isHealing = true;
//             heartbtn = new Engine::ImageButton("PixelArt/Heart/heart0.png", "PixelArt/Heart/heart0.png", (currenthealth) * 48 - (10 * 48) + 4, 6 + 42, 36, 36);
//             UILife->AddNewControlObject(heartbtn);
//             heartImages.push_back(heartbtn);
//         }
//     }
//}

void PlayScene::HealAnim()
{
    if (!isHealing)
    {
        // Image paths for healing animation frames
        std::vector<std::string> imagePaths = {
            "PixelArt/Heal/heal0.png",
            "PixelArt/Heal/heal1.png",
            "PixelArt/Heal/heal2.png",
            "PixelArt/Heal/heal3.png",
            "PixelArt/Heal/heal4.png",
            "PixelArt/Heal/heal5.png",
            "PixelArt/Heal/heal6.png",
            "PixelArt/Heal/heal0.png"};

        int currentHealth = player1->GetHealth() / 5;
        int maxHealth = player1->GetMaxHP() / 5;
        float yOffset = 6;
        float yOffsetMax = 6 + 42;

        // Determine number of healing animations to create
        int healCount = (currentHealth <= maxHealth - 2 && currentHealth > 0) ? 2 : (currentHealth == maxHealth - 1 ? 1 : 0);

        for (int i = 0; i < healCount; ++i)
        {
            // Determine x and y positions for the healing animation
            float xPos = (currentHealth + i) * 48 + 4;
            if (currentHealth + i >= 10)
            {
                xPos -= 10 * 48;
                yOffset = yOffsetMax;
            }

            // Create healing frames
            for (const auto &path : imagePaths)
            {
                auto img = std::make_shared<Engine::Image>(path, xPos, yOffset, 36, 36);
                healFrames.push_back(img);
            }

            // Create and add the heart button
            Engine::ImageButton *heartBtn = new Engine::ImageButton("PixelArt/Heart/heart0.png", "PixelArt/Heart/heart0.png", xPos, yOffset, 36, 36);
            UILife->AddNewControlObject(heartBtn);
            heartImages.push_back(heartBtn);
        }

        if (healCount > 0)
        {
            // Initialize animation properties
            healAnimationTimer = 0.0f;
            healFrame = 0;
            isHealing = true;
        }
    }
}

bool PlayScene::RegenState()
{
    return isHealing;
}

void PlayScene::ReadScoreBoard()
{
    std::string filename = "../Resource/scoreboard.txt";
    std::ifstream fin(filename);

    std::string line;
    while (getline(fin, line))
    {
        std::istringstream iss(line);
        std::string userName, scoreStr, dateStr, timeStr;

        std::getline(iss, userName, ' ');
        std::getline(iss, scoreStr, ' ');
        std::getline(iss, dateStr, ' ');
        std::getline(iss, timeStr, ' ');

        int score = std::stoi(scoreStr);

        // 日付と時刻をtime_pointに変換
        std::tm tm = {};
        std::istringstream ss(dateStr + " " + timeStr);
        ss >> std::get_time(&tm, "%Y-%m-%d %H:%M");
        auto date = std::chrono::system_clock::from_time_t(std::mktime(&tm));

        scoreboard.push_back({userName, score, date});
    }
    fin.close();
}

void PlayScene::WriteScoreBoard()
{
    std::string userName = User::getInstance().getName();
    int score = User::getInstance().getScore();

    ReadScoreBoard();

    bool updated = false;
    std::string tempFilename = "../Resource/scoreboard.txt.tmp";
    std::ofstream tempOut(tempFilename);

    for (auto &data : scoreboard)
    {
        if (data.userName == userName)
        {
            if (data.score < score)
            {
                data.score = score;
                data.date = std::chrono::system_clock::now(); // 日時を更新
            }
            updated = true;
        }
        // データを書き込む
        auto time_t = std::chrono::system_clock::to_time_t(data.date);
        std::tm tm = *std::localtime(&time_t);
        tempOut << data.userName << " " << data.score << " "
                << std::put_time(&tm, "%Y-%m-%d %H:%M") << std::endl;
    }

    if (!updated)
    {
        auto now = std::chrono::system_clock::now();
        auto time_t = std::chrono::system_clock::to_time_t(now);
        std::tm tm = *std::localtime(&time_t);

        tempOut << userName << " " << score << " "
                << std::put_time(&tm, "%Y-%m-%d %H:%M") << std::endl;
    }
    tempOut.close();

    std::filesystem::remove("../Resource/scoreboard.txt");
    std::filesystem::rename(tempFilename, "../Resource/scoreboard.txt");

    scoreboard.clear();
}

void PlayScene::ExpandLight(float boost)
{
    if (sinceLightExpandStart > lightExpandDuration)
    {
        shade->scaleX *= boost;
        shade->scaleY *= boost;
    }
    sinceLightExpandStart = 0.0f;
}

int PlayScene::getScore()
{
    return score;
}