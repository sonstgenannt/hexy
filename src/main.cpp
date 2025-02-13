#include "raylib.h" 
#include "../headers/board.h"
#include <numbers>
#include <cmath>
#include <iostream>
#include <vector>
#include <array>

const int SCREEN_WIDTH = 1000; 
const int SCREEN_HEIGHT = 1000;

const int TOTAL_CIRCLES = 6;
const int TOTAL_LINES = ( TOTAL_CIRCLES * (TOTAL_CIRCLES - 1) ) / 2; // Total number of edges in the complete graph on TOTAL_CIRCLES vertices

const float GROWTH_MULT = 1.3f;

std::vector<circle> circles;
circle* source = nullptr;
circle* target = nullptr;
circle* lines[TOTAL_LINES][2];
int line_counter = 0;
circle* draggable_circle = nullptr;
Vector2 circle_initial_positions[6];
std::vector<Color> player_colors = {RED, BLUE};

int main(void)
{
   //init_circles(300.0f, 30.0f);
   InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "hexy");
   SetTargetFPS(144);               
   board b(1000, circles, player_colors, 6, 2);
   b.init_circles(300.0f, 30.0f);
   
   while (!WindowShouldClose())    
   {
      b.poll_input_events();
      BeginDrawing();
      b.draw();

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
