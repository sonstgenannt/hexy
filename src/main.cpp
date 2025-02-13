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

const Color DEFAULT_CIRCLE_COLOR = BLACK;
const Color SOURCE_CIRCLE_COLOR = RED;
const Color FROZEN_CIRCLE_COLOR = BLUE;

void init_circles(const float& poly_radius, const float& circle_radius) {

   int centre_x = SCREEN_WIDTH / 2;
   int centre_y = SCREEN_HEIGHT / 2;
   double angle = (2.0f * std::numbers::pi) / (double)TOTAL_CIRCLES; 

   for (int i = 0; i < TOTAL_CIRCLES; ++i) {

      circle c {};

      int x = centre_x + (poly_radius * std::cos(i * angle));
      int y = centre_y + (poly_radius * std::sin(i * angle));

      // We are safe to cast x and y to floats since we do not expect them to be larger than 2^24.
      circle_initial_positions[i] = Vector2{ static_cast<float>(x), static_cast<float>(y) };
      c.set_centre(Vector2{ static_cast<float>(x), static_cast<float>(y)});
      c.set_current_radius(circle_radius);
      c.set_initial_radius(circle_radius);
      c.set_mouse_over_growth_mult(GROWTH_MULT);
      c.set_color(DEFAULT_CIRCLE_COLOR);
      c.set_frozen(false);

      circles.push_back(c);
   }
}

int main(void)
{
   init_circles(300.0f, 30.0f);
   InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "hexy");
   SetTargetFPS(144);               
   board b(1000, circles, player_colors, 6, 2);
   
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
