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

      Color background_color;

      float circle_growth_mult;

      circle* line_source;
      circle* line_target;
      circle* draggable_circle;

      std::vector<circle> circles;
      std::vector<std::array<circle*, 2>> lines;
      std::vector<Color> line_colors;
      std::vector<Color> player_colors;

      std::vector<Vector2> circle_initial_positions;
      Vector2 board_position;

   public:
      board(const unsigned int& board_size, const Vector2& board_position, const unsigned int& max_circles, const unsigned int& total_players, const std::vector<Color>& player_colors); 

      void poll_input_events();
      void draw();

      void init_circles(const float& poly_radius, const float& circle_radius);

      void set_background_color(const Color& col);
      Color get_background_color() const;

      Vector2 get_position() const;
      void set_position(const Vector2& position);

      unsigned int get_size() const;

      void set_default_circle_color(const Color& col);
      void set_frozen_circle_color(const Color& col);
      void set_source_circle_color(const Color& col);

      void return_circles_to_initial_positions();

      Color get_default_circle_color() const;
      Color get_frozen_circle_color() const;
      Color get_source_circle_color() const;

      void reset_board();
};

