//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_wid_minicon.h"
#include "my_wid_console.h"
#include "my_wid_popup.h"
#include "my_ascii.h"

static WidPopup *game_quit_window;

static void game_quit_destroy (void)
{_
    if (game_quit_window) {
        delete game_quit_window;
        game_quit_window = nullptr;
    }
}

uint8_t game_quit_yes (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    game_quit_destroy();
    DIE("USERCFG: quit");
    return (false);
}

uint8_t game_quit_no (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    game_quit_destroy();
    return (false);
}

uint8_t game_quit_key_up (Widp w, const struct SDL_KEYSYM *key)
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
                    case 'y':
                        game_quit_yes(nullptr, 0, 0, 0);
                        return (true);
                    case 'n':
                        game_quit_no(nullptr, 0, 0, 0);
                        return (true);
                    case SDLK_ESCAPE:
                        game_quit_no(nullptr, 0, 0, 0);
                        return (true);
                }
            }
        }
    }

    return (false);
}

uint8_t game_quit_key_down (Widp w, const struct SDL_KEYSYM *key)
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

void Game::quit_select (void)
{_
    if (game_quit_window) {
        game_quit_destroy();
    }

    auto m = ASCII_WIDTH / 2;
    auto n = ASCII_HEIGHT / 2;
    point tl = {m - WID_POPUP_WIDTH_NORMAL / 2, n - 4};
    point br = {m + WID_POPUP_WIDTH_NORMAL / 2, n + 5};
    auto width = br.x - tl.x;

    game_quit_window = new WidPopup(tl, br, nullptr, "ui_popup_short");
    {_
        Widp w = game_quit_window->wid_popup_container;
        wid_set_on_key_up(w, game_quit_key_up);
        wid_set_on_key_down(w, game_quit_key_down);
    }

    int y_at = 0;
    {_
        auto p = game_quit_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Quit");

        point tl = {0, y_at};
        point br = {width, y_at + 2};
        wid_set_shape_none(w);
        wid_set_on_mouse_up(w, game_quit_yes);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "Quit game?");
    }

    y_at = 3;
    {_
        auto p = game_quit_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Yes");

        point tl = {0, y_at};
        point br = {width / 2 - 2, y_at + 2};
        wid_set_style(w, WID_STYLE_RED);
        wid_set_on_mouse_up(w, game_quit_yes);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "%%fg=white$Y%%fg=reset$es");
    }

    {_
        auto p = game_quit_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "No");

        point tl = {width / 2 + 1, y_at};
        point br = {width - 2, y_at + 2};
        wid_set_style(w, WID_STYLE_GREEN);
        wid_set_on_mouse_up(w, game_quit_no);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "%%fg=white$N%%fg=reset$o");
    }

    wid_update(game_quit_window->wid_text_area->wid_text_area);
}
