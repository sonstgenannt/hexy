#include "../headers/board.h"
#include <iostream>

board::board(const Vector2& position, const unsigned int& board_size, const unsigned int& max_circles, const unsigned int& total_players, const std::vector<Color>& player_colors ) : entity(position) {
   this->board_size = board_size;

   for (size_t i = 0; i < 3; ++i) {
      this->triangle[i] = nullptr;
   }

   this->total_players = total_players;
   this->max_circles = max_circles;
   this->max_lines = ( max_circles * ( max_circles - 1 ) ) / 2;
   this->line_counter = 0;

   this->player_colors = player_colors;
   this->player_turn_idx = 0;

   this->line_source = nullptr;
   this->line_target = nullptr;

   this->draggable_circle = nullptr;

   this->default_circle_color = BLACK;
   this->frozen_circle_color = BLUE;
   this->source_circle_color = RED;

   this->circle_growth_mult = 1.2f;
}

void board::poll_input_events() {
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
            }
            else {
               if ( this->line_source != &this->circles[i] ) {
                  this->line_target = &this->circles[i];
               }
               else {
                  this->line_source = nullptr;
               }
            }
         }

         //////////////////////////////////////////////////////////////

         // Checking whether source and target circles exist and are distinct
         if ( ((this->line_source != nullptr) && (this->line_target != nullptr)) && (this->line_source != this->line_target) ) {

            bool valid_line = true;

            // Checking whether the lines [source -> target] and [target -> source] already exist
            if ( !lines.empty() ) {
               for (int j = 0; j < this->line_counter; ++j) {
                  if ( ((this->lines[j].get_source() == this->line_source) && (this->lines[j].get_target() == this->line_target)) || ((this->lines[j].get_source() == this->line_target) && (this->lines[j].get_target() == this->line_source)) ) {
                     valid_line = false;
                     break;
                  }
               }
            }

            if ( valid_line ) {
               this->lines.push_back( line(this->line_source, this->line_target, 5.0f, this->player_colors[this->player_turn_idx]) );
               this->player_turn_idx = ( 1 + this->player_turn_idx ) % this->total_players;
               this->line_counter++;
               this->line_source = nullptr;
               this->line_target = nullptr;

               if ( (line_counter >= 5) && contains_monochromatic_triangle().first ) {
                  std::cout << "TRIANGLE FOUND" << std::endl;
                  std::vector<circle*> two = contains_monochromatic_triangle().second;
                  triangle[0] = two[0];
                  triangle[1] = two[1];
                  triangle[2] = two[2];
               }
            }
         }
      }
      else
         this->circles[i].set_current_radius(this->circles[i].get_initial_radius());

      if ( &this->circles[i] != this->line_source ) {
         if ( this->circles[i].is_frozen() ) 
            this->circles[i].set_color(this->frozen_circle_color);
         else
            this->circles[i].set_color(this->default_circle_color);
      }
      else {
         this->circles[i].set_color( this->player_colors[player_turn_idx] );
      }


      if (this->draggable_circle != nullptr) {

         Vector2 mp = GetMousePosition();
         float cr = draggable_circle->get_current_radius();

         if ( ( mp.x > this->get_position().x ) && ( mp.x < this->get_position().x + this->board_size ) && ( mp.y > this->get_position().y ) && ( mp.y < this->get_position().y + this->board_size ) )
            this->draggable_circle->set_position(GetMousePosition());
         else
            this->draggable_circle = nullptr;
      }
   }

   if (IsKeyPressed(KEY_SPACE)) {
      this->reset_board();
   }

   if (IsKeyPressed(KEY_R)) {
      this->return_circles_to_initial_positions();
   }
}

void board::draw() {
   // Drawing the background rectangle of the board
   DrawRectangleV(this->get_position(), Vector2(this->board_size, this->board_size), this->get_color());

   if ( !this->lines.empty() ) {
      for (int i = 0; i < this->line_counter; ++i) {
         if ( (this->lines[i].get_source() != nullptr) && (this->lines[i].get_target() != nullptr) ) {
            lines[i].draw();
         }
      }
   }

   for (int i = 0; i < this->circles.size(); ++i) {
      circles[i].draw();
   }

   if (triangle[0] != nullptr) {
      DrawTriangle(triangle[0]->get_position(), triangle[1]->get_position(), triangle[2]->get_position(), PINK);
   }
}

void board::init_circles(const float& poly_radius, const float& circle_radius) {

   int centre_x = this->get_position().x + (this->board_size / 2); 
   int centre_y = this->get_position().y + (this->board_size / 2);
   double angle = (2.0f * std::numbers::pi) / (double)this->max_circles; 

   for (int i = 0; i < max_circles; ++i) {

      circle c {};

      int x = centre_x + (poly_radius * std::cos(i * angle));
      int y = centre_y + (poly_radius * std::sin(i * angle));

      // We are safe to cast x and y to floats since we do not expect them to be larger than 2^24.
      this->circle_initial_positions.push_back(Vector2{ static_cast<float>(x), static_cast<float>(y) });
      c.set_position(Vector2{ static_cast<float>(x), static_cast<float>(y)});
      c.set_current_radius(circle_radius);
      c.set_initial_radius(circle_radius);
      c.set_mouse_over_growth_mult(this->circle_growth_mult);
      c.set_color(this->default_circle_color);
      c.set_frozen(false);

      this->circles.push_back(c);
   }
}

void board::return_circles_to_initial_positions() {
   for (int i = 0; i < max_circles; ++i) {
      this->circles[i].set_position(this->circle_initial_positions[i]);
   }
}

std::pair<bool, std::vector<circle*>> board::contains_monochromatic_triangle() const {
   if (this->line_counter < 5)
      return std::make_pair(false, std::vector<circle*>());
   else
      return std::make_pair(false, std::vector<circle*>());
}

void board::reset_board() {
   this->player_turn_idx = 0;
   this->lines.clear();
   this->line_source = nullptr;
   this->line_target = nullptr;
   this->draggable_circle = nullptr;
   this->line_counter = 0;
}

unsigned int board::get_size() const {
   return this->board_size;
}
void board::set_default_circle_color(const Color& col) {
   this->default_circle_color = col;
}
void board::set_frozen_circle_color(const Color& col) {
   this->frozen_circle_color = col;
}
void board::set_source_circle_color(const Color& col) {
   this->source_circle_color = col;
}

Color board::get_default_circle_color() const {
   return this->default_circle_color;
}
Color board::get_frozen_circle_color() const {
   return this->frozen_circle_color;
}

Color board::get_source_circle_color() const {
   return this->source_circle_color;
}

