#include "../headers/entity.h"

entity::entity(const Vector2& position) {
   this->position = position;
   this->scale = Vector2(1,1);
   this->Color = BLACK;
}

void entity::set_position(const Vector2& position) {
   this->position = position;
}
Vector2 get_position() const {
   return this->position;
}

void set_scale(const Vector2& scale) {
   this->scale = scale;
}
Vector2 get_scale() const {
   return this->scale;
}

void set_color(const Color& color) {
   this->color = color;
}
Color get_color() const {
   return this->color;
}
