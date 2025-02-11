#include "circle.h"

circle::circle(Vector2 centre, float radius) {
   this->centre = centre;
   this->initial_radius = radius;
   this->current_radius = radius;
}

circle::circle() {}

void circle::set_centre(Vector2 centre) {
   this->centre = centre;
}

Vector2 circle::get_centre() const {
   return this->centre;
}

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
   return CheckCollisionPointCircle(GetMousePosition(), this->centre, this->current_radius);
}
