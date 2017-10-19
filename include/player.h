#ifndef PLAYER_H
#define PLAYER_H

#include <GL/glut.h>
#include "levels.h"

class Player
{
private:
    int current_level_id;
    int current_tile_x, current_tile_y, current_elevation;
    int level_tile_x, level_tile_y;
    int current_equated_tile_x, current_equated_tile_y;
    int current_tile_elevation;
    float player_size_radius, block_size;
    float x_starting_corner, y_starting_corner, z_starting_corner;
    bool updating_position;
    int next_tile_location[4][2]; // x y
    int rotation_performed;

    enum move_direction {
        NW, SW, SE, NE
    };

    void update_current_tiles_to_normalize_rotations();

public:
    // Direction of rotation
    enum direction {
        CLOCKWISE_DIRECTION,
        ANTICLOCKWISE_DIRECTION
    };

    void init(int current_level_dim, int level_id);
    void render();
    void moveInput(char key);
    void update_equivalent_tiles_after_rotation(enum direction rot_direction);
    void compute_next_tiles(int current_level_data[LEVEL_DIM_MAX][LEVEL_DIM_MAX]);
    bool levelCompleted();
};

#endif // PLAYER_H
