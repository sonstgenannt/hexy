#include "raylib.h" 
#include "../headers/board.h"
#include <numbers>
#include <cmath>
#include <iostream>
#include <vector>
#include <array>

const int SCREEN_WIDTH = 800; 
const int SCREEN_HEIGHT = 800;

std::vector<Color> player_colors = { RED, BLUE };

int main(void)
{
   InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "rokkaku");
   const Vector2 screen_centre = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
   SetTargetFPS(144);               
   board b(Vector2(0,0), 800, 6, 2, player_colors);
   b.init_circles(300.0f, 30.0f);
   b.set_color(WHITE);
   
   while (!WindowShouldClose())    
   {
      b.poll_input_events();
      b.set_default_circle_color(BLACK);
      b.set_frozen_circle_color(DARKPURPLE);
      BeginDrawing();
      b.draw();

      ClearBackground(RAYWHITE);
      EndDrawing();
   }
   CloseWindow();

   return 0;
}
