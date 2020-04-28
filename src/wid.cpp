//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_main.h"
#include "my_time.h"
#include "my_wid_console.h"
#include "my_sprintf.h"
#include "my_ascii.h"
#include <stdlib.h>
#include <list>

//
// Display sorted.
//
static wid_key_map_location wid_top_level;

//
// Creation sorted and global.
//
static wid_key_map_int wid_global;

//
// Creation sorted and per wid parent.
//
static wid_key_map_int wid_top_level2;

//
// For moving things.
//
static wid_key_map_int wid_top_level3;

//
// For garbage collection.
//
static wid_key_map_int wid_top_level4;

//
// For ticking things.
//
static wid_key_map_int wid_top_level5;

//
// Scope the focus to children of this widget and do not change it.
// Good for popups.
//
static Widp wid_focus_locked {};
Widp wid_focus {};
Widp wid_over {};

//
// Mouse
//
int wid_mouse_visible = 1;

//
// Widget moving
//
static Widp wid_moving {};
static int32_t wid_moving_last_x;
static int32_t wid_moving_last_y;

static timestamp_t wid_time;

//
// Widget effects
//
const timestamp_t wid_destroy_delay_ms = 200;

//
// Prototypes.
//
static void wid_destroy_delay(Widp *wp, int32_t delay);
static uint8_t wid_scroll_trough_mouse_down(Widp w, int32_t x, int32_t y,
                                            uint32_t button);
static uint8_t wid_scroll_trough_mouse_motion(Widp w,
                                              int32_t x, int32_t y,
                                              int32_t relx, int32_t rely,
                                              int32_t wheelx, int32_t wheely);
static void wid_find_first_focus(void);
static void wid_find_top_focus(void);
static void wid_destroy_immediate(Widp w);
static void wid_destroy_immediate_internal(Widp w);
static void wid_update_internal(Widp w);
static void wid_tree_detach(Widp w);
static void wid_tree_attach(Widp w);
static void wid_tree_remove(Widp w);
static void wid_tree2_unsorted_remove(Widp w);
static void wid_tree3_moving_wids_remove(Widp w);
static void wid_tree3_moving_wids_insert(Widp w);
static void wid_tree4_wids_being_destroyed_remove(Widp w);
static void wid_tree4_wids_being_destroyed_insert(Widp w);
static void wid_tree5_ticking_wids_remove(Widp w);
static void wid_tree5_ticking_wids_insert(Widp w);
static void wid_move_dequeue(Widp w);
static void wid_display(Widp w,
                        uint8_t disable_scissor,
                        uint8_t *updated_scissors,
                        int clip);

//
// Child sort priority
//
static int32_t wid_highest_priority = 1;
static int32_t wid_lowest_priority = -1;

//
// History for all text widgets.
//
#define HISTORY_MAX 16
std::array<std::wstring, HISTORY_MAX> history;
uint32_t history_at;
uint32_t history_walk;

//
// A tile over the mouse pointer
//
Widp wid_mouse_template {};
std::array<std::array<Widp, ASCII_HEIGHT_MAX>, ASCII_WIDTH_MAX> wid_on_screen_at {};

static uint8_t wid_init_done;
static uint8_t wid_exiting;

static int wid_refresh_overlay_count;

uint8_t wid_init (void)
{_
    wid_init_done = true;

    return (true);
}

void wid_fini (void)
{_
    wid_init_done = false;
    wid_exiting = true;

    wid_on_screen_at = {};

    wid_gc_all();

    for (;;) {
        if (!wid_top_level.size()) {
            break;
        }

        auto iter = wid_top_level.begin();
        auto child = iter->second;
        wid_destroy_immediate(child);
    }
}

void wid_dump (Widp w, int depth)
{_
    if (!w) {
        return;
    }

    int32_t tlx;
    int32_t tly;
    int32_t brx;
    int32_t bry;

    wid_get_abs_coords(w, &tlx, &tly, &brx, &bry);

    printf("\n          %*s dump: [%s] text [%S] %d,%d to %d,%d ", depth * 2, "", wid_name(w).c_str(), wid_get_text(w).c_str(), tlx, tly, brx, bry);

    for (auto iter : w->children_display_sorted) {
        auto child = iter.second;

        wid_dump(child, depth + 2);
    }
}

int32_t wid_get_tl_x (Widp w)
{_
    int32_t cx = (w->key.tl.x + w->key.br.x) / 2.0;

    return (cx - (cx - w->key.tl.x));
}

int32_t wid_get_tl_y (Widp w)
{_
    int32_t cy = (w->key.tl.y + w->key.br.y) / 2.0;

    return (cy - (cy - w->key.tl.y));
}

int32_t wid_get_br_x (Widp w)
{_
    int32_t cx = (w->key.tl.x + w->key.br.x) / 2.0;

    return (cx + (w->key.br.x - cx));
}

int32_t wid_get_br_y (Widp w)
{_
    int32_t cy = (w->key.tl.y + w->key.br.y) / 2.0;

    return (cy + (w->key.br.y - cy));
}

void wid_get_tl_x_tl_y_br_x_br_y (Widp w,
                                  int32_t *tl_x,
                                  int32_t *tl_y,
                                  int32_t *br_x,
                                  int32_t *br_y)
{_
    const int32_t tlx = w->key.tl.x;
    const int32_t tly = w->key.tl.y;
    const int32_t brx = w->key.br.x;
    const int32_t bry = w->key.br.y;

    const int32_t cx = (tlx + brx) / 2.0;
    const int32_t cy = (tly + bry) / 2.0;

    *tl_x = cx - (cx - tlx);
    *tl_y = cy - (cy - tly);
    *br_x = cx + (brx - cx);
    *br_y = cy + (bry - cy);
}

//
// Set the wid new co-ords. Returns true if there is a change.
//
void wid_set_pos (Widp w, point tl, point br)
{_
    Widp p {};

    wid_tree_detach(w);

    w->key.tl = tl;
    w->key.br = br;

    //
    // Child postion is relative from the parent.
    //
    p = w->parent;
    if (p) {
        w->key.tl.x += wid_get_tl_x(p);
        w->key.tl.y += wid_get_tl_y(p);
        w->key.br.x += wid_get_tl_x(p);
        w->key.br.y += wid_get_tl_y(p);

        w->key.tl.x -= p->offset.x;
        w->key.tl.y -= p->offset.y;
        w->key.br.x -= p->offset.x;
        w->key.br.y -= p->offset.y;
    }

    wid_tree_attach(w);
}

//
// Set the wid new co-ords. Returns true if there is a change.
//
void wid_set_pos_pct (Widp w, fpoint tl, fpoint br)
{_
    Widp p {};

    wid_tree_detach(w);

    if (!w->parent) {
        tl.x *= ASCII_WIDTH;
        tl.y *= ASCII_HEIGHT;
        br.x *= ASCII_WIDTH;
        br.y *= ASCII_HEIGHT;
    } else {
        tl.x *= wid_get_width(w->parent);
        tl.y *= wid_get_height(w->parent);
        br.x *= wid_get_width(w->parent);
        br.y *= wid_get_height(w->parent);
    }

    if (tl.x < 0) {
        tl.x = 0;
    }
    if (tl.y < 0) {
        tl.y = 0;
    }
    if (br.x >= wid_get_width(w->parent)) {
        br.x = wid_get_width(w->parent) - 1;
    }
    if (br.y >= wid_get_height(w->parent)) {
        br.y = wid_get_height(w->parent) - 1;
    }

    int32_t key_tl_x = tl.x;
    int32_t key_tl_y = tl.y;
    int32_t key_br_x = br.x;
    int32_t key_br_y = br.y;

    //
    // Child postion is relative from the parent.
    //
    p = w->parent;
    if (p) {
        key_tl_x += wid_get_tl_x(p);
        key_tl_y += wid_get_tl_y(p);
        key_br_x += wid_get_tl_x(p);
        key_br_y += wid_get_tl_y(p);
    }

    w->key.tl.x = (int)round(key_tl_x);
    w->key.tl.y = (int)round(key_tl_y);
    w->key.br.x = (int)round(key_br_x);
    w->key.br.y = (int)round(key_br_y);

    wid_tree_attach(w);
}

void wid_set_context (Widp w, void *context)
{_
    w->context = context;
}

void *wid_get_context (Widp w)
{_
    return (w->context);
}

void wid_set_string_context (Widp w, std::string string_context)
{_
    w->string_context = string_context;
}

std::string wid_get_string_context (Widp w)
{_
    return (w->string_context);
}

void wid_set_int_context (Widp w, int int_context)
{_
    w->int_context = int_context;
}

int wid_get_int_context (Widp w)
{_
    return (w->int_context);
}

void wid_set_prev (Widp w, Widp prev)
{_
    verify(w);
    if (prev) {
        verify(prev);
    }
    if (!w) {
        DIE("no wid");
    }

    if (w == prev) {
        DIE("wid list loop");
    }

    w->prev = prev;

    if (prev) {
        prev->next = w;
    }
}

Widp wid_get_prev (Widp w)
{_
    if (!w) {
        DIE("no wid");
    }

    if (w->prev == w) {
        DIE("wid list get prev loop");
    }

    return (w->prev);
}

Widp wid_get_next (Widp w)
{_
    if (!w) {
        DIE("no wid");
    }

    if (w->next == w) {
        ERR("wid list get next loop");
    }

    return (w->next);
}

Widp wid_get_head (Widp w)
{_
    Widp prev {};

    while (w) {
        prev = wid_get_prev(w);
        if (!prev) {
            break;
        }

        w = prev;
    }

    return (w);
}

Widp wid_get_tail (Widp w)
{_
    Widp next {};

    while (w) {
        next = wid_get_next(w);
        if (!next) {
            break;
        }

        w = next;
    }

    return (w);
}

Widp wid_get_top_parent (Widp w)
{_
    if (!w) {
        return (w);
    }
    verify(w);

    if (!w->parent) {
        return (w);
    }

    while (w->parent) {
        verify(w);
        w = w->parent;
    }

    return (w);
}

Widp wid_get_parent (Widp w)
{_
    return (w->parent);
}

Widp wid_get_scrollbar_vert (Widp w)
{_
    return (w->scrollbar_vert);
}

Widp wid_get_scrollbar_horiz (Widp w)
{_
    return (w->scrollbar_horiz);
}

static void wid_mouse_motion_end (void)
{_
    wid_moving = nullptr;
}

void wid_set_ignore_events (Widp w, uint8_t val)
{_
    w->ignore_events = val;
}

static void wid_set_scissors (int tlx, int tly, int brx, int bry)
{_
    ascii_set_scissors(point(tlx, tly), point(brx, bry));
}

//
// Should this widget be ignored for events?
//
uint8_t wid_ignore_events (Widp w)
{_
    Widp top {};

    if (!w) {
        return (true);
    }

    if (w->ignore_events || w->moving || w->hidden || w->being_destroyed) {
        return (true);
    }

    if (w->parent) {
        top = wid_get_top_parent(w);

        if (top->moving || top->hidden || top->being_destroyed) {
            return (true);
        }
    }

    return (false);
}

uint8_t wid_ignore_for_focus (Widp w)
{_
    Widp top {};

    if (w->hidden ||
        w->being_destroyed) {
        return (true);
    }

    if (w->parent) {
        top = wid_get_top_parent(w);

        if (top->hidden ||
            top->being_destroyed) {
            return (true);
        }
    }

    return (false);
}

//
// Should this widget be ignored for events?
//
uint8_t wid_ignore_being_destroyed (Widp w)
{_
    Widp top {};

    if (w->being_destroyed) {
        return (true);
    }

    if (w->parent) {
        top = wid_get_top_parent(w);

        if (top->being_destroyed) {
            return (true);
        }
    }

    return (false);
}

static void wid_mouse_motion_begin (Widp w, int32_t x, int32_t y)
{_
    wid_mouse_motion_end();

    if (wid_ignore_being_destroyed(w)) {
        return;
    }

    wid_moving = w;
    wid_moving_last_x = x;
    wid_moving_last_y = y;
}

static void wid_mfocus_end (void)
{_
    Widp w {};

    w = wid_focus;
    wid_focus = nullptr;
    wid_focus_locked = nullptr;

    if (!w) {
        return;
    }

    if (w->on_mouse_focus_end) {
        w->on_mouse_focus_end(w);
    }
}

Widp wid_get_current_focus (void)
{_
    return (wid_focus);
}

static void wid_mfocus_begin (Widp w)
{_
    Widp top {};

    if (!w) {
        wid_mfocus_end();
        wid_focus = nullptr;

        wid_find_top_focus();
        return;
    }

    if (wid_focus == w) {
        return;
    }

    wid_mfocus_end();

    if (wid_ignore_for_focus(w)) {
        return;
    }

    top = wid_get_top_parent(w);

    wid_focus = w;
    top->focus_last = w->focus_order;

    if (w->on_mouse_focus_begin) {
        w->on_mouse_focus_begin(w);
    }
}

static void wid_m_over_e (void)
{_
    Widp w {};

    if (!wid_mouse_visible) {
        return;
    }

    w = wid_over;
    wid_over = nullptr;

    if (!w) {
        return;
    }

    wid_set_mode(w, WID_MODE_NORMAL);

    if (wid_exiting) {
        return;
    }

    if (w->on_mouse_over_e) {
        w->on_mouse_over_e(w);
    }
}

static uint8_t wid_m_over_b (Widp w, uint32_t x, uint32_t y,
                             int32_t relx, int32_t rely,
                             int32_t wheelx, int32_t wheely)
{_
    if (!wid_mouse_visible) {
        return (false);
    }

    if (wid_over == w) {
        return (true);
    }

    if (!(w->on_mouse_over_b) && !(w->on_mouse_down)) {
        if (get(w->cfg, WID_MODE_OVER).color_set[WID_COLOR_BG] ||
            get(w->cfg, WID_MODE_OVER).color_set[WID_COLOR_TEXT]) {
            //
            // Changes appearance on mouse over, so choose this wid even
            // if it has no over callback.
            //
        } else {
            //
            // Can ignore. It doesn't really do anything when the mouse
            // is over.
            //
            return (false);
        }
    }

    if (wid_ignore_being_destroyed(w)) {
        return (false);
    }

    wid_m_over_e();

    wid_over = w;

    wid_set_mode(w, WID_MODE_OVER);

    if (w->on_mouse_over_b) {
        (w->on_mouse_over_b)(w, relx, rely, wheelx, wheely);
    }

    return (true);
}

//
// Map an SDL key event to the char the user typed
//
char wid_event_to_char (const struct SDL_KEYSYM *evt)
{_
    switch (evt->mod) {
        case KMOD_LSHIFT:
        case KMOD_RSHIFT:
            switch (evt->sym) {
                case SDLK_a: return ('A');
                case SDLK_b: return ('B');
                case SDLK_c: return ('C');
                case SDLK_d: return ('D');
                case SDLK_e: return ('E');
                case SDLK_f: return ('F');
                case SDLK_g: return ('G');
                case SDLK_h: return ('H');
                case SDLK_i: return ('I');
                case SDLK_j: return ('J');
                case SDLK_k: return ('K');
                case SDLK_l: return ('L');
                case SDLK_m: return ('M');
                case SDLK_n: return ('N');
                case SDLK_o: return ('O');
                case SDLK_p: return ('P');
                case SDLK_q: return ('Q');
                case SDLK_r: return ('R');
                case SDLK_s: return ('S');
                case SDLK_t: return ('T');
                case SDLK_u: return ('U');
                case SDLK_v: return ('V');
                case SDLK_w: return ('W');
                case SDLK_x: return ('X');
                case SDLK_y: return ('Y');
                case SDLK_z: return ('Z');
                case SDLK_QUOTE: return ('\'');
                case SDLK_COMMA: return ('<');
                case SDLK_MINUS: return ('_');
                case SDLK_PERIOD: return ('>');
                case SDLK_SLASH: return ('?');
                case SDLK_EQUALS: return ('+');
                case SDLK_0: return (')');
                case SDLK_1: return ('!');
                case SDLK_2: return ('"');
                case SDLK_3: return ('#');
                case SDLK_4: return ('$');
                case SDLK_5: return ('%');
                case SDLK_6: return ('^');
                case SDLK_7: return ('&');
                case SDLK_8: return ('*');
                case SDLK_9: return ('(');
                case SDLK_SEMICOLON: return (':');
                case SDLK_LEFTBRACKET: return ('{');
                case SDLK_BACKSLASH: return ('|');
                case SDLK_RIGHTBRACKET: return ('}');
                case SDLK_HASH: return ('~');

            default:
                break;
            }

        case KMOD_LALT:
        case KMOD_RALT:
            switch (evt->sym) {
                default:
                break;
            }

        case KMOD_LCTRL:
        case KMOD_RCTRL:
            switch (evt->sym) {
                default:
                break;
            }

        default:
            break;
    }

    switch (evt->sym) {
        case SDLK_BACKSPACE: return ('');
        case SDLK_TAB: return ('\t');
        case SDLK_RETURN: return ('\n');
        case SDLK_ESCAPE: return ('');
        case SDLK_SPACE: return (' ');
        case SDLK_EXCLAIM: return ('!');
        case SDLK_QUOTEDBL: return ('"');
        case SDLK_HASH: return ('#');
        case SDLK_DOLLAR: return ('$');
        case SDLK_AMPERSAND: return ('%');
        case SDLK_QUOTE: return ('\'');
        case SDLK_LEFTPAREN: return ('(');
        case SDLK_RIGHTPAREN: return (')');
        case SDLK_ASTERISK: return ('*');
        case SDLK_PLUS: return ('+');
        case SDLK_COMMA: return (',');
        case SDLK_MINUS: return ('-');
        case SDLK_PERIOD: return ('.');
        case SDLK_SLASH: return ('/');
        case SDLK_0: return ('0');
        case SDLK_1: return ('1');
        case SDLK_2: return ('2');
        case SDLK_3: return ('3');
        case SDLK_4: return ('4');
        case SDLK_5: return ('5');
        case SDLK_6: return ('6');
        case SDLK_7: return ('7');
        case SDLK_8: return ('8');
        case SDLK_9: return ('9');
        case SDLK_COLON: return (':');
        case SDLK_SEMICOLON: return (';');
        case SDLK_LESS: return ('<');
        case SDLK_EQUALS: return ('=');
        case SDLK_GREATER: return ('>');
        case SDLK_QUESTION: return ('?');
        case SDLK_AT: return ('@');
        case SDLK_LEFTBRACKET: return ('[');
        case SDLK_BACKSLASH: return ('\\');
        case SDLK_RIGHTBRACKET: return (']');
        case SDLK_CARET: return ('^');
        case SDLK_UNDERSCORE: return ('_');
        case SDLK_BACKQUOTE: return ('`');
        case SDLK_a: return ('a');
        case SDLK_b: return ('b');
        case SDLK_c: return ('c');
        case SDLK_d: return ('d');
        case SDLK_e: return ('e');
        case SDLK_f: return ('f');
        case SDLK_g: return ('g');
        case SDLK_h: return ('h');
        case SDLK_i: return ('i');
        case SDLK_j: return ('j');
        case SDLK_k: return ('k');
        case SDLK_l: return ('l');
        case SDLK_m: return ('m');
        case SDLK_n: return ('n');
        case SDLK_o: return ('o');
        case SDLK_p: return ('p');
        case SDLK_q: return ('q');
        case SDLK_r: return ('r');
        case SDLK_s: return ('s');
        case SDLK_t: return ('t');
        case SDLK_u: return ('u');
        case SDLK_v: return ('v');
        case SDLK_w: return ('w');
        case SDLK_x: return ('x');
        case SDLK_y: return ('y');
        case SDLK_z: return ('z');
        case SDLK_DELETE: return ('');
#if SDL_MAJOR_VERSION == 1 // {
        case SDLK_KP0: return ('0');
        case SDLK_KP1: return ('1');
        case SDLK_KP2: return ('2');
        case SDLK_KP3: return ('3');
        case SDLK_KP4: return ('4');
        case SDLK_KP5: return ('5');
        case SDLK_KP6: return ('6');
        case SDLK_KP7: return ('7');
        case SDLK_KP8: return ('8');
        case SDLK_KP9: return ('9');
#else
        case SDLK_KP_0: return ('0');
        case SDLK_KP_1: return ('1');
        case SDLK_KP_2: return ('2');
        case SDLK_KP_3: return ('3');
        case SDLK_KP_4: return ('4');
        case SDLK_KP_5: return ('5');
        case SDLK_KP_6: return ('6');
        case SDLK_KP_7: return ('7');
        case SDLK_KP_8: return ('8');
        case SDLK_KP_9: return ('9');
#endif // }
        case SDLK_KP_PERIOD: return ('.');
        case SDLK_KP_DIVIDE: return ('/');
        case SDLK_KP_MULTIPLY: return ('*');
        case SDLK_KP_MINUS: return ('-');
        case SDLK_KP_PLUS: return ('+');
        case SDLK_KP_ENTER: return ('\0');
        case SDLK_KP_EQUALS: return ('=');
        case SDLK_UP: return ('\0');
        case SDLK_DOWN: return ('\0');
        case SDLK_RIGHT: return ('\0');
        case SDLK_LEFT: return ('\0');
        case SDLK_INSERT: return ('\0');
        case SDLK_HOME: return ('\0');
        case SDLK_END: return ('\0');
        case SDLK_PAGEUP: return ('\0');
        case SDLK_PAGEDOWN: return ('\0');
        case SDLK_F1: return ('\0');
        case SDLK_F2: return ('\0');
        case SDLK_F3: return ('\0');
        case SDLK_F4: return ('\0');
        case SDLK_F5: return ('\0');
        case SDLK_F6: return ('\0');
        case SDLK_F7: return ('\0');
        case SDLK_F8: return ('\0');
        case SDLK_F9: return ('\0');
        case SDLK_F10: return ('\0');
        case SDLK_F11: return ('\0');
        case SDLK_F12: return ('\0');
        case SDLK_F13: return ('\0');
        case SDLK_F14: return ('\0');
        case SDLK_F15: return ('\0');
        case SDLK_CAPSLOCK: return ('\0');
        case SDLK_RSHIFT: return ('\0');
        case SDLK_LSHIFT: return ('\0');
        case SDLK_RCTRL: return ('\0');
        case SDLK_LCTRL: return ('\0');
        case SDLK_RALT: return ('\0');
        case SDLK_LALT: return ('\0');
        case SDLK_MODE: return ('\0');
        case SDLK_HELP: return ('!');
        case SDLK_SYSREQ: return ('\0');
        case SDLK_MENU: return ('\0');
        case SDLK_POWER: return ('\0');
        case SDLK_UNDO: return ('\0');
        default: return ('\0');
    }
    return ('\0');
}

//
// Widget mode, whether it is active, inactive etc...
//
void wid_set_mode (Widp w, wid_mode mode)
{_
    w->timestamp_last_mode_change = wid_time;
    w->mode = mode;
}

//
// Widget mode, whether it is active, inactive etc...
//
wid_mode wid_get_mode (Widp w)
{_
    //
    // Allow focus to override less important modes.
    //
    if (w == wid_focus) {
        if ((w->mode == WID_MODE_NORMAL) || (w->mode == WID_MODE_OVER)) {
            return (WID_MODE_FOCUS);
        }
    }

    return (w->mode);
}

std::string to_string (Widp w)
{_
    return (w->to_string);
}

#if 0
const char * to_cstring (Widp w)
{
    return (to_string(w).c_str());
}
#endif

std::string wid_name (Widp w)
{_
    return (w->name);
}

std::wstring wid_get_text (Widp w)
{_
    return (w->text);
}

std::string wid_get_name (Widp w)
{_
    return (w->name);
}

static std::wstring wid_get_text_with_cursor (Widp w)
{_
    if (!w->received_input) {
        w->cursor = (uint32_t)w->text.length();
    }

    std::wstring t = w->text;
    std::wstring o = t.substr(0, w->cursor) + ASCII_CURSOR_UCHAR +
                     t.substr(w->cursor);

    return (o);
}

void wid_set_name (Widp w, std::string name)
{_
    if (name != "") {
        oldptr(w);
        w->name = name;
        newptr(w, name);
    } else {
        w->name = name;
    }

#ifdef ENABLE_WID_DEBUG
#ifdef WID_FULL_LOGNAME
    if (w->parent) {
        w->to_string = string_sprintf("%s[%p] (parent %s[%p])",
                                    name.c_str(), w,
                                    w->parent->to_string.c_str(),
                                    w->parent);
    } else {
        w->to_string = string_sprintf("%s[%p]", name.c_str(), w);
    }
#else
    w->to_string = string_sprintf("%s[%p]", name.c_str(), w);
#endif
#endif
}

void wid_set_debug (Widp w, uint8_t val)
{_
    w->debug = val;
}

void wid_set_text (Widp w, std::wstring text)
{_
    if (text == L"") {
        w->text = L"";
    } else {
        if (text == w->text) {
            return;
        }

        w->text = text;
    }

    auto len = w->text.size();
    if (w->cursor > len) {
        w->cursor = len;
    }
}

void wid_set_text (Widp w, std::string text)
{_
    wid_set_text(w, string_to_wstring(text));
}

void wid_set_text (Widp w, int v)
{_
    wid_set_text(w, std::to_string(v));
}

uint8_t wid_get_received_input (Widp w)
{_
    return (w->received_input);
}

void wid_set_received_input (Widp w, uint8_t val)
{_
    w->received_input = val;
}

uint32_t wid_get_cursor (Widp w)
{_
    return (w->cursor);
}

void wid_set_cursor (Widp w, uint32_t val)
{_
    w->cursor = val;
}

int32_t wid_get_width (Widp w)
{_
    return (wid_get_br_x(w) - wid_get_tl_x(w)) + 1;
}

int32_t wid_get_height (Widp w)
{_
    return (wid_get_br_y(w) - wid_get_tl_y(w)) + 1;
}

uint8_t wid_get_focusable (Widp w)
{_
    return (w->focus_order);
}

void wid_set_focusable (Widp w, uint8_t val)
{_
    w->focus_order = val;
}

uint8_t wid_get_show_cursor (Widp w)
{_
    return (w->show_cursor);
}

void wid_set_show_cursor (Widp w, uint8_t val)
{_
    w->show_cursor = val;
}

uint8_t wid_get_do_not_raise (Widp w)
{_
    return (w->do_not_raise);
}

void wid_set_do_not_raise (Widp w, uint8_t val)
{_
    w->do_not_raise = val;
}

uint8_t wid_get_do_not_lower (Widp w)
{_
    return (w->do_not_lower);
}

void wid_set_do_not_lower (Widp w, uint8_t val)
{_
    w->do_not_lower = val;
}

uint8_t wid_get_movable (Widp w)
{_
    if (w->movable_set) {
        return (w->movable);
    }

    return (false);
}

void wid_set_movable (Widp w, uint8_t val)
{_
    w->movable = val;
    w->movable_set = true;

    wid_set_movable_horiz(w, val);
    wid_set_movable_vert(w, val);
}

uint8_t wid_get_movable_horiz (Widp w)
{_
    if (w->movable_horiz_set) {
        return (w->movable_horiz);
    }

    return (false);
}

void wid_set_movable_horiz (Widp w, uint8_t val)
{_
    w->movable_horiz = val;
    w->movable_horiz_set = true;
}

uint8_t wid_get_movable_vert (Widp w)
{_
    if (w->movable_vert_set) {
        return (w->movable_vert);
    }

    return (false);
}

void wid_set_movable_vert (Widp w, uint8_t val)
{_
    w->movable_vert = val;
    w->movable_vert_set = true;
}

uint8_t wid_get_movable_bounded (Widp w)
{_
    if (w->movable_bounded_set) {
        return (w->movable_bounded);
    }

    return (false);
}

void wid_set_movable_bounded (Widp w, uint8_t val)
{_
    w->movable_bounded = val;
    w->movable_bounded_set = true;
}

uint8_t wid_get_movable_no_user_scroll (Widp w)
{_
    if (w->movable_no_user_scroll_set) {
        return (w->movable_no_user_scroll);
    }

    return (false);
}

void wid_set_movable_no_user_scroll (Widp w, uint8_t val)
{_
    w->movable_no_user_scroll = val;
    w->movable_no_user_scroll_set = true;
}

uint8_t wid_get_text_lhs (Widp w)
{_
    return (w->text_lhs);
}

void wid_set_text_lhs (Widp w, uint8_t val)
{_
    w->text_lhs = val;
}

uint8_t wid_get_text_rhs (Widp w)
{_
    return (w->text_rhs);
}

void wid_set_text_rhs (Widp w, uint8_t val)
{_
    w->text_rhs = true;
}

uint8_t wid_get_text_centerx (Widp w)
{_
    return (w->text_centerx);
}

void wid_set_text_centerx (Widp w, uint8_t val)
{_
    w->text_centerx = val;
}

uint8_t wid_get_text_top (Widp w)
{_
    return (w->text_top);
}

void wid_set_text_top (Widp w, uint8_t val)
{_
    w->text_top = val;
}

uint8_t wid_get_text_bot (Widp w)
{_
    return (w->text_bot);
}

void wid_set_text_bot (Widp w, uint8_t val)
{_
    w->text_bot = val;
}

uint8_t wid_get_text_centery (Widp w)
{_
    return (w->text_centery);
}

void wid_set_text_centery (Widp w, uint8_t val)
{_
    w->text_centery = val;
}

uint8_t wid_get_text_pos (Widp w, int32_t *x, int32_t *y)
{_
    if (w->text_pos_set) {
        *x = w->text_pos.x;
        *y = w->text_pos.y;

        return (true);
    }

    return (false);
}

void wid_set_text_pos (Widp w, uint8_t val, int32_t x, int32_t y)
{_
    w->text_pos.x = x;
    w->text_pos.y = y;
    w->text_pos_set = val;
}

static Tilep wid_get_bg_tile (Widp w)
{_
    return (w->bg_tile);
}

static Tilep wid_get_fg_tile (Widp w)
{_
    return (w->fg_tile);
}

void wid_set_bg_tile (Widp w, Tilep tile)
{
    w->bg_tile = tile;
}

void wid_set_fg_tile (Widp w, Tilep tile)
{
    w->fg_tile = tile;
}

void wid_set_bg_tilename (Widp w, std::string name)
{_
    Tilep tile = tile_find(name);
    if (!tile) {
        ERR("failed to find wid tile %s", name.c_str());
    }

    if (!w) {
        DIE("widget does not exist to set tile %s", name.c_str());
    }

    w->bg_tile = tile;
}

void wid_set_fg_tilename (Widp w, std::string name)
{_
    Tilep tile = tile_find(name);
    if (!tile) {
        ERR("failed to find wid tile %s", name.c_str());
    }

    if (!w) {
        DIE("widget does not exist to set tile %s", name.c_str());
    }

    w->fg_tile = tile;
}

//
// Look at all the wid modes and return the most relevent setting
//
color wid_get_color (Widp w, wid_color which)
{_
    uint32_t mode = (__typeof__(mode)) wid_get_mode(w); // for c++, no enum walk
    wid_cfg *cfg = &getref(w->cfg, mode);

    if (cfg->color_set[which]) {
        return (cfg->colors[which]);
    }

    if ((wid_focus == w) && (wid_over == w)) {
        mode = WID_MODE_OVER;
        cfg = &getref(w->cfg, mode);
        if (cfg->color_set[which]) {
            return (cfg->colors[which]);
        }
    }

    mode = WID_MODE_NORMAL;
    cfg = &getref(w->cfg, mode);
    if (cfg->color_set[which]) {
        return (cfg->colors[which]);
    }

    return (WHITE);
}

//
// Look at all the widset modes and return the most relevent setting
//
void wid_set_color (Widp w, wid_color col, color val)
{_
    w->cfg[wid_get_mode(w)].colors[col] = val;
    w->cfg[wid_get_mode(w)].color_set[col] = true;
}

void wid_set_focus (Widp w)
{_
    //
    // Don't allow focus override if hard focus is set.
    //
    if (w) {
        if (wid_focus_locked) {
            if (wid_get_top_parent(w) != wid_focus_locked) {
                return;
            }
        }

        if (!w->focus_order) {
            return;
        }
    }

    wid_mfocus_begin(w);
}

void wid_unset_focus (void)
{_
    wid_mfocus_end();
}

void wid_set_shape_square (Widp w)
{
    w->square = true;
}

void wid_set_shape_none (Widp w)
{
    w->square = false;
}

void wid_set_active (Widp w)
{_
    wid_set_mode(w, WID_MODE_ACTIVE);
}

void wid_focus_lock (Widp w)
{_
    if (w) {
        WID_DBG(w, "focus locked");
    }

    wid_focus_locked = w;
}

void wid_unset_focus_lock (void)
{_
    wid_focus_locked = nullptr;
}

void wid_set_on_key_down (Widp w, on_key_down_t fn)
{_
    w->on_key_down = fn;
}

void wid_set_on_key_up (Widp w, on_key_up_t fn)
{_
    w->on_key_up = fn;
}

void wid_set_on_joy_button (Widp w, on_joy_button_t fn)
{_
    w->on_joy_button = fn;
}

void wid_set_on_mouse_down (Widp w, on_mouse_down_t fn)
{_
    w->on_mouse_down = fn;
}

void wid_set_on_mouse_up (Widp w, on_mouse_up_t fn)
{_
    w->on_mouse_up = fn;
}

void wid_set_on_mouse_motion (Widp w, on_mouse_motion_t fn)
{_
    w->on_mouse_motion = fn;
}

void wid_set_on_mouse_focus_begin (Widp w, on_mouse_focus_begin_t fn)
{_
    w->on_mouse_focus_begin = fn;
}

void wid_set_on_mouse_focus_end (Widp w, on_mouse_focus_end_t fn)
{_
    w->on_mouse_focus_end = fn;
}

void wid_set_on_mouse_over_b (Widp w, on_mouse_over_b_t fn)
{_
    w->on_mouse_over_b = fn;
}

void wid_set_on_mouse_over_e (Widp w, on_mouse_over_e_t fn)
{_
    w->on_mouse_over_e = fn;
}

void wid_set_on_destroy (Widp w, on_destroy_t fn)
{_
    w->on_destroy = fn;
}

void wid_set_on_destroy_begin (Widp w, on_destroy_t fn)
{_
    w->on_destroy_begin = fn;
}

void wid_set_on_tick (Widp w, on_tick_t fn)
{_
    if (!fn) {
        ERR("no ticker function set");
    }

    w->on_tick = fn;

    wid_tree5_ticking_wids_insert(w);
}

//
// Remove this wid from any trees it is in.
//
static void wid_tree_detach (Widp w)
{_
    wid_tree_remove(w);
}

//
// Add back to all trees.
//
static void wid_tree_attach (Widp w)
{_
    wid_key_map_location *root;

    if (w->in_tree_root) {
        DIE("wid is already attached");
    }

    if (!w->parent) {
        root = &wid_top_level;
    } else {
        root = &w->parent->children_display_sorted;
    }

    if (!root) {
        DIE("no root");
    }

    auto result = root->insert(std::make_pair(w->key, w));
    if (result.second == false) {
        DIE("wid insert name [%s] failed", wid_get_name(w).c_str());
    }

    w->in_tree_root = root;
}

static void wid_tree_insert (Widp w)
{_
    static uint64_t key;

    if (w->in_tree_root) {
        DIE("wid is already inserted");
    }

    wid_key_map_location *root;

    //
    // Get a wid sort ID.
    //
    w->key.key = ++key;

    if (!w->parent) {
        root = &wid_top_level;
    } else {
        root = &w->parent->children_display_sorted;
    }

    if (!root) {
        DIE("no root");
    }

    auto result = root->insert(std::make_pair(w->key, w));
    if (result.second == false) {
        DIE("wid insert name [%s] failed", wid_get_name(w).c_str());
    }

    w->in_tree_root = root;
}

static void wid_tree_global_unsorted_insert (Widp w)
{_
    static WidKeyType key;

    if (w->in_tree_global_unsorted_root) {
        DIE("wid is already in the global tree");
    }

    auto root = &wid_global;

    key.val++;

    w->tree_global_key = key;
    auto result = root->insert(std::make_pair(w->tree_global_key, w));
    if (result.second == false) {
        DIE("wid insert name [%s] tree_global failed", wid_get_name(w).c_str());
    }

    w->in_tree_global_unsorted_root = root;
}

static void wid_tree2_unsorted_insert (Widp w)
{_
    static uint64_t key;

    if (w->in_tree2_unsorted_root) {
        DIE("wid is already in the in_tree2_unsorted_root");
    }

    wid_key_map_int *root;

    if (!w->parent) {
        root = &wid_top_level2;
    } else {
        root = &w->parent->tree2_children_unsorted;
    }

    w->tree2_key = ++key;
    auto result = root->insert(std::make_pair(w->tree2_key, w));
    if (result.second == false) {
        DIE("wid insert name [%s] tree2 failed", wid_get_name(w).c_str());
    }

    w->in_tree2_unsorted_root = root;
}

static void wid_tree3_moving_wids_insert (Widp w)
{_
    if (w->in_tree3_moving_wids) {
        return;
    }

    if (wid_exiting) {
        return;
    }

    static uint64_t key;
    wid_key_map_int *root = &wid_top_level3;

    w->tree3_key = ++key;
    auto result = root->insert(std::make_pair(w->tree3_key, w));
    if (result.second == false) {
        DIE("wid insert name [%s] tree3 failed", wid_get_name(w).c_str());
    }

    w->in_tree3_moving_wids = root;
}

static void wid_tree4_wids_being_destroyed_insert (Widp w)
{_
    if (w->in_tree4_wids_being_destroyed) {
        return;
    }

    if (wid_exiting) {
        return;
    }

    static uint64_t key;

    wid_key_map_int *root;

    root = &wid_top_level4;

    w->tree4_key = ++key;
    auto result = root->insert(std::make_pair(w->tree4_key, w));
    if (result.second == false) {
        DIE("wid insert name [%s] tree4 failed", wid_get_name(w).c_str());
    }

    w->in_tree4_wids_being_destroyed = root;
}

static void wid_tree5_ticking_wids_insert (Widp w)
{_
    if (w->in_tree5_ticking_wids) {
        return;
    }

    if (wid_exiting) {
        return;
    }

    static uint64_t key;

    wid_key_map_int *root;

    root = &wid_top_level5;

    w->tree5_key = ++key;
    auto result = root->insert(std::make_pair(w->tree5_key, w));
    if (result.second == false) {
        DIE("wid insert name [%s] tree5 failed", wid_get_name(w).c_str());
    }

    w->in_tree5_ticking_wids = root;
}

static void wid_tree_remove (Widp w)
{_
    wid_key_map_location *root;

    root = w->in_tree_root;
    if (!root) {
        return;
    }

    auto result = root->find(w->key);
    if (result == root->end()) {
        DIE("wid tree did not find wid hence cannot remove it");
    }

    root->erase(w->key);

    w->in_tree_root = nullptr;
}

static void wid_tree2_unsorted_remove (Widp w)
{_
    auto root = w->in_tree2_unsorted_root;
    if (!root) {
        return;
    }

    auto result = root->find(w->tree2_key);
    if (result == root->end()) {
        DIE("wid tree2 did not find wid");
    }
    root->erase(w->tree2_key);

    w->in_tree2_unsorted_root = nullptr;
}

static void wid_tree_global_unsorted_remove (Widp w)
{_
    auto root = w->in_tree_global_unsorted_root;
    if (!root) {
        return;
    }

    auto result = root->find(w->tree_global_key);
    if (result == root->end()) {
        DIE("wid tree_global did not find wid");
    }
    root->erase(w->tree_global_key);

    w->in_tree_global_unsorted_root = nullptr;
}

WidKeyType wid_unsorted_get_key (Widp w)
{_
    auto root = &wid_global;

    auto result = root->find(w->tree_global_key);
    if (result == root->end()) {
        DIE("wid unsorted did not find wid");
    }

    w = result->second;

    return (w->tree_global_key);
}

static void wid_tree3_moving_wids_remove (Widp w)
{_
    auto root = w->in_tree3_moving_wids;
    if (!root) {
        return;
    }

    auto result = root->find(w->tree3_key);
    if (result == root->end()) {
        DIE("wid tree3 did not find wid");
    }
    root->erase(w->tree3_key);

    w->in_tree3_moving_wids = nullptr;
}

static void wid_tree4_wids_being_destroyed_remove (Widp w)
{_
    auto root = w->in_tree4_wids_being_destroyed;
    if (!root) {
        return;
    }

    auto result = root->find(w->tree4_key);
    if (result == root->end()) {
        DIE("wid tree4 did not find wid");
    }
    root->erase(w->tree4_key);

    w->in_tree4_wids_being_destroyed = nullptr;
}

static void wid_tree5_ticking_wids_remove (Widp w)
{_
    auto root = w->in_tree5_ticking_wids;
    if (!root) {
        return;
    }

    auto result = root->find(w->tree5_key);
    if (result == root->end()) {
        DIE("wid tree5 did not find wid");
    }
    root->erase(w->tree5_key);

    w->in_tree5_ticking_wids = nullptr;
    w->on_tick = 0;
}

//
// Initialize a wid with basic settings
//
static Widp wid_new (Widp parent)
{_
    auto w = new Wid ();

    w->parent = parent;
    w->timestamp_created = wid_time;

    WID_DBG(w, "new");

    wid_tree_insert(w);
    wid_tree2_unsorted_insert(w);
    wid_tree_global_unsorted_insert(w);

    //
    // Give some lame 3d to the wid
    //
    wid_set_mode(w, WID_MODE_NORMAL);

    w->visible = true;

    return (w);
}

static Widp wid_new (void)
{_
    auto w = new Wid ();

    w->timestamp_created = wid_time;

    WID_DBG(w, "new");

    wid_tree_insert(w);
    wid_tree2_unsorted_insert(w);
    wid_tree_global_unsorted_insert(w);

    //
    // Give some lame 3d to the wid
    //
    wid_set_mode(w, WID_MODE_NORMAL);

    w->visible = true;

    return (w);
}

static void wid_destroy_immediate_internal (Widp w)
{_
    wid_tree3_moving_wids_remove(w);
    wid_tree4_wids_being_destroyed_remove(w);
    wid_tree5_ticking_wids_remove(w);

    if (w->on_destroy) {
        (w->on_destroy)(w);
    }

    if (wid_focus == w) {
        wid_mfocus_end();
    }

    if (wid_focus_locked == w) {
        wid_focus_locked = nullptr;
    }

    if (wid_over == w) {
        wid_m_over_e();
    }

    if (wid_moving == w) {
        wid_mouse_motion_end();
    }

    if (w->scrollbar_vert) {
        w->scrollbar_vert->scrollbar_owner = nullptr;
    }

    if (w->scrollbar_horiz) {
        w->scrollbar_horiz->scrollbar_owner = nullptr;
    }

    if (w->scrollbar_owner) {
        if (w->scrollbar_owner->scrollbar_vert == w) {
            w->scrollbar_owner->scrollbar_vert = nullptr;
        }

        if (w->scrollbar_owner->scrollbar_horiz == w) {
            w->scrollbar_owner->scrollbar_horiz = nullptr;
        }
    }

    {
        auto iter = w->children_display_sorted.begin();

        while (iter != w->children_display_sorted.end()) {
            auto child = iter->second;
            wid_destroy_immediate(child);
            iter = w->children_display_sorted.begin();
        }
    }

    {
        auto iter = w->tree2_children_unsorted.begin();

        while (iter != w->tree2_children_unsorted.end()) {
            auto child = iter->second;
            wid_destroy_immediate(child);
            iter = w->tree2_children_unsorted.begin();
        }
    }
}

static void wid_destroy_immediate (Widp w)
{_
    WID_DBG(w, "destroy immediate");

    //
    // If removing a top level widget, choose a new focus.
    //
    if (!w->parent) {
        wid_find_top_focus();
    }

    wid_tree_detach(w);

    wid_tree2_unsorted_remove(w);
    wid_tree_global_unsorted_remove(w);

    wid_destroy_immediate_internal(w);

    if (w == wid_focus_locked) {
        wid_focus_locked = nullptr;
    }

    if (w == wid_focus) {
        wid_focus = nullptr;
    }

    if (w == wid_over) {
        wid_over = nullptr;
    }

    if (w == wid_moving) {
        wid_moving = nullptr;
    }

    for (auto x = 0; x < ASCII_WIDTH; x++) {
        for (auto y = 0; y < ASCII_HEIGHT; y++) {
            if (get(wid_on_screen_at, x, y) == w) {
                set(wid_on_screen_at, x, y, static_cast<Widp>(0));
            }
        }
    }

    delete w;
}

static void wid_destroy_delay (Widp *wp, int32_t delay)
{_
    int32_t tlx;
    int32_t tly;
    int32_t brx;
    int32_t bry;

    if (!wp) {
        return;
    }

    auto w = *wp;

    if (!w) {
        return;
    }

    WID_DBG(w, "destroy delay");

    (*wp) = nullptr;

    if (w->being_destroyed) {
        if (delay) {
            return;
        }
    }

    w->being_destroyed = true;
    wid_tree4_wids_being_destroyed_insert(w);

    if (wid_focus == w) {
        wid_mfocus_end();
    }

    if (wid_over == w) {
        wid_m_over_e();
    }

    if (wid_moving == w) {
        wid_mouse_motion_end();
    }

    for (auto iter : w->tree2_children_unsorted) {
        auto child = iter.second;
        wid_destroy(&child);
    }

    if (!w->parent) {
        wid_get_abs_coords(w, &tlx, &tly, &brx, &bry);
    }

    if (w->on_destroy_begin) {
        (w->on_destroy_begin)(w);
    }

    //
    // Make sure it stops ticking right now as client pointers this widget
    // might use in the ticker may no longer be valid.
    //
    wid_tree5_ticking_wids_remove(w);
}

void wid_destroy (Widp *wp)
{_
    wid_destroy_delay(wp, wid_destroy_delay_ms);
}

void wid_destroy_nodelay (Widp *wp)
{_
    wid_destroy_delay(wp, 0);
}

void wid_destroy_in (Widp w, uint32_t ms)
{_
    w->destroy_when = wid_time + ms;

    wid_tree4_wids_being_destroyed_insert(w);
}

//
// Initialize a top level wid with basic settings
//
Widp wid_new_window (std::string name)
{_
    Widp w = wid_new();

    w->to_string = string_sprintf("%s[%p]", name.c_str(), w);

    WID_DBG(w, "%s", __FUNCTION__);

    wid_set_name(w, name);

    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_color(w, WID_COLOR_BG, WHITE);
    wid_set_color(w, WID_COLOR_TEXT, WHITE);
    wid_set_shape_square(w);

    return (w);
}

//
// Initialize a top level wid with basic settings
//
Widp wid_new_container (Widp parent, std::string name)
{_
    Widp w = wid_new(parent);

#ifdef ENABLE_WID_DEBUG
#ifdef WID_FULL_LOGNAME
    w->to_string = string_sprintf("%s[%p] (parent %s[%p])",
                                  name.c_str(), w,
                                  parent->to_string.c_str(), parent);
#else
    w->to_string = string_sprintf("%s[%p]", name.c_str(), w);
#endif
#endif

    WID_DBG(w, "%s", __FUNCTION__);

    wid_set_name(w, name);

    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_color(w, WID_COLOR_BG, WHITE);
    wid_set_color(w, WID_COLOR_TEXT, WHITE);
    wid_set_shape_square(w);

    return (w);
}

//
// Initialize a top level wid with basic settings
//
Widp wid_new_square_window (std::string name)
{_
    Widp w = wid_new();

    w->to_string = string_sprintf("%s[%p]", name.c_str(), w);

    WID_DBG(w, "%s", __FUNCTION__);

    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_name(w, name);
    wid_set_shape_square(w);
    wid_set_color(w, WID_COLOR_BG, WHITE);
    wid_set_color(w, WID_COLOR_TEXT, WHITE);
    wid_raise(w);

    return (w);
}

Widp wid_new_square_button (Widp parent, std::string name)
{_
    if (!parent) {
        ERR("no parent");
    }

    Widp w = wid_new(parent);

#ifdef ENABLE_WID_DEBUG
#ifdef WID_FULL_LOGNAME
    w->to_string = string_sprintf("%s[%p] (parent %s[%p])",
                                  name.c_str(), w,
                                  parent->to_string.c_str(), parent);
#else
    w->to_string = string_sprintf("%s[%p]", name.c_str(), w);
#endif
#endif

    WID_DBG(w, "%s", __FUNCTION__);

    wid_set_name(w, name);
    wid_set_shape_square(w);

    wid_set_mode(w, WID_MODE_OVER);
    wid_set_color(w, WID_COLOR_BG, GRAY90);
    wid_set_color(w, WID_COLOR_TEXT, WHITE);

    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_color(w, WID_COLOR_BG, WHITE);
    wid_set_color(w, WID_COLOR_TEXT, WHITE);

    return (w);
}

//
// Initialize a wid with basic settings
//
static Widp wid_new_scroll_trough (Widp parent)
{_
    if (!parent) {
        ERR("no parent");
    }

    Widp w = wid_new(parent);

    w->to_string = string_sprintf("[%p] scroll trough (parent %s[%p])",
                                  w,
                                  parent->to_string.c_str(), parent);

    WID_DBG(w, "%s", __FUNCTION__);

    wid_set_mode(w, WID_MODE_NORMAL); {
        color c = GRAY90;
        wid_set_color(w, WID_COLOR_BG, c);
    }

    wid_set_on_mouse_down(w, wid_scroll_trough_mouse_down);
    wid_set_on_mouse_motion(w, wid_scroll_trough_mouse_motion);
    wid_set_shape_square(w);

    return (w);
}

//
// Initialize a wid with basic settings
//
static Widp wid_new_scroll_bar (Widp parent,
                                std::string name,
                                Widp scrollbar_owner,
                                uint8_t vertical)
{_
    if (!parent) {
        ERR("no parent");
    }

    color c;
    color tl;
    color br;

    Widp w = wid_new(parent);

    if (vertical) {
        w->to_string = string_sprintf("%s, %s[%p]",
                                      name.c_str(),
                                      "vert scroll bar", w);
    } else {
        w->to_string = string_sprintf("%s, %s[%p]",
                                      name.c_str(),
                                      "horiz scroll bar", w);
    }

    WID_DBG(w, "%s", __FUNCTION__);

    wid_set_name(w, name);

    wid_set_mode(w, WID_MODE_ACTIVE); {
        color c = GREEN;
        wid_set_color(w, WID_COLOR_BG, c);
    }

    wid_set_mode(w, WID_MODE_NORMAL); {
        color c = GRAY50;
        wid_set_color(w, WID_COLOR_BG, c);
    }

    wid_set_movable(w, true);
    wid_set_movable_bounded(w, true);
    wid_set_shape_square(w);

    if (vertical) {
        wid_set_movable_vert(w, true);
        wid_set_movable_horiz(w, false);
        scrollbar_owner->scrollbar_vert = w;
    } else {
        wid_set_movable_horiz(w, true);
        wid_set_movable_vert(w, false);
        scrollbar_owner->scrollbar_horiz = w;
    }

    w->scrollbar_owner = scrollbar_owner;

    wid_hide(w);

    return (w);
}

Widp wid_new_vert_scroll_bar (Widp parent,
                              std::string name,
                              Widp scrollbar_owner)
{_
    if (!parent) {
        ERR("no parent");
    }

    point tl;
    point br;

    int32_t tlx;
    int32_t tly;
    int32_t brx;
    int32_t bry;
    int32_t ptlx;
    int32_t ptly;
    int32_t pbrx;
    int32_t pbry;

    //
    // Make the trough line up with the scrolling window.
    //
    wid_get_abs_coords(parent, &ptlx, &ptly, &pbrx, &pbry);
    wid_get_abs_coords(scrollbar_owner, &tlx, &tly, &brx, &bry);

    tl.x = tlx - ptlx + wid_get_width(scrollbar_owner);
    br.x = tl.x;

    tl.y = tly - ptly;
    br.y = tly - ptly + wid_get_height(scrollbar_owner) - 1;

    Widp trough = wid_new_scroll_trough(parent);
    wid_set_pos(trough, tl, br);
    wid_set_shape_square(trough);

    {
        fpoint tl(0, 0);
        fpoint br(1, 1);
        Widp scrollbar =
            wid_new_scroll_bar(trough, name, scrollbar_owner, true);
        wid_set_pos_pct(scrollbar, tl, br);

        wid_update_internal(scrollbar);
        wid_visible(wid_get_parent(scrollbar));
        wid_visible(scrollbar);

        return (scrollbar);
    }
}

Widp wid_new_horiz_scroll_bar (Widp parent, std::string name,
                               Widp scrollbar_owner)
{_
    if (!parent) {
        ERR("no parent");
    }

    point tl;
    point br;

    int32_t tlx;
    int32_t tly;
    int32_t brx;
    int32_t bry;
    int32_t ptlx;
    int32_t ptly;
    int32_t pbrx;
    int32_t pbry;

    //
    // Make the trough line up with the scrolling window.
    //
    wid_get_abs_coords(parent, &ptlx, &ptly, &pbrx, &pbry);
    wid_get_abs_coords(scrollbar_owner, &tlx, &tly, &brx, &bry);

    tl.x = tlx - ptlx;
    br.x = tlx - ptlx + wid_get_width(scrollbar_owner) - 1;

    tl.y = tly - ptly + wid_get_height(scrollbar_owner);
    br.y = tl.y;

    Widp trough = wid_new_scroll_trough(parent);
    wid_set_pos(trough, tl, br);
    wid_set_shape_square(trough);

    {
        fpoint tl(0, 0);
        fpoint br(1, 1);
        Widp scrollbar = wid_new_scroll_bar(trough, name, scrollbar_owner, false);
        wid_set_pos_pct(scrollbar, tl, br);

        wid_update_internal(scrollbar);
        wid_visible(wid_get_parent(scrollbar));
        wid_visible(scrollbar);

        return (scrollbar);
    }
}

static void wid_raise_internal (Widp w)
{_
    if (w->do_not_raise) {
        return;
    }

    if (wid_moving != w) {
        wid_mouse_motion_end();
    }

    if (wid_get_top_parent(wid_moving) != w) {
        wid_mouse_motion_end();
    }

    wid_tree_detach(w);
    w->key.priority = ++wid_highest_priority;
    wid_tree_attach(w);
}

static void wid_raise_override (Widp parent)
{_
    //
    // If some widget wants to be on top, let it.
    //
    if (parent->do_not_lower) {
        wid_raise_internal(parent);
    }

    for (auto iter : parent->children_display_sorted) {
        auto w = iter.second;

        if (w->do_not_lower) {
            wid_raise_internal(w);
            break;
        }

        wid_raise_override(w);
    }
}

void wid_raise (Widp w_in)
{_
    if (!w_in) {
        return;
    }

    wid_raise_internal(w_in);

    //
    // If some widget wants to be on top, let it.
    //
    std::vector<Widp> worklist;
    for (auto iter : wid_top_level) {
        auto w = iter.second;
        worklist.push_back(w);
    }

    for (auto w : worklist) {
        wid_raise_override(w);
    }

    wid_find_top_focus();

    //
    // If we were hovering over a window and it was replaced, we need to fake
    // a mouse movement so we know we are still over it.
    //
    if (!w_in->parent) {
        wid_update_mouse();
    }
}

static void wid_lower_internal (Widp w)
{_
    if (w->do_not_lower) {
        return;
    }

    if (wid_moving == w) {
        wid_mouse_motion_end();
    }

    if (wid_get_top_parent(wid_moving) == w) {
        wid_mouse_motion_end();
    }

    wid_tree_detach(w);
    w->key.priority = --wid_lowest_priority;
    wid_tree_attach(w);
}

void wid_lower (Widp w_in)
{_
    if (!w_in) {
        return;
    }

    wid_lower_internal(w_in);

    //
    // If some widget wants to be on top, let it.
    //
    for (auto iter : wid_top_level) {
        auto w = iter.second;
        if (w->do_not_raise) {
            wid_lower_internal(w);
            break;
        }
    }

    wid_find_top_focus();

    //
    // If we were hovering over a window and it was replaced, we need to fake
    // a mouse movement so we know we are still over it.
    //
    if (!w_in->parent && !w_in->children_display_sorted.empty()) {
        wid_update_mouse();
    }
}

void wid_toggle_hidden (Widp w)
{_
    if (w->hidden) {
        wid_visible(w);
    } else {
        wid_hide(w);
    }
}

static void wid_find_first_child_focus (Widp w, Widp *best)
{_
    if (w->focus_order) {
        if (!*best) {
            *best = w;
        } else if (w->focus_order < (*best)->focus_order) {
            *best = w;
        }
    }

    for (auto iter : w->children_display_sorted) {
        auto child = iter.second;

        wid_find_first_child_focus(child, best);
    }
}

static void wid_find_first_focus (void)
{_
    Widp best {};

    for (auto iter = wid_top_level.rbegin();
         iter != wid_top_level.rend(); ++iter) {
        auto w = iter->second;
        if (wid_ignore_for_focus(w)) {
            continue;
        }

        best = nullptr;
        wid_find_first_child_focus(w, &best);
        if (best) {
            wid_set_focus(best);
            return;
        }
    }
}

static void wid_find_specific_child_focus (Widp w, Widp *best,
                                           uint8_t focus_order)
{_
    if (w->focus_order) {
        if (w->focus_order == focus_order) {
            *best = w;
            return;
        }
    }

    for (auto iter : w->children_display_sorted) {
        auto child = iter.second;

        wid_find_specific_child_focus(child, best, focus_order);
    }
}

static Widp wid_find_top_wid_focus (Widp w)
{_
    Widp best {};

    if (wid_ignore_for_focus(w)) {
        return (best);
    }

    //
    // First time we've looked at this widget, hunt for the first focus.
    //
    if (!w->focus_last) {
        wid_find_first_child_focus(w, &best);
        if (best) {
            return (best);
        }
    }

    wid_find_specific_child_focus(w, &best, w->focus_last);
    if (best) {
        return (best);
    }

    return (best);
}

static void wid_find_top_focus (void)
{_
    Widp best {};

    for (auto iter = wid_top_level.rbegin();
         iter != wid_top_level.rend(); ++iter) {
        auto w = iter->second;
        if (wid_ignore_for_focus(w)) {
            continue;
        }

        best = nullptr;

        //
        // First time we've looked at this widget, hunt for the first focus.
        //
        if (!w->focus_last) {
            wid_find_first_child_focus(w, &best);
            if (best) {
                wid_set_focus(best);
                return;
            }
        }

        wid_find_specific_child_focus(w, &best, w->focus_last);
        if (best) {
            wid_set_focus(best);
            return;
        }
    }

    wid_find_first_focus();
}

static void wid_find_last_child_focus (Widp w, Widp *best)
{_
    if (w->focus_order) {
        if (!*best) {
            *best = w;
        } else if (w->focus_order > (*best)->focus_order) {
            *best = w;
        }
    }

    for (auto iter : w->children_display_sorted) {
        auto child = iter.second;

        wid_find_last_child_focus(child, best);
    }
}

Widp wid_get_focus (Widp w)
{_
    Widp best {};

    if (wid_focus) {
        if (wid_get_top_parent(wid_focus) == wid_get_top_parent(w)) {
            return (wid_focus);
        }
    }

    if (!w->focus_last) {
        best = wid_find_top_wid_focus(wid_get_top_parent(w));
        if (best) {
            return (best);
        }
    }

    wid_find_specific_child_focus(w, &best, w->focus_last);

    return (best);
}

static void wid_find_last_focus (void)
{_
    Widp best {};

    for (auto iter = wid_top_level.rbegin();
         iter != wid_top_level.rend(); ++iter) {
        auto w = iter->second;
        if (wid_ignore_for_focus(w)) {
            continue;
        }

        best = nullptr;
        wid_find_last_child_focus(w, &best);
        if (best) {
            wid_set_focus(best);
            return;
        }
    }
}

static void wid_find_next_child_focus (Widp w, Widp *best)
{_
    if (w->focus_order) {
        if (*best) {
            if ((w->focus_order < (*best)->focus_order) &&
                (w->focus_order > wid_focus->focus_order)) {
                *best = w;
            }
        } else if (w->focus_order > wid_focus->focus_order) {
            *best = w;
        }
    }

    for (auto iter : w->children_display_sorted) {
        auto child = iter.second;

        wid_find_next_child_focus(child, best);
    }
}

static void wid_find_next_focus (void)
{_
    Widp best {};

    if (!wid_focus) {
        wid_find_first_focus();
        return;
    }

    for (auto iter = wid_top_level.rbegin();
         iter != wid_top_level.rend(); ++iter) {
        auto w = iter->second;

        if (wid_ignore_for_focus(w)) {
            continue;
        }

        if (!w->focus_last) {
            continue;
        }

        wid_find_next_child_focus(w, &best);
        if (best) {
            wid_set_focus(best);
            return;
        }

        wid_find_first_focus();
        break;
    }
}

static void wid_find_prev_child_focus (Widp w, Widp *best)
{_
    if (w->focus_order) {
        if (*best) {
            if ((w->focus_order > (*best)->focus_order) &&
                (w->focus_order < wid_focus->focus_order)) {
                *best = w;
            }
        } else if (w->focus_order < wid_focus->focus_order) {
            *best = w;
        }
    }

    for (auto iter : w->children_display_sorted) {
        auto child = iter.second;

        wid_find_prev_child_focus(child, best);
    }
}

static void wid_find_prev_focus (void)
{_
    Widp best {};

    if (!wid_focus) {
        wid_find_first_focus();
        return;
    }

    for (auto iter = wid_top_level.rbegin();
         iter != wid_top_level.rend(); ++iter) {
        auto w = iter->second;

        if (wid_ignore_for_focus(w)) {
            continue;
        }

        if (!w->focus_last) {
            continue;
        }

        wid_find_prev_child_focus(w, &best);
        if (best) {
            wid_set_focus(best);
            return;
        }

        wid_find_last_focus();
        break;
    }
}

Widp wid_find (Widp w, std::string name)
{_
    if (strcasestr_(w->name.c_str(), name.c_str())) {
        return (w);
    }

    for (auto iter : w->children_display_sorted) {
        auto child = iter.second;

        Widp ret {};

        ret = wid_find(child, name);
        if (ret) {
            return (ret);
        }
    }

    DIE("wid not found");
}

void wid_always_hidden (Widp w, uint8_t value)
{_
    w->always_hidden = value;
}

void wid_visible (Widp w)
{_
    if (!w) {
        return;
    }

    w->visible = true;
    w->hidden = false;

    std::vector<Widp> worklist;
    for (auto iter : w->children_display_sorted) {
        auto child = iter.second;
        wid_visible(child);
    }

    wid_find_top_focus();
}

void wid_this_visible (Widp w)
{_
    if (!w) {
        return;
    }

    w->visible = true;
    w->hidden = false;
}

void wid_hide (Widp w)
{_
    if (!w) {
        return;
    }

    w->hidden = true;
    w->visible = false;

    if (wid_over == w) {
        wid_m_over_e();
    }

    if (wid_moving == w) {
        wid_mouse_motion_end();
    }

    if (wid_get_top_parent(wid_over) == w) {
        wid_m_over_e();
    }

    if (wid_get_top_parent(wid_moving) == w) {
        wid_mouse_motion_end();
    }

    if (w == wid_focus) {
        wid_find_top_focus();
    }

    std::vector<Widp> worklist;
    for (auto iter : w->children_display_sorted) {
        auto child = iter.second;
        wid_hide(child);
    }
}

static uint8_t wid_scroll_trough_mouse_down (Widp w,
                                             int32_t x,
                                             int32_t y,
                                             uint32_t button)
{_
    int32_t dx;
    int32_t dy;

    std::vector<Widp> worklist;
    for (auto iter : w->children_display_sorted) {
        auto child = iter.second;
        worklist.push_back(child);
    }

    for (auto child : worklist) {
        dx = 0;
        dy = 0;

        if (x < wid_get_tl_x(child)) {
            dx = -1;
        }

        if (x > wid_get_tl_x(child)) {
            dx = 1;
        }

        if (y < wid_get_tl_y(child)) {
            dy = -1;
        }

        if (y > wid_get_tl_y(child)) {
            dy = 1;
        }

        if (dx || dy) {
            wid_set_mode(child, WID_MODE_ACTIVE);
        }

        if (!wid_get_movable_horiz(child)) {
            dx = 0;
        }

        if (!wid_get_movable_vert(child)) {
            dy = 0;
        }

        wid_move_delta(child, dx, dy);
    }

    return (true);
}

static uint8_t wid_scroll_trough_mouse_motion (Widp w,
                                               int32_t x, int32_t y,
                                               int32_t relx, int32_t rely,
                                               int32_t wheelx, int32_t wheely)
{_
    int32_t dx;
    int32_t dy;

    if ((SDL_BUTTON(SDL_BUTTON_LEFT) & SDL_GetMouseState(0, 0)) ||
        wheely || wheelx) {

        dy = rely ? rely : -wheely;

        dx = relx ? relx : -wheelx;

        dx = ((int)(dx / ASCII_WIDTH)) * ASCII_WIDTH;
        dy = ((int)(dy / ASCII_HEIGHT)) * ASCII_HEIGHT;

        if (dx < 0) {
            dx = -1;
        }
        if (dy < 0) {
            dy = -1;
        }
        if (dx > 0) {
            dx = 1;
        }
        if (dy > 0) {
            dy = 1;
        }
    } else {
        return (false);
    }

    std::vector<Widp> worklist;
    for (auto iter : w->children_display_sorted) {
        auto child = iter.second;
        worklist.push_back(child);
    }

    for (auto child : worklist) {
        if (dx || dy) {
            wid_set_mode(child, WID_MODE_ACTIVE);
        }

        if (!wid_get_movable_horiz(child)) {
            dx = 0;
        }

        if (!wid_get_movable_vert(child)) {
            dy = 0;
        }

        wid_move_delta(child, dx, dy);
    }

    return (true);
}

static void wid_adjust_scrollbar (Widp scrollbar, Widp owner)
{_
    double height = wid_get_height(owner);
    double width = wid_get_width(owner);
    double child_height = 0;
    double child_width = 0;
    double scrollbar_width;
    double scrollbar_height;
    double trough_height;
    double trough_width;
    double miny = 0;
    double maxy = 0;
    double minx = 0;
    double maxx = 0;
    double pct;
    uint8_t first = true;

    //
    // Find out the space that the children take up then use this to
    // adjust the scrollbar dimensions.
    //
    {
        for (auto iter : owner->tree2_children_unsorted) {
            auto child = iter.second;

            int32_t tl_x, tl_y, br_x, br_y;

            wid_get_tl_x_tl_y_br_x_br_y(child, &tl_x, &tl_y, &br_x, &br_y);

            if (first) {
                minx = tl_x;
                miny = tl_y;
                maxx = br_x;
                maxy = br_y;
                first = false;
                continue;
            }


            if (tl_x < minx) {
                minx = tl_x;
            }

            if (tl_y < miny) {
                miny = tl_y;
            }

            if (br_x > maxx) {
                maxx = br_x;
            }

            if (br_y > maxy) {
                maxy = br_y;
            }
        }
    }

    int32_t ptl_x, ptl_y, pbr_x, pbr_y;
    wid_get_tl_x_tl_y_br_x_br_y(owner, &ptl_x, &ptl_y, &pbr_x, &pbr_y);

    minx -= ptl_x;
    miny -= ptl_y;
    maxx -= ptl_x;
    maxy -= ptl_y;

    child_width = maxx - minx + 1;
    child_height = maxy - miny + 1;

    if (child_width < width) {
        maxx = minx + width - 1;
        child_width = maxx - minx + 1;
    }

    if (child_height < height) {
        maxy = miny + height - 1;
        child_height = maxy - miny + 1;
    }

    if (owner->scrollbar_vert) {
        if (wid_get_movable_vert(scrollbar)) {
            trough_height = wid_get_height(owner->scrollbar_vert->parent);
            scrollbar_height = (int)(trough_height * (height / child_height));

            if (trough_height - scrollbar_height == 0.0f) {
                pct = 0.0f;
            } else {
                pct = (wid_get_tl_y(scrollbar) -
                       wid_get_tl_y(scrollbar->parent)) /
                        (trough_height - scrollbar_height);
            }

            owner->offset.y = -miny;
            owner->offset.y -= (pct * (child_height - height));

            scrollbar->key.tl.y =
                wid_get_tl_y(scrollbar->parent) +
                pct * (trough_height - scrollbar_height);

            wid_tree_detach(scrollbar);
            scrollbar->key.br.y =
                wid_get_tl_y(scrollbar) + scrollbar_height - 1;
            wid_tree_attach(scrollbar);

            wid_set_mode(scrollbar, WID_MODE_ACTIVE);
        }
    }

    if (owner->scrollbar_horiz) {
        if (wid_get_movable_horiz(scrollbar)) {
            trough_width = wid_get_width(owner->scrollbar_horiz->parent);
            scrollbar_width = (int)(trough_width * (width / child_width));

            if (trough_width - scrollbar_width == 0.0f) {
                pct = 0.0f;
            } else {
                pct = (wid_get_tl_x(scrollbar) -
                       wid_get_tl_x(scrollbar->parent)) /
                        (trough_width - scrollbar_width);
            }

            owner->offset.x = -minx;
            owner->offset.x -= (pct * (child_width - width));

            scrollbar->key.tl.x =
                wid_get_tl_x(scrollbar->parent) +
                pct * (trough_width - scrollbar_width);

            wid_tree_detach(scrollbar);
            scrollbar->key.br.x =
                wid_get_tl_x(scrollbar) + scrollbar_width - 1;
            wid_tree_attach(scrollbar);

            wid_set_mode(scrollbar, WID_MODE_ACTIVE);
        }
    }
}

void wid_get_children_size (Widp owner, int32_t *w, int32_t *h)
{_
    double height = wid_get_height(owner);
    double width = wid_get_width(owner);
    double child_height = 0;
    double child_width = 0;
    double miny = 0;
    double maxy = 0;
    double minx = 0;
    double maxx = 0;
    uint8_t first = true;

    //
    // Find out the space that the children take up then use this to
    // adjust the scrollbar dimensions.
    //
    for (auto iter : owner->children_display_sorted) {

        auto child = iter.second;

        int32_t tminx = wid_get_tl_x(child) - wid_get_tl_x(child->parent);
        int32_t tminy = wid_get_tl_y(child) - wid_get_tl_y(child->parent);
        int32_t tmaxx = wid_get_br_x(child) - wid_get_tl_x(child->parent);
        int32_t tmaxy = wid_get_br_y(child) - wid_get_tl_y(child->parent);

        if (first) {
            minx = tminx;
            miny = tminy;
            maxx = tmaxx;
            maxy = tmaxy;
            first = false;
            continue;
        }

        if (tminx < minx) {
            minx = tminx;
        }

        if (tminy < miny) {
            miny = tminy;
        }

        if (tmaxx > maxx) {
            maxx = tmaxx;
        }

        if (tmaxy > maxy) {
            maxy = tmaxy;
        }
    }

    child_width = maxx - minx;
    child_height = maxy - miny;

    if (child_width < width) {
        maxx = minx + width;
        child_width = maxx - minx;
    }

    if (child_height < height) {
        maxy = miny + height;
        child_height = maxy - miny;
    }

    if (w) {
        *w = child_width;
    }

    if (h) {
        *h = child_height;
    }
}

static void wid_update_internal (Widp w)
{_
    int32_t tlx;
    int32_t tly;
    int32_t brx;
    int32_t bry;

    wid_get_abs_coords(w, &tlx, &tly, &brx, &bry);

    //
    // First time around, initialize the wid.
    //
    if (!w->first_update) {
        w->first_update = true;

        if (!w->parent) {
            //
            // Find the focus.
            //
            wid_find_top_focus();
        }

        //
        // Set back to normal to undo any settings when creating.
        //
        // No, make the clients fix their code.
        //
//        wid_set_mode(w, WID_MODE_NORMAL);
    }

    //
    // Clip all the children. Avoid this for speed for the main game window.
    //
    std::vector<Widp> worklist;
    for (auto iter : w->tree2_children_unsorted) {
        auto w = iter.second;
        worklist.push_back(w);
    }

    for (auto child : worklist) {
        wid_update_internal(child);
    }

    //
    // If the source of the event is the scrollbars themselves...
    //
    if (w->scrollbar_owner) {
        wid_adjust_scrollbar(w, w->scrollbar_owner);
        wid_update_internal(w->scrollbar_owner);
    } else {
        //
        // If the source of the event is the owner of the scrollbars...
        //
        if (w->scrollbar_vert) {
            wid_adjust_scrollbar(w->scrollbar_vert, w);
        }

        if (w->scrollbar_horiz) {
            wid_adjust_scrollbar(w->scrollbar_horiz, w);
        }
    }
}

void wid_update (Widp w)
{_
    wid_update_internal(w);

    //
    // If we were hovering over a window and it was replaced, we need to fake
    // a mouse movement so we know we are still over it.
    //
    if (!w->parent && !w->children_display_sorted.empty()) {
        wid_update_mouse();
    }
}

void wid_update_mouse (void)
{_
    //
    // So if we are now over a new widget that was created on top of the
    // mouse, we activate it.
    //
    int32_t x;
    int32_t y;

    SDL_GetMouseState(&x, &y);

    wid_mouse_motion(x, y, 0, 0, 0, 0);
}

void wid_scroll_text (Widp w)
{_
    std::wstring s;
    Widp prev {};
    Widp tmp {};

    //
    // Get the wid on the top of the list/screen.
    //
    tmp = wid_get_tail(w);

    //
    // Now copy the text up to the parent widgets.
    //
    while (tmp) {
        prev = wid_get_prev(tmp);

        if (prev) {
            s = wid_get_text(prev);

            wid_set_text(tmp, s);
        }

        tmp = prev;
    }
}

//
// Replace the 2nd last line of text and scroll. The assumption is the last
// line is the input line.
//
void wid_scroll_with_input (Widp w, std::wstring str)
{_
    Widp tmp {};

    wid_scroll_text(w);

    //
    // Get the wid on the bottom of the list/screen.
    //
    tmp = wid_get_head(w);

    //
    // Now get the 2nd last line. The last line is the input. The 2nd last
    // line is where new output goes.
    //
    if (tmp) {
        tmp = wid_get_next(tmp);
        if (tmp) {
            wid_set_text(tmp, str);
        }
    }
}

uint8_t wid_receive_input (Widp w, const SDL_KEYSYM *key)
{_
    std::wstring beforecursor;
    std::wstring aftercursor;
    std::wstring tmp;
    std::wstring origtext;
    std::wstring updatedtext;
    std::wstring newchar;
    uint32_t origlen;
    uint32_t cnt;

    newchar += wid_event_to_char(key);
    origtext = wid_get_text(w);
    origlen = (uint32_t)origtext.length();

    if (!w->received_input) {
        wid_set_received_input(w, true);
        w->cursor = (uint32_t)origtext.length();
    }

    if (origtext.empty()) {
        aftercursor = beforecursor = L"";
    } else {
        beforecursor = origtext.substr(0, w->cursor);
        aftercursor = origtext.substr(w->cursor);
    }

    switch (key->mod) {
        case KMOD_LCTRL:
        case KMOD_RCTRL:
            switch (wid_event_to_char(key)) {
            case 'p':
                if (!history_walk) {
                    history_walk = HISTORY_MAX - 1;
                } else {
                    history_walk--;
                }

                wid_set_text(w, get(history, history_walk));
                w->cursor = (uint32_t)wid_get_text(w).length();
                break;

            case 'n':
                history_walk++;
                if (history_walk >= HISTORY_MAX) {
                    history_walk = 0;
                }

                wid_set_text(w, get(history, history_walk));
                w->cursor = (uint32_t)wid_get_text(w).length();
                break;

            case 'a':
                w->cursor = 0;
                break;

            case 'e':
                w->cursor = origlen;
                break;
            }
            break;

        default:

        switch (key->sym) {
            case SDLK_BACKSPACE:
                if (beforecursor.size()) {
                    w->cursor--;

                    beforecursor.erase(beforecursor.end() - 1);
                    auto result = beforecursor + aftercursor;
                    wid_set_text(w, result);
                }
                break;

            case SDLK_TAB:
                if (w != wid_console_input_line) {
                    return (true);
                }

                command_handle(wid_get_text(w),
                               &updatedtext,
                               false /* show ambiguous */,
                               true /* show complete */,
                               false /* execute command */,
                               0 /* context */);

                if (!updatedtext.empty()) {
                    wid_set_text(w, updatedtext);
                    w->cursor = updatedtext.length();
                }
                return (true);

            case SDLK_RETURN:
                if (w != wid_console_input_line) {
                    return (false);
                }

                if (origlen && (w == wid_console_input_line)) {
                    static std::wstring entered;
                    static std::wstring entered2;

                    entered = wid_get_text(w);
                    entered2 = L"\u0084 %%fg=green$" + wid_get_text(w);

                    wid_scroll_text(w);
                    wid_set_text(w->next, entered2);

                    if (!command_handle(entered,
                                        &updatedtext,
                                        true /* show ambiguous */,
                                        false /* show complete */,
                                        true /* execute command */,
                                        0 /* context */)) {
                         return (true);
                    }

                    updatedtext = trim(updatedtext);

                    if (!updatedtext.empty()) {
                        wid_set_text(w, updatedtext);
                        w->cursor = updatedtext.length();
                    }

                    set(history, history_at, updatedtext);

                    history_at++;
                    if (history_at >= HISTORY_MAX) {
                        history_at = 0;
                    }
                    history_walk = history_at;

                    wid_set_text(w, L"");
                    w->cursor = 0;
                } else if (w == wid_console_input_line) {
                    wid_scroll_text(w);
                }
                return (true);

            case SDLK_LEFT:
                if (w->cursor > 0) {
                    w->cursor--;
                }
                break;

            case SDLK_RIGHT:
                if (w->cursor < origlen) {
                    w->cursor++;
                }
                break;

            case SDLK_UP:
                cnt = 0;
                while (cnt < HISTORY_MAX) {
                    cnt++;
                    if (!history_walk) {
                        history_walk = HISTORY_MAX - 1;
                    } else {
                        history_walk--;
                    }

                    wid_set_text(w, get(history, history_walk));
                    if (get(history, history_walk) == L"") {
                        continue;
                    }

                    w->cursor = (uint32_t)wid_get_text(w).length();
                    break;
                }
                break;

            case SDLK_DOWN:
                cnt = 0;
                while (cnt < HISTORY_MAX) {
                    cnt++;

                    history_walk++;
                    if (history_walk >= HISTORY_MAX) {
                        history_walk = 0;
                    }

                    wid_set_text(w, get(history, history_walk));
                    if (get(history, history_walk) == L"") {
                        continue;
                    }

                    w->cursor = (uint32_t)wid_get_text(w).length();
                    break;
                }
                break;

            case SDLK_HOME:
                w->cursor = 0;
                break;

            case SDLK_END:
                w->cursor = origlen;
                break;

            default: {
                auto c = wid_event_to_char(key);

                switch (c) {
                case SDLK_ESCAPE:
                    if (w != wid_console_input_line) {
                        break;
                    }

                case CONSOLE_KEY1:
                case CONSOLE_KEY2:
                case CONSOLE_KEY3:
                    //
                    // Magic keys we use to toggle the console.
                    //
                    return (false);

                case '?':
                    if (w != wid_console_input_line) {
                        break;
                    }

                    command_handle(wid_get_text(w),
                                   &updatedtext,
                                   true /* show ambiguous */,
                                   false /* show complete */,
                                   false /* execute command */,
                                   0 /* context */);

                    if (!updatedtext.empty()) {
                        wid_set_text(w, updatedtext);
                        w->cursor = updatedtext.length();
                    }
                    return (true);
                }

                if (c != '\0') {
                    std::wstring tmp = L"";
                    tmp += c;
                    updatedtext = beforecursor;
                    updatedtext += c;
                    updatedtext += aftercursor;

                    w->cursor++;

                    wid_set_text(w, updatedtext);
                }
            }
        }
    }

    return (true);
}

//
// Handle keys no one grabbed.
//
static uint8_t wid_receive_unhandled_input (const SDL_KEYSYM *key)
{_
    Widp w {};

    w = wid_get_top_parent(wid_console_input_line);

    switch (key->mod) {
        case KMOD_LCTRL:
        case KMOD_RCTRL:
        default:
            switch ((int32_t)key->sym) {
                case '\\':
                    sdl_screenshot();
                    MINICON("Screenshot taken");
                    MINICON("USERCFG: screenshot taken");
                    break;

                case '`':
                    wid_toggle_hidden(wid_console_window);
                    wid_raise(wid_console_window);

                    //
                    // Need this so the console gets focus over the menu.
                    //
                    if (w->visible) {
                        wid_set_focus(w);
                        wid_focus_lock(w);
                    } else {
                        wid_unset_focus();
                        wid_unset_focus_lock();
                    }
                    break;

                case SDLK_ESCAPE:
                    if (w->visible) {
                        wid_hide(w);
                    }

                    //
                    // Need this so the console gets focus over the menu.
                    //
                    if (w->visible) {
                        wid_set_focus(w);
                        wid_focus_lock(w);
                    } else {
                        wid_unset_focus();
                        wid_unset_focus_lock();
                    }
                    break;

                case SDLK_TAB:
                case SDLK_RETURN:
                case SDLK_DOWN:
                case SDLK_RIGHT:
                    wid_find_next_focus();
                    break;

                case SDLK_UP:
                case SDLK_LEFT:
                    wid_find_prev_focus();
                    break;

                default: {
                    if (wid_console_window && wid_console_window->visible) {
                        wid_console_receive_input(wid_console_input_line, key);
                    }
                    break;
                }
            }
            break;

        case KMOD_LSHIFT:
        case KMOD_RSHIFT:
            switch ((int32_t)key->sym) {
            }
    }

    return (true);
}

static Widp wid_find_at (Widp w, int32_t x, int32_t y)
{_
    w = get(wid_on_screen_at, x, y);
    if (!w) {
        return nullptr;
    }

    verify(w);
    if (wid_ignore_being_destroyed(w)) {
        return nullptr;
    }

    return (w);
}

static Widp wid_key_down_handler_at (Widp w, int32_t x, int32_t y,
                                     uint8_t strict)
{_
    if (!w) {
        return nullptr;
    }

    if (wid_ignore_events(w)) {
        return nullptr;
    }

    if (strict) {
        if ((x < w->abs_tl.x) ||
            (y < w->abs_tl.y) ||
            (x > w->abs_br.x) ||
            (y > w->abs_br.y)) {
            return nullptr;
        }
    }

    for (auto iter : w->children_display_sorted) {
        auto child = iter.second;

        if (wid_focus_locked &&
            (wid_get_top_parent(child) != wid_get_top_parent(wid_focus_locked))) {
            continue;
        }

        Widp closer_match = wid_key_down_handler_at(child, x, y,
                                                    true /* strict */);
        if (closer_match) {
            return (closer_match);
        }
    }

    for (auto iter : w->children_display_sorted) {
        auto child = iter.second;

        if (wid_focus_locked &&
            (wid_get_top_parent(child) != wid_get_top_parent(wid_focus_locked))) {
            continue;
        }

        Widp closer_match = wid_key_down_handler_at(child, x, y,
                                                    false /* strict */);
        if (closer_match) {
            return (closer_match);
        }
    }

    if (w->on_key_down) {
        if (wid_focus_locked &&
            (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
            return nullptr;
        }

        return (w);
    }

    w = wid_get_top_parent(w);
    if (w->on_key_down) {
        if (wid_focus_locked &&
            (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
            return nullptr;
        }

        return (w);
    }

    return nullptr;
}

static Widp wid_key_up_handler_at (Widp w, int32_t x, int32_t y,
                                     uint8_t strict)
{_
    if (!w) {
        return nullptr;
    }

    if (wid_ignore_events(w)) {
        return nullptr;
    }

    if (strict) {
        if ((x < w->abs_tl.x) ||
            (y < w->abs_tl.y) ||
            (x > w->abs_br.x) ||
            (y > w->abs_br.y)) {
            return nullptr;
        }
    }

    for (auto iter : w->children_display_sorted) {
        auto child = iter.second;

        if (wid_focus_locked &&
            (wid_get_top_parent(child) != wid_get_top_parent(wid_focus_locked))) {
            continue;
        }

        Widp closer_match = wid_key_up_handler_at(child, x, y,
                                                  true /* strict */);
        if (closer_match) {
            return (closer_match);
        }
    }

    for (auto iter : w->children_display_sorted) {
        auto child = iter.second;

        if (wid_focus_locked &&
            (wid_get_top_parent(child) != wid_get_top_parent(wid_focus_locked))) {
            continue;
        }

        Widp closer_match = wid_key_up_handler_at(child, x, y,
                                                  false /* strict */);
        if (closer_match) {
            return (closer_match);
        }
    }

    if (w->on_key_up) {
        if (wid_focus_locked &&
            (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
            return nullptr;
        }

        return (w);
    }

    return nullptr;
}

static Widp wid_joy_button_handler_at (Widp w, int32_t x, int32_t y,
                                       uint8_t strict)
{_
    if (!w) {
        return nullptr;
    }

    if (wid_ignore_events(w)) {
        return nullptr;
    }

    if (strict) {
        if ((x < w->abs_tl.x) ||
            (y < w->abs_tl.y) ||
            (x > w->abs_br.x) ||
            (y > w->abs_br.y)) {
            return nullptr;
        }
    }

    for (auto iter : w->children_display_sorted) {
        auto child = iter.second;

        if (wid_focus_locked &&
            (wid_get_top_parent(child) != wid_get_top_parent(wid_focus_locked))) {
            continue;
        }

        Widp closer_match = wid_joy_button_handler_at(child, x, y,
                                                    true /* strict */);
        if (closer_match) {
            return (closer_match);
        }
    }

    if (w->on_joy_button) {
        if (wid_focus_locked &&
            (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
            return nullptr;
        }

        return (w);
    }

    return nullptr;
}

static Widp wid_mouse_down_handler_at (Widp w, int32_t x, int32_t y,
                                       uint8_t strict)
{_
    if (!w) {
        return nullptr;
    }

    if (w->ignore_for_mouse_down) {
        return nullptr;
    }

    if (wid_ignore_events(w)) {
        return nullptr;
    }

    if (strict) {
        if ((x < w->abs_tl.x) ||
            (y < w->abs_tl.y) ||
            (x > w->abs_br.x) ||
            (y > w->abs_br.y)) {
            return nullptr;
        }
    }

    for (auto iter : w->children_display_sorted) {
        auto child = iter.second;

        if (wid_focus_locked &&
            (wid_get_top_parent(child) != wid_get_top_parent(wid_focus_locked))) {
            continue;
        }

        Widp closer_match = wid_mouse_down_handler_at(child, x, y,
                                                      true /* strict */);
        if (closer_match) {
            return (closer_match);
        }
    }

    if (w->on_mouse_down) {
        if (wid_focus_locked &&
            (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
            return nullptr;
        }

        return (w);
    }

    if (wid_get_movable(w)) {
        if (wid_focus_locked &&
            (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
            return nullptr;
        }

        return (w);
    }

    //
    // Prevent mouse events that occur in the bounds of one window, leaking
    // into lower levels.
    //
    if (!w->parent) {
        if (wid_focus_locked &&
            (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
            return nullptr;
        }

        return (w);
    }

    return nullptr;
}

static Widp wid_mouse_up_handler_at (Widp w, int32_t x, int32_t y, uint8_t strict)
{_
    if (!w) {
        return nullptr;
    }

    if (wid_ignore_events(w)) {
        return nullptr;
    }

    if (strict) {
        if ((x < w->abs_tl.x) ||
            (y < w->abs_tl.y) ||
            (x > w->abs_br.x) ||
            (y > w->abs_br.y)) {
            return nullptr;
        }
    }

    for (auto iter : w->children_display_sorted) {
        auto child = iter.second;

        if (wid_focus_locked &&
            (wid_get_top_parent(child) != wid_get_top_parent(wid_focus_locked))) {
            continue;
        }

        Widp closer_match = wid_mouse_up_handler_at(child, x, y,
                                                      true /* strict */);
        if (closer_match) {
            return (closer_match);
        }
    }

    if (w->on_mouse_up) {
        if (wid_focus_locked &&
            (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
            return nullptr;
        }

        return (w);
    }

    if (wid_get_movable(w)) {
        if (wid_focus_locked &&
            (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
            return nullptr;
        }

        return (w);
    }

    //
    // Prevent mouse events that occur in the bounds of one window, leaking
    // into lower levels.
    //
    if (!w->parent) {
        if (wid_focus_locked &&
            (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
            return nullptr;
        }

        return (w);
    }

    return nullptr;
}

static void wid_children_move_delta_internal (Widp w, int32_t dx, int32_t dy)
{_
    //
    // Make sure you can't move a wid outside the parents box.
    //
    Widp p = w->parent;
    if (p) {
        if (wid_get_movable_bounded(w)) {
            if (wid_get_tl_x(w) + dx < wid_get_tl_x(p)) {
                dx = wid_get_tl_x(p) - wid_get_tl_x(w);
            }

            if (wid_get_tl_y(w) + dy < wid_get_tl_y(p)) {
                dy = wid_get_tl_y(p) - wid_get_tl_y(w);
            }

            if (wid_get_br_x(w) + dx > wid_get_br_x(p)) {
                dx = wid_get_br_x(p) - wid_get_br_x(w);
            }

            if (wid_get_br_y(w) + dy > wid_get_br_y(p)) {
                dy = wid_get_br_y(p) - wid_get_br_y(w);
            }
        }
    }

    w->key.tl.x += dx;
    w->key.tl.y += dy;
    w->key.br.x += dx;
    wid_tree_detach(w);
    w->key.br.y += dy;
    wid_tree_attach(w);

    for (auto iter : w->tree2_children_unsorted) {
        auto child = iter.second;

        wid_children_move_delta_internal(child, dx, dy);
    }
}

static void wid_move_delta_internal (Widp w, int32_t dx, int32_t dy)
{_
    wid_tree_detach(w);

    //
    // Make sure you can't move a wid outside the parents box.
    //
    Widp p = w->parent;
    if (p) {
        if (wid_get_movable_bounded(w)) {
            if (wid_get_tl_x(w) + dx < wid_get_tl_x(p)) {
                dx = wid_get_tl_x(p) - wid_get_tl_x(w);
            }

            if (wid_get_tl_y(w) + dy < wid_get_tl_y(p)) {
                dy = wid_get_tl_y(p) - wid_get_tl_y(w);
            }

            if (wid_get_br_x(w) + dx > wid_get_br_x(p)) {
                dx = wid_get_br_x(p) - wid_get_br_x(w);
            }

            if (wid_get_br_y(w) + dy > wid_get_br_y(p)) {
                dy = wid_get_br_y(p) - wid_get_br_y(w);
            }
        }
    }

    w->key.tl.x += dx;
    w->key.tl.y += dy;
    w->key.br.x += dx;
    w->key.br.y += dy;
    wid_tree_attach(w);

    std::vector<Widp> worklist;
    for (auto iter : w->tree2_children_unsorted) {
        auto w = iter.second;
        worklist.push_back(w);
    }

    for (auto child : worklist) {
        wid_children_move_delta_internal(child, dx, dy);
    }
}

void wid_move_delta (Widp w, int32_t dx, int32_t dy)
{_
    wid_move_delta_internal(w, dx, dy);

    wid_update_internal(w);
}

void wid_move_delta_pct (Widp w, double dx, double dy)
{_
    if (!w->parent) {
        dx *= (double)ASCII_WIDTH;
        dy *= (double)ASCII_HEIGHT;
    } else {
        dx *= wid_get_width(w->parent);
        dy *= wid_get_height(w->parent);
    }

    wid_move_delta_internal(w, dx, dy);

    wid_update_internal(w);
}

void wid_move_to_bottom (Widp w)
{_
    if (w->parent) {
        wid_move_delta(w, 0, wid_get_br_y(w->parent) - wid_get_br_y(w));
    } else {
        wid_move_delta(w, 0, ASCII_HEIGHT - wid_get_br_y(w));
    }
}

void wid_move_to_left (Widp w)
{_
    if (w->parent) {
        wid_move_delta(w, wid_get_tl_x(w->parent) - wid_get_tl_x(w), 0);
    } else {
        wid_move_delta(w, - wid_get_tl_x(w), 0);
    }
}

void wid_move_to_right (Widp w)
{_
    if (w->parent) {
        wid_move_delta(w, wid_get_br_x(w->parent) - wid_get_br_x(w), 0);
    } else {
        wid_move_delta(w, ASCII_WIDTH - wid_get_br_x(w), 0);
    }
}

void wid_move_to_vert_pct (Widp w, double pct)
{_
    double pheight = wid_get_br_y(w->parent) - wid_get_tl_y(w->parent);
    double at = (wid_get_tl_y(w) - wid_get_tl_y(w->parent)) / pheight;
    double delta = (pct - at) * pheight;

    wid_move_delta(w, 0, delta);
}

void wid_move_to_horiz_pct (Widp w, double pct)
{_
    double pwidth = wid_get_br_x(w->parent) - wid_get_tl_x(w->parent);
    double at = (wid_get_tl_x(w) - wid_get_tl_x(w->parent)) / pwidth;
    double delta = (pct - at) * pwidth;

    wid_move_delta(w, delta, 0);
}

void wid_move_to_vert_pct_in (Widp w, double pct, double in)
{_
    if (pct < 0.0) {
        pct = 0.0;
    }

    if (pct > 1.0) {
        pct = 1.0;
    }

    double pheight = wid_get_br_y(w->parent) - wid_get_tl_y(w->parent);
    double at = (wid_get_tl_y(w) - wid_get_tl_y(w->parent)) / pheight;
    double delta = (pct - at) * pheight;

    wid_move_to_abs_in(w, wid_get_tl_x(w), wid_get_tl_y(w) + delta, in);
}

void wid_move_to_horiz_pct_in (Widp w, double pct, double in)
{_
    if (pct < 0.0) {
        pct = 0.0;
    }

    if (pct > 1.0) {
        pct = 1.0;
    }

    double pwidth = wid_get_br_x(w->parent) - wid_get_tl_x(w->parent);
    double at = (wid_get_tl_x(w) - wid_get_tl_x(w->parent)) / pwidth;
    double delta = (pct - at) * pwidth;

    wid_move_to_abs_in(w, wid_get_tl_x(w) + delta, wid_get_tl_y(w), in);
}

void wid_move_to_horiz_vert_pct_in (Widp w, double x, double y, double in)
{_
    if (x < 0.0) {
        x = 0.0;
    }

    if (x > 1.0) {
        x = 1.0;
    }

    if (y < 0.0) {
        y = 0.0;
    }

    if (y > 1.0) {
        y = 1.0;
    }

    double pheight = wid_get_br_y(w->parent) - wid_get_tl_y(w->parent);
    double aty = (wid_get_tl_y(w) - wid_get_tl_y(w->parent)) / pheight;
    double dy = (y - aty) * pheight;

    double pwidth = wid_get_br_x(w->parent) - wid_get_tl_x(w->parent);
    double atx = (wid_get_tl_x(w) - wid_get_tl_x(w->parent)) / pwidth;
    double dx = (x - atx) * pwidth;

    wid_move_to_abs_in(w, wid_get_tl_x(w) + dx, wid_get_tl_y(w) + dy, in);
}

void wid_move_to_top (Widp w)
{_
    if (w->parent) {
        wid_move_delta(w, 0, wid_get_tl_y(w->parent) - wid_get_tl_y(w));
    } else {
        wid_move_delta(w, 0, - wid_get_tl_y(w));
    }
}

static Widp wid_joy_button_handler (int32_t x, int32_t y)
{_
    for (auto iter = wid_top_level.rbegin();
         iter != wid_top_level.rend(); ++iter) {
        auto w = iter->second;

        if (wid_focus_locked &&
            (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
            continue;
        }

        w = wid_joy_button_handler_at(w, x, y, false /* strict */);
        if (!w) {
            continue;
        }

        return (w);
    }

    return nullptr;
}

static Widp wid_mouse_down_handler (int32_t x, int32_t y)
{_
    Widp w {};

    w = wid_mouse_down_handler_at(wid_focus, x, y, true /* strict */);
    if (w) {
        return (w);
    }

    w = wid_mouse_down_handler_at(wid_over, x, y, true /* strict */);
    if (w) {
        return (w);
    }

    for (auto iter = wid_top_level.rbegin();
         iter != wid_top_level.rend(); ++iter) {
        auto w = iter->second;

        if (wid_focus_locked &&
            (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
            continue;
        }

        w = wid_mouse_down_handler_at(w, x, y, true /* strict */);
        if (!w) {
            continue;
        }

        return (w);
    }

    for (auto iter = wid_top_level.rbegin();
         iter != wid_top_level.rend(); ++iter) {
        auto w = iter->second;

        if (wid_focus_locked &&
            (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
            continue;
        }

        w = wid_mouse_down_handler_at(w, x, y, false /* strict */);
        if (!w) {
            continue;
        }

        return (w);
    }

    return nullptr;
}

static Widp wid_mouse_up_handler (int32_t x, int32_t y)
{_
    Widp w {};

    w = wid_mouse_up_handler_at(wid_focus, x, y, true /* strict */);
    if (w) {
        return (w);
    }

    w = wid_mouse_up_handler_at(wid_over, x, y, true /* strict */);
    if (w) {
        return (w);
    }

    for (auto iter = wid_top_level.rbegin();
         iter != wid_top_level.rend(); ++iter) {
        auto w = iter->second;

        if (wid_focus_locked &&
            (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
            continue;
        }

        w = wid_mouse_up_handler_at(w, x, y, true /* strict */);
        if (!w) {
            continue;
        }

        return (w);
    }

    for (auto iter = wid_top_level.rbegin();
         iter != wid_top_level.rend(); ++iter) {
        auto w = iter->second;

        if (wid_focus_locked &&
            (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
            continue;
        }

        w = wid_mouse_up_handler_at(w, x, y, false /* strict */);
        if (!w) {
            continue;
        }

        return (w);
    }

    return nullptr;
}

static Widp wid_mouse_motion_handler (int32_t x, int32_t y,
                                      int32_t relx, int32_t rely,
                                      int32_t wheelx, int32_t wheely)
{_
    Widp w {};

    w = get(wid_on_screen_at, x, y);
    if (w) {
        verify(w);
        return (w);
    }

    return nullptr;
}

//
// Catch recursive cases:
//
static int wid_mouse_motion_recursion;

void wid_mouse_motion (int32_t x, int32_t y,
                       int32_t relx, int32_t rely,
                       int32_t wheelx, int32_t wheely)
{_
    int got_one = false;

    pixel_to_ascii(&x, &y);
    if (!ascii_ok(x, y)) {
        return;
    }

    wid_refresh_overlay_count += 1;

    if (wid_mouse_motion_recursion) {
        return;
    }

    wid_mouse_motion_recursion = 1;

    if (wid_mouse_template) {
        wid_move_to_abs_centered_in(wid_mouse_template, x, y, 10);
        wid_raise(wid_mouse_template);
    }

    uint8_t over = false;

    for (auto iter : wid_top_level) {
        auto w = iter.second;

        if (wid_focus_locked &&
            (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
            continue;
        }

        //
        // Allow wheel events to go everywhere
        //
        if (!wheelx && !wheely) {
            w = wid_find_at(w, x, y);
            if (!w) {
                continue;
            }
        }

        if (wid_ignore_events(w)) {
            //
            // This wid is ignoring events, but what about the parent?
            //
            w = w->parent;
            while (w) {
                if (!wid_ignore_events(w)) {
                    break;
                }
                w = w->parent;
            }

            if (!w) {
                continue;
            }
        }

        //
        // Over a new wid.
        //

        while (w &&
               !wid_m_over_b(w, x, y, relx, rely, wheelx, wheely)) {
            w = w->parent;
        }

        uint8_t done = false;

        if (!w) {
            //
            // Allow scrollbar to grab.
            //
        } else {
            //
            // This widget reacted somehow when we went over it. i.e. popup ot
            // function.
            //
            over = true;
        }

        w = wid_mouse_motion_handler(x, y, relx, rely, wheelx, wheely);
        if (w) {

            if (wid_m_over_b(w, x, y, relx, rely, wheelx, wheely)) {
                over = true;
            }

            //
            // If the mouse event is fully processed then do not pass onto
            // scrollbars.
            //
            if (w->on_mouse_motion) {
                if ((w->on_mouse_motion)(w, x, y, relx, rely, wheelx, wheely)) {
                    got_one = true;
                    break;
                }
            }

            if (wid_over == w) {
                if (!wheelx && !wheely) {
                    break;
                }
            }

            while (w) {
                //
                // If there are scrollbars and the wid did not grab the event
                // then scroll for it.
                //
                if (wheely) {
                    if (w->scrollbar_vert &&
                        !wid_get_movable_no_user_scroll(w->scrollbar_vert)) {

                        got_one = true;
                        wid_move_delta(w->scrollbar_vert, 0, -wheely);
                        done = true;
                    }
                }

                if (wheelx) {
                    if (w->scrollbar_horiz &&
                        !wid_get_movable_no_user_scroll(w->scrollbar_horiz)) {

                        got_one = true;
                        wid_move_delta(w->scrollbar_horiz, -wheelx, 0);
                        done = true;
                    }
                }

                if (done) {
                    break;
                }

                //
                // Maybe the container has a scrollbar. Try it.
                //
                w = w->parent;
            }
        }

        if (done) {
            break;
        }
    }

    if (!over) {
        wid_m_over_e();
    }

    //
    // If nothing then pass the event to the console to allow scrolling
    // of the console.
    //
    if (!got_one){
        if (wid_console_container && (wheelx || wheely)) {
            Widp w = wid_console_container->scrollbar_vert;
            if (w) {
                w = w->parent;
            }

            if (w && w->on_mouse_motion) {
                (w->on_mouse_motion)(w, x, y, relx, rely, wheelx, wheely);
            }
        }
    }

    wid_mouse_motion_recursion = 0;
}

//
// If no handler for this button, fake a mouse event.
//
void wid_fake_joy_button (int32_t x, int32_t y)
{_
    if (get(sdl_joy_buttons, SDL_JOY_BUTTON_A)) {
        wid_mouse_down(SDL_BUTTON_LEFT, x, y);
        return;
    }
    if (get(sdl_joy_buttons, SDL_JOY_BUTTON_B)) {
        wid_mouse_down(SDL_BUTTON_RIGHT, x, y);
        return;
    }
    if (get(sdl_joy_buttons, SDL_JOY_BUTTON_X)) {
        wid_mouse_down(SDL_BUTTON_RIGHT, x, y);
        return;
    }
    if (get(sdl_joy_buttons, SDL_JOY_BUTTON_Y)) {
        wid_mouse_down(2, x, y);
        return;
    }
    if (get(sdl_joy_buttons, SDL_JOY_BUTTON_TOP_LEFT)) {
        wid_mouse_down(SDL_BUTTON_LEFT, x, y);
        return;
    }
    if (get(sdl_joy_buttons, SDL_JOY_BUTTON_TOP_RIGHT)) {
        wid_mouse_down(SDL_BUTTON_RIGHT, x, y);
        return;
    }
    if (get(sdl_joy_buttons, SDL_JOY_BUTTON_LEFT_STICK_DOWN)) {
        wid_mouse_down(SDL_BUTTON_LEFT, x, y);
        return;
    }
    if (get(sdl_joy_buttons, SDL_JOY_BUTTON_RIGHT_STICK_DOWN)) {
        wid_mouse_down(SDL_BUTTON_RIGHT, x, y);
        return;
    }
    if (get(sdl_joy_buttons, SDL_JOY_BUTTON_START)) {
        wid_mouse_down(SDL_BUTTON_LEFT, x, y);
        return;
    }
    if (get(sdl_joy_buttons, SDL_JOY_BUTTON_XBOX)) {
        wid_mouse_down(SDL_BUTTON_LEFT, x, y);
        return;
    }
    if (get(sdl_joy_buttons, SDL_JOY_BUTTON_BACK)) {
        wid_mouse_down(SDL_BUTTON_RIGHT, x, y);
        return;
    }
    if (get(sdl_joy_buttons, SDL_JOY_BUTTON_UP)) {
    }
    if (get(sdl_joy_buttons, SDL_JOY_BUTTON_DOWN)) {
    }
    if (get(sdl_joy_buttons, SDL_JOY_BUTTON_LEFT)) {
    }
    if (get(sdl_joy_buttons, SDL_JOY_BUTTON_RIGHT)) {
    }
    if (get(sdl_joy_buttons, SDL_JOY_BUTTON_LEFT_FIRE)) {
        wid_mouse_down(SDL_BUTTON_LEFT, x, y);
        return;
    }
    if (get(sdl_joy_buttons, SDL_JOY_BUTTON_RIGHT_FIRE)) {
        wid_mouse_down(SDL_BUTTON_RIGHT, x, y);
        return;
    }
}

void wid_joy_button (int32_t x, int32_t y)
{_
    pixel_to_ascii(&x, &y);
    if (!ascii_ok(x, y)) {
        return;
    }

    //
    // Only if there is a change in status, send an event.
    //
    static std::array<timestamp_t, SDL_MAX_BUTTONS> ts;
    int changed = false;
    int b;

    for (b = 0; b < SDL_MAX_BUTTONS; b++) {
        if (get(sdl_joy_buttons, b)) {
            if (time_have_x_tenths_passed_since(2, get(ts, b))) {
                changed = true;
                set(ts, b, time_get_time_ms_cached());
            }
        }
    }

    if (!changed) {
        return;
    }

    Widp w {};

    w = wid_joy_button_handler(x, y);
    if (!w) {
        wid_fake_joy_button(x, y);
        return;
    }

    //
    // Raise on mouse.
    //
    if (w->on_joy_button) {
        //
        // If the button doesn't eat the event, try the parent.
        //
        while (!(w->on_joy_button)(w, x, y)) {
            w = w->parent;

            while (w && !w->on_joy_button) {
                w = w->parent;
            }

            if (!w) {
                wid_fake_joy_button(x, y);
                return;
            }
        }

        wid_set_focus(w);
        wid_set_mode(w, WID_MODE_ACTIVE);
        wid_raise(w);

        //
        // Move on mouse.
        //
        if (wid_get_movable(w)) {
            wid_mouse_motion_begin(w, x, y);
            return;
        }

        return;
    } else {
        wid_fake_joy_button(x, y);
    }

    if (wid_get_movable(w)) {
        wid_set_mode(w, WID_MODE_ACTIVE);
        wid_raise(w);
        wid_mouse_motion_begin(w, x, y);
        return;
    }
}

void wid_mouse_down (uint32_t button, int32_t x, int32_t y)
{_
    Widp w {};

    pixel_to_ascii(&x, &y);
    if (!ascii_ok(x, y)) {
        return;
    }

    w = wid_mouse_down_handler(x, y);
    if (!w) {
        return;
    }

    //
    // Raise on mouse.
    //
    if ((w->on_mouse_down && (w->on_mouse_down)(w, x, y, button)) ||
        wid_get_movable(w)) {

        wid_set_focus(w);
        wid_set_mode(w, WID_MODE_ACTIVE);
        wid_raise(w);

        //
        // Move on mouse.
        //
        if (wid_get_movable(w)) {
            wid_mouse_motion_begin(w, x, y);
            return;
        }

        return;
    }

    if (wid_get_movable(w)) {
        wid_set_mode(w, WID_MODE_ACTIVE);
        wid_raise(w);
        wid_mouse_motion_begin(w, x, y);
        return;
    }

    if (game_mouse_down(x, y, button)) {
        return;
    }
}

void wid_mouse_up (uint32_t button, int32_t x, int32_t y)
{_
    Widp w {};

    pixel_to_ascii(&x, &y);
    if (!ascii_ok(x, y)) {
        return;
    }

    wid_mouse_motion_end();

    w = wid_mouse_up_handler(x, y);
    if (!w) {
        return;
    }

    if ((w->on_mouse_up && (w->on_mouse_up)(w, x, y, button)) ||
        wid_get_movable(w)) {

        wid_set_mode(w, WID_MODE_ACTIVE);
        wid_raise(w);
        return;
    }

    if (game_mouse_up(x, y, button)) {
        return;
    }
}

static Widp wid_key_down_handler (int32_t x, int32_t y)
{_
    Widp w {};

//CON("key down");
    w = wid_key_down_handler_at(wid_focus, x, y, true /* strict */);
    if (w) {
//CON("%s %d",to_string(w),__LINE__);
        return (w);
    }

    w = wid_key_down_handler_at(
                wid_get_top_parent(wid_focus), x, y, false /* strict */);
    if (w) {
//CON("%s %d",to_string(w),__LINE__);
        return (w);
    }

    w = wid_key_down_handler_at(wid_over, x, y, true /* strict */);
    if (w) {
//CON("%s %d",to_string(w),__LINE__);
        return (w);
    }

    w = wid_key_down_handler_at(
                wid_get_top_parent(wid_over), x, y, false /* strict */);
    if (w) {
//CON("%s %d",to_string(w),__LINE__);
        return (w);
    }

    for (auto iter = wid_top_level.rbegin();
         iter != wid_top_level.rend(); ++iter) {
        auto w = iter->second;

        if (wid_focus_locked &&
            (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
//CON("  focus is locked");
            continue;
        }

        w = wid_key_down_handler_at(w, x, y, true /* strict */);
        if (!w) {
            continue;
        }
//CON("     got top level strict handler%s",to_string(w));

        return (w);
    }

    for (auto iter = wid_top_level.rbegin();
         iter != wid_top_level.rend(); ++iter) {
        auto w = iter->second;

        if (wid_focus_locked &&
            (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
//CON("  focus is locked");
            continue;
        }

        w = wid_key_down_handler_at(w, x, y, false /* strict */);
        if (!w) {
            continue;
        }

//CON("     got top level loose handler%s",to_string(w));
        return (w);
    }

    return nullptr;
}

static Widp wid_key_up_handler (int32_t x, int32_t y)
{_
    Widp w {};

    w = wid_key_up_handler_at(wid_focus, x, y, true /* strict */);
    if (w) {
        return (w);
    }

    w = wid_key_up_handler_at(
                wid_get_top_parent(wid_focus), x, y, false /* strict */);
    if (w) {
        return (w);
    }

    w = wid_key_up_handler_at(wid_over, x, y, true /* strict */);
    if (w) {
        return (w);
    }

    w = wid_key_up_handler_at(
                wid_get_top_parent(wid_over), x, y, false /* strict */);
    if (w) {
        return (w);
    }

    for (auto iter = wid_top_level.rbegin();
         iter != wid_top_level.rend(); ++iter) {
        auto w = iter->second;

        if (wid_focus_locked &&
            (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
            continue;
        }

        w = wid_key_up_handler_at(w, x, y, true /* strict */);
        if (!w) {
            continue;
        }

        return (w);
    }

    for (auto iter = wid_top_level.rbegin();
         iter != wid_top_level.rend(); ++iter) {
        auto w = iter->second;

        if (wid_focus_locked &&
            (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
            continue;
        }

        w = wid_key_up_handler_at(w, x, y, false /* strict */);
        if (!w) {
            continue;
        }

        return (w);
    }

    return nullptr;
}

#define DEBUG_GL_BLEND
#ifdef DEBUG_GL_BLEND
int vals[] = {
    GL_ZERO,
    GL_ONE,
    GL_CONSTANT_ALPHA,
    GL_CONSTANT_COLOR,
    GL_DST_ALPHA,
    GL_DST_COLOR,
    GL_ONE_MINUS_CONSTANT_ALPHA,
    GL_ONE_MINUS_CONSTANT_ALPHA,
    GL_ONE_MINUS_CONSTANT_COLOR,
    GL_ONE_MINUS_DST_ALPHA,
    GL_ONE_MINUS_DST_ALPHA,
    GL_ONE_MINUS_DST_COLOR,
    GL_ONE_MINUS_SRC_ALPHA,
    GL_ONE_MINUS_SRC_COLOR,
    GL_SRC_ALPHA,
    GL_SRC_ALPHA_SATURATE,
    GL_SRC_COLOR,
};

std::string  vals_str[] = {
    "GL_ZERO",
    "GL_ONE",
    "GL_CONSTANT_ALPHA",
    "GL_CONSTANT_COLOR",
    "GL_DST_ALPHA",
    "GL_DST_COLOR",
    "GL_ONE_MINUS_CONSTANT_ALPHA",
    "GL_ONE_MINUS_CONSTANT_ALPHA",
    "GL_ONE_MINUS_CONSTANT_COLOR",
    "GL_ONE_MINUS_DST_ALPHA",
    "GL_ONE_MINUS_DST_ALPHA",
    "GL_ONE_MINUS_DST_COLOR",
    "GL_ONE_MINUS_SRC_ALPHA",
    "GL_ONE_MINUS_SRC_COLOR",
    "GL_SRC_ALPHA",
    "GL_SRC_ALPHA_SATURATE",
    "GL_SRC_COLOR",
};

int i1;
int i2;
#endif

#if 0
glBlendEquation(GL_FUNC_ADD);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
extern int vals[];
extern std::string vals_str[];
extern int i1;
extern int i2;
CON("%s %s", vals_str[i1].c_str(), vals_str[i2].c_str());
glBlendFunc(vals[i1], vals[i2]);
#endif

void wid_key_down (const struct SDL_KEYSYM *key, int32_t x, int32_t y)
{_
    Widp w {};

#ifdef DEBUG_GL_BLEND
if (wid_event_to_char(key) == '+') {
    usleep(50);
    i1 ++;
    if (i1 >= (int)ARRAY_SIZE(vals)) {
        i1 = 0;
        i2 ++;
        if (i2 >= (int)ARRAY_SIZE(vals)) {
            i2 = 0;
            DIE("wrapped");
        }
    }
    return;
}

if (wid_event_to_char(key) == '-') {
    usleep(50);
    i1 --;
    if (i1 < 0) {
        i1 = (int)ARRAY_SIZE(vals);
        i2 --;
        if (i2 < 0) {
            i2 = (int)ARRAY_SIZE(vals);
        }
    }
    return;
}
#endif

    if (wid_focus &&
        !wid_is_hidden(wid_focus) &&
        (wid_focus->on_key_down)) {

        if ((wid_focus->on_key_down)(wid_focus, key)) {
            //
            // Do not raise, gets in the way of popups the callback creates.
            //
            return;
        }

        w = wid_focus;

        goto try_parent;
    }

    w = wid_key_down_handler(x, y);
    if (!w) {
        //
        // If no-one handles it, feed it to the default handler, the console.
        //
        wid_receive_unhandled_input(key);
        return;
    }

    if ((w->on_key_down)(w, key)) {
        //
        // Do not raise, gets in the way of popups the callback creates.
        //
//CON("wid did not handle");
        return;
    }

try_parent:
    w = w->parent;

    //
    // Ripple the key event to the parent so global things like pressing
    // escape can do things.
    //
    while (w) {
        if (w->on_key_down) {
            if ((w->on_key_down)(w, key)) {
                //
                // Do not raise, gets in the way of popups the callback
                // creates.
                //
                return;
            }
        }

        w = w->parent;
    }

    //
    // If no-one handles it, feed it to the default handler, the console.
    //
    wid_receive_unhandled_input(key);
}

void wid_key_up (const struct SDL_KEYSYM *key, int32_t x, int32_t y)
{_
    Widp w {};

    if (wid_focus &&
        !wid_is_hidden(wid_focus) &&
        (wid_focus->on_key_up)) {

        if ((wid_focus->on_key_up)(wid_focus, key)) {
            wid_set_mode(wid_focus, WID_MODE_ACTIVE);

            //
            // Do not raise, gets in the way of popups the callback creates.
            //
            return;
        }

        w = wid_focus;

        goto try_parent;
    }

    w = wid_key_up_handler(x, y);
    if (!w) {
        //
        // If no-one handles it, drop it. We only hand key down to the
        // console.
        //
        return;
    }

    if ((w->on_key_up)(w, key)) {
        wid_set_mode(w, WID_MODE_ACTIVE);

        //
        // Do not raise, gets in the way of popups the callback creates.
        //
        return;
    }

try_parent:
    w = w->parent;

    //
    // Ripple the key event to the parent so global things like pressing
    // escape can do things.
    //
    while (w) {
        if (w->on_key_up) {
            if ((w->on_key_up)(w, key)) {
                wid_set_mode(w, WID_MODE_ACTIVE);

                //
                // Do not raise, gets in the way of popups the callback
                // creates.
                //
                return;
            }
        }

        w = w->parent;
    }
}

//
// Get the onscreen co-ords of the widget, clipped to the parent.
//
void wid_get_abs_coords (Widp w,
                         int32_t *tlx,
                         int32_t *tly,
                         int32_t *brx,
                         int32_t *bry)
{_
    Widp p {};

    *tlx = wid_get_tl_x(w);
    *tly = wid_get_tl_y(w);
    *brx = wid_get_br_x(w);
    *bry = wid_get_br_y(w);
if(w->debug) {
    CON("%d,%d %d,%d", *tlx, *tly, *brx, *bry);
}

    p = w->parent;
    if (p) {
        *tlx += p->offset.x;
        *tly += p->offset.y;
        *brx += p->offset.x;
        *bry += p->offset.y;
if(w->debug) {
    CON("  %d,%d %d,%d", *tlx, *tly, *brx, *bry);
}
    }

    while (p) {
        int32_t ptlx = wid_get_tl_x(p);
        int32_t ptly = wid_get_tl_y(p);
        int32_t pbrx = wid_get_br_x(p);
        int32_t pbry = wid_get_br_y(p);

        if (p->parent) {
            ptlx += p->parent->offset.x;
            ptly += p->parent->offset.y;
            pbrx += p->parent->offset.x;
            pbry += p->parent->offset.y;
        }

        if (ptlx > *tlx) {
            *tlx = ptlx;
        }

        if (ptly > *tly) {
            *tly = ptly;
        }

        if (pbrx < *brx) {
            *brx = pbrx;
        }

        if (pbry < *bry) {
            *bry = pbry;
        }

if(w->debug) {
    CON("    %d,%d %d,%d", *tlx, *tly, *brx, *bry);
}
        p = p->parent;
    }

    w->abs_tl.x = *tlx;
    w->abs_tl.y = *tly;
    w->abs_br.x = *brx;
    w->abs_br.y = *bry;
}

//
// Get the onscreen co-ords of the widget, clipped to the parent.
//
void wid_get_abs (Widp w, int32_t *x, int32_t *y)
{_
    int32_t tlx;
    int32_t tly;
    int32_t brx;
    int32_t bry;

    wid_get_abs_coords(w, &tlx, &tly, &brx, &bry);

    *x = (tlx + brx) / 2;
    *y = (tly + bry) / 2;
}

void wid_get_pct (Widp w, double *px, double *py)
{_
    int32_t x;
    int32_t y;

    wid_get_abs(w, &x, &y);

    *px = (double)x / (double)ASCII_WIDTH;
    *py = (double)y / (double)ASCII_HEIGHT;
}

//
// Finish off a widgets move.
//
void wid_move_end (Widp w)
{_
    while (w->moving) {
        wid_move_dequeue(w);
    }
}

//
// Display one wid and its children
//
static void wid_display (Widp w,
                        uint8_t disable_scissor,
                        uint8_t *updated_scissors,
                        int clip)
{_
    int32_t clip_height = 0;
    int32_t clip_width = 0;
    uint8_t hidden;
    uint8_t always_hidden;
    int32_t owidth;
    int32_t oheight;
    int32_t otlx;
    int32_t otly;
    int32_t obrx;
    int32_t obry;
    int32_t tlx;
    int32_t tly;
    int32_t brx;
    int32_t bry;
    Widp p {};

    //
    // Bounding box for drawing the wid. Co-ords are negative as we
    // flipped the screen
    //
    tlx = w->abs_tl.x;
    tly = w->abs_tl.y;
    brx = w->abs_br.x;
    bry = w->abs_br.y;

    //
    // If we're clipped out of existence! then nothing to draw. This can
    // be outside the bounds of a widget or if at the top level, off screeen.
    //
    if (clip) {
        clip_width = brx - tlx;
        if (clip_width < 0) {
            return;
        }

        clip_height = bry - tly;
        if (clip_height < 0) {
            return;
        }
    }

    hidden = wid_is_hidden(w);
    always_hidden = wid_is_always_hidden(w);

    if (always_hidden) {
        //
        // Always render. Not hidden yet.
        //
        return;
    } else if (hidden) {
        //
        // Hidden or parent is hidden.
        //
        return;
    }

    //
    // Record the original pre clip sizes for text centering.
    //
    otlx = wid_get_tl_x(w);
    otly = wid_get_tl_y(w);
    obrx = wid_get_br_x(w);
    obry = wid_get_br_y(w);

    p = w->parent;
    if (p) {
        otlx += p->offset.x;
        otly += p->offset.y;
        obrx += p->offset.x;
        obry += p->offset.y;
    }

    //
    // Inclusive width
    //
    owidth = obrx - otlx + 1;
    oheight = obry - otly + 1;

    //
    // If this widget was active and the time has elapsed, make it normal.
    //
    if (wid_get_mode(w) == WID_MODE_ACTIVE) {
        if ((wid_time - w->timestamp_last_mode_change) > 250) {
            wid_set_mode(w, WID_MODE_NORMAL);
        }
    }

    //
    // Draw the wid frame
    //
    color col_text = wid_get_color(w, WID_COLOR_TEXT);

    //
    // If inputting text, show a cursor.
    //
    std::wstring text;

    if (wid_get_show_cursor(w)) {
        text = wid_get_text_with_cursor(w);
    } else {
        text = wid_get_text(w);
    }

    if (w->disable_scissors) {
        disable_scissor = true;
    }

    //
    // Should be no need for scissors if you do not have any children
    // or are not the top level wid.
    //
    if (!disable_scissor) {
#if 0
    //
    // Why would we not always want scissors on?
    //
    if (!w->children_display_sorted.empty() || !w->parent || w->show_cursor) {
#endif
            //
            // Tell the parent we are doing scissors so they can re-do
            // their own scissors.
            //
            if (updated_scissors) {
                *updated_scissors = true;
            }

            wid_set_scissors(tlx, tly, brx, bry);
#if 0
        }
#endif
    }

    auto width = wid_get_width(w);
    auto height = wid_get_height(w);
    Tilep bg_tile = wid_get_bg_tile(w);
    Tilep fg_tile = wid_get_fg_tile(w);

    point tl;
    point br;

    tl.x = otlx;
    tl.y = otly;
    br.x = otlx + width;
    br.y = otly + height;

    box_args w_box_args = {
        .x              = tl.x,
        .y              = tl.y,
        .width          = (br.x - tl.x),
        .height         = (br.y - tl.y),
    };

    if (w == wid_over) {
        w_box_args.over = true;
        w_box_args.col_text = get(w->cfg, WID_MODE_OVER).colors[WID_COLOR_TEXT];
        w_box_args.col_bg   = get(w->cfg, WID_MODE_OVER).colors[WID_COLOR_BG];
    } else {
        w_box_args.col_text = get(w->cfg, WID_MODE_NORMAL).colors[WID_COLOR_TEXT];
        w_box_args.col_bg   = get(w->cfg, WID_MODE_NORMAL).colors[WID_COLOR_BG];
    }

    if (w->square) {
        ascii_put_box(w_box_args, w->style, bg_tile, fg_tile, L"");
    } else {
        // shape none
    }

    {
        for (auto x = tl.x; x <= br.x; x++) {
            if (unlikely(!ascii_x_ok(x))) {
                continue;
            }
            for (auto y = tl.y; y <= br.y; y++) {
                if (unlikely(!ascii_y_ok(y))) {
                    continue;
                }
                set(wid_on_screen_at, x, y, w);
            }
        }
    }

    if (!text.empty()) {
        int32_t x, y;
        int32_t xpc, ypc;
        int32_t width, height;

        //
        // Manually specified text position.
        //
        width = ascii_strlen(text);
        height = 0;

        if (wid_get_text_pos(w, &xpc, &ypc)) {
            x = (owidth * xpc) - ((int32_t)width / 2) + otlx;
            y = (oheight * ypc) - ((int32_t)height / 2) + otly;
        } else {
            //
            // Position the text
            //
            if (((int)width > owidth) && w->show_cursor) {
                //
                // If the text is too big, center it on the cursor.
                //
                x = ((owidth - (int32_t)width) / 2) + otlx;

                uint32_t c_width = (width / (double)text.length());

                x -= (w->cursor - (text.length() / 2)) * c_width;
            } else if (wid_get_text_lhs(w)) {
                x = otlx;
            } else if (wid_get_text_centerx(w)) {
                x = ((owidth - (int32_t)width) / 2) + otlx;
            } else if (wid_get_text_rhs(w)) {
                x = obrx - (int32_t)width;
            } else {
                x = ((owidth - (int32_t)width) / 2) + otlx;
            }

            if (wid_get_text_top(w)) {
                y = otly;
            } else if (wid_get_text_centery(w)) {
                y = ((oheight - (int32_t)height) / 2) + otly;
            } else if (wid_get_text_bot(w)) {
                y = obry - (int32_t)height;
            } else {
                y = ((oheight - (int32_t)height) / 2) + otly;
            }
        }

        ascii_putf__(x, y, col_text, COLOR_NONE, text);
    }


    for (auto iter = w->children_display_sorted.begin();
        iter != w->children_display_sorted.end(); ++iter) {

        auto child = iter->second;

        uint8_t child_updated_scissors = false;

        wid_display(child, disable_scissor, &child_updated_scissors, clip);

        //
        // Need to re-enforce the parent's scissors if the child did
        // their own bit of scissoring?
        //
        if (!disable_scissor && child_updated_scissors) {
            wid_set_scissors(
                tlx,
                tly,
                brx,
                bry);
        }
    }
}

//
// Do stuff for all widgets.
//
void wid_move_all (void)
{_
    if (wid_top_level3.empty()) {
        return;
    }

    uint32_t N = wid_top_level3.size();
    Widp w {};
    Widp wids[N];
    uint32_t n = 0;

    for (auto iter : wid_top_level3) {
        auto w = iter.second;
        wids[n] = w;
        n++;
    }

    while (n--) {
        w = wids[n];

        double x;
        double y;

        if (wid_time >= w->timestamp_moving_end) {

            wid_move_dequeue(w);

            //
            // If nothing else in the move queue, we're dine.
            //
            if (!w->moving) {
                continue;
            }
        }

        double time_step =
            (double)(wid_time - w->timestamp_moving_begin) /
            (double)(w->timestamp_moving_end - w->timestamp_moving_begin);

        x = (time_step * (double)(w->moving_end.x - w->moving_start.x)) +
            w->moving_start.x;
        y = (time_step * (double)(w->moving_end.y - w->moving_start.y)) +
            w->moving_start.y;

        wid_move_to_abs(w, x, y);
    }
}

//
// Delayed destroy?
//
static void wid_gc (Widp w)
{_
    WID_DBG(w, "gc");

    if (w->being_destroyed) {
        wid_destroy_immediate(w);
        return;
    }

    if (w->destroy_when && (wid_time >= w->destroy_when)) {
        wid_destroy(&w);
    }
}

//
// Do stuff for all widgets.
//
void wid_gc_all (void)
{_
    std::vector<Widp> to_gc;

    for (;;) {
        if (!wid_top_level4.size()) {
            return;
        }
        auto i = wid_top_level4.begin();
        auto w = i->second;

        wid_gc(w);
    }
}

//
// Do stuff for all widgets.
//
void wid_tick_all (void)
{_
//    wid_time = time_get_time_ms_cached();
    if (!game->config.sdl_delay) {
        wid_time += 100/1;
    } else {
        wid_time += 100/game->config.sdl_delay;
    }

    std::list<Widp> work;
    for (auto iter : wid_top_level5) {
        auto w = iter.second;
        work.push_back(w);
    }

    for (auto w : work) {
        if (!w->on_tick) {
            ERR("wid on ticker tree, but no callback set");
        }

        (w->on_tick)(w);
    }
}

static int saved_mouse_x;
static int saved_mouse_y;

void wid_mouse_hide (int value)
{_
    int visible = !value;

    if (visible != wid_mouse_visible) {
        wid_mouse_visible = visible;
        if (visible) {
            sdl_mouse_warp(saved_mouse_x, saved_mouse_y);
        } else {
            saved_mouse_x = mouse_x;
            saved_mouse_y = mouse_y;
        }
    }
}

void wid_mouse_warp (Widp w)
{_
    int32_t tlx, tly, brx, bry;

    wid_get_abs_coords(w, &tlx, &tly, &brx, &bry);

    int32_t x = (tlx + brx) / 2.0;
    int32_t y = (tly + bry) / 2.0;

    sdl_mouse_warp(x, y);
}

void wid_mouse_move (Widp w)
{_
    int32_t tlx, tly, brx, bry;

    wid_get_abs_coords(w, &tlx, &tly, &brx, &bry);

    int32_t x = (tlx + brx) / 2.0;
    int32_t y = (tly + bry) / 2.0;

    saved_mouse_x = mouse_x;
    saved_mouse_y = mouse_y;

    mouse_x = x;
    mouse_y = y;
}

//
// Display all widgets
//
void wid_display_all (void)
{_
    blit_fbo_bind(FBO_WID);
    glClear(GL_COLOR_BUFFER_BIT);
    glcolor(WHITE);

    wid_tick_all();

    wid_move_all();

    wid_on_screen_at = {};

    for (auto iter = wid_top_level.begin();
        iter != wid_top_level.end(); ++iter) {

        auto w = iter->second;

        if (wid_is_hidden(w)) {
            continue;
        }

        wid_display(w,
                    false /* disable_scissors */,
                    0 /* updated_scissors */,
                    true);
    }

    ascii_clear_scissors();

#ifdef DEBUG_WID_FOCUS
    if (wid_focus) {
        ascii_putf(0, ASCII_HEIGHT-4, WHITE, GRAY, L"focus %s", to_string(wid_focus).c_str());
    }
    if (wid_over) {
        ascii_putf(0, ASCII_HEIGHT-3, WHITE, GRAY, L"over  %s", to_string(wid_over).c_str());
    }
#endif

    //
    // FPS counter.
    //
    if (game->config.fps_counter) {
        ascii_putf(ASCII_WIDTH - 7, ASCII_HEIGHT - 1, GREEN, BLACK,
                   L"%u FPS", game->fps_value);
    }

    ascii_display();

    blit_fbo_unbind();
}

uint8_t wid_is_hidden (Widp w)
{_
    if (!w) {
        return (false);
    }

    if (w->hidden) {
        return (true);
    }

    while (w->parent) {
        w = w->parent;

        if (w->hidden) {
            return (true);
        }
    }

    return (false);
}

uint8_t wid_is_always_hidden (Widp w)
{_
    if (w->always_hidden) {
        return (true);
    }

    return (false);
}

void wid_move_to_pct (Widp w, double x, double y)
{_
    if (!w->parent) {
        x *= (double)ASCII_WIDTH;
        y *= (double)ASCII_HEIGHT;
    } else {
        x *= wid_get_width(w->parent);
        y *= wid_get_height(w->parent);
    }

    double dx = x - wid_get_tl_x(w);
    double dy = y - wid_get_tl_y(w);

    wid_move_delta(w, dx, dy);
}

void wid_move_to_abs (Widp w, int32_t x, int32_t y)
{_
    int32_t dx = x - wid_get_tl_x(w);
    int32_t dy = y - wid_get_tl_y(w);

    wid_move_delta(w, dx, dy);
}

void wid_move_to_pct_centered (Widp w, double x, double y)
{_
    if (!w->parent) {
        x *= (double)ASCII_WIDTH;
        y *= (double)ASCII_HEIGHT;
    } else {
        x *= wid_get_width(w->parent);
        y *= wid_get_height(w->parent);
    }

    double dx = x - wid_get_tl_x(w);
    double dy = y - wid_get_tl_y(w);

    dx -= (wid_get_br_x(w) - wid_get_tl_x(w))/2;
    dy -= (wid_get_br_y(w) - wid_get_tl_y(w))/2;

    wid_move_delta(w, dx, dy);
}

void wid_move_to_abs_centered (Widp w, int32_t x, int32_t y)
{_
    int32_t dx = x - wid_get_tl_x(w);
    int32_t dy = y - wid_get_tl_y(w);

    dx -= (wid_get_br_x(w) - wid_get_tl_x(w))/2;
    dy -= (wid_get_br_y(w) - wid_get_tl_y(w))/2;

    wid_move_delta(w, dx, dy);
}

static void wid_move_enqueue (Widp w,
                            int32_t moving_start_x,
                            int32_t moving_start_y,
                            int32_t moving_end_x,
                            int32_t moving_end_y,
                            uint32_t ms)
{_
    if (w->moving) {
        //
        // Smoother character moves with this.
        //
#if 1
        w->moving_start.x = moving_start_x;
        w->moving_start.y = moving_start_y;
        w->moving_end.x = moving_end_x;
        w->moving_end.y = moving_end_y;
        w->timestamp_moving_begin = wid_time;
        w->timestamp_moving_end = wid_time + ms;
        return;
#else
        //
        // If this is not a widget with a thing, then just zoom it to the
        // destination. We don't need queues.
        //
        Thingp t = wid_get_thing(w);
        if (!t) {
            w->moving_end.x = moving_end_x;
            w->moving_end.y = moving_end_y;
            w->timestamp_moving_begin = wid_time;
            w->timestamp_moving_end = wid_time + ms;
            return;
        }

        if (w->moving == WID_MAX_MOVE_QUEUE) {
            Thingp t = wid_get_thing(w);

            ERR("too many moves queued up for widget %s",
                to_string(w));

            if (t) {
                log(t, "Too many moves queued up");
            }

#ifdef DEBUG_WID_MOVE
            int i;
            CON("    [-] to %f,%f in %d",
                w->moving_end.x, w->moving_end.y,
                w->timestamp_moving_end - wid_time);

            for (i = 0; i < w->moving - 1; i++) {
                wid_move_t *c = &w->move[i];

                CON("    [%d] to %f,%f in %d", i,
                    c->moving_end.x, c->moving_end.y,
                    c->timestamp_moving_end - wid_time);
            }
#endif
        }

        wid_move_t *c = &w->move[w->moving - 1];

        c->timestamp_moving_end = wid_time + ms;
        c->moving_end.x = moving_end_x;
        c->moving_end.y = moving_end_y;
#endif
    } else {
        w->moving_start.x = moving_start_x;
        w->moving_start.y = moving_start_y;
        w->moving_end.x = moving_end_x;
        w->moving_end.y = moving_end_y;
        w->timestamp_moving_begin = wid_time;
        w->timestamp_moving_end = wid_time + ms;

        wid_tree3_moving_wids_insert(w);
    }

    w->moving++;
}

static void wid_move_dequeue (Widp w)
{_
    if (!w->moving) {
        return;
    }

    wid_move_to_abs(w, w->moving_end.x, w->moving_end.y);

    w->moving--;
    if (!w->moving) {
        wid_tree3_moving_wids_remove(w);
        return;
    }

    wid_move_t *c = &getref(w->move, 0);

    w->moving_start.x = w->moving_end.x;
    w->moving_start.y = w->moving_end.y;
    w->moving_end.x = c->moving_endx;
    w->moving_end.y = c->moving_endy;
    w->timestamp_moving_begin = wid_time;
    w->timestamp_moving_end = c->timestamp_moving_end;

    uint8_t i;
    for (i = 0; i < w->moving; i++) {
        if (i < WID_MAX_MOVE_QUEUE - 1) {
            wid_move_t *c = &getref(w->move, i);
            memcpy(c, c+1, sizeof(*c));
        }
    }

    {
        wid_move_t *c = &getref(w->move, i);
        memset(c, 0, sizeof(*c));
    }
}

void wid_move_to_pct_in (Widp w, double x, double y, uint32_t ms)
{_
    if (!w->parent) {
        x *= (double)ASCII_WIDTH;
        y *= (double)ASCII_HEIGHT;
    } else {
        x *= wid_get_width(w->parent);
        y *= wid_get_height(w->parent);
    }

    //
    // Child postion is relative from the parent.
    //
    Widp p = w->parent;
    if (p) {
        x += wid_get_tl_x(p);
        y += wid_get_tl_y(p);
    }

    wid_move_enqueue(w, wid_get_tl_x(w), wid_get_tl_y(w), x, y, ms);
}

void wid_move_to_abs_in (Widp w, int32_t x, int32_t y, uint32_t ms)
{_
    wid_move_enqueue(w, wid_get_tl_x(w), wid_get_tl_y(w), x, y, ms);
}

void wid_move_delta_in (Widp w, int32_t dx, int32_t dy, uint32_t ms)
{_
    int32_t x = wid_get_tl_x(w);
    int32_t y = wid_get_tl_y(w);

    wid_move_enqueue(w, x, y, x + dx, y + dy, ms);
}

void wid_move_to_pct_centered_in (Widp w, double x, double y, uint32_t ms)
{_
    if (!w->parent) {
        x *= (double)ASCII_WIDTH;
        y *= (double)ASCII_HEIGHT;
    } else {
        x *= wid_get_width(w->parent);
        y *= wid_get_height(w->parent);
    }

    //
    // Child postion is relative from the parent.
    //
    Widp p = w->parent;
    if (p) {
        x += wid_get_tl_x(p);
        y += wid_get_tl_y(p);
    }

    x -= (wid_get_br_x(w) - wid_get_tl_x(w))/2;
    y -= (wid_get_br_y(w) - wid_get_tl_y(w))/2;

    wid_move_enqueue(w, wid_get_tl_x(w), wid_get_tl_y(w), x, y, ms);
}

void wid_move_to_abs_centered_in (Widp w, int32_t x, int32_t y, uint32_t ms)
{_
    x -= (wid_get_br_x(w) - wid_get_tl_x(w))/2;
    y -= (wid_get_br_y(w) - wid_get_tl_y(w))/2;

    wid_move_enqueue(w, wid_get_tl_x(w), wid_get_tl_y(w), x, y, ms);
}

void wid_move_to_centered_in (Widp w, int32_t x, int32_t y, uint32_t ms)
{_
    wid_move_enqueue(w, wid_get_tl_x(w), wid_get_tl_y(w), x, y, ms);
}

uint8_t wid_is_moving (Widp w)
{
    if (w->moving) {
        return (true);
    }

    return (false);
}

void wid_set_style (Widp w, int style)
{
    w->style = style;
}
