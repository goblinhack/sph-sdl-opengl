//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_main.h"
#include "SPHSolver.h"
#include "Constants.h"

extern SPHSolver *sph;

void Game::display (void)
{_
    if (paused) {
        return;
    }
    sph->update(0.0001, Visualization::Water);
    sph->render(Visualization::Water);
}
