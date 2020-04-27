//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_wid_popup.h"
#include "my_ascii.h"

static WidPopup *game_notice_window;

void game_notice_destroy (void)
{_
    if (game_notice_window) {
        delete game_notice_window;
        game_notice_window = nullptr;
    }
}

uint8_t game_notice_ok (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    game_notice_destroy();
    return (false);
}

uint8_t game_notice_key_up (Widp w, const struct SDL_KEYSYM *key)
{_
    game_notice_ok(nullptr, 0, 0, 0);
    return (true);
}

uint8_t game_notice_key_down (Widp w, const struct SDL_KEYSYM *key)
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

void game_notice (std::string s)
{_
    if (game_notice_window) {
        game_notice_destroy();
    }

    auto m = ASCII_WIDTH / 2;
    auto n = ASCII_HEIGHT / 2;
    point tl = {m - WID_POPUP_WIDTH_NORMAL / 2, n - 5};
    point br = {m + WID_POPUP_WIDTH_NORMAL / 2, n + 5};
    auto width = br.x - tl.x;

    game_notice_window = new WidPopup(tl, br, nullptr, "ui_popup_notice");
    {_
        Widp w = game_notice_window->wid_popup_container;
        wid_set_on_key_up(w, game_notice_key_up);
        wid_set_on_key_down(w, game_notice_key_down);
    }

    int y_at = 0;
    {_
        auto p = game_notice_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "notice");

        point tl = {0, y_at};
        point br = {width, y_at + 1};
        wid_set_shape_none(w);
        wid_set_on_mouse_up(w, game_notice_ok);
        wid_set_pos(w, tl, br);
        wid_set_text(w, s);
    }

    y_at = 3;
    {_
        auto p = game_notice_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "ok");

        point tl = {width / 2 - 4, y_at};
        point br = {width / 2 + 4, y_at + 2};
        wid_set_style(w, WID_STYLE_GREEN);
        wid_set_on_mouse_up(w, game_notice_ok);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "ok");
    }

    wid_update(game_notice_window->wid_text_area->wid_text_area);
}
