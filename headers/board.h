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

      unsigned int total_players = 2;
      unsigned int max_circles = 0;
      unsigned int max_lines = 0;
      unsigned int turn_idx = 0;
      unsigned int line_counter = 0;

      int losing_player = -1;

      Color default_circle_color = BLACK;
      Color frozen_circle_color = PURPLE;
      Color source_circle_color = PINK;

      float circle_growth_mult = 1.2f;

      circle* line_source = nullptr;
      circle* line_target = nullptr;
      circle* draggable_circle = nullptr;
      circle* hover_circle = nullptr;

      std::tuple<bool, std::vector<circle*>, Color> mono_tri_data;

      bool game_started = false;
      bool game_over = false;
      bool only_show_hover_lines = false;
      bool ai_enabled = false;

      std::vector<circle> circles;
      std::vector<Color> player_colors;
      std::vector<Vector2> circle_initial_positions;

      std::pair<bool, line*> does_line_exist(circle* circ_a, circle* circ_b);
      bool are_colors_equal(const Color& col_a, const Color& col_b) const;

   public:
      std::vector<line> lines;
      board(const Vector2& position, const unsigned int& board_size, const unsigned int& max_circles, const unsigned int& total_players, const std::vector<Color>& player_colors); 
      board(const Vector2& position, const unsigned int& board_size);

      void poll_input_events();
      void draw();

      void init_circles(const float& poly_radius, const float& circle_radius);

      unsigned int get_size() const;
      void set_size(const unsigned int& size);

      void return_circles_to_initial_positions();
      void make_move(circle*& circ_a, circle*& circ_b, const float& line_thickness);
      bool simulate_move(circle*& circ_a, circle*& circ_b);

      void set_default_circle_color(const Color& col);
      void set_frozen_circle_color(const Color& col);
      void set_source_circle_color(const Color& col);

      void set_player_colors(const std::vector<Color>& player_colors);
      std::vector<Color> get_player_colors() const;

      void set_max_circles(const unsigned int& max_circles);

      void set_ai_enabled(const bool& b);
      bool get_ai_enabled() const;

      Color get_default_circle_color() const;
      Color get_frozen_circle_color() const;
      Color get_source_circle_color() const;

      std::vector<circle>& get_circles();

      unsigned int get_turn_idx() const;
      unsigned int get_max_circles() const;
      unsigned int get_line_counter() const;
      int get_losing_player() const;

      bool is_move_valid(circle*& circ_a, circle*& circ_b);

      bool is_game_over() const;

      bool get_game_started() const;
      void set_game_started(const bool& b);

      void reset_board();
      void kill_board();

      std::tuple<bool, std::vector<circle*>, Color> contains_monochromatic_triangle();
};
#endif
