#ifndef LINE
#define LINE

#include "circle.h"

class line {
   private:
      circle* source;
      circle* target;
      Color color;

   public:
      line(circle* source, circle* target);
      line(circle* source, circle* target, const Color& color);

      circle* get_source() const;
      void set_source(circle* source);

      circle* get_target() const;
      void set_target(circle* target);

      Color get_color() const;
      void set_color(const Color& color);

      ~line() = default;
};

#endif
