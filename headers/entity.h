#ifndef ENTITY
#define ENTITY

#include "../include/raylib.h"

class entity {
   private:
      Vector2 position;
      Vector2 scale;
      Color color;

   public:
      entity(const Vector2& position);
      entity();

      void set_position(const Vector2& position);
      Vector2 get_position() const;

      void set_scale(const Vector2& scale);
      Vector2 get_scale() const;

      void set_color(const Color& color);
      Color get_color() const;

      virtual void draw() = 0;
      virtual ~entity() = default;
};

#endif
