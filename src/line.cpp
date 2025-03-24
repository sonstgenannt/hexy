#include "../headers/line.h"
#include "../include/raymath.h"

line::line(circle* source, circle* target) 
{
   this->source = source;
   this->target = target;
   source->add_outgoing_line(this);
   target->add_outgoing_line(this);
   this->thickness = 1.0f;
   this->color = BLACK;
}

line::line(circle* source, circle* target, const Color& color) 
{
   this->source = source;
   this->target = target;
   source->add_outgoing_line(this);
   target->add_outgoing_line(this);
   this->thickness = 1.0f;
   this->color = color;
}

line::line(circle* source, circle* target, const float& thickness, const Color& color) 
{
   this->source = source;
   this->target = target;
   source->add_outgoing_line(this);
   target->add_outgoing_line(this);
   this->thickness = thickness;
   this->color = color;
}

circle* line::get_source() const 
{
   return this->source;
}
void line::set_source(circle* source) 
{
   this->source = source;
}

circle* line::get_target() const 
{ 
   return this->target;
}
void line::set_target(circle* target) 
{
   this->target = target;
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
