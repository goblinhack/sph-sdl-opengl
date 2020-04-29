//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_wid_minicon.h"
#include "my_wid_popup.h"
#include "my_ascii.h"
#include "my_game_notice.h"

static WidPopup *game_config_window;

//
// Check for saving keys to config can fit
//
static_assert(sizeof(SDL_Scancode) <= sizeof(game->config.key_move_left));

static void game_config_destroy (void)
{_
    if (game_config_window) {
        delete game_config_window;
        game_config_window = nullptr;
    }
}

uint8_t game_config_pause (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    MINICON("paused");
    game->paused = true;
    game->config_select();
    return (true);
}

uint8_t game_config_reset (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    game->init();
    MINICON("restart");
    return (true);
}

uint8_t game_config_screenshot (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    sdl_screenshot();
    return (true);
}

uint8_t game_config_resume (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    MINICON("resumed");
    game->paused = false;
    game->config_select();
    return (true);
}

uint8_t game_config_quit (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    DIE("user quit");
}

uint8_t game_config_key_up (Widp w, const struct SDL_KEYSYM *key)
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

    return (false);
}

uint8_t game_config_key_down (Widp w, const struct SDL_KEYSYM *key)
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

void Game::config_select (void)
{_
    game_notice_destroy();

    if (game_config_window) {
        game_config_destroy();
    }

    auto width = 12;
    auto height = 20;
    point tl = {ASCII_WIDTH - width - 2, MINICON_VIS_HEIGHT - 1 };
    point br = {ASCII_WIDTH - 1, MINICON_VIS_HEIGHT + height - 1};

    game_config_window = new WidPopup(tl, br, nullptr, "ui_popup_widest");
    {_
        Widp w = game_config_window->wid_popup_container;
        wid_set_on_key_up(w, game_config_key_up);
        wid_set_on_key_down(w, game_config_key_down);
        wid_set_shape_none(w);
    }

    int y_at = 0;

    y_at = 0;
    if (paused) {_
        auto p = game_config_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Resume");

        point tl = {0, y_at};
        point br = {width - 1, y_at + 2};
        wid_set_style(w, WID_STYLE_DARK);
        wid_set_on_mouse_up(w, game_config_resume);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "Resume");
    } else {
        auto p = game_config_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Pause");

        point tl = {0, y_at};
        point br = {width - 1, y_at + 2};
        wid_set_style(w, WID_STYLE_DARK);
        wid_set_on_mouse_up(w, game_config_pause);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "Pause");
    }

    ///////////////////////////////////////////////////////////////////////
    // help
    ///////////////////////////////////////////////////////////////////////
    y_at += 3;
    {_
        auto p = game_config_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Reset");

        point tl = {0, y_at};
        point br = {width - 1, y_at + 2};
        wid_set_style(w, WID_STYLE_DARK);
        wid_set_on_mouse_up(w, game_config_reset);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "Reset");
    }
    ///////////////////////////////////////////////////////////////////////
    // help
    ///////////////////////////////////////////////////////////////////////
    y_at += 3;
    {_
        auto p = game_config_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Screenshot");

        point tl = {0, y_at};
        point br = {width - 1, y_at + 2};
        wid_set_style(w, WID_STYLE_DARK);
        wid_set_on_mouse_up(w, game_config_screenshot);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "Screenshot");
    }
    ///////////////////////////////////////////////////////////////////////
    // help
    ///////////////////////////////////////////////////////////////////////
    y_at += 3;
    {_
        auto p = game_config_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Quit");

        point tl = {0, y_at};
        point br = {width - 1, y_at + 2};
        wid_set_style(w, WID_STYLE_DARK);
        wid_set_on_mouse_up(w, game_config_quit);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "Quit");
    }

    wid_update(game_config_window->wid_text_area->wid_text_area);
}
