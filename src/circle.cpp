#include "../headers/circle.h"
#include "../include/raymath.h"

circle::circle(Vector2 position, float radius) : entity(position) 
{
   this->initial_radius = radius;
   this->current_radius = radius;
   this->target_position = position;
   this->target_radius = radius;
}

circle::circle() {}

void circle::set_initial_radius(float radius) 
{
   this->initial_radius = radius;
}

float circle::get_initial_radius() const 
{
   return this->initial_radius;
}

void circle::set_current_radius(float radius) 
{
   this->current_radius = radius;
}

float circle::get_current_radius() const 
{
   return this->current_radius;
}

void circle::set_mouse_over_growth_mult(float mult) 
{
   this->mouse_over_growth_mult = mult;
}

float circle::get_mouse_over_growth_mult() const 
{
   return this->mouse_over_growth_mult;
}

void circle::add_outgoing_line(line* outgoing_line) 
{
   this->outgoing_lines.push_back(outgoing_line);
}

std::vector<line*> circle::get_outgoing_lines() const 
{
   return this->outgoing_lines;
}

void circle::kill_outgoing_lines() 
{
   this->outgoing_lines.clear();
}

bool circle::is_mouse_over() const 
{
   return CheckCollisionPointCircle(GetMousePosition(), get_position(), this->current_radius);
}

void circle::set_frozen(bool b) 
{
   this->frozen = b;
}

bool circle::is_frozen() const 
{
   return this->frozen;
}

void circle::draw() 
{
   if (this->enable_shadow)
   {
      Color c = Color( get_color().r, get_color().g, get_color().b, this->shadow_alpha );
      DrawCircle( get_position().x + this->shadow_offset.x, get_position().y + this->shadow_offset.y, this->current_radius, c );
   }
   DrawCircle(get_position().x, get_position().y, this->current_radius, get_color());
}

void circle::set_enable_shadow(const bool& b)
{
   this->enable_shadow = b;
}
bool circle::get_enable_shadow() const
{
   return this->enable_shadow;
}
void circle::set_target_position(const Vector2 v)
{
   this->target_position = v;
}
void circle::set_target_radius(const float& f)
{
   this->target_radius = f;
}

void circle::update(const float& delta) 
{
   set_position(Vector2Lerp(get_position(), this->target_position, 5.0f * delta));
   set_current_radius(Lerp(get_current_radius(), this->target_radius, 10.0f * delta));
}
