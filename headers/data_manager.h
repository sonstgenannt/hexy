#ifndef DATA_MANAGER
#define DATA_MANAGER
#define STORAGE_DATA_FILE "storage.data"
#include <stdlib.h>
#include "raylib.h"

class data_manager 
{ 
   public:
      enum class storage_position : unsigned int {
         WINS_SIX = 0,
         LOSSES_SIX = 1,
         RES_X = 2,
         RES_Y = 3,
         SELECTED_RES = 4,
      };

      data_manager() = delete;
      static bool save_storage_value(unsigned int position, int value);
      static int load_storage_value(unsigned int position);

      static void save_sr_config(unsigned int window_width, unsigned int window_height, unsigned int selected_item);
      static void load_sr_config(unsigned int& window_width, unsigned int& window_height, int& selected_item);
};

#endif
