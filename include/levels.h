#ifndef LEVELS_H
#define LEVELS_H

#define LEVEL_DIM_MAX 6
#define NO_OF_LEVELS 5

static const int levels_data[][LEVEL_DIM_MAX][LEVEL_DIM_MAX] =
{   // x->, y|

    {   // Level 1
        {1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0},
        {1, 5, 0, 0, 0, 0}
    },
    {   // Level 2
        {0, 0, 0, 6, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {8, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 4},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 2, 0, 0, 0}
    },
    {
        // level 3
        {0, 0, 3, 1, 1, 1},
        {0, 0, 3, 1, 0, 1},
        {0, 0, 3, 1, 0, 1},
        {1, 0, 1, 3, 0, 0},
        {1, 0, 1, 3, 0, 0},
        {1, 1, 1, 3, 0, 0}
    },
    {
        // level 4
        {2, 2, 0, 2, 2, 2},
        {2, 0, 0, 0, 2, 2},
        {0, 0, 3, 0, 0, 2},
        {2, 0, 0, 3, 0, 0},
        {2, 2, 0, 0, 0, 2},
        {2, 2, 2, 0, 2, 2}
    },
    {
        // level 5
        {1, 1, 2, 1, 5, 1},
        {5, 0, 0, 1, 0, 1},
        {1, 1, 1, 1, 0, 2},
        {2, 0, 1, 1, 1, 1},
        {1, 0, 1, 0, 0, 5},
        {1, 5, 1, 2, 1, 1}
    }
};

static const int level_dims [] = {
    6, // level 1
    6, // level 2
    6, // level 3
    6, // level 4
    6  // level 5
};

static const int player_starting_positions[][2] = {
    // {x, y}
    {0, 0}, // Level 1
    {0, 2}, // level 2
    {3, 2}, // level 3
    {5, 5}, // level 4
    {0, 0}  // level 5
};

static const int player_target_positions[][2] = {
    // {x, y}
    {1, 5}, // level 1
    {2, 5}, // level 2
    {2, 3}, // level 3
    {0, 0}, // level 4
    {5, 5}  // level 5
};

static const float player_color[3] = {1.0, 1.0, 1.0};

static const float game_colors[][3][3] =
{
    { // level 1
        {0.0, 0.0, 0.5}, // Background top
        {0.0, 0.4, 0.5}, // background bottom
        {0.0, 0.4, 1.0}  // Level world
    },
    { // level 2
        {0.0, 0.8, 0.5}, // Background top
        {0.0, 0.7, 0.6}, // background bottom
        {1.0, 1.0, 0.0}  // Level world
    },
    { // level 3
        {0.8, 0.8, 0.0}, // Background top
        {0.0, 0.8, 0.8}, // background bottom
        {0.0, 1.0, 0.0}  // Level world
    },
    { // level 4
        {1.0, 0.75, 0.85}, // Background top
        {0.2, 0.6, 0.8}, // background bottom
        {0.8, 0.5, 0.6}  // Level world
    },
    { // level 5
        {0.82, 0.87, 0.77}, // Background top
        {0.72, 0.77, 0.67}, // background bottom
        {0.45, 0.4, 0.25}  // Level world
    }
};

#endif // LEVELS_H

