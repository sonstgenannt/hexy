#ifndef LINE
#define LINE

#include "circle.h"

class line {
   private:
      const circle* source;
      const circle* target;
      Color color;
      float thickness;
      Vector2 end;
      float end_delta;

   public:
      line(const circle* source, const circle* target);
      line(const circle* source, const circle* target, const Color& color);
      line(const circle* source, const circle* target, const float& thickness, const Color& color);

      const circle* get_source() const;
      const circle* get_target() const;

      Color get_color() const;
      void set_color(const Color& color);

      void set_thickness(const float& thickness);
      float get_thickness() const;

      void update(const float& delta);
      void draw() const;

      bool operator==(const line& l) const;

      ~line() = default;
};

#endif
