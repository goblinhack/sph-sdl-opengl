//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"

void Game::display (void)
{_
    if (paused) {
        return;
    }
    extern void sph_display(void);
    sph_display();
}
