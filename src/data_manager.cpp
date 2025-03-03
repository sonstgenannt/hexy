#include "../headers/data_manager.h"
#include <iostream>

// Adapted from https://www.raylib.com/examples/core/loader.html?name=core_storage_values
bool data_manager::save_storage_value(unsigned int position, int value)
{
   bool success = false;
   int data_size = 0;
   unsigned int new_data_size = 0;
   unsigned char* file_data = LoadFileData(STORAGE_DATA_FILE, &data_size);
   unsigned char* new_file_data = NULL;

   if (file_data != NULL)
   {
      if ( data_size <= ( position * sizeof(int) ) )
      {
         // Increase data size up to position and store value
         new_data_size = (position + 1) * sizeof(int);
         new_file_data = (unsigned char*) RL_REALLOC(file_data, new_data_size);

         if (new_file_data != NULL)
         {
            // RL_REALLOC succeded
            int* data_ptr = (int*)new_file_data;
            data_ptr[position] = value;
         }
         else
         {
            // RL_REALLOC failed
            TraceLog(
                  LOG_WARNING, 
                  "FILEIO: [%s] Failed to realloc data (%u), position in bytes (%u) bigger than actual file size", 
                  STORAGE_DATA_FILE, data_size, 
                  position*sizeof(int));

            // We store the old size of the file
            new_file_data = file_data;
            new_data_size = data_size;
         }
      }
      else
      {
         // Store the old size of the file
         new_file_data = file_data;
         new_data_size = data_size;

         // Replace value on selected position
         int* data_ptr = (int*)new_file_data;
         data_ptr[position] = value;
      }

      success = SaveFileData(STORAGE_DATA_FILE, new_file_data, new_data_size);
      RL_FREE(new_file_data);

      TraceLog(LOG_INFO, "FILEIO: [%s] Saved storage value: %i", STORAGE_DATA_FILE, value);
   }
   else
   {
      TraceLog(LOG_INFO, "FILEIO: [%s] File created successfully", STORAGE_DATA_FILE);

      data_size = (position + 1) * sizeof(int);
      file_data = (unsigned char*) RL_MALLOC(data_size);
      int* data_ptr = (int*)file_data;
      data_ptr[position] = value;

      success = SaveFileData(STORAGE_DATA_FILE, file_data, data_size);
      UnloadFileData(file_data);

      TraceLog(LOG_INFO, "FILEIO: [%s] Saved storage value: %i", STORAGE_DATA_FILE, value);
   }

   return success;
}

int data_manager::load_storage_value(unsigned int position)
{
   int value = -1;
   int data_size = 0;

   unsigned char* file_data = LoadFileData(STORAGE_DATA_FILE, &data_size);

   if (file_data != NULL)
   {
      if (data_size <= ((int)(position*4))) 
      {
         TraceLog(LOG_WARNING, "FILEIO: [%s] Failed to find storage position: %i", STORAGE_DATA_FILE, position);
      }
      else
      {
         int* data_ptr = (int*)file_data;
         value = data_ptr[position];
      }

      UnloadFileData(file_data);

      TraceLog(LOG_INFO, "FILEIO: [%s] Loaded storage value: %i", STORAGE_DATA_FILE, value);
   }
   return value;
}

void data_manager::save_sr_config(unsigned int window_width, unsigned int window_height, unsigned int selected_item) 
{
   data_manager::save_storage_value(data_manager::storage_position::RES_X, window_width);
   data_manager::save_storage_value(data_manager::storage_position::RES_Y, window_height);
   data_manager::save_storage_value(data_manager::storage_position::SELECTED_RES, selected_item);
}

void data_manager::load_sr_config(unsigned int& window_width, unsigned int& window_height, int& selected_item)
{
   window_width = data_manager::load_storage_value(data_manager::storage_position::RES_X);
   window_height = data_manager::load_storage_value(data_manager::storage_position::RES_Y);
   selected_item = data_manager::load_storage_value(data_manager::storage_position::SELECTED_RES);

   if (window_width == ~0U)
   {
      window_width = 800;
      data_manager::save_storage_value(data_manager::storage_position::RES_X, window_width);
   }

   if (window_height == ~0U)
   {
      window_height = 800;
      data_manager::save_storage_value(data_manager::storage_position::RES_Y, window_height);
   }

   if (selected_item == -1)
   {
      selected_item = 0;
      data_manager::save_storage_value(data_manager::storage_position::SELECTED_RES, selected_item);
   }
}
