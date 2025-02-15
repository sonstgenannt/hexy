#include "../headers/line.h"

line::line(circle* source, circle* target) {
   this->source = source;
   this->target = target;
   this->color = BLACK;
}

line::line(circle* source, circle* target, const Color& color) {
   this->source = source;
   this->target = target;
   this->color = color;
}

circle* line::get_source() const {
   return this->source;
}
void line::set_source(circle* source) {
   this->source = source;
}

circle* line::get_target() const { 
   return this->target;
}
void line::set_target(circle* target) {
   this->target = target;
}

Color line::get_color() const {
   return this->color;
}
void line::set_color(const Color& color) {
   this->color = color;
}
