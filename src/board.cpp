#include "../headers/board.h"

board::board(const unsigned int& board_size, const std::vector<circle>& circles, const std::vector<Color>& player_colors, const unsigned int& max_circles, const unsigned int& total_players) {
   this->circles = circles;
   this->board_size = board_size;

   this->total_players = total_players;
   this->max_circles = max_circles;
   this->max_lines = ( max_circles * ( max_circles - 1 ) ) / 2;
   this->line_counter = 0;

   this->player_colors = player_colors;

   this->line_source = nullptr;
   this->line_target = nullptr;
   this->draggable_circle = nullptr;

   this->default_circle_color = BLACK;
   this->frozen_circle_color = BLUE;
   this->source_circle_color = RED;
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
                  if ( ((this->lines[j][0] == this->line_source) && (this->lines[j][1] == this->line_target)) || ((this->lines[j][0] == this->line_target) && (this->lines[j][1] == this->line_source)) ) {
                     valid_line = false;
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
            this->circles[i].set_color(this->frozen_circle_color);
         else
            this->circles[i].set_color(this->default_circle_color);
      }
      else {
         this->circles[i].set_color(this->source_circle_color);
      }


      if (this->draggable_circle != nullptr) {

         Vector2 mp = GetMousePosition();
         float cr = draggable_circle->get_current_radius();

         if ( ( mp.x > 0 ) && ( mp.x < this->board_size ) && ( mp.y > 0 ) && ( mp.y < this->board_size ) )
            this->draggable_circle->set_centre(GetMousePosition());
         else
            this->draggable_circle = nullptr;
      }
   }
}

void board::draw() {
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

