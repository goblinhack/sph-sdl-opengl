//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"

void Game::init (void)
{_
    game = this;
    extern void sph_init(void);
    sph_init();
    config_select();
}
