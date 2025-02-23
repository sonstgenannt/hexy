#include "raylib.h" 
#define RAYGUI_IMPLEMENTATION
#include "../include/raygui.h"

#include "../headers/board.h"
#include "../headers/ai.h"
#include "../headers/data_manager.h"
#include <numbers>
#include <cmath>
#include <iostream>
#include <vector>
#include <array>
#include <string>


unsigned int window_width = 800; 
unsigned int window_height = 800;

std::vector<Color> player_colors = { RED, BLUE };
std::vector<std::pair<int, int>> resolutions = 
{
   {800, 800}, {900, 900}, {1000, 1000}, {1100, 1100}, {1200, 1200}
};

int temp_val = 6;
int* val_ptr = &temp_val;

bool start_game = false;
bool board_initalised = false;
bool change_resolution = false;

int active_toggle;

Color col = RED;

board b(Vector2(0,0), 800);

int main(void)
{
   int wins = data_manager::load_storage_value(static_cast<unsigned int>(data_manager::storage_data::STORAGE_POSITION_WINS));
   int losses = data_manager::load_storage_value(static_cast<unsigned int>(data_manager::storage_data::STORAGE_POSITION_LOSSES));

   if (wins == 0)
      data_manager::save_storage_value(static_cast<unsigned int>(data_manager::storage_data::STORAGE_POSITION_WINS), 0);

   if (losses == 0)
      data_manager::save_storage_value(static_cast<unsigned int>(data_manager::storage_data::STORAGE_POSITION_LOSSES), 0);

   ai robot;
   srand(time(0));
   InitWindow(window_width, window_height, "rokkaku v0.03");
   SetWindowState(FLAG_WINDOW_RESIZABLE);
   SetWindowMinSize(800, 800);
   GuiLoadStyle("styles/cherry/style_cherry.rgs");
   Vector2 window_centre = {static_cast<float>(window_width / 2), static_cast<float>(window_height / 2)};
   SetTargetFPS(60);               

   Font rockwell = LoadFontEx("fonts/rockwell.ttf", 24, NULL, 0);

   if (rockwell.texture.id == 0)
      std::cout << "APPLICATON ERROR: Failed to load font." << std::endl;
   else
      GuiSetFont(rockwell);

   GuiSetStyle(DEFAULT, TEXT_SIZE, 24);

   int sr_dd_active_item = 0;
   bool sr_dd_edit = false;
   bool updated_win_loss = false;

   int mode_selector_active_item = 0;
   bool mode_selector_edit = false;

   while (!WindowShouldClose())    
   {
      ClearBackground(RAYWHITE);

      if (!start_game) 
      {
         // GuiToggleGroup( (Rectangle) {window_centre.x + 150, window_centre.y, 100, 100}, "Player 1;Player 2", &active_toggle );
         // GuiColorPicker( (Rectangle) {window_centre.x - 100, window_centre.y, 200, 200}, "", &col);
         GuiLabel((Rectangle){ 4, static_cast<float>(window_height) - 40.0f, 300, 48}, "rokkaku v0.03 by gjoa");

         if (!sr_dd_edit) 
         {
            // Play button
            start_game = GuiButton((Rectangle) { window_centre.x - 100, window_centre.y + 200, 200, 48}, "Play");

            // Number of vertices selector
            GuiSpinner((Rectangle){ window_centre.x - 100, window_centre.y - 100, 200, 48 }, "", val_ptr, 6, 24, false);
            GuiLabel((Rectangle){window_centre.x - 250, window_centre.y - 100, 200, 48}, "Board Size");

            // Win/loss
            std::string win_loss = std::to_string(wins) + "-" + std::to_string(losses);
            GuiLabel((Rectangle){window_centre.x, window_centre.y + 100, 200, 48}, win_loss.c_str());
            // Mode selection
            GuiLabel((Rectangle){window_centre.x - 300, window_centre.y, 200, 48}, "Choose Opponent");
            if ( GuiDropdownBox((Rectangle){ window_centre.x - 100, window_centre.y, 200, 48 }, "Computer;Local co-op", &mode_selector_active_item, mode_selector_edit) )
               mode_selector_edit = !mode_selector_edit;
         }

         GuiLabel((Rectangle){window_centre.x - 310, window_centre.y - 200, 200, 48}, "Screen Resolution");


         // Resolution selector
         if ( GuiDropdownBox((Rectangle){ window_centre.x - 100, window_centre.y - 200, 200, 48 }, "800x800;900x900;1000x1000;1100x1100;1200x1200", &sr_dd_active_item, sr_dd_edit) ) 
         {
            sr_dd_edit = !sr_dd_edit;
         }

         // Apply resolution change button
         change_resolution = GuiButton((Rectangle) { window_centre.x + 150, window_centre.y - 200, 100, 48}, "Apply");

         if ( change_resolution) 
         {
            window_width = resolutions[sr_dd_active_item].first;
            window_height = resolutions[sr_dd_active_item].second;
            SetWindowSize(window_width, window_height);
            b.set_size(window_width);
            window_centre = {static_cast<float>(window_width / 2), static_cast<float>(window_height / 2)};

            int monitor_width = GetMonitorWidth(GetCurrentMonitor());
            int monitor_height = GetMonitorHeight(GetCurrentMonitor());
            int monitor_centre_x = monitor_width / 2;
            int monitor_centre_y = monitor_height / 2;

            SetWindowPosition(monitor_centre_x - (window_width / 2), monitor_centre_y - (window_height / 2));
         }
      }
      if (start_game && !board_initalised) 
      {
         b.set_color(WHITE);
         b.set_player_colors(player_colors);
         b.set_default_circle_color(BLACK);
         b.set_frozen_circle_color(DARKPURPLE);
         b.set_max_circles(*val_ptr);
         b.init_circles(300.0f, 30.0f);
         board_initalised = true;
      }

      if (board_initalised) 
      {
         b.poll_input_events();

         // If SPACE is pressed and the game is not yet over, we mark this game as a loss
         if (IsKeyPressed(KEY_SPACE))
         {
            if (!b.is_game_over() && mode_selector_active_item == 0) 
            {
               data_manager::save_storage_value(static_cast<unsigned int>(data_manager::storage_data::STORAGE_POSITION_LOSSES), losses + 1);
               losses++;
            }
            b.reset_board();
         }

         if ( mode_selector_active_item == 0 && !b.is_game_over() && b.get_player_turn_idx() == 0 )
         {
            robot.make_move(b);
         }

         if ( mode_selector_active_item == 0 && b.get_losing_player() != -1 && !updated_win_loss)
         {
            if ( b.get_losing_player() == 0 )
            {
               data_manager::save_storage_value(static_cast<unsigned int>(data_manager::storage_data::STORAGE_POSITION_WINS), wins + 1);
               wins++;
            }
            else
            {
               data_manager::save_storage_value(static_cast<unsigned int>(data_manager::storage_data::STORAGE_POSITION_LOSSES), losses + 1);
               losses++;
            }
            updated_win_loss = true;
         }
      }

      if (IsKeyPressed(KEY_M) && start_game)
      {
         start_game = false;
         board_initalised = false;
         updated_win_loss = false;
         b.kill_board();
      }

      BeginDrawing();

      if (board_initalised)
         b.draw();

      EndDrawing();
   }

   CloseWindow();

   return 0;
}
