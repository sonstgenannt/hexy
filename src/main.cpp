#include "raylib.h" 
#include "../headers/board.h"
#include <numbers>
#include <cmath>
#include <iostream>
#include <vector>
#include <array>

const int SCREEN_WIDTH = 1600; 
const int SCREEN_HEIGHT = 800;

std::vector<Color> player_colors = {WHITE};

int main(void)
{
   InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "hexy");
   SetTargetFPS(144);               
   board b(800, Vector2(0,0), 6, 2, player_colors);
   b.init_circles(300.0f, 30.0f);
   b.set_background_color(GREEN);
   board bb(800, Vector2(800,0), 8, 2, player_colors);
   bb.init_circles(300.0f, 30.0f);
   bb.set_background_color(ORANGE);
   
   while (!WindowShouldClose())    
   {
      b.poll_input_events();
      bb.poll_input_events();
      BeginDrawing();
      b.draw();
      bb.draw();

      /*
      // Reset circle positions
      if ( IsKeyDown(KEY_R) ) {
         for (int i = 0; i < TOTAL_CIRCLES; ++i) {
            if ( !circles[i].is_frozen() )
               circles[i].set_centre(circle_initial_positions[i]);
         }
      }
      */

      ClearBackground(RAYWHITE);
      EndDrawing();
   }
   CloseWindow();

   return 0;
}
