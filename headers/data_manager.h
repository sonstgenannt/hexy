#ifndef DATA_MANAGER
#define DATA_MANAGER
#define STORAGE_DATA_FILE "storage.data"
#include <stdlib.h>
#include "raylib.h"

class data_manager 
{ 
   public:
      enum class storage_data : unsigned int {
         STORAGE_POSITION_WINS = 0,
         STORAGE_POSITION_LOSSES = 1
      };

      data_manager() = delete;
      static bool save_storage_value(unsigned int position, int value);
      static int load_storage_value(unsigned int position);
};

#endif
