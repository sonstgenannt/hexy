#include "raylib.h"
#include "../headers/circle.h"
#include <numbers>
#include <cmath>
#include <iostream>

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 1000;

const int TOTAL_CIRCLES = 6;
const int TOTAL_LINES = ( TOTAL_CIRCLES * (TOTAL_CIRCLES - 1) ) / 2; // Total number of edges in the complete graph on TOTAL_CIRCLES vertices


circle circles[TOTAL_CIRCLES];
circle* source = nullptr;
circle* target = nullptr;
circle* lines[TOTAL_LINES][2];
int line_counter = 0;
circle* draggable_circle = nullptr;
Vector2 circle_initial_positions[6];

const Color DEFAULT_CIRCLE_COLOR = BLACK;
const Color SOURCE_CIRCLE_COLOR = BLUE;

void init_circles(const float& poly_radius, const float& circle_radius) {

   int centre_x = SCREEN_WIDTH / 2;
   int centre_y = SCREEN_HEIGHT / 2;

   double angle = (2.0f * std::numbers::pi) / (double)TOTAL_CIRCLES;

   for (int i = 0; i < TOTAL_CIRCLES; ++i) {

      int x = centre_x + (poly_radius * std::cos(i * angle));
      int y = centre_y + (poly_radius * std::sin(i * angle));

      // We are safe to cast x and y to floats since we do not expect them to be larger than 2^24.
      circle_initial_positions[i] = Vector2{ static_cast<float>(x), static_cast<float>(y) };
      circles[i].set_centre(Vector2{ static_cast<float>(x), static_cast<float>(y)});
      circles[i].set_current_radius(circle_radius);
      circles[i].set_initial_radius(circle_radius);
      circles[i].set_mouse_over_growth_mult(1.2f);
   }
}

int main(void)
{
   init_circles(300.0f, 30.0f);
   InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "hexy");
   SetTargetFPS(144);               

   while (!WindowShouldClose())    
   {
      BeginDrawing();

      for (int i = 0; i < TOTAL_LINES; ++i) {
         if ( (lines[i][0] != nullptr) && (lines[i][1] != nullptr) ) {
            DrawLineEx(lines[i][0]->get_centre(), lines[i][1]->get_centre(), 5.0f, RED);
         }
      }

      // Checking for mouse over circles
      for (int i = 0; i < TOTAL_CIRCLES; ++i) {
         // If mouse is over a circle
         if ( circles[i].is_mouse_over() ) {
            circles[i].set_current_radius(circles[i].get_mouse_over_growth_mult() * circles[i].get_initial_radius());

            // If RMB is pressed
            if ( IsMouseButtonPressed(1) ) 
               draggable_circle = &circles[i];

            else if ( IsMouseButtonReleased(1) && draggable_circle != nullptr) 
               draggable_circle = nullptr;

            // If LMB is pressed
            else if ( IsMouseButtonPressed(0) ) {
               if ( source == nullptr ) {
                  source = &circles[i];
                  std::cout << "source: " << i << std::endl;
               }
               else {
                  if ( source != &circles[i] ) {
                     target = &circles[i];
                     std::cout << "target: " << i << std::endl;
                  }
                  else {
                     source = nullptr;
                     std::cout << "source: null" << std::endl;
                  }
               }
            }

            if ( ( ( source != nullptr ) && (target != nullptr) ) && (source != target) ) {

               bool valid_line = true;

               for (int j = 0; j < TOTAL_LINES; ++j) {
                  if ( ( ( lines[j][0] == source ) && ( lines[j][1] == target ) ) || ( ( lines[j][0] == target ) && ( lines[j][1] == source ) ) ){
                     valid_line = false;
                     break;
                  }
               }

               if ( valid_line ) {
                  lines[line_counter][0] = source;
                  lines[line_counter][1] = target;
                  line_counter++;
                  std::cout << "added line: " << line_counter << std::endl;
                  source = nullptr;
                  target = nullptr;
                  std::cout << "source = target = null" << std::endl;
               }
            }
         }
         else
            circles[i].set_current_radius(circles[i].get_initial_radius());

         if ( &circles[i] != source )
            DrawCircle(circles[i].get_centre().x, circles[i].get_centre().y, circles[i].get_current_radius(), DEFAULT_CIRCLE_COLOR);
         else
            DrawCircle(circles[i].get_centre().x, circles[i].get_centre().y, circles[i].get_current_radius(), SOURCE_CIRCLE_COLOR);
      }


      if (draggable_circle != nullptr) {
         draggable_circle->set_centre(GetMousePosition());
      }

      // Reset circle positions
      if ( IsKeyDown(KEY_R) ) {
         for (int i = 0; i < TOTAL_CIRCLES; ++i) {
            circles[i].set_centre(circle_initial_positions[i]);
         }
      }

      ClearBackground(RAYWHITE);
      EndDrawing();
   }
   CloseWindow();

   return 0;
}
