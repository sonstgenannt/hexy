#include "circle.h"
#include <vector>
#include <array>
#include <cmath>

class board {
   private:
      unsigned int board_size;

      unsigned int total_players;
      unsigned int max_circles;
      unsigned int max_lines;
      unsigned int player_turn_idx;
      unsigned int line_counter;

      Color default_circle_color;
      Color frozen_circle_color;
      Color source_circle_color;

      float circle_growth_mult;

      circle* line_source;
      circle* line_target;
      circle* draggable_circle;

      std::vector<circle> circles;
      std::vector<std::array<circle*, 2>> lines;
      std::vector<Color> player_colors;

      std::vector<Vector2> circle_initial_positions;

   public:
      board(const unsigned int& board_size, const std::vector<circle>& circles, const std::vector<Color>& player_colors, const unsigned int& max_circles, const unsigned int& total_players); 

      void poll_input_events();
      void draw();

      void init_circles(const float& poly_radius, const float& circle_radius);
};

