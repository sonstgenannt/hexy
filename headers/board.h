#ifndef BOARD
#define BOARD

#include "line.h"
#include <vector>
#include <cmath>
#include <utility>

class board : public entity {
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

      circle* triangle[3];

      std::vector<circle> circles;
      std::vector<line> lines;
      std::vector<Color> player_colors;

      std::vector<Vector2> circle_initial_positions;

   public:
      board(const Vector2& position, const unsigned int& board_size, const unsigned int& max_circles, const unsigned int& total_players, const std::vector<Color>& player_colors); 

      void poll_input_events();
      void draw();

      void init_circles(const float& poly_radius, const float& circle_radius);

      unsigned int get_size() const;

      void set_default_circle_color(const Color& col);
      void set_frozen_circle_color(const Color& col);
      void set_source_circle_color(const Color& col);

      void return_circles_to_initial_positions();

      Color get_default_circle_color() const;
      Color get_frozen_circle_color() const;
      Color get_source_circle_color() const;

      void reset_board();
      std::pair<bool, std::vector<circle*>> contains_monochromatic_triangle() const;
};
#endif
