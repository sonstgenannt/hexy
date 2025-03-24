#ifndef CIRCLE
#define CIRCLE

#include "entity.h"
#include <vector>

class line;

class circle : public entity 
{
   private:
      float initial_radius;
      float current_radius;
      float mouse_over_growth_mult;

      char shadow_alpha = 100;
      Vector2 shadow_offset = Vector2(5.0f, 5.0f);

      Vector2 target_position;
      float target_radius;

      bool frozen = false;
      bool enable_shadow = true;

      std::vector<line*> outgoing_lines;

      void set_current_radius(float radius);
      float get_current_radius() const;

   public:
      circle(Vector2 position, float radius);
      circle();

      void set_initial_radius(float radius);
      float get_initial_radius() const;

      void set_target_position(const Vector2 v);
      void set_target_radius(const float& f);

      void add_outgoing_line(line* outgoing_lines);
      std::vector<line*> get_outgoing_lines() const;
      void kill_outgoing_lines();

      void set_mouse_over_growth_mult(float mult);
      float get_mouse_over_growth_mult() const;

      bool is_mouse_over() const;

      bool is_frozen() const;
      void set_frozen(bool b);

      void set_enable_shadow(const bool& b);
      bool get_enable_shadow() const;

      void draw();
      void draw_shadow() const;
      void update(const float& delta);
};

#endif
