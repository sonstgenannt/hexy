#ifndef DATA_MANAGER
#define DATA_MANAGER
#define STORAGE_DATA_FILE "storage.data"
#include <stdlib.h>
#include "raylib.h"

class data_manager 
{ 
   public:
      enum storage_position : unsigned int {
         WINS_SIX = 0,
         LOSSES_SIX = 1,
         WINS_SEVEN = 2,
         LOSSES_SEVEN = 3,
         WINS_EIGHT = 4,
         LOSSES_EIGHT = 5,
         WINS_NINE = 6,
         LOSSES_NINE = 7,
         WINS_TEN = 8,
         LOSSES_TEN = 9,
         WINS_ELEVEN = 10,
         LOSSES_ELEVEN = 11,
         WINS_TWELVE = 12,
         LOSSES_TWELVE = 13,
         RES_X = 14,
         RES_Y = 15,
         SELECTED_RES = 16,
      };

      data_manager() = delete;
      static bool save_storage_value(unsigned int position, int value);
      static int load_storage_value(unsigned int position);

      static void save_sr_config(unsigned int window_width, unsigned int window_height, unsigned int selected_item);
      static void load_sr_config(unsigned int& window_width, unsigned int& window_height, int& selected_item);
};

#endif
