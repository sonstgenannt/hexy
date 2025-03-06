#include "../headers/rect_button.h"

rect_button::rect_button(const Rectangle& bounds, const Vector2& position, const Color& background_color, const Color& texture_color, Texture2D& icon_texture)
{
   this->bounds = bounds;
   this->position = position;
   this->background_color = background_color;
   this->texture_color = texture_color;
   this->icon_texture = icon_texture;
}

void rect_button::draw() const
{
   DrawRectangleRec(this->bounds, this->current_color);
   DrawTextureEx(this->icon_texture, position, this->rotation, this->scale, this->texture_color);
}

void rect_button::set_hover_background_color(const Color& color)
{
   this->hover_background_color = color;
}
void rect_button::update()
{
   this->mouse_over = CheckCollisionPointRec(GetMousePosition(), this->bounds);

   if ( mouse_over )
   {
      this->current_color = hover_background_color;

      if ( IsMouseButtonPressed(0) )
         this->activated = true;
      else
         this->activated = false;
   }
   else
      this->current_color = background_color;
}

bool rect_button::get_activated() const
{
   return this->activated;
}

void rect_button::set_scale(const float& f)
{
   this->scale = f;
   const Rectangle new_bounds(this->bounds.x, this->bounds.y, this->bounds.width * scale, this->bounds.height * scale);
   this->bounds = new_bounds;
}
