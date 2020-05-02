//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_ascii.h"
#include "my_time.h"
#include "my_wid_console.h"
#include "stb_image_write.h"

extern bool game_needs_restart;

static int sdl_get_mouse(void);
static void sdl_screenshot_(void);
static int sdl_do_screenshot;
static void config_gfx_update(void);

int TILES_ACROSS;
int TILES_DOWN;

uint8_t sdl_main_loop_running;
uint8_t sdl_shift_held;
uint8_t sdl_init_video;
uint32_t mouse_down;
timestamp_t mouse_down_when;
int mouse_x;
int mouse_y;
int wheel_x;
int wheel_y;
int mouse_tick;

int sdl_left_fire;
int sdl_right_fire;

int sdl_joy1_right;
int sdl_joy1_left;
int sdl_joy1_down;
int sdl_joy1_up;

int sdl_joy2_right;
int sdl_joy2_left;
int sdl_joy2_down;
int sdl_joy2_up;

std::array<uint8_t, SDL_MAX_BUTTONS> sdl_joy_buttons;

static SDL_Joystick *joy;
static SDL_Haptic *haptic;

int *sdl_joy_axes;
int sdl_joy_deadzone = 8000;
int joy_index;
int joy_naxes;
int joy_buttons;
int joy_balls;

SDL_Window *window; // Our window handle
SDL_GLContext context; // Our opengl context handle

SDL_Scancode sdl_grabbed_scancode;
bool sdl_grab_next_key;
on_sdl_key_grab_t on_sdl_key_grab;

void sdl_fini (void)
{_
#ifdef ENABLE_ASCII_MOUSE
    SDL_ShowCursor(0);
    SDL_ShowCursor(1);
#endif

    if (sdl_init_video) {
        sdl_init_video = 0;
        SDL_VideoQuit();
    }

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);

    SDL_Quit();
}

static inline void sdl_list_video_size (void)
{_
    int i;

    for (i = 0; i < SDL_GetNumDisplayModes(0); ++i) {
        SDL_DisplayMode mode;
        SDL_GetDisplayMode(0, i, &mode);
        LOG("- SDL video            : %dx%d available, ratio %f",
            mode.w, mode.h,
            (float)mode.w / (float)mode.h);
    }
}

void sdl_joy_rumble (float strength, timestamp_t ms)
{_
    if (!haptic) {
        return;
    }

    SDL_HapticRumblePlay(haptic, strength, ms);
}

static void sdl_init_rumble (void)
{_
    LOG("SDL init rumble:");

    if (!haptic) {
        haptic = SDL_HapticOpenFromJoystick(joy);
        if (!haptic) {
            LOG("- Couldn't initialize SDL rumble: %s", SDL_GetError());
            SDL_ClearError();
            return;
        }
    }

    if (!SDL_HapticRumbleSupported(haptic)) {
        LOG("- No SDL rumble support: %s", SDL_GetError());
        SDL_ClearError();
        return;
    }

    if (SDL_HapticRumbleInit(haptic) != 0) {
        LOG("- SDL rumble nit failed: %s", SDL_GetError());
        SDL_ClearError();
        return;
    }

    LOG("- Opened Haptic for joy index %d", joy_index);
}

static void sdl_init_joystick (void)
{_
    LOG("SDL init input:");

    SDL_GameController *controller = NULL;

    LOG("- Init game controleer");
    SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER);

    LOG("- Init haptic");
    SDL_InitSubSystem(SDL_INIT_HAPTIC);

    LOG("- Init joystick");
    SDL_InitSubSystem(SDL_INIT_JOYSTICK);

    joy_index = 0;
    for (joy_index = 0;
         joy_index < SDL_NumJoysticks(); ++joy_index) {

        if (SDL_IsGameController(joy_index)) {
            controller = SDL_GameControllerOpen(joy_index);
            if (controller) {
                LOG("- Found gamecontroller");
                break;
            } else {
                WARN("Could not open gamecontroller %i: %s",
                    joy_index, SDL_GetError());
                SDL_ClearError();
            }
        }
    }

    if (!controller) {
        LOG("- No found gamecontroller");
        return;
    }

    joy = SDL_JoystickOpen(joy_index);
    if (joy) {
        LOG("- Opened Joystick %d", joy_index);
        LOG("- Name: %s", SDL_JoystickNameForIndex(0));
        LOG("- Number of Axes: %d", SDL_JoystickNumAxes(joy));
        LOG("- Number of Buttons: %d", SDL_JoystickNumButtons(joy));
        LOG("- Number of Balls: %d", SDL_JoystickNumBalls(joy));

        joy_naxes = SDL_JoystickNumAxes(joy);
        joy_buttons = SDL_JoystickNumButtons(joy);
        joy_balls = SDL_JoystickNumBalls(joy);
    } else {
        WARN("Couldn't open Joystick 0");
    }
}

uint8_t sdl_init (void)
{_
    gl_ext_init();

    int video_width;
    int video_height;
    int value;

    LOG("INIT: SDL version: %u.%u", SDL_MAJOR_VERSION, SDL_MINOR_VERSION);

    LOG("INIT: SDL_Init");
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        SDL_MSG_BOX("SDL_Init failed %s", SDL_GetError());
        ERR("SDL_Init failed %s", SDL_GetError());
    }

    LOG("INIT: SDL_VideoInit");
    if (SDL_VideoInit(0) != 0) {
        SDL_MSG_BOX("SDL_VideoInit failed %s", SDL_GetError());
        ERR("SDL_VideoInit failed %s", SDL_GetError());
    }

    int x = 0;
    if (x) {
        sdl_init_joystick();
        sdl_init_rumble();
    }

    sdl_init_video = 1;

    sdl_list_video_size();

    //
    // If we have a saved setting, use that.
    //
    if (game->config.outer_pix_width && game->config.outer_pix_height) {
        video_width = game->config.outer_pix_width;
        video_height = game->config.outer_pix_height;
    } else {
        //
        // Else guess.
        //
        SDL_DisplayMode mode;
        SDL_GetCurrentDisplayMode(0, &mode);

        game->config.outer_pix_width = mode.w;
        game->config.outer_pix_height = mode.h;

        video_width = game->config.outer_pix_width;
        video_height = game->config.outer_pix_height;
    }

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    //
    // Don't use this. It seemed to mess up graphics on FireGL.
    //
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

#ifdef ENABLE_GENERATE_TTF
    return (true);
#endif

    uint32_t video_flags;

    LOG("INIT: SDL_WINDOW_OPENGL");
    LOG("INIT: SDL_WINDOW_BORDERLESS");
    video_flags = SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS;

    if (game->config.fullscreen) {
        LOG("INIT: SDL_WINDOW_FULLSCREEN");
        video_flags |= SDL_WINDOW_FULLSCREEN;
    }

    if (game->config.allow_highdpi) {
        //
        // For a lo pixel game this makes no sense as the frame
        // buffers are really large and slows things down.
        //
        LOG("INIT: Calling SDL_GetDisplayDPI");
        float dpi;
        if (SDL_GetDisplayDPI(0, 0, &dpi, 0) == 0) {
            video_flags |= SDL_WINDOW_ALLOW_HIGHDPI;
            LOG("INIT: SDL_WINDOW_ALLOW_HIGHDPI");
        } else {
            ERR("INIT: Cannot enable high DPI");
        }
    }

    LOG("INIT: SDL_CreateWindow");
    window = SDL_CreateWindow("sph_sdl",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              video_width,
                              video_height,
                              video_flags);
    if (!window) {
        SDL_MSG_BOX("Couldn't set windowed display %ux%u: %s",
                    video_width, video_height,
                    SDL_GetError());

        ERR("Couldn't set windowed display %ux%u: %s",
            video_width, video_height,
            SDL_GetError());
    }

    if (video_flags & SDL_WINDOW_ALLOW_HIGHDPI) {
        SDL_GL_GetDrawableSize(window,
                               &game->config.outer_pix_width,
                               &game->config.outer_pix_height);
    } else {
        SDL_GetWindowSize(window,
                          &game->config.outer_pix_width,
                          &game->config.outer_pix_height);
    }

    LOG("INIT: SDL_GL_CreateContext (%dx%d)",
        game->config.outer_pix_width,
        game->config.outer_pix_height);

    context = SDL_GL_CreateContext(window);

    if (!context) {
        SDL_MSG_BOX("SDL_GL_CreateContext failed %s", SDL_GetError());
        SDL_ClearError();
        ERR("SDL_GL_CreateContext failed %s", SDL_GetError());
    }

    if (SDL_GL_MakeCurrent(window, context) < 0) {
        SDL_MSG_BOX("SDL_GL_MakeCurrent failed %s", SDL_GetError());
        SDL_ClearError();
        ERR("SDL_GL_MakeCurrent failed %s", SDL_GetError());
    }

    SDL_ClearError();

    glClearColor(0, 0, 0, 0);
    SDL_Delay(400); // avoids white flash on startup!
    glClear(GL_COLOR_BUFFER_BIT |
            GL_DEPTH_BUFFER_BIT |
            GL_ACCUM_BUFFER_BIT |
            GL_STENCIL_BUFFER_BIT);

    config_gfx_update();

    LOG("INIT: SDL_SetWindowTitle");
    SDL_SetWindowTitle(window, "sph_sdl");

    LOG("INIT: GL Vendor   : %s", glGetString(GL_VENDOR));
    LOG("INIT: GL Renderer : %s", glGetString(GL_RENDERER));
    LOG("INIT: GL Version  : %s", glGetString(GL_VERSION));
    DBG("INIT: GL Exts     : %s", glGetString(GL_EXTENSIONS));

    SDL_GL_GetAttribute(SDL_GL_RED_SIZE, &value);
    DBG("Red         : %d", value);

    SDL_GL_GetAttribute(SDL_GL_GREEN_SIZE, &value);
    DBG("Green       : %d", value);

    SDL_GL_GetAttribute(SDL_GL_BLUE_SIZE, &value);
    DBG("Blue        : %d", value);

    SDL_GL_GetAttribute(SDL_GL_DEPTH_SIZE, &value);
    DBG("Depth       : %d", value);

    SDL_GL_GetAttribute(SDL_GL_DOUBLEBUFFER, &value);
    DBG("Doub Buffer : %d", value);

    SDL_GL_GetAttribute(SDL_GL_ACCELERATED_VISUAL, &value);
    DBG("Hw Accel    : %d", value);

    DBG("Vsync       : %d", SDL_GL_GetSwapInterval());

    return (true);
}

static int sdl_filter_events (void *userdata, SDL_Event *event)
{_
    switch (event->type) {
        // This is important!  Queue it if we want to quit. */
        case SDL_QUIT:
            return (1);

        // Mouse and keyboard events go to threads */
        case SDL_MOUSEMOTION:
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
        case SDL_MOUSEWHEEL:
        case SDL_KEYDOWN:
        case SDL_KEYUP:
        case SDL_CONTROLLERDEVICEADDED:
        case SDL_CONTROLLERBUTTONDOWN:
        case SDL_CONTROLLERBUTTONUP:
        case SDL_CONTROLLERAXISMOTION:
        case SDL_JOYAXISMOTION:               // Joystick axis motion
        case SDL_JOYBALLMOTION:               // Joystick trackball motion
        case SDL_JOYHATMOTION:                // Joystick hat position change
        case SDL_JOYBUTTONDOWN:               // Joystick button pressed
        case SDL_JOYBUTTONUP:                 // Joystick button released
            return (1);

        // Drop all other events */
        default:
            return (0);
    }
}

static void sdl_event (SDL_Event * event)
{_
    SDL_KEYSYM *key;

    switch (event->type) {
    case SDL_KEYDOWN:
        if (sdl_grab_next_key) {
            CON("Keyboard: grabbed 0x%08X = %s / %s",
                event->key.keysym.sym,
                SDL_GetKeyName(event->key.keysym.sym),
                SDL_GetScancodeName(event->key.keysym.scancode));

            sdl_grab_next_key = false;
            sdl_grabbed_scancode = event->key.keysym.scancode;
            if (on_sdl_key_grab) {
                (*on_sdl_key_grab)(sdl_grabbed_scancode);
            }
            return;
        }

        DBG("Keyboard: key pressed keycode 0x%08X = %s",
            event->key.keysym.sym,
            SDL_GetKeyName(event->key.keysym.sym));

            key = &event->key.keysym;

            {
                static struct SDL_KEYSYM last;
                static timestamp_t last_time_for_key;

                //
                // SDL2 has no auto repeat.
                //
                if (!memcmp(&last, key, sizeof(*key))) {
                    if (!time_have_x_hundredths_passed_since(5, last_time_for_key)) {
                        return;
                    }
                    last_time_for_key = time_get_time_ms_cached();
                }
                last = *key;
            }

            wid_key_down(key, mouse_x, mouse_y);

            sdl_shift_held = (key->mod & KMOD_SHIFT) ? 1 : 0;
        break;

    case SDL_KEYUP:
        DBG("Keyboard: key released keycode 0x%08X = %s",
            event->key.keysym.sym,
            SDL_GetKeyName(event->key.keysym.sym));

            key = &event->key.keysym;

            wid_key_up(key, mouse_x, mouse_y);

            sdl_shift_held = (key->mod & KMOD_SHIFT) ? 1 : 0;
        break;

    case SDL_TEXTINPUT:
        DBG("Keyboard: text input \"%s\" in window %d",
            event->text.text, event->text.windowID);
        break;

    case SDL_MOUSEWHEEL: {
        DBG("Mouse: wheel scrolled %d in x and %d in y in window %d",
            event->wheel.x, event->wheel.y, event->wheel.windowID);

        sdl_get_mouse();

        static double accel = 1.0;

        {
            static timestamp_t ts;

            if (time_have_x_tenths_passed_since(5, ts)) {
                accel = 1.0;
            } else {
                accel *= ENABLE_WHEEL_SCROLL_SPEED_SCALE;

                if (accel > ENABLE_WHEEL_MAX_SCROLL_SPEED_SCALE) {
                    accel = ENABLE_WHEEL_MAX_SCROLL_SPEED_SCALE;
                }
            }

            ts = time_get_time_ms_cached();
        }

        wheel_x = event->wheel.x;
        wheel_y = event->wheel.y;

        wheel_x *= accel;
        wheel_y *= accel;

        //
        // Negative wheel x so side scrolls seem natural. Could just be
        // a dumb macos thing to ifdef?
        //
        wid_mouse_visible = 1;
        mouse_tick ++;
        wid_mouse_motion(mouse_x, mouse_y, 0, 0, -wheel_x, wheel_y);
        break;
    }

    case SDL_MOUSEMOTION:
        mouse_down = sdl_get_mouse();

        DBG("Mouse: moved to %d,%d (%d,%d) state %d",
            event->motion.x, event->motion.y,
            event->motion.xrel, event->motion.yrel, mouse_down);

        wid_mouse_visible = 1;
        mouse_tick ++;
        wid_mouse_motion(mouse_x, mouse_y,
                         event->motion.xrel, event->motion.yrel,
                         0, 0);
        break;

    case SDL_MOUSEBUTTONDOWN:
        mouse_down = sdl_get_mouse();
        mouse_down_when = time_get_time_ms_cached();

        DBG("Mouse DOWN: button %d pressed at %d,%d state %x",
            event->button.button, event->button.x, event->button.y,
            mouse_down);

        wid_mouse_visible = 1;

        wid_mouse_down(event->button.button, mouse_x, mouse_y);
        break;

    case SDL_MOUSEBUTTONUP:
        mouse_down = sdl_get_mouse();
        mouse_down_when = 0;

        DBG("Mouse UP: button %d released at %d,%d state %d",
            event->button.button, event->button.x, event->button.y,
            mouse_down);

        wid_mouse_up(event->button.button, mouse_x, mouse_y);
        break;

    case SDL_JOYAXISMOTION: {
        DBG("Joystick %d: axis %d moved by %d",
            event->jaxis.which, event->jaxis.axis, event->jaxis.value);

        int axis = event->jaxis.axis;
        int value = event->jaxis.value;

        if (!sdl_joy_axes) {
            sdl_joy_axes = (int*) myzalloc(sizeof(int) * joy_naxes, "joy axes");
        }

        sdl_joy_axes[axis] = value;

        sdl_left_fire = false;
        sdl_right_fire = false;

        if (sdl_joy_axes[2] > sdl_joy_deadzone) {
            DBG("left fire");
            sdl_left_fire = true;
            set(sdl_joy_buttons, SDL_JOY_BUTTON_LEFT_FIRE, (uint8_t)1);
        } else {
            set(sdl_joy_buttons, SDL_JOY_BUTTON_LEFT_FIRE, (uint8_t)0);
        }


        if (sdl_joy_axes[5] > sdl_joy_deadzone) {
            DBG("right fire");
            sdl_right_fire = true;
            set(sdl_joy_buttons, SDL_JOY_BUTTON_RIGHT_FIRE, (uint8_t)1);
        } else {
            set(sdl_joy_buttons, SDL_JOY_BUTTON_RIGHT_FIRE, (uint8_t)0);
        }

        if (sdl_right_fire || sdl_left_fire) {
            sdl_get_mouse();
            wid_joy_button(mouse_x, mouse_y);
        }

        break;
    }

    case SDL_JOYBALLMOTION:
        DBG("Joystick %d: ball %d moved by %d,%d",
            event->jball.which, event->jball.ball, event->jball.xrel,
            event->jball.yrel);
        break;

    case SDL_JOYHATMOTION:
        DBG("Joystick %d: hat %d moved to ", event->jhat.which,
            event->jhat.hat);

        switch (event->jhat.value) {
        case SDL_HAT_CENTERED:
            break;
        case SDL_HAT_UP:
            DBG("UP");
            sdl_joy2_up = true;
            break;
        case SDL_HAT_RIGHTUP:
            DBG("RIGHTUP");
            sdl_joy2_right = true;
            sdl_joy2_up = true;
            break;
        case SDL_HAT_RIGHT:
            DBG("RIGHT");
            sdl_joy2_right = true;
            break;
        case SDL_HAT_RIGHTDOWN:
            DBG("RIGHTDOWN");
            sdl_joy2_right = true;
            sdl_joy2_down = true;
            break;
        case SDL_HAT_DOWN:
            DBG("DOWN");
            sdl_joy2_down = true;
            break;
        case SDL_HAT_LEFTDOWN:
            DBG("LEFTDOWN");
            sdl_joy2_left = true;
            sdl_joy2_down = true;
            break;
        case SDL_HAT_LEFT:
            DBG("LEFT");
            sdl_joy2_left = true;
            break;
        case SDL_HAT_LEFTUP:
            sdl_joy2_left = true;
            sdl_joy2_up = true;
            DBG("LEFTUP");
            break;
        default:
            DBG("UNKNOWN");
            break;
        }
        break;

    case SDL_JOYBUTTONDOWN:
        DBG("Joystick %d: button %d pressed",
            event->jbutton.which, event->jbutton.button);
        set(sdl_joy_buttons, event->jbutton.button, (uint8_t)1);
        sdl_get_mouse();
        wid_joy_button(mouse_x, mouse_y);
        break;

    case SDL_JOYBUTTONUP:
        DBG("Joystick %d: button %d released",
            event->jbutton.which, event->jbutton.button);
        set(sdl_joy_buttons, event->jbutton.button, (uint8_t)0);
        break;

    case SDL_CLIPBOARDUPDATE:
        DBG("Clipboard updated");
        break;

    case SDL_QUIT: {
#ifdef ENABLE_ASCII_MOUSE
        SDL_ShowCursor(1);
#endif
        DIE("Quit requested");
    }

    case SDL_USEREVENT:
        DBG("User event %d", event->user.code);
        break;

    default:
        DBG("Unknown event %d", event->type);
        break;
    }
}

static int sdl_get_mouse (void)
{_
    if (!wid_mouse_visible) {
        return (0);
    }

    int x, y;
    int button = SDL_GetMouseState(&x, &y);

    if (!x && !y) {
        return (button);
    }

    mouse_x = x;
    mouse_y = y;

    return (button);
}

void sdl_mouse_center (void)
{_
    int x, y;

    x = game->config.outer_pix_width / 2;
    y = game->config.outer_pix_height / 2;

    sdl_mouse_warp(x, y);
}

void sdl_mouse_warp (int x, int y)
{_
    int border = 10;

    if (x <= 0) {
        x = border;
    } else if (x >= game->config.outer_pix_width - border) {
        x = game->config.outer_pix_width - border;
    }
    if (y <= 0) {
        y = border;
    } else if (y >= game->config.outer_pix_height - border) {
        y = game->config.outer_pix_height - border;
    }

    SDL_WarpMouseInWindow(window, x, y);

    mouse_x = x;
    mouse_y = y;
}

static void sdl_tick (void)
{_
    sdl_left_fire = false;
    sdl_left_fire = true;

    sdl_joy1_right = false;
    sdl_joy1_left = false;
    sdl_joy1_down = false;
    sdl_joy1_up = false;

    sdl_joy2_right = false;
    sdl_joy2_left = false;
    sdl_joy2_down = false;
    sdl_joy2_up = false;

    sdl_get_mouse();

    //
    // Right stick
    //
    if (sdl_joy_axes[3] > sdl_joy_deadzone) {
        DBG("right stick, right");
        sdl_joy1_right = true;

        incr(sdl_joy_buttons, SDL_JOY_BUTTON_RIGHT);
        wid_joy_button(mouse_x, mouse_y);
        decr(sdl_joy_buttons, SDL_JOY_BUTTON_RIGHT);
    }

    if (sdl_joy_axes[3] < -sdl_joy_deadzone) {
        DBG("right stick, left");
        sdl_joy1_left = true;

        incr(sdl_joy_buttons, SDL_JOY_BUTTON_LEFT);
        wid_joy_button(mouse_x, mouse_y);
        decr(sdl_joy_buttons, SDL_JOY_BUTTON_LEFT);
    }

    if (sdl_joy_axes[4] > sdl_joy_deadzone) {
        DBG("right stick, down");
        sdl_joy1_down = true;

        incr(sdl_joy_buttons, SDL_JOY_BUTTON_DOWN);
        wid_joy_button(mouse_x, mouse_y);
        decr(sdl_joy_buttons, SDL_JOY_BUTTON_DOWN);
    }

    if (sdl_joy_axes[4] < -sdl_joy_deadzone) {
        DBG("right stick, up");
        sdl_joy1_up = true;

        incr(sdl_joy_buttons, SDL_JOY_BUTTON_UP);
        wid_joy_button(mouse_x, mouse_y);
        decr(sdl_joy_buttons, SDL_JOY_BUTTON_UP);
    }

    //
    // Left stick
    //
    int mx = 0;
    int my = 0;

    if (sdl_joy_axes[0] > sdl_joy_deadzone) {
        DBG("left stick, right");
        sdl_joy2_right = true;
        mx = 1;
    }

    if (sdl_joy_axes[0] < -sdl_joy_deadzone) {
        DBG("left stick, left");
        sdl_joy2_left = true;
        mx = -1;
    }

    if (sdl_joy_axes[1] > sdl_joy_deadzone) {
        DBG("left stick, down");
        sdl_joy2_down = true;
        my = 1;
    }

    if (sdl_joy_axes[1] < -sdl_joy_deadzone) {
        DBG("left stick, up");
        sdl_joy2_up = true;
        my = -1;
    }

    static double accel = 1.0;
    static timestamp_t ts;

    if (time_have_x_tenths_passed_since(5, ts)) {
        accel = 1.0;
    }

    if ((mx != 0) || (my != 0)) {
        ts = time_get_time_ms_cached();

        accel *= ENABLE_JOY_SCROLL_SPEED_SCALE;

        if (accel > ENABLE_JOY_MAX_SCROLL_SPEED_SCALE) {
            accel = ENABLE_JOY_MAX_SCROLL_SPEED_SCALE;
        }

        double x = mouse_x + ((double)mx * accel);
        double y = mouse_y + ((double)my * accel);

        if (x < 0) {
            x = 0;
        }

        if (y < 0) {
            y = 0;
        }

        if (x > game->config.outer_pix_width - 1) {
            x = game->config.outer_pix_width - 1;
        }

        if (y > game->config.outer_pix_height - 1) {
            y = game->config.outer_pix_height - 1;
        }

        if (wid_mouse_visible) {
            sdl_mouse_warp(x, y);
        }
    }
}

void sdl_exit (void)
{_
    if (!sdl_main_loop_running) {
        return;
    }

    LOG("finishing: SDL main loop is exiting...");

#ifdef ENABLE_ASCII_MOUSE
    SDL_ShowCursor(1);
#endif

    sdl_main_loop_running = false;
}

//
// User has entered a command, run it
//
uint8_t config_fps_counter_set (tokens_t *tokens, void *context)
{_
    char *s = tokens->args[2];

    if (!s || (*s == '\0')) {
        game->config.fps_counter = true;
        CON("FSP counter enabled (default)");
    } else {
        game->config.fps_counter = strtol(s, 0, 10) ? 1 : 0;
        if (game->config.fps_counter) {
            CON("FPS counter enabled");
        } else {
            CON("FPS counter disabled");
        }
    }

    return (true);
}

//
// User has entered a command, run it
//
void config_gfx_inverted_toggle (void)
{_
    if (!game->config.gfx_inverted) {
        game->config.gfx_inverted = true;
        CON("gfx inverted enabled");
    } else {
        game->config.gfx_inverted = false;
        CON("gfx inverted disabled");
    }
}

//
// User has entered a command, run it
//
uint8_t config_gfx_inverted_set (tokens_t *tokens, void *context)
{_
    char *s = tokens->args[3];

    if (!s || (*s == '\0')) {
        game->config.gfx_inverted = true;
        CON("gfx inverted enabled (default)");
    } else {
        int val = strtol(s, 0, 10) ? 1 : 0;
        game->config.gfx_inverted = val;
        if (game->config.gfx_inverted) {
            CON("gfx inverted enabled");
        } else {
            CON("gfx inverted disabled");
        }
    }

    return (true);
}

//
// User has entered a command, run it
//
uint8_t config_gfx_vsync_enable (tokens_t *tokens, void *context)
{_
    char *s = tokens->args[2];

    if (!s || (*s == '\0')) {
        game->config.gfx_vsync_enable = true;
    } else {
        game->config.gfx_vsync_enable = strtol(s, 0, 10) ? 1 : 0;
    }

    if (game->config.gfx_vsync_enable) {
        CON("USERCFG: Vsync enabled");
        SDL_GL_SetSwapInterval(1);
    } else {
        CON("USERCFG: Vsync disabled");
        SDL_GL_SetSwapInterval(0);
    }

    return (true);
}

void config_gfx_vsync_update (void)
{_
    if (game->config.gfx_vsync_enable) {
        SDL_GL_SetSwapInterval(1);
    } else {
        SDL_GL_SetSwapInterval(0);
    }
}

//
// User has entered a command, run it
//
uint8_t config_debug_mode (tokens_t *tokens, void *context)
{_
    char *s = tokens->args[2];

    if (!s || (*s == '\0')) {
        game->config.debug_mode = true;
    } else {
        game->config.debug_mode = strtol(s, 0, 10) ? 1 : 0;
    }

    if (game->config.debug_mode) {
        CON("USERCFG: Debug mode enabled");
    } else {
        CON("USERCFG: Debug mode disabled");
    }

    return (true);
}

//
// User has entered a command, run it
//
uint8_t config_errored (tokens_t *tokens, void *context)
{_
    errored = false;
    CON("USERCFG: Errored mode cleared");
    return (true);
}

void config_update_all (void)
{
    config_gfx_update();
    config_gfx_vsync_update();
}

//
// User has entered a command, run it
//
uint8_t sdl_user_exit (tokens_t *tokens, void *context)
{_
    sdl_exit();

    return (true);
}

//
// Main loop
//
void sdl_loop (void)
{_
    SDL_Event events[10];
    int found;
    int i;
    uint16_t frames = 0;

    sdl_mouse_center();
    SDL_SetEventFilter(sdl_filter_events, 0);

    glEnable(GL_TEXTURE_2D);

    //
    // Wait for events
    //
    int timestamp_then = time_get_time_ms();
    int timestamp_then2 = timestamp_then;

    sdl_main_loop_running = true;

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

    if (game->config.gfx_vsync_enable) {
        SDL_GL_SetSwapInterval(1);
    } else {
        SDL_GL_SetSwapInterval(0);
    }

    gl_enter_2d_mode();

#ifdef ENABLE_ASCII_MOUSE
    SDL_ShowCursor(0);
#endif

    for (;/*ever*/;) {
        frames++;

        //
        // Reset joystick handling before we poll and update.
        //
        if (unlikely(sdl_joy_axes != nullptr)) {
            sdl_tick();
        }

        //fluid_tick();

        static bool old_errored;
        if (errored) {
            if (errored != old_errored) {
                ERR("An error occurred. Check the logs above.");
                ERR("To continue try 'clear errored'");
                if (wid_console_window && !(wid_console_window->visible)) {
                    wid_visible(wid_console_window);
                    wid_raise(wid_console_window);
                    wid_set_focus(wid_console_window);
                    wid_focus_lock(wid_console_window);
                }
            }
        }
        old_errored = errored;

        gl_enter_2d_mode(game->config.inner_pix_width,
                         game->config.inner_pix_height);

        glcolor(WHITE);
        game->display();
        blit_fbo_unbind();

        gl_enter_2d_mode(game->config.outer_pix_width,
                         game->config.outer_pix_height);

        //
        // Do processing of some things, like reading the keyboard or doing
        // stuff with widgets only occasionally if we do not need to.
        //
        int timestamp_now = time_update_time_milli();

        if (unlikely(timestamp_now - timestamp_then > 10)) {
            //
            // Give up some CPU to allow events to arrive and time for the GPU
            // to process the above.
            //
            timestamp_then = timestamp_now;

            //
            // Clean up dead widgets.
            //
            wid_gc_all();

            //
            // Read events
            //
            SDL_PumpEvents();

            wheel_x = 0;
            wheel_y = 0;

            found = SDL_PeepEvents(events, ARRAY_SIZE(events), SDL_GETEVENT,
                                   SDL_QUIT, SDL_LASTEVENT);

            for (i = 0; i < found; ++i) {
                sdl_event(&events[i]);
            }

            if (unlikely(!sdl_main_loop_running)) {
                break;
            }

            //
            // Display UI.
            //
            wid_display_all();
        }

        blit_fbo_bind(FBO_FINAL);
        glClear(GL_COLOR_BUFFER_BIT);
        glcolor(WHITE);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_COLOR);
        glBlendFunc(GL_ONE, GL_ZERO);
        blit_fbo_outer(FBO_MAP);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        blit_fbo_outer(FBO_WID);
        blit_fbo_unbind();

        glBlendFunc(GL_ONE, GL_ZERO);
        if (game->config.gfx_inverted) {
            glLogicOp(GL_COPY_INVERTED);
            glEnable(GL_COLOR_LOGIC_OP);
        }
        blit_fbo_outer(FBO_FINAL);
        if (game->config.gfx_inverted) {
            glLogicOp(GL_COPY);
            glDisable(GL_COLOR_LOGIC_OP);
        }

        //
        // FPS counter.
        //
        {
            //
            // Very occasional.
            //
            if (unlikely(timestamp_now - timestamp_then2 >= 1000)) {
                timestamp_then2 = timestamp_now;

                if (game->config.fps_counter) {
                    //
                    // Update FPS counter.
                    //
                    game->fps_value = frames;
                    frames = 0;
                }

                if (unlikely(sdl_do_screenshot)) {
                    sdl_do_screenshot = 0;
                    sdl_screenshot_();
                }
            }
        }

        SDL_Delay(game->config.sdl_delay);

        //
        // Flip
        //
        SDL_GL_SwapWindow(window);

        //
        // Optimization to only bother checking pointers if some kind of
        // allocation occurred.
        //
        extern bool ptr_check_some_pointers_changed;
        ptr_check_some_pointers_changed = false;

        //
        // Config change?
        //
        if (unlikely(game_needs_restart)) {
            break;
        }
    }

    gl_leave_2d_mode();

#ifdef ENABLE_ASCII_MOUSE
    SDL_ShowCursor(1);
#endif
}

void sdl_screenshot (void)
{_
    sdl_do_screenshot = 1;
}

static void sdl_screenshot_ (void)
{_
    int w = game->config.inner_pix_width;
    int h = game->config.inner_pix_height;

    static int count;
    count++;

    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glReadBuffer(GL_BACK_LEFT);

    std::vector<uint8_t> pixels(3 * w * h);
    glReadPixels(0, 0, w, h, GL_RGB, GL_UNSIGNED_BYTE, pixels.data());

    for(int line = 0; line != h/2; ++line) {
        std::swap_ranges(pixels.begin() + 3 * w * line,
                         pixels.begin() + 3 * w * (line+1),
                         pixels.begin() + 3 * w * (h-line-1));
    }

    int components = 3;

    char *png = dynprintf("screenshot.%d.png", count);
    stbi_write_png(png, w, h, components, pixels.data(), 3 * w);
    MINICON("Screenshot: %s", png);
    myfree(png);

    char *tga = dynprintf("screenshot.%d.tga", count);
    stbi_write_tga(tga, w, h, components, pixels.data());
    MINICON("Screenshot: %s", tga);
    myfree(tga);
}

void sdl_flush_display (void)
{
    glEnable(GL_TEXTURE_2D);
    gl_enter_2d_mode();
    wid_display_all();
    if (game->config.gfx_inverted) {
        glLogicOp(GL_COPY_INVERTED);
        glEnable(GL_COLOR_LOGIC_OP);
    }
    blit_fbo(FBO_WID);
    if (game->config.gfx_inverted) {
        glLogicOp(GL_COPY);
        glDisable(GL_COLOR_LOGIC_OP);
    }
    SDL_GL_SwapWindow(window);
}

void config_gfx_update (void)
{
    if (!game->config.gfx_zoom) {
        game->config.gfx_zoom = 1;
    }

    game->config.one_pixel_width = 1;
    game->config.one_pixel_height = 1;

    game->config.scale_pix_width = game->config.gfx_zoom;
    game->config.scale_pix_height = game->config.gfx_zoom;

    game->config.inner_pix_width =
        game->config.outer_pix_width / game->config.scale_pix_width;
    game->config.inner_pix_height =
        game->config.outer_pix_height / game->config.scale_pix_height;

    float tiles_across = game->config.inner_pix_width / TILE_WIDTH;
    float tiles_down = game->config.inner_pix_height / TILE_HEIGHT;

    TILES_ACROSS = (int)tiles_across;
    TILES_DOWN = (int)tiles_down;

    game->config.tile_pix_width =
        game->config.one_pixel_width * TILE_WIDTH;
    game->config.tile_pix_height =
        game->config.one_pixel_height * TILE_HEIGHT;

    game->config.video_w_h_ratio =
        (double)game->config.inner_pix_width /
        (double)game->config.inner_pix_height;

    game->config.tile_pixel_width =
        game->config.inner_pix_width / TILES_ACROSS;
    game->config.tile_pixel_height =
        game->config.inner_pix_height / TILES_DOWN;

    CON("INIT: Graphics zoom          : %d", game->config.gfx_zoom);
    CON("INIT: - outer    pix size    : %dx%d", game->config.outer_pix_width,
                                                game->config.outer_pix_height);
    CON("INIT: - inner    pix size    : %dx%d", game->config.inner_pix_width,
                                                game->config.inner_pix_height);

    game->config.ascii_gl_width = FONT_WIDTH;
    game->config.ascii_gl_height = FONT_HEIGHT;

    ASCII_WIDTH  = (int)(game->config.outer_pix_width / FONT_WIDTH);
    ASCII_HEIGHT = (int)(game->config.outer_pix_height / FONT_HEIGHT);

    if (ASCII_WIDTH >= ASCII_WIDTH_MAX) {
        LOG("INIT: Exceeded console hit max width  : %d", ASCII_WIDTH);
        ASCII_WIDTH = ASCII_WIDTH_MAX;
        game->config.ascii_gl_width =
            (float)game->config.outer_pix_width / (float)ASCII_WIDTH;
    }

    if (ASCII_HEIGHT >= ASCII_HEIGHT_MAX) {
        LOG("INIT: Exceeded console hit max height : %d", ASCII_HEIGHT);
        ASCII_HEIGHT = ASCII_HEIGHT_MAX;
        game->config.ascii_gl_height =
            (float)game->config.outer_pix_height / (float)ASCII_HEIGHT;
    }

    CON("INIT: - console size         : %dx%d", ASCII_WIDTH, ASCII_HEIGHT);
    CON("INIT: - width to height ratio: %f", game->config.video_w_h_ratio);
}
