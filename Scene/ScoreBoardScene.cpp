#include <allegro5/allegro_audio.h>
#include <functional>
#include <memory>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "PlayScene.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"
#include "UI/Component/Slider.hpp"
#include "StageSelectScene.hpp"
#include "ScoreBoardScene.hpp"

Engine::Label *ScoreBoard;

std::vector<ScoreEntry> ScoreBoardScene::ReadScores(const std::string &filename)
{
   std::ifstream file(filename);
   std::vector<ScoreEntry> scores;
   std::string line;

   while (std::getline(file, line))
   {
      std::istringstream iss(line);
      ScoreEntry entry;
      if (!(iss >> entry.name >> entry.score >> entry.date))
      {
         break;
      }
      scores.push_back(entry);
      std::cout << "Name: " << entry.name << ", Score: " << entry.score
                << ", DateTime: " << entry.date << std::endl;
   }

   // Sort scores in descending order
   std::sort(scores.begin(), scores.end(), [](const ScoreEntry &a, const ScoreEntry &b)
             { return b.score < a.score; });

   return scores;
}

void ScoreBoardScene::Initialize()
{
   int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
   int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
   int halfW = w / 2;
   int halfH = h / 2;
   AddNewObject(new Engine::Label("SCOREBOARD", "pirulen.ttf", 56, halfW, halfH / 6 + 10, 255, 255, 255, 255, 0.5, 0.5));

   scores = ReadScores("Resource/scoreboard.txt");
   currentPage = 0;
   totalPages = std::ceil(scores.size() / static_cast<float>(SCORES_PER_PAGE));

   for (int i = 0; i < 3 * SCORES_PER_PAGE; ++i)
   {
      Engine::Label *scoreLabel = new Engine::Label("", "pirulen.ttf", 32,
                                                    halfW, halfH / 4 + 50 + i * 50,
                                                    255, 255, 255, 255, 0.5, 0.5);
      scoreLabels.push_back(scoreLabel);
      AddNewObject(scoreLabel);
   }

   ShowPage(currentPage);

   Engine::ImageButton *btn;
   
   btn = new Engine::ImageButton("play/play2.png", "play/play5.png", halfW - 250, halfH * 7 / 4 - 100, 500, 202.5);
   btn->SetOnClickCallback(std::bind(&ScoreBoardScene::BackOnClick, this, 2));
   AddNewControlObject(btn);
   AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW, halfH * 7 / 4, 0, 0, 0, 255, 0.5, 0.5));

   btn = new Engine::ImageButton("play/play2.png", "play/play5.png", halfW + 500, halfH * 7 / 4 - 50, 250, 101.25);
   btn->SetOnClickCallback(std::bind(&ScoreBoardScene::NextPageOnClick, this));
   AddNewControlObject(btn);
   AddNewObject(new Engine::Label("Next", "pirulen.ttf", 24, halfW + 625, halfH * 7 / 4, 0, 0, 0, 255, 0.5, 0.5));

   // Previous Page Button
   btn = new Engine::ImageButton("play/play2.png", "play/play5.png", halfW - 750, halfH * 7 / 4 - 50, 250, 101.25);
   btn->SetOnClickCallback(std::bind(&ScoreBoardScene::PrevPageOnClick, this));
   AddNewControlObject(btn);
   AddNewObject(new Engine::Label("Prev", "pirulen.ttf", 24, halfW - 625, halfH * 7 / 4, 0, 0, 0, 255, 0.5, 0.5));
}

void ScoreBoardScene::Terminate()
{
   // for (auto label : scoreLabels) {
   //      delete label;
   //  }
   scoreLabels.clear();
   IScene::Terminate();
}

void ScoreBoardScene::BackOnClick(int stage)
{
   
   Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}

void ScoreBoardScene::ShowPage(int page)
{
   int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
   int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
   int halfW = w / 2;
   int halfH = h / 2;

   int startIndex = page * SCORES_PER_PAGE;
   int endIndex = std::min(startIndex + SCORES_PER_PAGE, static_cast<int>(scores.size()));

   int labelIndex = 0; // Keep track of label index

   // Update and show labels for the current page
   for (int i = startIndex; i < endIndex; ++i)
   {
      if (labelIndex < 3 * SCORES_PER_PAGE)
      {
         // 1. Set the Text FIRST (for both name and score labels)
         scoreLabels[labelIndex]->Text = scores[i].name;
         scoreLabels[labelIndex + 1]->Text = std::to_string(scores[i].score);
         scoreLabels[labelIndex + 2]->Text = scores[i].date;

         // 2. Calculate Text Widths using the Label's method
         int nameWidth = scoreLabels[labelIndex]->GetTextWidth();
         int scoreWidth = scoreLabels[labelIndex + 1]->GetTextWidth();
         int dateWidth = scoreLabels[labelIndex + 2]->GetTextWidth();

         // 3. Position the Name Label (Example: Left Aligned)
         scoreLabels[labelIndex]->Position.x = halfW - nameWidth / 2 - 250;             // Adjust spacing as needed
         scoreLabels[labelIndex]->Position.y = halfH / 4 + 50 + (labelIndex / 3) * 50; // Correct vertical spacing
         scoreLabels[labelIndex]->Visible = true;

         // 4. Position the Score Label (Example: Right Aligned)
         scoreLabels[labelIndex + 1]->Position.x = halfW + scoreWidth / 2 - 50;            // Adjust spacing
         scoreLabels[labelIndex + 1]->Position.y = halfH / 4 + 50 + (labelIndex / 3) * 50; // Correct vertical spacing
         scoreLabels[labelIndex + 1]->Visible = true;

         // 4. Position the Score Label (Example: Right Aligned)
         scoreLabels[labelIndex + 2]->Position.x = halfW + dateWidth / 2 + 200;           // Adjust spacing
         scoreLabels[labelIndex + 2]->Position.y = halfH / 4 + 50 + (labelIndex / 3) * 50; // Correct vertical spacing
         scoreLabels[labelIndex + 2]->Visible = true;

         labelIndex += 3;
      }
   }

   // Hide any remaining labels
   for (int i = labelIndex; i < 3 * SCORES_PER_PAGE; ++i)
   {
      scoreLabels[i]->Visible = false;
   }
}

void ScoreBoardScene::NextPageOnClick()
{
   if (currentPage < totalPages - 1)
   {
      currentPage++;
      ShowPage(currentPage);
   }
}

void ScoreBoardScene::PrevPageOnClick()
{
   if (currentPage > 0)
   {
      currentPage--;
      ShowPage(currentPage);
   }
}

void ScoreBoardScene::ClearScoreLabels()
{
   // // Delete each label and clear the vector
   // for (size_t i = 0; i < scoreLabels.size(); ++i)
   // {
   //    delete scoreLabels[i]; // Release memory for the label
   // }
   // // scoreLabels.clear();
}