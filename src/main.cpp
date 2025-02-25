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

const unsigned int DEFAULT_WINDOW_WIDTH = 800;
const unsigned int DEFAULT_WINDOW_HEIGHT = 800;

unsigned int window_width = DEFAULT_WINDOW_WIDTH;
unsigned int window_height = DEFAULT_WINDOW_HEIGHT;

const Color CYBER_BLUE = (Color) {0, 34, 43, 1};
const Color CYBER_BASE = (Color) {2, 70, 88, 255};
const Color CYBER_LIGHT = (Color) {130, 205, 224, 255};

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

int sr_dd_active_item = -1;
int active_toggle;

Color col = RED;

void save_screen_resolution_config()
{
   data_manager::save_storage_value(static_cast<unsigned int>(data_manager::storage_position::RES_X), window_width);
   data_manager::save_storage_value(static_cast<unsigned int>(data_manager::storage_position::RES_Y), window_height);
   data_manager::save_storage_value(static_cast<unsigned int>(data_manager::storage_position::SELECTED_RES), sr_dd_active_item);
}

void load_screen_resolution_config() 
{
   window_width = data_manager::load_storage_value(static_cast<unsigned int>(data_manager::storage_position::RES_X));
   window_height = data_manager::load_storage_value(static_cast<unsigned int>(data_manager::storage_position::RES_Y));
   sr_dd_active_item = data_manager::load_storage_value(static_cast<unsigned int>(data_manager::storage_position::SELECTED_RES));

   if (window_width == -1)
   {
      window_width = DEFAULT_WINDOW_WIDTH;
      data_manager::save_storage_value(static_cast<unsigned int>(data_manager::storage_position::RES_X), window_width);
   }

   if (window_height == -1)
   {
      window_height = DEFAULT_WINDOW_HEIGHT;
      data_manager::save_storage_value(static_cast<unsigned int>(data_manager::storage_position::RES_Y), window_height);
   }

   if (sr_dd_active_item == -1)
   {
      sr_dd_active_item = 0;
      data_manager::save_storage_value(static_cast<unsigned int>(data_manager::storage_position::SELECTED_RES), sr_dd_active_item);
   }
}

int main(void)
{
   int wins = data_manager::load_storage_value(static_cast<unsigned int>(data_manager::storage_position::WINS_SIX));
   int losses = data_manager::load_storage_value(static_cast<unsigned int>(data_manager::storage_position::LOSSES_SIX));

   load_screen_resolution_config();

   if (wins == -1)
   {
      wins = 0;
      data_manager::save_storage_value(static_cast<unsigned int>(data_manager::storage_position::LOSSES_SIX), 0);
   }

   if (losses == -1)
   {
      losses = 0;
      data_manager::save_storage_value(static_cast<unsigned int>(data_manager::storage_position::LOSSES_SIX), 0);
   }

   board b(Vector2(0,0), window_width);

   ai robot;
   srand(time(0));
   SetConfigFlags(FLAG_MSAA_4X_HINT);
   InitWindow(window_width, window_height, "takaku v0.04");
   SetWindowState(FLAG_WINDOW_RESIZABLE);
   SetWindowState(FLAG_VSYNC_HINT);
   SetWindowMinSize(800, 800);
   GuiLoadStyle("styles/cyber/style_cyber.rgs");
   Vector2 window_centre = {static_cast<float>(window_width / 2), static_cast<float>(window_height / 2)};

   Font rockwell = LoadFontEx("fonts/rockwell.ttf", 24, NULL, 0);

   if (rockwell.texture.id == 0)
      std::cout << "APPLICATON ERROR: Failed to load font." << std::endl;
   else
      GuiSetFont(rockwell);

   GuiSetStyle(DEFAULT, TEXT_SIZE, 24);
   GuiSetStyle(DEFAULT, TEXT_SPACING, 2);

   bool sr_dd_edit = false;
   bool updated_win_loss = false;

   int mode_selector_active_item = 0;
   bool mode_selector_edit = false;

   while (!WindowShouldClose())    
   {
      ClearBackground(CYBER_BLUE);

      if (!start_game) 
      {
         // Text labels
         GuiLabel((Rectangle){ 4, static_cast<float>(window_height) - 40.0f, 300, 48}, "takaku v0.04 by gjoa");

         Vector2 size = MeasureTextEx(rockwell, "BOARD SIZE", 24, 2.0f);
         GuiLabel((Rectangle){window_centre.x - 300, window_centre.y - 200, 250, 48}, "WINDOW SIZE");
         GuiLabel((Rectangle){window_centre.x - 300, window_centre.y - 100, 250, 48}, "BOARD SIZE");
         GuiLabel((Rectangle){window_centre.x - 300, window_centre.y, 250, 48}, "OPPONENT");

         // Have we been instructed to change the screen resolution
         change_resolution = GuiButton((Rectangle) { window_centre.x + 150, window_centre.y - 200, 100, 48}, "Apply");

         // Play button
         start_game = GuiButton((Rectangle) { window_centre.x + 150, window_centre.y, 100, 48}, "Play");

         // Resolution selector
         if ( GuiDropdownBox((Rectangle){ window_centre.x - 100, window_centre.y - 200, 200, 48 }, "800x800;900x900;1000x1000;1100x1100;1200x1200", &sr_dd_active_item, sr_dd_edit) ) 
         {
            sr_dd_edit = !sr_dd_edit;
         }

         if ( !sr_dd_edit ) 
         {
            // Opponent selection
            if ( GuiDropdownBox((Rectangle){ window_centre.x - 100, window_centre.y, 200, 48 }, "Computer;Human", &mode_selector_active_item, mode_selector_edit) )
               mode_selector_edit = !mode_selector_edit;

            // Board size selector
            GuiSpinner((Rectangle){ window_centre.x - 100, window_centre.y - 100, 200, 48 }, "", val_ptr, 6, 12, false);

         }

         if (*val_ptr == 6 && mode_selector_active_item == 0 && !mode_selector_edit)
         {
            // Win/loss
            std::string win_loss = "WIN/LOSS: " + std::to_string(wins) + " - " + std::to_string(losses);
            GuiLabel((Rectangle){window_centre.x - 100, window_centre.y + 100, 200, 48}, win_loss.c_str());
         }

         if ( change_resolution) 
         {
            window_width = resolutions[sr_dd_active_item].first;
            window_height = resolutions[sr_dd_active_item].second;
            SetWindowSize(window_width, window_height);
            save_screen_resolution_config();
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
         b.set_color(CYBER_BLUE);
         b.set_player_colors(player_colors);
         b.set_default_circle_color(CYBER_BASE);
         b.set_frozen_circle_color(CYBER_LIGHT);
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
            // If the game isn't over, the opponent is a computer, we're playing on a 6-vertex board, and at least two moves have been made
            if (!b.is_game_over() && mode_selector_active_item == 0 && *val_ptr == 6 && b.get_line_counter() > 1) 
            {
               data_manager::save_storage_value(static_cast<unsigned int>(data_manager::storage_position::LOSSES_SIX), losses + 1);
               losses++;
            }
            b.reset_board();
            updated_win_loss = false;
         }

         if ( mode_selector_active_item == 0 && !b.is_game_over() && b.get_player_turn_idx() == 0 )
         {
            robot.make_move(b);
         }

         // Horrible if statement
         if  ( mode_selector_active_item == 0 && b.get_losing_player() != -1 && !updated_win_loss && *val_ptr == 6)
         {
            if ( b.get_losing_player() == 0 )
            {
               data_manager::save_storage_value(static_cast<unsigned int>(data_manager::storage_position::WINS_SIX), wins + 1);
               wins++;
            }
            else
            {
               data_manager::save_storage_value(static_cast<unsigned int>(data_manager::storage_position::LOSSES_SIX), losses + 1);
               losses++;
            }
            updated_win_loss = true;
         }
      }

      if (IsKeyPressed(KEY_M) && start_game)
      {
         if ( !b.is_game_over() && b.get_line_counter() > 1 && mode_selector_active_item == 0 && *val_ptr == 6)
         {
            data_manager::save_storage_value(static_cast<unsigned int>(data_manager::storage_position::LOSSES_SIX), losses + 1);
            losses++;
         }
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

   UnloadFont(rockwell);
   CloseWindow();

   return 0;
}
