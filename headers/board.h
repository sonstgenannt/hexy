#ifndef BOARD
#define BOARD

#include "line.h"
#include <vector>
#include <cmath>
#include <utility>
#include <tuple>

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

      std::tuple<bool, std::vector<circle*>, Color> mono_tri_data;

      bool game_over;

      std::vector<circle> circles;
      std::vector<line> lines;
      std::vector<Color> player_colors;

      bool only_show_hover_lines;
      circle* hover_circle;

      std::vector<Vector2> circle_initial_positions;

      std::pair<bool, line*> does_line_exist(circle* circ_a, circle* circ_b);
      bool are_colors_equal(const Color& col_a, const Color& col_b) const;

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
      std::tuple<bool, std::vector<circle*>, Color> contains_monochromatic_triangle();
};
#endif
