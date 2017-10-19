#include "player.h"

using namespace std;

void Player::init(int current_level_dim, int level_id)
{
    float game_bound = 1;

    current_level_id = level_id;
    x_starting_corner = game_bound / -2;
    y_starting_corner = -0.6;
    z_starting_corner = game_bound / -2;
    block_size = game_bound / current_level_dim;
    rotation_performed = 0;

    player_size_radius = game_bound / (current_level_dim * 4);
    current_tile_x = level_tile_x = player_starting_positions[level_id][0];
    current_tile_y = level_tile_y = player_starting_positions[level_id][1];
    current_tile_elevation = levels_data[level_id][current_tile_y][current_tile_x];

    current_equated_tile_x = current_tile_x - current_tile_elevation;
    current_equated_tile_y = current_tile_y - current_tile_elevation;
}

void Player::render()
{
    current_elevation = levels_data[current_level_id][current_tile_y][current_tile_x];
    // Note mapping of y and z axes are interchanged in the game world
    float x_effective_pos = ((current_tile_x + 0.5) * block_size) + x_starting_corner;
    float y_effective_pos = ((current_elevation + 0.5) * block_size) + y_starting_corner;
    float z_effective_pos = ((current_tile_y + 0.5) * block_size) + z_starting_corner;

    glTranslatef(x_effective_pos, y_effective_pos, z_effective_pos);
    glMaterialfv(GL_FRONT, GL_AMBIENT, player_color);
    glColor3f(0.0, 1.0, 1.0);
    glutSolidSphere(player_size_radius, 20, 20);
    glTranslatef(-x_effective_pos, -y_effective_pos, -z_effective_pos);
}

void Player::moveInput(char key)
{
    enum move_direction direction_to_move;
    switch (key) {
    case '7':
        direction_to_move = NW;
        break;
    case '9':
        direction_to_move = NE;
        break;
    case '1':
        direction_to_move = SW;
        break;
    case '3':
        direction_to_move = SE;
        break;
    }

    if (next_tile_location[direction_to_move][0] == -1 || next_tile_location[direction_to_move][1] == -1)
        return;

    current_tile_x = level_tile_x = next_tile_location[direction_to_move][0];
    current_tile_y = level_tile_y = next_tile_location[direction_to_move][1];
    // Update current elevation for the new pos
    current_tile_elevation = levels_data[current_level_id][level_tile_y][level_tile_x];

    update_current_tiles_to_normalize_rotations();

    // Update equated tiles to reflect new pos
    current_equated_tile_x = level_tile_x - current_tile_elevation;
    current_equated_tile_y = level_tile_y - current_tile_elevation;
}

void Player::update_equivalent_tiles_after_rotation(direction rot_direction)
{
    int new_tile_x, new_tile_y;
    if (rot_direction == CLOCKWISE_DIRECTION) {
        new_tile_x = level_dims[current_level_id] - 1 - level_tile_y;
        new_tile_y = level_tile_x;
        rotation_performed += 1;
    }
    else if (rot_direction == ANTICLOCKWISE_DIRECTION) {
        new_tile_x = level_tile_y;
        new_tile_y = level_dims[current_level_id] - 1 - level_tile_x;
        rotation_performed += -1;
    }
    level_tile_x = new_tile_x;
    level_tile_y = new_tile_y;
    current_equated_tile_x = level_tile_x - current_tile_elevation;
    current_equated_tile_y = level_tile_y - current_tile_elevation;
}

// Determine the next tile on which player moves
void Player::compute_next_tiles(int current_level_data[LEVEL_DIM_MAX][LEVEL_DIM_MAX])
{
    int i, j;
    int equated_tile_x, equated_tile_y;
    int c_map[] = {109, 97, 100, 101, 95, 98, 121, 95, 114, 101, 110, 111};

    current_tile_elevation = current_level_data[level_tile_y][level_tile_x];
    current_equated_tile_x = level_tile_x - current_tile_elevation;
    current_equated_tile_y = level_tile_y - current_tile_elevation;

    // Clear existing next tile values
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 2; j++) {
            next_tile_location[i][j] = -1;
        }
    }

    // Iterate thru each level tile to check if it has a suitable equated tile value
    // i.e. a tile value corresponding to the 4 immediate positions from the current/level tile
    for (i = 0; i < level_dims[current_level_id]; i++) {
        for (j = 0; j < level_dims[current_level_id]; j++) {
            if (current_level_data[i][j] == 0) { // Not a tile that can be moved on top of
                continue;
            }
            equated_tile_x = j - current_level_data[i][j];
            equated_tile_y = i - current_level_data[i][j];
            if (level_tile_x + level_tile_y > i + j) { // For the Norths 0 & 3
                if (equated_tile_y == current_equated_tile_y && equated_tile_x == current_equated_tile_x - 1) { // NW-> 0
                    next_tile_location[NW][0] = j; // If suitable then set it as the next tile
                    next_tile_location[NW][1] = i;
                }
                else if (equated_tile_y == current_equated_tile_y - 1 && equated_tile_x == current_equated_tile_x) { // NE-> 3
                    next_tile_location[NE][0] = j;
                    next_tile_location[NE][1] = i;
                }
            }
            else if (level_tile_x + level_tile_y < i + j) { // For the Souths 1 & 2
                if (equated_tile_y == current_equated_tile_y + 1 && equated_tile_x == current_equated_tile_x) { // SW-> 1
                    next_tile_location[SW][0] = j;
                    next_tile_location[SW][1] = i;
                }
                else if (equated_tile_y == current_equated_tile_y && equated_tile_x == current_equated_tile_x + 1) { // SE-> 2
                    next_tile_location[SE][0] = j;
                    next_tile_location[SE][1] = i;
                }
            }
        }
    }
}

bool Player::levelCompleted()
{
    if (current_tile_x == player_target_positions[current_level_id][0]    // If player has reached the target position
            && current_tile_y == player_target_positions[current_level_id][1]) {
        return true;
    }
    return false;
}

// Find out the current tile on which to render player based on the amount of rotations performed and the level tile
// by actually rotating the current tile in the opposite direction
void Player::update_current_tiles_to_normalize_rotations()
{
    int r = rotation_performed;
    int tx, ty;
    while (r < 0) { // ANTICLOCKWISE rotation was performed
        // So do a CLOCKWISE rotation to normalize
        tx = level_dims[current_level_id] - 1 - current_tile_y;
        ty = current_tile_x;
        r++;
        current_tile_x = tx;
        current_tile_y = ty;
    }
    while (r > 0) { // CLOCKWISE rotation was performed
        // So do a ANTICLOCKWISE rotation to normalize
        tx = current_tile_y;
        ty = level_dims[current_level_id] - 1 - current_tile_x;
        r--;
        current_tile_x = tx;
        current_tile_y = ty;
    }
}
