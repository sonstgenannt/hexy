#include "raylib.h"
#include "../headers/circle.h"
#include <numbers>
#include <cmath>
#include <iostream>

const int screen_width = 1000;
const int screen_height = 1000;


circle circles[6];
circle* source = nullptr;
circle* target = nullptr;
circle* lines[15][2];
int line_counter = 0;
circle* draggable_circle = nullptr;
Vector2 circle_initial_positions[6];

const Color DEFAULT_CIRCLE_COLOR = BLACK;

void init_circles(unsigned int number_of_vertices, float poly_radius, float circle_radius) {

   int centre_x = screen_width / 2.0f;
   int centre_y = screen_height / 2.0f;

   double angle = (2.0f * std::numbers::pi) / number_of_vertices;

   for (int i = 0; i < number_of_vertices; ++i) {
      int x = centre_x + (poly_radius * std::cos(i * angle));
      int y = centre_y + (poly_radius * std::sin(i * angle));
      circles[i].set_centre(Vector2{x,y});
      circle_initial_positions[i] = Vector2{x,y};
      circles[i].set_current_radius(circle_radius);
      circles[i].set_initial_radius(circle_radius);
      circles[i].set_mouse_over_growth_mult(1.2f);
   }
}

int main(void)
{
   init_circles(6, 300.0f, 30.0f);
   InitWindow(screen_width, screen_height, "hexy");
   SetTargetFPS(144);               

   while (!WindowShouldClose())    
   {
      BeginDrawing();

      for (int i = 0; i < 15; ++i) {
         if ( (lines[i][0] != nullptr) && (lines[i][1] != nullptr) ) {
            DrawLineEx(lines[i][0]->get_centre(), lines[i][1]->get_centre(), 5.0f, RED);
         }
      }

      // Checking for mouse over circles
      for (int i = 0; i < 6; ++i) {
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
               }
               else {
                  if ( source != &circles[i] ) 
                     target = &circles[i];
                  else
                     source = nullptr;
               }
            }

            if ( ( source != nullptr ) && (target != nullptr) ) {
               bool valid_line = true;

               for (int j = 0; j < 15; ++j) {
                  if ( ( ( lines[j][0] == source ) && ( lines[j][1] == target ) ) || ( ( lines[j][0] == target ) && ( lines[j][1] == source ) ) ){
                     valid_line = false;
                     break;
                  }
               }

               if ( valid_line ) {
                  lines[line_counter][0] = source;
                  lines[line_counter][1] = target;
                  line_counter++;
                  std::cout << "added line " << line_counter << std::endl;
                  source = nullptr;
                  target = nullptr;
               }
            }
         }
         else
            circles[i].set_current_radius(circles[i].get_initial_radius());

         if ( &circles[i] != source )
            DrawCircle(circles[i].get_centre().x, circles[i].get_centre().y, circles[i].get_current_radius(), DEFAULT_CIRCLE_COLOR);
         else
            DrawCircle(circles[i].get_centre().x, circles[i].get_centre().y, circles[i].get_current_radius(), BLUE);
      }


      if (draggable_circle != nullptr) {
         draggable_circle->set_centre(GetMousePosition());
      }

      // Reset circle positions
      if ( IsKeyDown(KEY_R) ) {
         for (int i = 0; i < 6; ++i) {
            circles[i].set_centre(circle_initial_positions[i]);
         }
      }

      ClearBackground(RAYWHITE);
      EndDrawing();
   }
   CloseWindow();

   return 0;
}
