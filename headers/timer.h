#ifndef TIMER
#define TIMER
#include <chrono>
#include <thread>

class timer
{
   private:
      std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
      bool running;
   public:
      timer(const bool& b);

      void start();
      void stop();
      double time_elapsed();
};
#endif
