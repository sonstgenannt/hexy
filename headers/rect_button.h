#ifndef RECT_BUTTON
#define RECT_BUTTON

#include "raylib.h"

class rect_button 
{
   private:
      Vector2 size;
      Vector2 position;
      Rectangle bounds;

      Color background_color;
      Color hover_background_color;
      Color current_background_color;

      Color texture_color;
      Color hover_texture_color;
      Color current_texture_color;

      Texture2D icon_texture;

      float scale = 1.0f;
      float rotation = 0.0f;

      bool mouse_over = false;
      bool activated = false;

      bool rounded = false;
      float roundness = 0.2f;
      int segments = 10;

   public:
      rect_button(const Vector2& position, const Vector2& size, const Color& background_color, const Color& texture_color, Texture2D& icon_texture);
      void draw() const;
      void update();

      void set_hover_background_color(const Color& color);
      void set_hover_texture_color(const Color& color);

      void set_scale(const float& f);

      bool get_activated() const;

      bool get_rounded() const;
      void set_rounded(const bool& b);
};

#endif
