#ifndef CIRCLE
#define CIRCLE

#include "entity.h"
#include <vector>

class line;

class circle : public entity {
   private:
      float initial_radius;
      float current_radius;
      float mouse_over_growth_mult;
      bool frozen;
      std::vector<line*> outgoing_lines;

   public:
      circle(Vector2 position, float radius);
      circle();

      void set_initial_radius(float radius);
      float get_initial_radius() const;

      void set_current_radius(float radius);
      float get_current_radius() const;

      void add_outgoing_line(line* outgoing_lines);
      std::vector<line*> get_outgoing_lines() const;
      void kill_outgoing_lines();

      void set_mouse_over_growth_mult(float mult);
      float get_mouse_over_growth_mult() const;

      bool is_mouse_over() const;

      bool is_frozen() const;
      void set_frozen(bool b);

      void draw();
};

#endif
