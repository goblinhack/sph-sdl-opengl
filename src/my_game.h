#pragma once
#ifndef _MY_GAME_H_
#define _MY_GAME_H_

#include "my_main.h"
#include "my_point.h"

typedef struct Particle_ {
public:
    bool in_use;
    fpoint at;
    spoint attach_at;
    fpoint velocity;
    fpoint force;
    float mass;
    float density;
    float pressure;
} Particle;

class Game {
public:
    Game (void) {}
    Game (std::string appdata);
    void config_select(void);
    void display(void);
    void fini(void);
    void reset(void);
    void init(void);
    void quit_select(void);
    void help_select(void);

    std::string        appdata;
    Config             config;
    uint32_t           fps_value = {};
    bool               paused {};

    //
    // Particle size in pixels
    //
#define PARTICLE_SLOTS   10
#define PARTICLE_RADIUS  8
#define PARTICLE_MAX     5000
#define PARTICLES_WIDTH  1000
#define PARTICLES_HEIGHT 1000

    //
    // All particles
    //
    std::array<
      std::array<
        std::array<uint16_t, PARTICLE_SLOTS>, PARTICLES_HEIGHT>, PARTICLES_WIDTH>
          all_particle_ids_at {};

    std::array<Particle, PARTICLE_MAX> particles {};
    int num_particles {};

    Particle* new_particle(const fpoint &at);
    void free_particle(Particle* p);
    void attach_particle(Particle* p);
    void detach_particle(Particle* p);
    void move_particle(Particle* p, fpoint to);
    bool is_oob(const Particle *p);
    bool is_oob(const fpoint &p);
};

extern spoint point_to_grid(const fpoint &p);
extern spoint particle_to_grid(const Particle* p);

extern class Game *game;

extern uint8_t game_mouse_down(int32_t x, int32_t y, uint32_t button);
extern uint8_t game_mouse_up(int32_t x, int32_t y, uint32_t button);
#endif
