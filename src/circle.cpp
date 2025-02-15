#include "../headers/circle.h"

circle::circle(Vector2 position, float radius) : entity(position) {
   this->initial_radius = radius;
   this->current_radius = radius;
}

circle::circle() {}

void circle::set_initial_radius(float radius) {
   this->initial_radius = radius;
}

float circle::get_initial_radius() const {
   return this->initial_radius;
}

void circle::set_current_radius(float radius) {
   this->current_radius = radius;
}

float circle::get_current_radius() const {
   return this->current_radius;
}

void circle::set_mouse_over_growth_mult(float mult) {
   this->mouse_over_growth_mult = mult;
}

float circle::get_mouse_over_growth_mult() const {
   return this->mouse_over_growth_mult;
}

bool circle::is_mouse_over() const {
   return CheckCollisionPointCircle(GetMousePosition(), get_position(), this->current_radius);
}

void circle::set_frozen(bool b) {
   this->frozen = b;
}

bool circle::is_frozen() const {
   return this->frozen;
}

void circle::draw() {
   DrawCircle(get_position().x, get_position().y, this->current_radius, get_color());
}
