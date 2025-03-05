#ifndef RECT_BUTTON
#define RECT_BUTTON

#include "raylib.h"

class rect_button 
{
   private:
      Rectangle bounds;
      Vector2 position;
      Color background_color = WHITE;
      Color hover_background_color = WHITE;
      Color current_color = WHITE;
      Color texture_color;
      Texture2D icon_texture;

      bool mouse_over = false;
      bool activated = false;

   public:
      rect_button(const Rectangle& bounds, const Vector2& position, const Color& background_color, const Color& texture_color, Texture2D& icon_texture);
      void draw() const;
      void update();

      void set_hover_background_color(const Color& color);
      bool get_activated() const;
};

#endif
