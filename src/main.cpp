#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "../include/raygui.h"

#include "../headers/board.h"
#include "../headers/ai.h"
#include "../headers/data_manager.h"
#include "../headers/rect_button.h"
#include <numbers>
#include <cmath>
#include <iostream>
#include <vector>
#include <string>

unsigned int window_width = ~0U;
unsigned int window_height = ~0U;

const Color CYBER_BLUE = (Color) {0, 34, 43, 1};
const Color CYBER_BASE = (Color) {2, 70, 88, 255};
const Color CYBER_LIGHT = (Color) {130, 205, 224, 255};

std::vector<Color> player_colors = { RED, BLUE };
const std::vector<std::pair<int, int>> resolutions = 
{
   {800, 800}, {900, 900}, {1000, 1000}, {1100, 1100}, {1200, 1200}
};

int temp_val = 6;
int* val_ptr = &temp_val;

bool change_resolution = false;
bool player_idx = -1; // Controls whether the player makes the first move or not in vs AI mode

const char* VERSION_STR = "takaku v0.05a";

int main(void)
{
   bool show_warning_box = false;
   int warning_output = false;
   bool updated_win_loss = false;

   int mode_selector_active_item = 0;
   int sr_dd_active_item = -1;
   bool sr_dd_edit = false;

   bool mode_selector_edit = false;

   //////////////////////////////////////////////////////////////////////////////
   //// DATA LOADING (WIN/LOSS; RESOLUTION OPTIONS)
   //////////////////////////////////////////////////////////////////////////////

   int wins = data_manager::load_storage_value(data_manager::storage_position::WINS_SIX);

   if (wins == -1)
   {
      wins = 0;
      data_manager::save_storage_value(data_manager::storage_position::WINS_SIX, 0);
   }

   int losses = data_manager::load_storage_value(data_manager::storage_position::LOSSES_SIX);

   if (losses == -1)
   {
      losses = 0;
      data_manager::save_storage_value(data_manager::storage_position::LOSSES_SIX, 0);
   }

   data_manager::load_sr_config(window_width, window_height, sr_dd_active_item);

   //////////////////////////////////////////////////////////////////////////////
   //// GAME OBJECT INITIALISATION
   //////////////////////////////////////////////////////////////////////////////

   board b(Vector2(0,0), window_width);
   ai robot;

   //////////////////////////////////////////////////////////////////////////////
   //// WINDOW INITIALISATION
   //////////////////////////////////////////////////////////////////////////////
   
   SetConfigFlags(FLAG_MSAA_4X_HINT); 
   InitWindow(window_width, window_height, VERSION_STR); 
   SetWindowState(FLAG_WINDOW_RESIZABLE); 
   SetWindowMinSize(800, 800); 
   SetWindowState(FLAG_VSYNC_HINT); 
   Vector2 window_centre = {static_cast<float>(window_width / 2), static_cast<float>(window_height / 2)};

   //////////////////////////////////////////////////////////////////////////////
   //// RECT BUTTON INITIALISATION
   //////////////////////////////////////////////////////////////////////////////

   Image house = LoadImage("icons/home.png");
   if ( IsImageValid (house) ) 
      std::cout << "Loaded image successfully." << std::endl;
   Texture2D house_texture = LoadTextureFromImage(house);
   UnloadImage(house);

   rect_button rb ( Rectangle{ 0, 0, 128, 128}, Vector2 {0, 0}, CYBER_BASE, CYBER_LIGHT, house_texture);
   rb.set_hover_background_color(GREEN);
   rb.set_scale(0.5f);

   //////////////////////////////////////////////////////////////////////////////
   //// FONT AND RAYGUI STYLE INITIALISATION
   //////////////////////////////////////////////////////////////////////////////

   GuiLoadStyle("styles/cyber/style_cyber.rgs"); // Load style that is used for raygui 
   Font rockwell = LoadFontEx("fonts/rockwell.ttf", 24, NULL, 0); 

   if (rockwell.texture.id == 0)
      std::cout << "APPLICATON ERROR: Failed to load font." << std::endl;
   else
      GuiSetFont(rockwell);

   GuiSetStyle(DEFAULT, TEXT_SIZE, 24);
   GuiSetStyle(DEFAULT, TEXT_SPACING, 2);

   //////////////////////////////////////////////////////////////////////////////
   //// MAIN LOOP BEGINS
   //////////////////////////////////////////////////////////////////////////////

   while (!WindowShouldClose())    
   {
      ClearBackground(CYBER_BLUE);
      rb.update();
      b.update();

      //////////////////////////////////////////////////////////////////////////////
      //// HANDLING MAIN MENU UI
      //////////////////////////////////////////////////////////////////////////////

      if (!b.get_game_started()) 
      {
         // Text labels
         GuiLabel((Rectangle){ 4, static_cast<float>(window_height) - 40.0f, 300, 48}, VERSION_STR);
         GuiLabel((Rectangle){static_cast<float>(window_centre.x) - 300.0f, window_centre.y - 200, 250, 48}, "WINDOW SIZE");
         GuiLabel((Rectangle){static_cast<float>(window_centre.x) - 300.0f, window_centre.y - 100, 250, 48}, "BOARD SIZE");
         GuiLabel((Rectangle){static_cast<float>(window_centre.x) - 300.0f, window_centre.y, 250, 48}, "OPPONENT");

         // Have we been instructed to change the screen resolution
         change_resolution = GuiButton((Rectangle) { window_centre.x + 150, window_centre.y - 200, 100, 48}, "Apply");

         // Play button
         bool game_status = GuiButton((Rectangle) { window_centre.x + 150, window_centre.y, 100, 48}, "Play");
         b.set_game_started(game_status);

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
            GuiLabel((Rectangle){window_centre.x - 100, window_centre.y + 100, 400, 48}, win_loss.c_str());
         }

         if (change_resolution) 
         {
            window_width = resolutions[sr_dd_active_item].first;
            window_height = resolutions[sr_dd_active_item].second;
            SetWindowSize(window_width, window_height);
            data_manager::save_sr_config(window_width, window_height, sr_dd_active_item);
            b.set_size(window_width);
            window_centre = {static_cast<float>(window_width / 2), static_cast<float>(window_height / 2)};

            int monitor_width = GetMonitorWidth(GetCurrentMonitor());
            int monitor_height = GetMonitorHeight(GetCurrentMonitor());
            int monitor_centre_x = monitor_width / 2;
            int monitor_centre_y = monitor_height / 2;

            SetWindowPosition(monitor_centre_x - (window_width / 2), monitor_centre_y - (window_height / 2));
         }
      }

      //////////////////////////////////////////////////////////////////////////////
      //// HANDLING GAME STARTED BEHAVIOUR
      //////////////////////////////////////////////////////////////////////////////

      else
      {
         if (!b.get_initialised())
         {
            // If opponent is computer
            if ( mode_selector_active_item == 0 )
            {
               b.set_ai_enabled(true);
               player_idx = rand() % 2; // Randomly choose whether the player moves first or second
            }
            else
            {
               player_idx = -1;
               b.set_ai_enabled(false);
            }

            b.set_color(CYBER_BLUE);
            b.set_player_colors(player_colors);
            b.set_default_circle_color(CYBER_BASE); b.set_frozen_circle_color(CYBER_LIGHT); b.set_max_circles(*val_ptr);
            b.init_circles(300.0f, 30.0f);
         }
         else 
         {
            if ( b.get_ai_enabled() && !b.is_game_over() && b.get_turn_idx() == !player_idx )
               robot.make_move(b);


            // If SPACE is pressed and the game is not yet over, we mark this game as a loss
            if ( IsKeyPressed(KEY_SPACE) && b.is_game_over() )
            {
               b.reset_board();
               updated_win_loss = false;
               player_idx = rand() % 2;
            }

            // Horrible if statement -- essentially handles whether wins/losses should be written to file and updated
            if  ( mode_selector_active_item == 0 && b.get_losing_player() != -1 && !updated_win_loss && *val_ptr == 6)
            {
               if ( b.get_losing_player() == !player_idx )
               {
                  wins++;
                  data_manager::save_storage_value(static_cast<unsigned int>(data_manager::storage_position::WINS_SIX), wins);
               }
               else
               {
                  losses++;
                  data_manager::save_storage_value(static_cast<unsigned int>(data_manager::storage_position::LOSSES_SIX), losses);
               }
               updated_win_loss = true;
            }
         }
      }

      // This if statement handles whether the warning box pop-up should be shown to the player or not 
      // when pressing M or the home button
      
      if ( (IsKeyPressed(KEY_M) || rb.get_activated() ) && b.get_game_started() )
      {
         // If the opponent is a human
         if ( mode_selector_active_item == 1 )
         {
            show_warning_box = false;
         }
         // If the opponent is a robot, the player moves first, and they haven't moved yet
         else if ( player_idx == 0 && b.get_line_counter() < 1 )
         {
            show_warning_box = false;
         }
         // If the opponent is a robot, the player moves second, and they haven't moved yet
         else if ( player_idx == 1 && b.get_line_counter() < 2 )
         {
            show_warning_box = false;
         }
         // If the game is over
         else if ( b.is_game_over() )
         {
            show_warning_box = false;
         }
         else
            show_warning_box = true;

         if ( !show_warning_box )
         {
            updated_win_loss = false;
            show_warning_box = false;
            b.kill_board();
         }
      }

      if ( show_warning_box )
      warning_output = GuiMessageBox( (Rectangle) {(static_cast<float>(window_width) / 2.0f) - 300.0f, (static_cast<float>(window_height) / 2.0f) - 150, 600, 300}, 
            "", "Returning to the main menu now will forfeit \nthe current game and count as a loss.",
            "Return to main menu;Continue playing");
      else
         warning_output = -1;

      if ( show_warning_box && warning_output == 1 )
      {
         if ( !b.is_game_over() && mode_selector_active_item == 0 && *val_ptr == 6)
         {
            losses++;
            data_manager::save_storage_value(static_cast<unsigned int>(data_manager::storage_position::LOSSES_SIX), losses);
         }
         updated_win_loss = false;
         show_warning_box = false;
         b.kill_board();
      }
      else if ( warning_output == 2 )
         show_warning_box = false;

      BeginDrawing();

      if (b.get_initialised() && !show_warning_box)
      {
         b.draw();
         rb.draw();

         if ( b.get_ai_enabled() )
         {
            // Who is who bottom-left corner UI
            DrawRectangle(25, window_height - 75, 50, 50, RED);
            DrawRectangle(25, window_height - 135, 50, 50, BLUE);

            if (player_idx == 0)
            {
               DrawTextEx(rockwell, "you", (Vector2){30, static_cast<float>(window_height) - 60.0f}, 24, 2.0f, RAYWHITE);
               DrawTextEx(rockwell, "ai", (Vector2){30, static_cast<float>(window_height) - 115.0f}, 24, 2.0f, RAYWHITE);
            }
            else if (player_idx == 1)
            {
               DrawTextEx(rockwell, "ai", (Vector2){30, static_cast<float>(window_height) - 60.0f}, 24, 2.0f, RAYWHITE);
               DrawTextEx(rockwell, "you", (Vector2){30, static_cast<float>(window_height) - 115.0f}, 24, 2.0f, RAYWHITE);
            }
         }
      }
      EndDrawing();
   }

   //////////////////////////////////////////////////////////////////////////////
   //// Main loop has ended
   //////////////////////////////////////////////////////////////////////////////
   
   UnloadFont(rockwell);
   CloseWindow();
   return 0;
}
