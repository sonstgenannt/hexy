#include "../headers/timer.h"

timer::timer(const bool& b)
{
   this->running = b;
}

void timer::start()
{
   this->start_time = std::chrono::high_resolution_clock::now();
   this->running = true;
}

void timer::stop()
{
   this->running = false;
}

double timer::time_elapsed() const
{
   if (this->running) 
   {
      auto end_time = std::chrono::high_resolution_clock::now();
      return std::chrono::duration<double>(end_time - this->start_time).count();
   }
   return 0.0d;
}
