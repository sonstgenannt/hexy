#ifndef RECT_BUTTON
#define RECT_BUTTON

#include "raylib.h"

class rect_button 
{
   private:
      Rectangle bounds;
      Vector2 position;
      Color background_color = WHITE;
      Color texture_color;
      Texture2D icon_texture;

   public:
      rect_button(const Rectangle& bounds, const Vector2& position, const Color& background_color, const Color& texture_color, Texture2D& icon_texture);
      void draw() const;

};

#endif
