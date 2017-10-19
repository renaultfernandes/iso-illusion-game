#ifndef GAME_H
#define GAME_H

#include <GL/glut.h>
#include <math.h>
#include "levels.h"
#include "world.h"
#include "player.h"
#include "textscreen.h"

#define DEBUGGING_ENABLED 0

#define GAME_SCREEN_WIDTH 700
#define GAME_SCREEN_HEIGHT 700

class Game
{
private:
    World world;
    Player player;
    TextScreen textscreen;

    enum direction {
        CLOCKWISE_DIRECTION,
        ANTICLOCKWISE_DIRECTION
    };

    void draw_axes();

    bool game_just_started, level_just_started, game_completed;

    float drag_ratio; // Ratio of (mouse) distance dragged on screen to half of the screen width
    float fixed_rot_angle, varying_rot_angle, previous_rot_angle;

    bool rot_flag;
    bool mouse_down_flag;

    int initial_mouse_down_x; // Used when rotating while draging with mouse button down
    bool rotating_to_proper_position;

    int wait_to_change_level; // Introduce a delay to show final player pos just before changing
    int wait_to_show_credits;

    void rotate_to_proper_position();
    void rotate_level_data(enum direction rotation_direction);
    void load_next_level();

public:
    int current_level[LEVEL_DIM_MAX][LEVEL_DIM_MAX]; // Holds a copy of the cuttent levels map data which can be manipulated
    int current_level_dim; // Holds dimensions of the current level
    int current_level_id;

    Game();
    void init(int level_id);
    void render();

    void mouse_input(int btn, int state, int x, int y);
    void keyboard_input(unsigned char key);
    void motion_input(int x, int y);
};

#endif // GAME_H
