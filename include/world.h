#ifndef WORLD_H
#define WORLD_H

#include <GL/glut.h>
#include <math.h>
#include <time.h>
#include "levels.h"

class World
{
public:
    void init(int current_level_dim, int current_level_data[LEVEL_DIM_MAX][LEVEL_DIM_MAX], const float game_colors[3][3],
        const int target_positions[2]);
    void render_world();
    bool initial_animation_completed();

private:
    int level_world_list_id;
    int background_list_id;
    int target_square_list_id;
    float initial_world_animation_scale;
    void draw_block(float x, float y, float z, float size);
    void draw_block_stack(float x, float y, float z, float size, int count);
    void draw_background();
    void draw_target_square();
};

#endif // WORLD_H
