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
   DrawRectangleRec(this->bounds, this->background_color);
   DrawTexture(this->icon_texture, position.x, position.y, this->texture_color);
}
