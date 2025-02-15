#include "../headers/entity.h"

entity::entity(const Vector2& position) {
   this->position = position;
   this->scale = Vector2(1,1);
   this->color = BLACK;
}

entity::entity() {}

void entity::set_position(const Vector2& position) {
   this->position = position;
}
Vector2 entity::get_position() const {
   return this->position;
}

void entity::set_scale(const Vector2& scale) {
   this->scale = scale;
}
Vector2 entity::get_scale() const {
   return this->scale;
}

void entity::set_color(const Color& color) {
   this->color = color;
}
Color entity::get_color() const {
   return this->color;
}
