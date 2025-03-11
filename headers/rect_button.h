#ifndef RECT_BUTTON
#define RECT_BUTTON

#include "raylib.h"

class rect_button 
{
   private:
      Vector2 size;
      Vector2 position;
      Vector2 icon_size;

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
      float rect_scale_multiplier = 1.0f;

      bool mouse_over = false;
      bool activated = false;
      bool enable_shadow = true;

      bool rounded = false;
      float roundness = 0.2f;
      int segments = 10;

   public:
      rect_button(const Vector2& position, const Vector2& size, const Color& background_color, const Color& texture_color, const Texture2D& icon_texture, const Vector2& icon_size);
      void draw() const;
      void update();

      void set_hover_background_color(const Color& color);
      void set_hover_texture_color(const Color& color);

      void set_scale(const float& f);

      bool get_activated() const;

      bool get_rounded() const;
      void set_rounded(const bool& b);

      float get_rect_scale_multiplier() const;
      void set_rect_scale_multiplier(const float& f);

      bool get_enable_shadow() const;
      void set_enable_shadow(const bool& b);
};

#endif
