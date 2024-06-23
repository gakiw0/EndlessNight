#include <fstream>
#include <algorithm>
#include <sstream>
#include "Engine/GameEngine.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "ScoreBoardScene.hpp"

using namespace std;

void ScoreBoardScene::Initialize()
{
   int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
   int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
   int halfW = w / 2;
   int halfH = h / 2;
   Engine::ImageButton *btn;
   numMap = 2;
   currMap = 1;

   AddNewObject(UITitle = new Engine::Label("Leaderboards", "onesize.ttf", 48, halfW, 75, 0, 255, 255, 255, 0.5, 0.5));

   // Backボタン
   btn = new Engine::ImageButton("settings/backbutton1.png", "settings/backbutton2.png", halfW - 200, h - 150, 400, 100);
   btn->SetOnClickCallback(std::bind(&ScoreBoardScene::BackOnClick, this, 1));
   AddNewControlObject(btn);
   AddNewObject(new Engine::Label("Back", "onesize.ttf", 48, halfW, h - 100, 255, 255, 255, 255, 0.5, 0.5));

   // Prevボタン
   btn = new Engine::ImageButton("settings/backbutton1.png", "settings/backbutton2.png", halfW - 750, h - 150, 400, 100);
   btn->SetOnClickCallback(std::bind(&ScoreBoardScene::PrevPageOnClick, this));
   AddNewControlObject(btn);
   AddNewObject(new Engine::Label("Prev", "onesize.ttf", 48, halfW - 550, h - 100, 255, 255, 255, 255, 0.5, 0.5));

   // Nextボタン
   btn = new Engine::ImageButton("settings/backbutton1.png", "settings/backbutton2.png", halfW + 350, h - 150, 400, 100);
   btn->SetOnClickCallback(std::bind(&ScoreBoardScene::NextPageOnClick, this));
   AddNewControlObject(btn);
   AddNewObject(new Engine::Label("Next", "onesize.ttf", 48, halfW + 550, h - 100, 255, 255, 255, 255, 0.5, 0.5));

   // btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 750, 50, 100, 100);
   // btn->SetOnClickCallback(std::bind(&ScoreBoardScene::PrevMapOnClick, this));
   // AddNewControlObject(btn);
   // AddNewObject(new Engine::Label("<", "onesize.ttf", 48, halfW - 700, 100, 0, 0, 0, 255, 0.5, 0.5));

   // Nextボタン
   // btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW + 650, 50, 100, 100);
   // btn->SetOnClickCallback(std::bind(&ScoreBoardScene::NextMapOnClick, this));
   // AddNewControlObject(btn);
   // AddNewObject(new Engine::Label(">", "onesize.ttf", 48, halfW + 700, 100, 0, 0, 0, 255, 0.5, 0.5));

   ReadScoreBoards();
   // スコアボードのラベルを初期化
   displayStart = 0;
   UpdateScoreBoardDisplay();
}

void ScoreBoardScene::Terminate()
{
   for (auto &scoreboard : scoreboards)
   {
      scoreboard.clear();
   }
   scoreboards.clear();
   scoreboardLabels.clear();
   IScene::Terminate();
}

void ScoreBoardScene::BackOnClick(int stage)
{
   Engine::GameEngine::GetInstance().ChangeScene("start");
}

void ScoreBoardScene::PrevPageOnClick()
{
   if (displayStart > 0)
   {
      displayStart -= 10;
      UpdateScoreBoardDisplay();
   }
}

void ScoreBoardScene::NextPageOnClick()
{
   if (displayStart + 10 < scoreboards[currMap - 1].size())
   {
      displayStart += 10;
      UpdateScoreBoardDisplay();
   }
}

// void ScoreBoardScene::PrevMapOnClick()
// {
//    if (currMap > 1)
//    {
//       displayStart = 0;
//       currMap--;
//       UITitle->Text = "Stage " + to_string(currMap);
//       UpdateScoreBoardDisplay();
//    }
// }

// void ScoreBoardScene::NextMapOnClick()
// {
//    if (currMap < numMap)
//    {
//       displayStart = 0;
//       currMap++;
//       UITitle->Text = "Stage " + to_string(currMap);
//       UpdateScoreBoardDisplay();
//    }
// }

void ScoreBoardScene::ReadScoreBoards()
{
   for (int idx = 0; idx < numMap; idx++)
   {
      std::vector<ScoreData> scoreboard;
      string filename = "../Resource/scoreboard.txt";
      ifstream fin(filename);

      string line;
      while (getline(fin, line))
      {
         // スペースで区切って、ユーザー名、スコア、日付と時刻を取得
         std::istringstream iss(line);
         std::string userName, scoreStr, dateStr, timeStr;
         std::getline(iss, userName, ' ');
         std::getline(iss, scoreStr, ' ');
         std::getline(iss, dateStr, ' ');
         std::getline(iss, timeStr, ' ');

         // スコアを整数に変換
         int score = std::stoi(scoreStr);

         // 日付と時刻をtime_pointに変換
         std::tm tm = {};
         std::istringstream ss(dateStr + " " + timeStr);
         ss >> std::get_time(&tm, "%Y-%m-%d %H:%M");
         auto date = std::chrono::system_clock::from_time_t(std::mktime(&tm));

         // ScoreDataを作成して、scoreboardに追加
         ScoreData data{userName, score, date};
         scoreboard.push_back(data);
      }
      fin.close();
      sort(scoreboard.begin(), scoreboard.end(), [](const ScoreData &a, const ScoreData &b)
           { return a.score > b.score; });
      scoreboards.push_back(scoreboard);
   }
}

void ScoreBoardScene::UpdateScoreBoardDisplay()
{
   // 既存のスコアボードのラベルを削除
   for (auto label : scoreboardLabels)
   {
      RemoveObject(label->GetObjectIterator());
   }
   scoreboardLabels.clear();

   // 新しいスコアボードのラベルを作成・追加
   int startY = 180;
   int defaultFontSize = 36;
   int lineHeight = 50;
   int maxDisplayCount = 10;
   int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
   int halfW = w / 2;

   for (size_t i = displayStart; i < scoreboards[currMap - 1].size() && i < maxDisplayCount + displayStart; ++i)
   {
      const auto &data = scoreboards[currMap - 1][i];
      int fontSize = defaultFontSize;

      int x = 50;
      Engine::Label *userNameLabel = new Engine::Label(data.userName, "onesize.ttf", fontSize, x, startY, 255, 255, 255, 255, 0.0, 0.5);
      AddNewObject(userNameLabel);
      scoreboardLabels.push_back(userNameLabel);

      x = halfW;
      Engine::Label *scoreLabel = new Engine::Label(std::to_string(data.score), "onesize.ttf", fontSize, x, startY, 255, 255, 255, 255, 0.5, 0.5);
      AddNewObject(scoreLabel);
      scoreboardLabels.push_back(scoreLabel);

      // 日付と時刻を文字列に変換して表示
      std::time_t t = std::chrono::system_clock::to_time_t(data.date);
      std::tm tm = *std::localtime(&t);
      char dateTimeStr[24];
      std::strftime(dateTimeStr, sizeof(dateTimeStr), "%Y-%m-%d %H:%M", &tm);

      x = w - 500; // 日付と時刻の位置を調整
      Engine::Label *dateTimeLabel = new Engine::Label(dateTimeStr, "onesize.ttf", defaultFontSize, x, startY, 255, 255, 255, 255, 0.0, 0.5);
      AddNewObject(dateTimeLabel);
      scoreboardLabels.push_back(dateTimeLabel);

      startY += lineHeight;
   }
}