#include "raylib.h"
#include "../headers/circle.h"
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
class board {
   private:
      unsigned int total_players;
      unsigned int max_circles;
      unsigned int max_lines;
      unsigned int player_turn_idx;
      unsigned int line_counter;

      circle* line_source;
      circle* line_target;
      circle* draggable_circle;

      std::vector<circle> circles;
      std::vector<std::array<circle*, 2>> lines;
      std::vector<Color> player_colors;

   public:
      board(const std::vector<circle>& circles, const std::vector<Color> player_colors, const unsigned int& max_circles, const unsigned int& total_players) {
         this->circles = circles;

         this->total_players = total_players;
         this->max_circles = max_circles;
         this->max_lines = ( max_lines * ( max_lines - 1 ) ) / 2;
         this->line_counter = 0;

         this->player_colors = player_colors;

         this->line_source = nullptr;
         this->line_target = nullptr;
         this->draggable_circle = nullptr;
      }

      void poll_input_events() {
         for (int i = 0; i < this->max_circles; ++i) {
            if ( this->circles[i].is_mouse_over() ) {
               this->circles[i].set_current_radius(this->circles[i].get_mouse_over_growth_mult() * this->circles[i].get_initial_radius());

               //////////////////////////////////////////////////////////////

               if ( IsKeyPressed(KEY_F) ) {
                  this->circles[i].set_frozen(!this->circles[i].is_frozen());

                  if (this->draggable_circle = &this->circles[i])
                     this->draggable_circle = nullptr;
               }

               //////////////////////////////////////////////////////////////

               if ( IsMouseButtonPressed(1) ) {
                  if ( !this->circles[i].is_frozen() ) 
                     this->draggable_circle = &this->circles[i];
               }
               else if ( IsMouseButtonReleased(1) && this->draggable_circle != nullptr) 
                  draggable_circle = nullptr;

               else if ( IsMouseButtonPressed(0) ) {
                  if ( this->line_source == nullptr ) {
                     this->line_source = &this->circles[i];
                     std::cout << "source set to: " << i << std::endl;
                  }
                  else {
                     if ( this->line_source != &this->circles[i] ) {
                        this->line_target = &this->circles[i];
                        std::cout << "target set to: " << i << std::endl;
                     }
                     else {
                        this->line_source = nullptr;
                        std::cout << "source reset to nullptr" << std::endl;
                     }
                  }
               }

               //////////////////////////////////////////////////////////////

               // Checking whether source and target circles exist and are distinct
               if ( ((this->line_source != nullptr) && (this->line_target != nullptr)) && (this->line_source != this->line_target) ) {

                  bool valid_line = true;

                  // Checking whether the lines [source -> target] and [target -> source] already exist
                  if ( !lines.empty() ) {
                     std::cout << "checking whether line is duplicate" << std::endl;
                     for (int j = 0; j < this->line_counter; ++j) {
                        std::cout << &lines[j][0] << " --- " << this->line_source << std::endl;
                        if ( ((this->lines[j][0] == this->line_source) && (this->lines[j][1] == this->line_target)) || ((this->lines[j][0] == this->line_target) && (this->lines[j][1] == this->line_source)) ) {
                           valid_line = false;
                           std::cout << "invalid line from source to target" << std::endl;
                           break;
                        }
                     }
                  }

                  if ( valid_line ) {
                     this->lines.push_back( {this->line_source, this->line_target} );
                     /*
                     lines[line_counter][0] = *this->line_source;
                     lines[line_counter][1] = *this->line_target;
                     */
                     this->line_counter++;

                     this->line_source = nullptr;
                     this->line_target = nullptr;
                  }
               }
            }
            else
               this->circles[i].set_current_radius(this->circles[i].get_initial_radius());

            if ( &this->circles[i] != this->line_source ) {
               if ( this->circles[i].is_frozen() ) 
                  this->circles[i].set_color(FROZEN_CIRCLE_COLOR);
               else
                  this->circles[i].set_color(DEFAULT_CIRCLE_COLOR);
            }
            else {
               this->circles[i].set_color(SOURCE_CIRCLE_COLOR);
            }


            if (this->draggable_circle != nullptr) {

               Vector2 mp = GetMousePosition();
               float cr = draggable_circle->get_current_radius();

               if ( ( mp.x > 0 ) && ( mp.x < SCREEN_WIDTH ) && ( mp.y > 0 ) && ( mp.y < SCREEN_HEIGHT ) )
                  this->draggable_circle->set_centre(GetMousePosition());
               else
                  this->draggable_circle = nullptr;
            }
         }
      }
      void draw() {
         if ( !this->lines.empty() ) {
            for (int i = 0; i < this->line_counter; ++i) {
               if ( (&this->lines[i][0] != nullptr) && (&this->lines[i][1] != nullptr) ) {
                  DrawLineEx(this->lines[i][0]->get_centre(), this->lines[i][1]->get_centre(), 5.0f, RED);
               }
            }
         }

         for (int i = 0; i < this->circles.size(); ++i) {
            DrawCircle(circles[i].get_centre().x, circles[i].get_centre().y, circles[i].get_current_radius(), circles[i].get_color());
         }
      }

};

int main(void)
{
   init_circles(300.0f, 30.0f);
   InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "hexy");
   SetTargetFPS(144);               
   board b(circles, player_colors, 6, 2);
   
   while (!WindowShouldClose())    
   {
      b.poll_input_events();
      BeginDrawing();
      b.draw();

      /*
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

            if ( IsKeyPressed(KEY_F) ) {
               circles[i].set_frozen(!circles[i].is_frozen());
               // The below if statement is required to ensure that if a circle is frozen whilst being dragged, then it cannot continue to be dragged.
               if ( draggable_circle = &circles[i] )
                  draggable_circle = nullptr;
            }

            // If RMB is pressed
            if ( IsMouseButtonPressed(1) ) {
               if ( !circles[i].is_frozen() ) 
                  draggable_circle = &circles[i];
            }

            else if ( IsMouseButtonReleased(1) && draggable_circle != nullptr) 
               draggable_circle = nullptr;

            // If LMB is pressed
            else if ( IsMouseButtonPressed(0) ) {
               if ( source == nullptr ) {
                  source = &circles[i];
               }
               else {
                  if ( source != &circles[i] ) {
                     target = &circles[i];
                  }
                  else {
                     source = nullptr;
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
                  source = nullptr;
                  target = nullptr;
               }
            }
         }
         else
            circles[i].set_current_radius(circles[i].get_initial_radius());

         if ( &circles[i] != source ) {
            if ( circles[i].is_frozen() ) 
               circles[i].set_color(FROZEN_CIRCLE_COLOR);
            else
               circles[i].set_color(DEFAULT_CIRCLE_COLOR);
         }
         else
            circles[i].set_color(SOURCE_CIRCLE_COLOR);
         DrawCircle(circles[i].get_centre().x, circles[i].get_centre().y, circles[i].get_current_radius(), circles[i].get_color());
      }


      if (draggable_circle != nullptr) {
         Vector2 mp = GetMousePosition();
         float cr = draggable_circle->get_current_radius();
         if ( ( mp.x > 0 ) && ( mp.x < SCREEN_WIDTH ) && ( mp.y > 0 ) && ( mp.y < SCREEN_HEIGHT ) )
            draggable_circle->set_centre(GetMousePosition());
         else
            draggable_circle = nullptr;
      }

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
