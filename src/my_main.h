//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#ifndef _MY_MAIN_H_
#define _MY_MAIN_H_

//
// It crashes? Enable this for more info
//
#define DEBUG_CRASH
#define ENABLE_CRASH_HANDLER       // Intercept SEGV

//
// Commonly changed settings
//
#ifdef DEBUG_CRASH
#define ENABLE_TRACING             // Function tracing
#define ENABLE_ASSERT              // DIE on errors, like array bound check
#define ENABLE_PTRCHECK            // Check validity of pointers too
#define ENABLE_PTRCHECK_HISTORY 2  // Per pointer history
#define ENABLE_PTRCHECK_LEAK
#undef  ENABLE_PTRCHECK_DEBUG      // Debug ptrcheck itself
#define ENABLE_THING_ID_LOGS       // Thing ID allocations
#endif

#define ENABLE_INVERTED_GFX        // For vision impaired
#undef  ENABLE_FULL_TIMESTAMPS     // Full timestamps with date in logs

//
// Settings to override compiler errors
//
// `error' to treat this diagnostic as an error,
// `warning' to treat it like a warning (even if -Werror is in effect)
// `ignored' if the diagnostic is to be ignored
//
// #pragma GCC diagnostic warning "-Wformat"
// #pragma GCC diagnostic error "-Wformat"
// #pragma GCC diagnostic ignored "-Wformat"
//
#ifdef __clang__
/*code specific to clang compiler*/
#elif __GNUC__
/*code for GNU C compiler */
#elif _MSC_VER
/*usually has the version number in _MSC_VER*/
/*code specific to MSVC compiler*/
#elif __BORLANDC__
/*code specific to borland compilers*/
#elif __MINGW32__
/*code specific to mingw compilers*/
#endif




// %d--> for int
//
// %u--> for unsigned int
//
// %ld--> for long int
//
// %lu--> for unsigned long int
//
// %lld--> for long long int
//
// %llu--> for unsigned long long int
//
// "%zu" workaround for moronic windows
// https://stackoverflow.com/questions/44382862/how-to-printf-a-size-t-without-warning-in-mingw-w64-gcc-7-1
//
#ifdef _WIN32
#  ifdef _WIN64
#    ifdef __MINGW32__
#      define PRI_SIZET "llu"
#    else
#      define PRI_SIZET PRIu64
#    endif
#  else
#    define PRI_SIZET PRIu32
#  endif
#else
#  define PRI_SIZET "zu"
#endif

//
// UI debugging
//
#undef  ENABLE_WID_DEBUG
#undef  DEBUG_WID_FOCUS
#ifdef  ENABLE_WID_DEBUG
#define WID_FULL_LOGNAME
#endif

#undef  ENABLE_ASCII_MOUSE
#define ENABLE_TILE_COLLISION_CHECKING

////////////////////////////////////////////////////////////////////////////
// Tiles
////////////////////////////////////////////////////////////////////////////

//
// Per screen
//
extern int TILES_ACROSS;
extern int TILES_DOWN;

//
// Tile size of the player
//
#define TILE_WIDTH       16
#define TILE_HEIGHT      16

//
// Largest tile for collisions
//
#define MAX_TILE_WIDTH   64
#define MAX_TILE_HEIGHT  64

//
// Dimentions of the fixed text on screen
//
#define ASCII_WIDTH_MAX  80
#define ASCII_HEIGHT_MAX ASCII_WIDTH_MAX

////////////////////////////////////////////////////////////////////////////
// Particles
////////////////////////////////////////////////////////////////////////////
//
// Particle size in pixels
//
#define PARTICLE_SLOTS   100
#define PARTICLE_RADIUS  8
#define PARTICLE_MAX     200
#define PARTICLES_WIDTH  (MAP_WIDTH * (TILE_WIDTH / PARTICLE_RADIUS))
#define PARTICLES_HEIGHT (MAP_HEIGHT * (TILE_HEIGHT / PARTICLE_RADIUS))

////////////////////////////////////////////////////////////////////////////
// UI button styles
////////////////////////////////////////////////////////////////////////////

#define WID_STYLE_OUTLINE           0
#define WID_STYLE_GREEN             1
#define WID_STYLE_RED               2
#define WID_STYLE_NORMAL            3
#define WID_STYLE_DARK              4
#define WID_STYLE_NONE              5
#define WID_STYLE_MAX               6

#define WID_POPUP_WIDTH_NORMAL      24
#define WID_POPUP_WIDTH_WIDE        36
#define WID_POPUP_WIDTH_WIDEST      48

////////////////////////////////////////////////////////////////////////////
// UI console
////////////////////////////////////////////////////////////////////////////

#define CONSOLE_CURSOR_COLOR        GRAY
#define CONSOLE_CURSOR_OTHER_COLOR  WHITE
#define CONSOLE_TEXT_COLOR          GRAY
#define CONSOLE_INPUT_COLOR         ORANGE
#define CONSOLE_WIDTH               120
#define CONSOLE_HEIGHT              200
#define CONSOLE_KEY1                '`'
#define CONSOLE_KEY2                '~'
#define CONSOLE_KEY3                '\\'

////////////////////////////////////////////////////////////////////////////
// UI mini console
////////////////////////////////////////////////////////////////////////////

//
// Minicon
//
#define MINICON_TEXT_COLOR          RESET_TEXT_COLOR
#define MINICON_WIDTH               ASCII_WIDTH
#define MINICON_HEIGHT              20 // scrollbar limit
#define MINICON_VIS_HEIGHT          5
#define MINICON_VIS_WIDTH           MINICON_WIDTH

////////////////////////////////////////////////////////////////////////////
// UI status bar and inventory
////////////////////////////////////////////////////////////////////////////

//
// How many graduations on e.g. the health bar
//
#define STATUSBAR_ICON_STEPS        12
#define HEALTH_ICON_STEPS           5

#define ACTIONBAR_HEIGHT            3
#define ACTIONBAR_WIDTH             3
#define ACTIONBAR_TOT_WIDTH         (10 * ACTIONBAR_WIDTH)
#define ACTIONBAR_TL_X              (ASCII_WIDTH / 2 - (ACTIONBAR_TOT_WIDTH / 2))
#define ACTIONBAR_TL_Y              (ASCII_HEIGHT - 4)
#define ACTIONBAR_BR_X              ((ASCII_WIDTH / 2 + (ACTIONBAR_TOT_WIDTH / 2)) - 1)
#define ACTIONBAR_BR_Y              (ASCII_HEIGHT - 1)
#define INVENTORY_ITEM_WIDTH        2
#define INVENTORY_ITEM_HEIGHT       2
#define INVENTORY_DOWN              5
#define INVENTORY_ACROSS            6

////////////////////////////////////////////////////////////////////////////
// UI text
////////////////////////////////////////////////////////////////////////////

//
// Default text color
//
#define RESET_TEXT_COLOR            GRAY
#define RESET_TEXT_COLOR_STR        "gray"

//
// Popups
//
#define POPUP_TEXT_COLOR            RESET_TEXT_COLOR

//
// Fonts
//
#define FIXED_FONT                  "data/ttf/lowresfont.tga"
#define FONT_WIDTH                  20
#define FONT_HEIGHT                 24

#define TTF_GLYPH_MIN               ' '
//
// Do we really need all these glyphs? It's slow to generate
//
// #define TTF_GLYPH_MAX            0xffff // SDL can only do 2b fonts
#define TTF_GLYPH_MAX               559 /* As we use UNICODE_0x22e */

#define TTF_GLYPH_PER_ROW           60
#define TTF_CURSOR_CHAR             127

////////////////////////////////////////////////////////////////////////////
// UI mouse
////////////////////////////////////////////////////////////////////////////

//
// How much the wheel mouse moves.
//
#define ENABLE_WHEEL_SCROLL_SPEED_SCALE         1.0
#define ENABLE_WHEEL_MAX_SCROLL_SPEED_SCALE     10

#define ENABLE_JOY_SCROLL_SPEED_SCALE           1.0
#define ENABLE_JOY_MAX_SCROLL_SPEED_SCALE       1.5

////////////////////////////////////////////////////////////////////////////
// Random numbers
////////////////////////////////////////////////////////////////////////////

//
// Enhanced random number generator.
//
#include "my_pcg_basic.h"

#define myrand()                     pcg32_random()
#define mysrand(a)                   pcg32_srandom(a,a)

#define random_range(a, b)           (pcg32_boundedrand(b - a) + a)
#define random_range_inclusive(a, b) (pcg32_boundedrand(b - a + 1) + a)

////////////////////////////////////////////////////////////////////////////
// Misc
////////////////////////////////////////////////////////////////////////////

//
// Simple array routines
//
#define ARRAY_SIZE(_array_) (sizeof(_array_)/sizeof(_array_[0]))

#define FOR_ALL_IN_ARRAY(iterator, _array_)                                 \
    __typeof__(&_array_[0]) iterator;                                       \
    for ((iterator) = (_array_);                                            \
         (iterator) < ((_array_) + ARRAY_SIZE(_array_));                    \
         (iterator)++)

//
// GCC extensions
//
#define likely(x)       __builtin_expect((x),1)
#define unlikely(x)     __builtin_expect((x),0)

//
// Types
//
#ifndef _BITS_STDINT_INTN_H
#ifndef __int8_t_defined
#ifndef _INT8_T
#define _INT8_T
typedef signed char          int8_t;
#endif //_INT8_T

#ifndef _INT16_T
#define _INT16_T
typedef short                int16_t;
#endif // _INT16_T

#ifndef _INT32_T
#define _INT32_T
typedef int                  int32_t;
#endif // _INT32_T

#ifndef _INT64_T
#define _INT64_T
typedef long long            int64_t;
#endif // _INT64_T
#endif

#ifndef _UINT8_T
#define _UINT8_T
typedef unsigned char        uint8_t;
#endif //_UINT8_T

#ifndef _UINT16_T
#define _UINT16_T
typedef unsigned short       uint16_t;
#endif // _UINT16_T

#ifndef _UINT32_T
#define _UINT32_T
typedef unsigned int         uint32_t;
#endif // _UINT32_T

#ifndef _UINT64_T
#define _UINT64_T
typedef unsigned long long   uint64_t;
#endif // _UINT64_T
#endif

//
// msys functions seem to accept either / or \ so we don't need to worry.
//
#ifdef _WIN32
#define PATHSEP ";"
#define DIR_SEP "\\"
#define DIR_SEP_CHAR '\\'
#else
#define PATHSEP ":"
#define DIR_SEP "/"
#define DIR_SEP_CHAR '/'
#endif

void CROAK(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));
void DYING(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));
#define DIE(args...)                                                          \
    _                                                                         \
    DYING("Died at %s:%s():%u", __FILE__, __FUNCTION__, __LINE__);            \
    CROAK(args);                                                              \
    exit(1);

#ifdef ENABLE_ASSERT
#define ASSERT(x)                                                             \
    if (!(x)) {                                                               \
        DIE("Failed assert:" #x);                                             \
    }
#else
#define ASSERT(x)
#endif

//
// Code tracing
// https://github.com/goblinhack/callstack
//
#include "my_callstack.h"

//
// Array bounds checks
// https://github.com/goblinhack/c-plus-plus-array-bounds-checker
//
#include "my_array_bounds_check.h"
#include "my_vector_bounds_check.h"

//
// Nested crash detection.
//
extern uint8_t croaked;
extern uint8_t errored;

//
// Serious errors
//
void WARN(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));

//
// Also serious. UI msg box popups, in game and pre game with SDL
//
void SDL_MSG_BOX(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));
void GAME_UI_MSG_BOX(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));

//
// Add _ so we get a traceback element.
//
void myerr(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));
#define ERR _ myerr

//
// Normal logging
//
void LOG(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));

//
// Consoles
//
void CON(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));
void MINICON(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));
void CON(const wchar_t *fmt, ...);
void MINICON(const wchar_t *fmt, ...);
void con(const wchar_t *fmt);
void minicon(const wchar_t *fmt);

//
// Enabled only when debug_mode is on
//
void DBG(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));

//
// main.c
//
#define MY_STDOUT (LOG_STDOUT ? LOG_STDOUT : stdout)
#define MY_STDERR (LOG_STDERR ? LOG_STDERR : stderr)
extern FILE *LOG_STDOUT;
extern FILE *LOG_STDERR;
extern char *EXEC_FULL_PATH_AND_NAME;
extern char *EXEC_DIR;
extern char *DATA_PATH;
extern char *GFX_PATH;
extern char *TTF_PATH;
extern uint8_t quitting;
extern void quit(void);
extern void restart(void);
extern void die(void);
extern bool opt_new_game;
extern bool opt_debug_mode;

#include "my_ptrcheck.h"

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
    uint32_t           gfx_zoom                     = 1;
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
