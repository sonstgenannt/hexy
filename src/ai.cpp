#include "../headers/ai.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

ai::ai() = default;

void ai::make_move(board& b) 
{
   std::vector<std::pair<circle*, circle*>> move_candidates;
   std::vector<std::pair<circle*, circle*>> losing_moves;
   const unsigned int num_circles = b.get_circles().size();

   for (size_t i = 0; i < num_circles - 1; ++i)
   {
      for (size_t j = i + 1; j < num_circles; ++j) 
      {
         circle* circ_a = &b.get_circles()[i];
         circle* circ_b = &b.get_circles()[j];

         if ( b.is_move_valid( circ_a, circ_b ) ) 
         {
            if (!b.simulate_move (circ_a, circ_b))
            {
               move_candidates.push_back(std::make_pair(circ_a, circ_b));
            }
            else
            {
               losing_moves.push_back(std::make_pair(circ_a, circ_b));
            }
         }
      }
   }
   if ( move_candidates.size() > 0 ) 
   {
      int rand_int = rand() % move_candidates.size();
      b.make_move(move_candidates[rand_int].first, move_candidates[rand_int].second);
   }
   else
   {
      int rand_int = rand() % losing_moves.size();
      b.make_move(losing_moves[rand_int].first, losing_moves[rand_int].second);
   }
}

