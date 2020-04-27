//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#ifndef _MY_GAME_H_
#define _MY_GAME_H_

#include "my_sdl.h"
#include "my_callstack.h"
#include <string>

typedef class Config_ {
public:
    bool               fps_counter                  = true;
#ifdef ENABLE_INVERTED_GFX
    bool               gfx_inverted                 = true;
#else
    bool               gfx_inverted                 = false;
#endif
    bool               gfx_minimap                  = true;
    bool               gfx_show_hidden              = false;
    bool               gfx_lights                   = true;
    uint32_t           gfx_zoom                     = 4;
    bool               gfx_vsync_enable             = true;
    bool               debug_mode                   = false;
    bool               fullscreen                   = false;
    bool               allow_highdpi                = false;
    //
    // This is the window size.
    //
    int32_t            outer_pix_width              = {};
    int32_t            outer_pix_height             = {};
    //
    // This is the virtual size of the game within the above window.
    //
    int32_t            inner_pix_width              = {};
    int32_t            inner_pix_height             = {};
    //
    // The ratiou of outer to inner
    //
    int32_t            scale_pix_width              = {};
    int32_t            scale_pix_height             = {};
    double             video_w_h_ratio              = {};
    double             tile_pix_width               = {};
    double             tile_pix_height              = {};
    double             one_pixel_width              = {};
    double             one_pixel_height             = {};
    double             ascii_gl_width               = {};
    double             ascii_gl_height              = {};
    double             tile_pixel_width             = {};
    double             tile_pixel_height            = {};
    uint32_t           sdl_delay                    = 1;
    uint32_t           key_map_up                   = {SDL_SCANCODE_UP};
    uint32_t           key_map_down                 = {SDL_SCANCODE_DOWN};
    uint32_t           key_map_left                 = {SDL_SCANCODE_LEFT};
    uint32_t           key_map_right                = {SDL_SCANCODE_RIGHT};
    uint32_t           key_move_up                  = {SDL_SCANCODE_W};
    uint32_t           key_move_down                = {SDL_SCANCODE_S};
    uint32_t           key_move_left                = {SDL_SCANCODE_A};
    uint32_t           key_move_right               = {SDL_SCANCODE_D};
    uint32_t           key_todo1                    = {SDL_SCANCODE_Z};
    uint32_t           key_todo2                    = {SDL_SCANCODE_X};
    uint32_t           key_help                     = {SDL_SCANCODE_H};
    uint32_t           key_quit                     = {SDL_SCANCODE_Q};

    void fini(void);
    void dump(std::string prefix, std::ostream &out);
    void log(std::string prefix);
} Config;

class Game {
public:
    Game (void) {}
    Game (std::string appdata);
    void config_keyboard_select(void);
    void display(void);
    void fini(void);
    void init(void);
    void quit_select(void);
    void help_select(void);

    std::string        appdata;
    Config             config;
    uint32_t           fps_value = {};
};

extern class Game *game;

extern uint8_t game_mouse_down(int32_t x, int32_t y, uint32_t button);
extern uint8_t game_mouse_up(int32_t x, int32_t y, uint32_t button);

#endif
