#ifndef CIRCLE
#define CIRCLE

#include "entity.h"

class circle : public entity {
   private:
      float initial_radius;
      float current_radius;
      float mouse_over_growth_mult;
      bool frozen;

   public:
      circle(Vector2 position, float radius);
      circle();

      void set_initial_radius(float radius);
      float get_initial_radius() const;

      void set_current_radius(float radius);
      float get_current_radius() const;

      void set_mouse_over_growth_mult(float mult);
      float get_mouse_over_growth_mult() const;

      bool is_mouse_over() const;

      bool is_frozen() const;
      void set_frozen(bool b);

      void draw();
};

#endif
