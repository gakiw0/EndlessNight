#include "StoryScene.hpp"
#include "Engine/GameEngine.hpp"
#include "UI/Component/Label.hpp" // Or however you manage fonts in your engine
#include <allegro5/allegro_font.h>

StoryScene::StoryScene()
    : currentLineIndex(0), textAlpha(0.0f),
      fadeSpeed(0.5f), fadingIn(true), timeElapsed(0.0f) {}

void StoryScene::Initialize()
{
   lines = {
       "HOW LONG WILL THE NIGHT BE?",
       "NOW....",
       "WHO KNOWS?"};
}

void StoryScene::Update(float deltaTime)
{
   timeElapsed += deltaTime;

   if (fadingIn)
   {
      textAlpha += fadeSpeed * deltaTime;
      if (textAlpha >= 1.0f)
      {
         textAlpha = 1.0f;
         fadingIn = false;
         timeElapsed = 0.0f; // Reset timeElapsed when fading in starts
      }
   }
   else
   {
      textAlpha -= fadeSpeed * deltaTime;
      if (textAlpha <= 0.0f)
      {
         textAlpha = 0.0f;
         currentLineIndex++; // Move to the next line
         fadingIn = true;

         // Check if we're at the end of the story lines
         if (currentLineIndex >= lines.size())
         {
            // If we are, set timeElapsed to 2.0f to trigger the scene change
            // on the next update
            timeElapsed = 2.0f;
         }
         else
         {
            // If not, reset timeElapsed for the next line
            timeElapsed = 0.0f;
         }
      }
   }

   // Now, check if the time elapsed is greater than or equal to 2.0f
   // The scene will change after the last line has faded out
   if (timeElapsed >= 2.0f)
   {
      Engine::GameEngine::GetInstance().ChangeScene("play");
      AudioHelper::StopSample(bgmInstance);
   }
}

void StoryScene::Draw() const
{
   IScene::Draw();
   if (currentLineIndex < lines.size())
   {
      int screenWidth = Engine::GameEngine::GetInstance().GetScreenSize().x;
      int screenHeight = Engine::GameEngine::GetInstance().GetScreenSize().y;

      Engine::Label label(lines[currentLineIndex],
                          "onesize.ttf", // Your font name
                          32,
                          screenWidth / 2,
                          screenHeight / 2,
                          255, 255, 255, static_cast<unsigned char>(textAlpha * 255),
                          0.5f, 0.5f);

      label.Draw(); // Draw the label
   }
}

void StoryScene::Terminate()
{
   IScene::Terminate();
}
