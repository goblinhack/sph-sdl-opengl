//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_main.h"
#include "SPHSolver.h"

class Game *game;
bool game_needs_restart;

SPHSolver sph = SPHSolver();

Game::Game (std::string appdata)
{_
    this->appdata = appdata;
}

uint8_t
game_mouse_down (int32_t x, int32_t y, uint32_t button)
{_
    if (!game) {
        return (false);
    }

    return (false);
}

uint8_t
game_mouse_up (int32_t x, int32_t y, uint32_t button)
{_
    if (!game) {
        return (false);
    }

    return (false);
}
