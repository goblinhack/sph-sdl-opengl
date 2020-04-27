//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_wid_minicon.h"
#include "my_wid_popup.h"
#include "my_ascii.h"
#include "my_game_notice.h"

static WidPopup *game_config_keyboard_window;

//
// Check for saving keys to config can fit
//
static_assert(sizeof(SDL_Scancode) <= sizeof(game->config.key_move_left));

static void game_config_keyboard_destroy (void)
{_
    if (game_config_keyboard_window) {
        delete game_config_keyboard_window;
        game_config_keyboard_window = nullptr;
    }
}

uint8_t game_config_keyboard_back (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    game_config_keyboard_destroy();
    return (true);
}

static void game_config_key_move_left_set (SDL_Scancode code)
{_
    game->config.key_move_left = code;
    game->config_keyboard_select();
}

static void game_config_key_move_right_set (SDL_Scancode code)
{_
    game->config.key_move_right = code;
    game->config_keyboard_select();
}

static void game_config_key_move_up_set (SDL_Scancode code)
{_
    game->config.key_move_up = code;
    game->config_keyboard_select();
}

static void game_config_key_move_down_set (SDL_Scancode code)
{_
    game->config.key_move_down = code;
    game->config_keyboard_select();
}

static void game_config_key_map_left_set (SDL_Scancode code)
{_
    game->config.key_map_left = code;
    game->config_keyboard_select();
}

static void game_config_key_map_right_set (SDL_Scancode code)
{_
    game->config.key_map_right = code;
    game->config_keyboard_select();
}

static void game_config_key_map_up_set (SDL_Scancode code)
{_
    game->config.key_map_up = code;
    game->config_keyboard_select();
}

static void game_config_key_map_down_set (SDL_Scancode code)
{_
    game->config.key_map_down = code;
    game->config_keyboard_select();
}

static void game_config_key_todo1_set (SDL_Scancode code)
{_
    game->config.key_todo1 = code;
    game->config_keyboard_select();
}

static void game_config_key_todo2_set (SDL_Scancode code)
{_
    game->config.key_todo2 = code;
    game->config_keyboard_select();
}

static void game_config_key_help_set (SDL_Scancode code)
{_
    game->config.key_help = code;
    game->config_keyboard_select();
}

static void game_config_key_quit_set (SDL_Scancode code)
{_
    game->config.key_quit = code;
    game->config_keyboard_select();
}

static void grab_key (void) 
{_
    game_notice("Press any key");
    sdl_grab_next_key = true;
}

uint8_t game_config_keyboard_profile_arrow_keys (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    game->config.key_move_up    = SDL_SCANCODE_UP;
    game->config.key_move_left  = SDL_SCANCODE_LEFT;
    game->config.key_move_down  = SDL_SCANCODE_DOWN;
    game->config.key_move_right = SDL_SCANCODE_RIGHT;
    game->config.key_map_up     = SDL_SCANCODE_W;
    game->config.key_map_left   = SDL_SCANCODE_A;
    game->config.key_map_down   = SDL_SCANCODE_S;
    game->config.key_map_right  = SDL_SCANCODE_D;
    game->config_keyboard_select();

    return (true);
}

uint8_t game_config_keyboard_profile_wasd (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    game->config.key_move_up    = SDL_SCANCODE_W;
    game->config.key_move_left  = SDL_SCANCODE_A;
    game->config.key_move_down  = SDL_SCANCODE_S;
    game->config.key_move_right = SDL_SCANCODE_D;
    game->config.key_map_up     = SDL_SCANCODE_UP;
    game->config.key_map_left   = SDL_SCANCODE_LEFT;
    game->config.key_map_down   = SDL_SCANCODE_DOWN;
    game->config.key_map_right  = SDL_SCANCODE_RIGHT;
    game->config_keyboard_select();

    return (true);
}

uint8_t game_config_key_move_left (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    grab_key();
    on_sdl_key_grab = game_config_key_move_left_set;
    return (true);
}

uint8_t game_config_key_move_right (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    grab_key();
    on_sdl_key_grab = game_config_key_move_right_set;
    return (true);
}

uint8_t game_config_key_move_up (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    grab_key();
    on_sdl_key_grab = game_config_key_move_up_set;
    return (true);
}

uint8_t game_config_key_move_down (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    grab_key();
    on_sdl_key_grab = game_config_key_move_down_set;
    return (true);
}

uint8_t game_config_key_map_left (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    grab_key();
    on_sdl_key_grab = game_config_key_map_left_set;
    return (true);
}

uint8_t game_config_key_map_right (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    grab_key();
    on_sdl_key_grab = game_config_key_map_right_set;
    return (true);
}

uint8_t game_config_key_map_up (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    grab_key();
    on_sdl_key_grab = game_config_key_map_up_set;
    return (true);
}

uint8_t game_config_key_map_down (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    grab_key();
    on_sdl_key_grab = game_config_key_map_down_set;
    return (true);
}

uint8_t game_config_key_todo1 (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    grab_key();
    on_sdl_key_grab = game_config_key_todo1_set;
    return (true);
}

uint8_t game_config_key_todo2 (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    grab_key();
    on_sdl_key_grab = game_config_key_todo2_set;
    return (true);
}

uint8_t game_config_key_help (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    grab_key();
    on_sdl_key_grab = game_config_key_help_set;
    return (true);
}

uint8_t game_config_key_quit (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    grab_key();
    on_sdl_key_grab = game_config_key_quit_set;
    return (true);
}

uint8_t game_config_keyboard_key_up (Widp w, const struct SDL_KEYSYM *key)
{_
    switch (key->mod) {
        case KMOD_LCTRL:
        case KMOD_RCTRL:
        default:
        switch (key->sym) {
            default: {_
                auto c = wid_event_to_char(key);
                switch (c) {
                    case CONSOLE_KEY1:
                    case CONSOLE_KEY2:
                    case CONSOLE_KEY3:
                        //
                        // Magic keys we use to toggle the console.
                        //
                        return (false);
                    case SDLK_ESCAPE:
                        game_config_keyboard_back(nullptr, 0, 0, 0);
                        return (true);
                }
            }
        }
    }

    return (false);
}

uint8_t game_config_keyboard_key_down (Widp w, const struct SDL_KEYSYM *key)
{_
    switch (key->mod) {
        case KMOD_LCTRL:
        case KMOD_RCTRL:
        default:
        switch (key->sym) {
            default: {_
                auto c = wid_event_to_char(key);
                switch (c) {
                    case CONSOLE_KEY1:
                    case CONSOLE_KEY2:
                    case CONSOLE_KEY3:
                        //
                        // Magic keys we use to toggle the console.
                        //
                        return (false);
                }
            }
        }
    }

    return (true);
}

void Game::config_keyboard_select (void)
{_
    game_notice_destroy();

    if (game_config_keyboard_window) {
        game_config_keyboard_destroy();
    }

    auto m = ASCII_WIDTH / 2;
    point tl = {m - WID_POPUP_WIDTH_WIDEST / 2, MINICON_VIS_HEIGHT + 2};
    point br = {m + WID_POPUP_WIDTH_WIDEST / 2, ACTIONBAR_TL_Y - 2};
    auto width = br.x - tl.x;

    game_config_keyboard_window =
                    new WidPopup(tl, br, nullptr, "ui_popup_widest");
    {_
        Widp w = game_config_keyboard_window->wid_popup_container;
        wid_set_on_key_up(w, game_config_keyboard_key_up);
        wid_set_on_key_down(w, game_config_keyboard_key_down);
    }

    int y_at = 0;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "The keys of mighty power");

        point tl = {0, y_at};
        point br = {width - 2, y_at + 2};
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "The keys of mighty power");
    }

    y_at = 3;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Back");

        point tl = {1, y_at};
        point br = {8, y_at + 2};
        wid_set_style(w, WID_STYLE_DARK);
        wid_set_on_mouse_up(w, game_config_keyboard_back);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "Back");
    }

    ///////////////////////////////////////////////////////////////////////
    y_at++;
    ///////////////////////////////////////////////////////////////////////

    y_at += 3;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "");

        point tl = {0, y_at};
        point br = {46, y_at + 2};
        wid_set_style(w, WID_STYLE_DARK);
        wid_set_on_mouse_up(w, game_config_keyboard_profile_wasd);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "Use W,A,S,D for moving, arrow keys for map");
    }
    y_at += 3;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "");

        point tl = {0, y_at};
        point br = {46, y_at + 2};
        wid_set_style(w, WID_STYLE_DARK);
        wid_set_on_mouse_up(w, game_config_keyboard_profile_arrow_keys);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "Use arrow keys for moving, W,A,S,D for map");
    }

    ///////////////////////////////////////////////////////////////////////
    y_at++;
    ///////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////
    // Move up
    ///////////////////////////////////////////////////////////////////////
    y_at += 3;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Move up");

        point tl = {0, y_at};
        point br = {width / 2, y_at + 2};
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Move up");
    }
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "value");

        point tl = {width / 2 + 8, y_at};
        point br = {width / 2 + 22, y_at + 2};
        wid_set_style(w, WID_STYLE_DARK);
        wid_set_pos(w, tl, br);
        wid_set_text(w,
          SDL_GetScancodeName((SDL_Scancode)game->config.key_move_up));
        wid_set_on_mouse_up(w, game_config_key_move_up);
    }
    ///////////////////////////////////////////////////////////////////////
    // Move left
    ///////////////////////////////////////////////////////////////////////
    y_at += 3;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Move left");

        point tl = {0, y_at};
        point br = {width / 2, y_at + 2};
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Move left");
    }
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "value");

        point tl = {width / 2 + 8, y_at};
        point br = {width / 2 + 22, y_at + 2};
        wid_set_style(w, WID_STYLE_DARK);
        wid_set_pos(w, tl, br);
        wid_set_text(w,
          SDL_GetScancodeName((SDL_Scancode)game->config.key_move_left));
        wid_set_on_mouse_up(w, game_config_key_move_left);
    }
    ///////////////////////////////////////////////////////////////////////
    // Move down
    ///////////////////////////////////////////////////////////////////////
    y_at += 3;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Move down");

        point tl = {0, y_at};
        point br = {width / 2, y_at + 2};
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Move down");
    }
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "value");

        point tl = {width / 2 + 8, y_at};
        point br = {width / 2 + 22, y_at + 2};
        wid_set_style(w, WID_STYLE_DARK);
        wid_set_pos(w, tl, br);
        wid_set_text(w,
          SDL_GetScancodeName((SDL_Scancode)game->config.key_move_down));
        wid_set_on_mouse_up(w, game_config_key_move_down);
    }
    ///////////////////////////////////////////////////////////////////////
    // Move right
    ///////////////////////////////////////////////////////////////////////
    y_at += 3;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Move right");

        point tl = {0, y_at};
        point br = {width / 2, y_at + 2};
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Move right");
    }
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "value");

        point tl = {width / 2 + 8, y_at};
        point br = {width / 2 + 22, y_at + 2};
        wid_set_style(w, WID_STYLE_DARK);
        wid_set_pos(w, tl, br);
        wid_set_text(w,
          SDL_GetScancodeName((SDL_Scancode)game->config.key_move_right));
        wid_set_on_mouse_up(w, game_config_key_move_right);
    }

    ///////////////////////////////////////////////////////////////////////
    y_at++;
    ///////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////
    // Map up
    ///////////////////////////////////////////////////////////////////////
    y_at += 3;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Map up");

        point tl = {0, y_at};
        point br = {width / 2, y_at + 2};
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Map up");
    }
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "value");

        point tl = {width / 2 + 8, y_at};
        point br = {width / 2 + 22, y_at + 2};
        wid_set_style(w, WID_STYLE_DARK);
        wid_set_pos(w, tl, br);
        wid_set_text(w,
          SDL_GetScancodeName((SDL_Scancode)game->config.key_map_up));
        wid_set_on_mouse_up(w, game_config_key_map_up);
    }
    ///////////////////////////////////////////////////////////////////////
    // Map left
    ///////////////////////////////////////////////////////////////////////
    y_at += 3;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Map left");

        point tl = {0, y_at};
        point br = {width / 2, y_at + 2};
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Map left");
    }
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "value");

        point tl = {width / 2 + 8, y_at};
        point br = {width / 2 + 22, y_at + 2};
        wid_set_style(w, WID_STYLE_DARK);
        wid_set_pos(w, tl, br);
        wid_set_text(w,
          SDL_GetScancodeName((SDL_Scancode)game->config.key_map_left));
        wid_set_on_mouse_up(w, game_config_key_map_left);
    }
    ///////////////////////////////////////////////////////////////////////
    // Map down
    ///////////////////////////////////////////////////////////////////////
    y_at += 3;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Map down");

        point tl = {0, y_at};
        point br = {width / 2, y_at + 2};
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Map down");
    }
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "value");

        point tl = {width / 2 + 8, y_at};
        point br = {width / 2 + 22, y_at + 2};
        wid_set_style(w, WID_STYLE_DARK);
        wid_set_pos(w, tl, br);
        wid_set_text(w,
          SDL_GetScancodeName((SDL_Scancode)game->config.key_map_down));
        wid_set_on_mouse_up(w, game_config_key_map_down);
    }
    ///////////////////////////////////////////////////////////////////////
    // Map right
    ///////////////////////////////////////////////////////////////////////
    y_at += 3;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Map right");

        point tl = {0, y_at};
        point br = {width / 2, y_at + 2};
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Map right");
    }
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "value");

        point tl = {width / 2 + 8, y_at};
        point br = {width / 2 + 22, y_at + 2};
        wid_set_style(w, WID_STYLE_DARK);
        wid_set_pos(w, tl, br);
        wid_set_text(w,
          SDL_GetScancodeName((SDL_Scancode)game->config.key_map_right));
        wid_set_on_mouse_up(w, game_config_key_map_right);
    }

    ///////////////////////////////////////////////////////////////////////
    y_at++;
    ///////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////
    // quit
    ///////////////////////////////////////////////////////////////////////
    y_at += 3;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "quit");

        point tl = {0, y_at};
        point br = {width / 2, y_at + 2};
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Quit");
    }
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "value");

        point tl = {width / 2 + 8, y_at};
        point br = {width / 2 + 22, y_at + 2};
        wid_set_style(w, WID_STYLE_DARK);
        wid_set_pos(w, tl, br);
        wid_set_text(w,
          SDL_GetScancodeName((SDL_Scancode)game->config.key_quit));
        wid_set_on_mouse_up(w, game_config_key_quit);
    }
    ///////////////////////////////////////////////////////////////////////
    // help
    ///////////////////////////////////////////////////////////////////////
    y_at += 3;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "help");

        point tl = {0, y_at};
        point br = {width / 2, y_at + 2};
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "This help");
    }
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "value");

        point tl = {width / 2 + 8, y_at};
        point br = {width / 2 + 22, y_at + 2};
        wid_set_style(w, WID_STYLE_DARK);
        wid_set_pos(w, tl, br);
        wid_set_text(w,
          SDL_GetScancodeName((SDL_Scancode)game->config.key_help));
        wid_set_on_mouse_up(w, game_config_key_help);
    }

    wid_update(game_config_keyboard_window->wid_text_area->wid_text_area);
}
