//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_gl.h"
#include "my_tile.h"
#include "my_tex.h"
#include "my_pixel.h"
#include "my_size.h"
#include "my_string.h"

std::map<std::string, class Tile* > all_tiles;
std::vector<class Tile* > all_tiles_array;

static uint8_t tile_init_done;

uint8_t tile_init (void)
{_
    tile_init_done = true;

    return (true);
}

void tile_fini (void)
{_
    if (tile_init_done) {
        tile_init_done = false;
    }

    for (auto t : all_tiles) {
        verify(t.second);
        delete t.second;
    }

    all_tiles.clear();
    all_tiles_array.clear();
}

Tile::Tile (const class Tile *tile)
{
    newptr(this, "Tile copy");

    pix_width = tile->pix_width;
    pix_height = tile->pix_height;
    pct_width = tile->pct_width;
    pct_height = tile->pct_height;
    x1 = tile->x1;
    y1 = tile->y1;
    x2 = tile->x2;
    y2 = tile->y2;
    ox1 = tile->ox1;
    oy1 = tile->oy1;
    ox2 = tile->ox2;
    oy2 = tile->oy2;
    px1 = tile->px1;
    py1 = tile->py1;
    px2 = tile->px2;
    py2 = tile->py2;
    set_gl_binding(tile->gl_binding());
    tex = tile->tex;
    std::copy(mbegin(tile->pix), mend(tile->pix), mbegin(pix));
    delay_ms = tile->delay_ms;
    dir = tile->dir;
    is_join_node = tile->is_join_node;
    is_join_left = tile->is_join_left;
    is_join_bot = tile->is_join_bot;
    is_join_right = tile->is_join_right;
    is_join_top = tile->is_join_top;
    is_join_horiz = tile->is_join_horiz;
    is_join_vert = tile->is_join_vert;
    is_join_l90 = tile->is_join_l90;
    is_join_l = tile->is_join_l;
    is_join_l270 = tile->is_join_l270;
    is_join_l180 = tile->is_join_l180;
    is_join_t270 = tile->is_join_t270;
    is_join_t180 = tile->is_join_t180;
    is_join_t90 = tile->is_join_t90;
    is_join_t = tile->is_join_t;
    is_join_x = tile->is_join_x;
    is_moving = tile->is_moving;
    is_yyy5 = tile->is_yyy5;
    is_yyy6 = tile->is_yyy6;
    is_yyy7 = tile->is_yyy7;
    is_yyy8 = tile->is_yyy8;
    is_yyy9 = tile->is_yyy9;
    is_yyy10 = tile->is_yyy10;
    is_hp_25_percent = tile->is_hp_25_percent;
    is_hp_50_percent = tile->is_hp_50_percent;
    is_hp_75_percent = tile->is_hp_75_percent;
    is_hp_100_percent = tile->is_hp_100_percent;
    gfx_outline_index_offset = tile->gfx_outline_index_offset;
    is_sleeping = tile->is_sleeping;
    is_open = tile->is_open;
    is_dead = tile->is_dead;
    is_end_of_anim = tile->is_end_of_anim;
    is_dead_on_end_of_anim = tile->is_dead_on_end_of_anim;
    internal_has_dir_anim = tile->internal_has_dir_anim;

    index = 0;
    global_index = all_tiles_array.size() + 1;
    name = tile->name + " " + std::to_string(global_index);

    auto result = all_tiles.insert(std::make_pair(name, this));
    if (result.second == false) {
        ERR("tile copy insert name [%s] failed", name.c_str());
    }
    all_tiles_array.push_back(this);
}

void tile_load_arr (std::string file, std::string name,
                    uint32_t width, uint32_t height,
                    uint32_t nargs, const char * arr[])
{_
    Texp tex = tex_load(file, name, GL_NEAREST);

    float fw = 1.0 / (((float)tex_get_width(tex)) / ((float)width));
    float fh = 1.0 / (((float)tex_get_height(tex)) / ((float)height));
    float pw = 1.0 / ((float)tex_get_width(tex));
    float ph = 1.0 / ((float)tex_get_height(tex));
    pw /= 2.0;
    ph /= 2.0;

    int x = 0;
    int y = 0;
    int idx = 0;

    size pixel_size;

    pixel_size.w = width;
    pixel_size.h = height;

    while (nargs--) {

        std::string name = arr[idx++];

        if (name != "") {

            if (tile_find(name)) {
                ERR("tile name [%s] already used", name.c_str());
            }

            auto t = new Tile(); // std::make_shared< class Tile >();
            auto result = all_tiles.insert(std::make_pair(name, t));
            if (result.second == false) {
                ERR("tile insert name [%s] failed", name.c_str());
            }

            //
            // Global array of all tiles
            //
            all_tiles_array.push_back(t);
            t->global_index = all_tiles_array.size();

            t->name = name;
            t->index = idx - 1;
            t->pix_width = width;
            t->pix_height = height;
            t->tex = tex;
            t->set_gl_binding(tex_get_gl_binding(tex));

            t->x1 = fw * (float)(x);
            t->y1 = fh * (float)(y);
            t->x2 = t->x1 + fw;
            t->y2 = t->y1 + fh;

#ifdef ENABLE_TILE_COLLISION_CHECKING
            t->ox1 = t->x1;
            t->oy1 = t->y1;
            t->ox2 = t->x2;
            t->oy2 = t->y2;
#endif

            t->pct_width = fw;
            t->pct_height = fh;

#ifdef DEBUG_TILE
            printf("Tile: %-10s %ux%u (%u, %u)", name.c_str(), width, height, x, y);
#endif

#ifdef ENABLE_TILE_COLLISION_CHECKING
            if ((pixel_size.w <= MAX_TILE_WIDTH) &&
                (pixel_size.h <= MAX_TILE_HEIGHT)) {
                SDL_Surface *s = tex_get_surface(tex);

                point AT = {
                    pixel_size.w * x,
                    pixel_size.h * y
                };

                point MAX = {
                    pixel_size.w * x,
                    pixel_size.h * y
                };

                point MIN = {
                    (pixel_size.w * x) + pixel_size.w - 1,
                    (pixel_size.h * y) + pixel_size.h - 1
                };

                int x1, y1;

                for (y1=pixel_size.h - 1; y1>=0; y1--) {
                    for (x1=0; x1<pixel_size.w; x1++) {

                        point at = {
                            (pixel_size.w * x) + x1,
                            (pixel_size.h * y) + y1
                        };

                        color p = getPixel(s, at.x, at.y);

                        //
                        // If solid...
                        //
                        if (p.a >= 0xef) {
                            MIN.x = std::min(at.x, MIN.x);
                            MIN.y = std::min(at.y, MIN.y);
                            MAX.x = std::max(at.x, MAX.x);
                            MAX.y = std::max(at.y, MAX.y);
#ifdef DEBUG_TILE
                            printf("X");
#endif
                            if ((x1 < MAX_TILE_WIDTH) && (y1 < MAX_TILE_HEIGHT)) {
                                set(t->pix, x1, y1, (uint8_t)1);
                            }
                        } else if (p.a > 0) {
#ifdef DEBUG_TILE
                            printf(".");
#endif
                        } else {
#ifdef DEBUG_TILE
                            printf(" ");
#endif
                        }
                    }
#ifdef DEBUG_TILE
                    printf("\n");
#endif
                }

                t->px1 = ((double) (MIN.x - AT.x)) / (double) pixel_size.w;
                t->px2 = ((double) (MAX.x - AT.x + 1)) / (double) pixel_size.w;
                t->py1 = ((double) (MIN.y - AT.y)) / (double) pixel_size.h;
                t->py2 = ((double) (MAX.y - AT.y + 1)) / (double) pixel_size.h;
            }
#endif

#ifdef DEBUG_TILE
            printf("^^^  %s %f %f %f %f min x %d %d min y %d %d\n",name.c_str(),t->px1,t->py1,t->px2,t->py2, MIN.x,MAX.x,MIN.y,MAX.y);
#endif
        }

        x++;

        //
        // Check the whole tile can be read
        //
        if ((x * width) + (width - 1) >= tex_get_width(tex)) {
            x = 0;
            y++;
        }

        if (y * height > tex_get_height(tex)) {
            if (name != "") {
                ERR("overflow reading tile arr[%s]", name.c_str());
            } else {
                ERR("overflow reading tile arr at x %d y %d", x, y);
            }
        }
    }
}

void tile_load_arr (std::string file, std::string name,
                    uint32_t width, uint32_t height,
                    std::vector<std::string> arr)
{_
    Texp tex = tex_load(file, name, GL_NEAREST);

    float fw = 1.0 / (((float)tex_get_width(tex)) / ((float)width));
    float fh = 1.0 / (((float)tex_get_height(tex)) / ((float)height));
    float pw = 1.0 / ((float)tex_get_width(tex));
    float ph = 1.0 / ((float)tex_get_height(tex));
    pw /= 2.0;
    ph /= 2.0;

    int x = 0;
    int y = 0;
    int idx = 0;

    size pixel_size;

    pixel_size.w = width;
    pixel_size.h = height;

    for (auto name : arr) {
        idx++;

        if (name != "") {
            if (tile_find(name)) {
                ERR("tile name [%s] already used", name.c_str());
            }

            auto t = new Tile(); // std::make_shared< class Tile >();
            auto result = all_tiles.insert(std::make_pair(name, t));
            if (result.second == false) {
                ERR("tile insert name [%s] failed", name.c_str());
            }

            //
            // Global array of all tiles
            //
            all_tiles_array.push_back(t);
            t->global_index = all_tiles_array.size();

            t->name = name;
            t->index = idx - 1;
            t->pix_width = width;
            t->pix_height = height;
            t->tex = tex;
            t->set_gl_binding(tex_get_gl_binding(tex));

            t->x1 = fw * (float)(x);
            t->y1 = fh * (float)(y);
            t->x2 = t->x1 + fw;
            t->y2 = t->y1 + fh;

#ifdef ENABLE_TILE_COLLISION_CHECKING
            t->ox1 = t->x1;
            t->oy1 = t->y1;
            t->ox2 = t->x2;
            t->oy2 = t->y2;
#endif

            t->pct_width = fw;
            t->pct_height = fh;

#ifdef DEBUG_TILE
            printf("Tile: %-10s %ux%u (%u, %u)", name.c_str(), width, height, x, y);
#endif

#ifdef ENABLE_TILE_COLLISION_CHECKING
            if ((pixel_size.w <= MAX_TILE_WIDTH) &&
                (pixel_size.h <= MAX_TILE_HEIGHT)) {
                SDL_Surface *s = tex_get_surface(tex);

                point AT = {
                    pixel_size.w * x,
                    pixel_size.h * y
                };

                point MAX = {
                    pixel_size.w * x,
                    pixel_size.h * y
                };

                point MIN = {
                    (pixel_size.w * x) + pixel_size.w - 1,
                    (pixel_size.h * y) + pixel_size.h - 1
                };

                int x1, y1;

                for (y1=pixel_size.h - 1; y1>=0; y1--) {
                    for (x1=0; x1<pixel_size.w; x1++) {

                        point at = {
                            (pixel_size.w * x) + x1,
                            (pixel_size.h * y) + y1
                        };

                        color p = getPixel(s, at.x, at.y);

                        //
                        // If solid...
                        //
                        if (p.a >= 0xef) {
                            MIN.x = std::min(at.x, MIN.x);
                            MIN.y = std::min(at.y, MIN.y);
                            MAX.x = std::max(at.x, MAX.x);
                            MAX.y = std::max(at.y, MAX.y);
#ifdef DEBUG_TILE
                            printf("X");
#endif
                            if ((x1 < MAX_TILE_WIDTH) && (y1 < MAX_TILE_HEIGHT)) {
                                set(t->pix, x1, y1, (uint8_t)1);
                            }
                        } else if (p.a > 0) {
#ifdef DEBUG_TILE
                            printf(".");
#endif
                        } else {
#ifdef DEBUG_TILE
                            printf(" ");
#endif
                        }
                    }
#ifdef DEBUG_TILE
                    printf("\n");
#endif
                }

                t->px1 = ((double) (MIN.x - AT.x)) / (double) pixel_size.w;
                t->px2 = ((double) (MAX.x - AT.x + 1)) / (double) pixel_size.w;
                t->py1 = ((double) (MIN.y - AT.y)) / (double) pixel_size.h;
                t->py2 = ((double) (MAX.y - AT.y + 1)) / (double) pixel_size.h;
            }
#endif

#ifdef DEBUG_TILE
            printf("^^^  %s %f %f %f %f min x %d %d min y %d %d\n",name.c_str(),t->px1,t->py1,t->px2,t->py2, MIN.x,MAX.x,MIN.y,MAX.y);
#endif
        }

        x++;

        //
        // Check the whole tile can be read
        //
        if ((x * width) + (width - 1) >= tex_get_width(tex)) {
            x = 0;
            y++;
        }

        if (y * height > tex_get_height(tex)) {
            if (name != "") {
                ERR("overflow reading tile arr[%s]", name.c_str());
            } else {
                ERR("overflow reading tile arr at x %d y %d", x, y);
            }
        }
    }
}

//
// Find an existing tile.
//
Tilep tile_find (std::string name)
{_
    if (name == "") {
        return (0);
    }

    auto result = all_tiles.find(name);

    if (result == all_tiles.end()) {
        return (0);
    }

    return (result->second);
}

Tilep tile_find_mand (std::string name)
{_
    if (name == "") {
        ERR("no tile name give");
        return (0);
    }

    auto result = all_tiles.find(name);

    if (result == all_tiles.end()) {
        ERR("tile name %s not found", name.c_str());
        return (0);
    }

    return (result->second);
}

int32_t tile_get_width (Tilep tile)
{
    return (tile->pix_width);
}

std::string tile_get_name (Tilep tile)
{
    return (tile->name);
}

int32_t tile_get_height (Tilep tile)
{
    return (tile->pix_height);
}

Texp tile_get_tex (Tilep tile)
{
    return (tile->tex);
}

uint32_t tile_get_index (Tilep tile)
{
    return (tile->index);
}

void tile_get_coords (Tilep tile, float *x1, float *y1, float *x2, float *y2)
{
    *x1 = tile->x1;
    *y1 = tile->x1;
    *x2 = tile->x2;
    *x2 = tile->x2;
}

Tilep string2tile (const char **s)
{_
    static char tmp[MAXSHORTSTR];
    static const char * eo_tmp = tmp + MAXSHORTSTR;
    const char * c = *s;
    char *t = tmp;

    while (t < eo_tmp) {
        if ((*c == '\0') || (*c == '$')) {
            break;
        }

        *t++ = *c++;
    }

    if (c == eo_tmp) {
        return (0);
    }

    *t++ = '\0';
    *s += (t - tmp);

    auto result = all_tiles.find(tmp);
    if (result == all_tiles.end()) {
        ERR("unknown tile [%s]", tmp);
        return (0);
    }

    return (result->second);
}

Tilep string2tile (std::string &s, int *len)
{_
    auto iter = s.begin();
    std::string out;

    while (iter != s.end()) {
        auto c = *iter;

        if ((c == '\0') || (c == '$')) {
            break;
        }

        out += c;
        iter++;
    }

    if (iter == s.end()) {
        ERR("unknown tile [%s]", out.c_str());
    }

    if (len) {
        *len = iter - s.begin();
    }

    auto result = all_tiles.find(out);
    if (result == all_tiles.end()) {
        ERR("unknown tile [%s]", out.c_str());
    }

    return (result->second);
}

Tilep string2tile (std::wstring &s, int *len)
{_
    auto v = wstring_to_string(s);
    return (string2tile(v, len));
}

//
// Blits a whole tile.
//
void tile_blit_at (const Tilep &tile, fpoint tl, fpoint br)
{
    blit(tile->gl_binding(),
        tile->x1, tile->y2, tile->x2, tile->y1, tl.x, tl.y, br.x, br.y);
}

void tile_blit_colored (Tilep tile,
                        fpoint tl,
                        fpoint br,
                        color color_tl,
                        color color_tr,
                        color color_bl,
                        color color_br)
{
    double x1 = tile->x1;
    double x2 = tile->x2;
    double y1 = tile->y1;
    double y2 = tile->y2;

    blit_colored(tile->gl_binding(),
                 x1, y2, x2, y1,
                 tl.x, br.y, br.x, tl.y,
                 color_tl,
                 color_tr,
                 color_bl,
                 color_br);
}

std::string tile_name (Tilep t)
{_
    return (t->name);
}

uint32_t tile_delay_ms (Tilep t)
{_
    return (t->delay_ms);
}

uint8_t tile_is_moving (Tilep t)
{_
    return (t->is_moving);
}

uint8_t tile_is_yyy5 (Tilep t)
{_
    return (t->is_yyy5);
}

uint8_t tile_is_yyy6 (Tilep t)
{_
    return (t->is_yyy6);
}

uint8_t tile_is_yyy7 (Tilep t)
{_
    return (t->is_yyy7);
}

uint8_t tile_is_yyy8 (Tilep t)
{_
    return (t->is_yyy8);
}

uint8_t tile_is_yyy9 (Tilep t)
{_
    return (t->is_yyy9);
}

uint8_t tile_is_yyy10 (Tilep t)
{_
    return (t->is_yyy10);
}

uint8_t tile_is_hp_25_percent (Tilep t)
{_
    return (t->is_hp_25_percent);
}

uint8_t tile_is_hp_50_percent (Tilep t)
{_
    return (t->is_hp_50_percent);
}

uint8_t tile_is_hp_75_percent (Tilep t)
{_
    return (t->is_hp_75_percent);
}

uint8_t tile_is_hp_100_percent (Tilep t)
{_
    return (t->is_hp_100_percent);
}

uint8_t tile_gfx_outline_index_offset (Tilep t)
{_
    return (t->gfx_outline_index_offset);
}

uint8_t tile_is_sleeping (Tilep t)
{_
    return (t->is_sleeping);
}

uint8_t tile_is_open (Tilep t)
{_
    return (t->is_open);
}

uint8_t tile_is_dead (Tilep t)
{_
    return (t->is_dead);
}

uint8_t tile_is_end_of_anim (Tilep t)
{_
    return (t->is_end_of_anim);
}

uint8_t tile_is_dead_on_end_of_anim (Tilep t)
{_
    return (t->is_dead_on_end_of_anim);
}

Tilep tile_first (Tilemap *tiles)
{_
    if (!tiles || tiles->empty()) {
        return (0);
    }

    return ((*tiles)[0]);
}

Tilep tile_random (Tilemap *tiles)
{_
    if (!tiles || tiles->empty()) {
        return (0);
    }

    return ((*tiles)[myrand() % tiles->size()]);
}

Tilep tile_n (Tilemap *tiles, int n)
{_
    if (!tiles || tiles->empty()) {
        return (0);
    }

    return ((*tiles)[n % tiles->size()]);
}

Tilep tile_next (Tilemap *tiles, Tilep in)
{_
    if (!tiles || tiles->empty()) {
        return (0);
    }

    auto cursor = in->index;
    cursor++;
    if (cursor >= tiles->size()) {
        cursor = 0;
    }
    return ((*tiles)[cursor]);
}
