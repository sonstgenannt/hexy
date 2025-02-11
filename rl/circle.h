#include "raylib.h"

class circle {
   private:
      Vector2 centre;
      float initial_radius;
      float current_radius;
      float mouse_over_growth_mult;

   public:
      circle(Vector2 centre, float radius);
      circle();

      Vector2 get_centre() const;
      void set_centre(Vector2 centre);

      void set_initial_radius(float radius);
      float get_initial_radius() const;

      void set_current_radius(float radius);
      float get_current_radius() const;

      void set_mouse_over_growth_mult(float mult);
      float get_mouse_over_growth_mult() const;

      bool is_mouse_over() const;
      
};
