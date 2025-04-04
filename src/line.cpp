#include "../headers/line.h"
#include "../include/raymath.h"

line::line(const circle* source, const circle* target) : source(source), target(target)
{
   this->thickness = 1.0f;
   this->color = BLACK;
}

line::line(const circle* source, const circle* target, const Color& color) : source(source), target(target)
{
   this->thickness = 1.0f;
   this->color = color;
}

line::line(const circle* source, const circle* target, const float& thickness, const Color& color) : source(source), target(target)
{
   this->thickness = thickness;
   this->color = color;
}

const circle* line::get_source() const 
{
   return this->source;
}

const circle* line::get_target() const 
{ 
   return this->target;
}

Color line::get_color() const 
{
   return this->color;
}
void line::set_color(const Color& color) 
{
   this->color = color;
}

void line::set_thickness(const float& thickness) 
{
   this->thickness = thickness;
}
float line::get_thickness() const 
{
   return this->thickness;
}

void line::update(const float& delta)
{
   this->end = Vector2Lerp(this->source->get_position(), this->target->get_position(), end_delta);
   if ( this->end_delta < 1.0f)
      this->end_delta += (5.0f * delta);

   this->end_delta = Clamp(this->end_delta, 0.0f, 1.0f);
}
void line::draw() const 
{
   DrawLineEx(this->source->get_position(), this->end, this->thickness, this->color);
}

bool line::operator==(const line& l) const
{
   if ( (this->source == l.get_source() && this->target == l.get_target()) ||
        (this->source == l.get_target() && this->target == l.get_source()) )
   {
      return true;
   }
   return false;
}
