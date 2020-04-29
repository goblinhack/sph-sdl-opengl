//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_main.h"
#include "SPHSolver.h"
extern SPHSolver *sph;

void Game::init (void)
{_
    if (sph) {
        delete sph;
    }
    sph = new SPHSolver();
    config_select();
}
