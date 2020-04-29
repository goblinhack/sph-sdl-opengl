```diff
 ____  ____  ____     ____  ____  _         ___  ____  _____ _   _  ____ _
/ ___||  _ \|  _ \   / ___||  _ \| |       / _ \|  _ \| ____| \ | |/ ___| |
\___ \| |_) | | | |  \___ \| | | | |      | | | | |_) |  _| |  \| | |  _| |
 ___) |  __/| |_| |   ___) | |_| | |___   | |_| |  __/| |___| |\  | |_| | |___
|____/|_|   |____/   |____/|____/|_____|   \___/|_|   |_____|_| \_|\____|_____|

```
A simple (unoptimized) 2D implementation of the SPH (Smoothed Particle Hydrodynamics) method for water simulation in C++. Inspired by [this code](https://github.com/tizian/SPH-Water-Simulation)
Uses SDL + opengl, no shaders. The guts of the simulation is in src/sph.cpp. The rest of the code is fluff for creating the UI and rendering and can be ignored.

![Alt text](screenshot.1.png?raw=true "")
![Alt text](screenshot.2.png?raw=true "")
![Alt text](screenshot.3.png?raw=true "")
![Alt text](screenshot.4.png?raw=true "")

![#1589F0](https://placehold.it/15/1589F0/000000?text=+) To build:

    On Linux:
        sh ./RUNME

    On MacOS:
        sh ./RUNME

    On Windows: (install msys2 first via https://www.msys2.org/)
        sh ./RUNME.windows.mingw64

If it doesn't build, just email goblinhack@gmail.com for help
