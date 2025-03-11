#include "../headers/rect_button.h"
#include <iostream>

rect_button::rect_button(const Vector2& position, const Vector2& size, const Color& background_color, const Color& texture_color, const Texture2D& icon_texture, const Vector2& icon_size)
{
   this->size = size;
   this->position = position;
   this->icon_size = icon_size;

   this->bounds = Rectangle(position.x, position.y, size.x, size.y);
   this->background_color = background_color;
   this->texture_color = texture_color;
   this->icon_texture = icon_texture;

   this->hover_background_color = background_color;
   this->hover_texture_color = texture_color;
}

void rect_button::draw() const
{
   Color shadow = Color(this->current_background_color.r, this->current_background_color.g, this->current_background_color.b, 128);


   if (!rounded)
   {
      if (this->enable_shadow)
         DrawRectangleRec(Rectangle(this->bounds.x + 5.0f, this->bounds.y + 5.0f, this->bounds.width, this->bounds.height), shadow);

      DrawRectangleRec(this->bounds, this->current_background_color);
   }
   else
   {
      if (this->enable_shadow)
         DrawRectangleRounded(Rectangle(this->bounds.x + 5.0f, this->bounds.y + 5.0f, this->bounds.width, this->bounds.height) , this->roundness, this->segments, shadow);

      DrawRectangleRounded(this->bounds, this->roundness, this->segments, this->current_background_color);
   }

   const Vector2 icon_position = Vector2(position.x + ( (bounds.width - icon_size.x) / 2.0f ), position.y + ( (bounds.height - icon_size.y) / 2.0f) );
   DrawTextureEx(this->icon_texture, icon_position, this->rotation, this->scale, this->current_texture_color);
}

void rect_button::set_hover_background_color(const Color& color)
{
   this->hover_background_color = color;
}

void rect_button::set_hover_texture_color(const Color& color)
{
   this->hover_texture_color = color;
}

void rect_button::update()
{
   this->mouse_over = CheckCollisionPointRec(GetMousePosition(), this->bounds);

   if ( mouse_over )
   {
      this->current_background_color = hover_background_color;
      this->current_texture_color = hover_texture_color;

      if ( IsMouseButtonPressed(0) )
         this->activated = true;
      else
         this->activated = false;
   }
   else
   {
      this->current_background_color = background_color;
      this->current_texture_color = texture_color;
   }
}

bool rect_button::get_activated() const
{
   return this->activated;
}
bool rect_button::get_rounded() const
{
   return this->rounded;
}

void rect_button::set_scale(const float& f)
{
   this->scale = f;
   const Rectangle new_bounds(this->bounds.x, this->bounds.y, this->bounds.width * scale * this->rect_scale_multiplier, this->bounds.height * scale * rect_scale_multiplier);
   this->bounds = new_bounds;

   this->icon_size.x *= f;
   this->icon_size.y *= f;
}

void rect_button::set_rounded(const bool& b)
{
   this->rounded = b;
}

float rect_button::get_rect_scale_multiplier() const
{
   return this->rect_scale_multiplier;
}

void rect_button::set_rect_scale_multiplier(const float& f)
{
   this->rect_scale_multiplier = f;
}

bool rect_button::get_enable_shadow() const
{
   return this->enable_shadow;
}

void rect_button::set_enable_shadow(const bool& b)
{
   this->enable_shadow = b;
}
