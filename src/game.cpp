#include "game.h"

using namespace std;

Game::Game()
{
    game_just_started = true;
    level_just_started = true;
    game_completed = false;
    wait_to_show_credits = 0;
}

void Game::init(int level_id)
{
    int i, j;

    current_level_id = level_id;

    // Load level datas
    current_level_dim = level_dims[level_id];
    for (i = 0; i < current_level_dim; i++) {
        for (j = 0; j < current_level_dim; j++) {
            current_level[i][j]  = levels_data[level_id][i][j];
        }
    }

    fixed_rot_angle = 0.0;
    rot_flag = false;
    mouse_down_flag = false;
    rotating_to_proper_position = false;

    wait_to_change_level = 0;

    world.init(current_level_dim, current_level, game_colors[level_id], player_target_positions[level_id]);
    player.init(current_level_dim, level_id);
    player.compute_next_tiles(current_level);
    if (DEBUGGING_ENABLED)
        draw_axes();
}

// Draws the axes (6 lines) for Debugging purposes
void Game::draw_axes()
{
    float world_max = 1.0;
        glVertex3f(-world_max, 0, 0);
    glBegin(GL_LINES);
        glVertex3f(world_max, 0, 0);
        glVertex3f(-world_max, 0, 0);
        glVertex3f(0, world_max, 0);
        glVertex3f(0, -world_max, 0);
        glVertex3f(0, 0, world_max);
        glVertex3f(0, 0, -world_max);
    glEnd();
}

void Game::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Rotate to isometric view
    glRotatef(35.264, 1.0, 0.0, 0.0);
    glRotatef(-45.0, 0.0, 1.0, 0.0);

    if (wait_to_show_credits > 0) { // Wait for 60 ticks before triggering level complete
        wait_to_show_credits++;
        if (wait_to_show_credits > 60) {
            game_completed = true;
            textscreen.show_textscreen("Congrats! Level Completed");
        }
    }

    if (wait_to_change_level > 0) { // Wait for 60 ticks beforre changing level
        wait_to_change_level++;
        if (wait_to_change_level > 60) {
            load_next_level();
        }
    }

    if (game_just_started) {
        textscreen.show_textscreen("Isometric optical illusion game");
    }

    if (textscreen.isEnabled()) {
        textscreen.render_textscreen();
        return;
    }

    if (rot_flag && !mouse_down_flag) {
        rotate_to_proper_position();
    }

    glRotatef(fixed_rot_angle + varying_rot_angle, 0.0, 1.0, 0.0); // Rotate game world only on the y axis

    if (DEBUGGING_ENABLED){
        draw_axes();
    }
    world.render_world();
    player.render();
}

void Game::mouse_input(int btn, int state, int x, int y)
{
    if (textscreen.isEnabled()) // Ignore input while textscreen is shown
        return;

    if (state == GLUT_DOWN && btn == GLUT_LEFT_BUTTON) {
        if (rotating_to_proper_position) { // If in the middle of a previous rotation
            //previous_rot_angle = varying_rot_angle; // then add previous rotation angle to current rot angle
            return; // Ignore input
        }
        else {
            previous_rot_angle = 0;
        }
        rot_flag = true;
        mouse_down_flag = true;
        initial_mouse_down_x = x;
    }
    else if (state == GLUT_UP && btn == GLUT_LEFT_BUTTON) {
        mouse_down_flag = false;
    }
}

void Game::keyboard_input(unsigned char key)
{
    if (game_completed) { // If all levels completed
        if (textscreen.isEnabled()) // Remove level completed text screen
            textscreen.remove_textscreen();
        textscreen.show_credits(); // And show credits
        return;
    }

    // Hides title screen on pressing any key
    if (textscreen.isEnabled()) {
        game_just_started = false;
        textscreen.remove_textscreen();
    }

    switch(key) {
    case 'Q': case 'q':
        exit(0);
        break;
    case 'R': case 'r':
        init(current_level_id);
        break;
    case '9': case '7': case '3': case '1':
        player.moveInput(key);
        if (player.levelCompleted()) {
            if (current_level_id + 1 < NO_OF_LEVELS) {
                wait_to_change_level = 1; // Once level is completed the make game pause for a while
            }
            else {
                wait_to_show_credits = 1;
            }
        }
        player.compute_next_tiles(current_level);
        break;
    }
}

void Game::motion_input(int x, int y)
{
    if (rotating_to_proper_position) { // If in the middle of a previous rotation
        return; // Ignore input
    }
    if (!rot_flag) {
        return; // Ignore input
    }
    drag_ratio = (float)(x - initial_mouse_down_x) / (float)(GAME_SCREEN_WIDTH / 2);
    // Cap drag_ratio between 1.0 and -1.0
    if (drag_ratio > 1.0)
        drag_ratio = 1.0;
    else if (drag_ratio < -1.0)
        drag_ratio = -1.0;

    varying_rot_angle = 90.0 * drag_ratio + previous_rot_angle; // Amount of completion of drag
}

void Game::rotate_to_proper_position()
{
    float auto_rot_inc = 0.75;
    if (drag_ratio == 0.0) { // No rotation was performed, but the left mouse btn was simply clicked
        return;
    }

    rotating_to_proper_position = true;
    if ((int)round(varying_rot_angle) % 90 == 0) { // We have arrived at the proper position
        rot_flag = false;
        rotating_to_proper_position = false;
        fixed_rot_angle += round(varying_rot_angle);
        varying_rot_angle = 0;
        // Rotate current level data and Player to reflect the change
        if (drag_ratio > 0) {
            rotate_level_data(ANTICLOCKWISE_DIRECTION);
            player.update_equivalent_tiles_after_rotation(Player::ANTICLOCKWISE_DIRECTION);
        }
        else if (drag_ratio < 0) {
            rotate_level_data(CLOCKWISE_DIRECTION);
            player.update_equivalent_tiles_after_rotation(Player::CLOCKWISE_DIRECTION);
        }
        player.compute_next_tiles(current_level);
        drag_ratio = 0.0;
    }
    else if (drag_ratio > 0) {
        varying_rot_angle += auto_rot_inc;
    }
    else if (drag_ratio < 0) {
        varying_rot_angle -= auto_rot_inc;
    }
}

void Game::rotate_level_data(enum direction rotation_direction)
{
    int i, j;
    int new_level_data[LEVEL_DIM_MAX][LEVEL_DIM_MAX];

    // Findout the new level data after rotation
    for (i = 0; i < current_level_dim; i++) {
        for (j = 0; j < current_level_dim; j++) {
            if (rotation_direction == CLOCKWISE_DIRECTION) {
                new_level_data[i][j] = current_level[current_level_dim - 1 - j][i];
            }
            else if (rotation_direction == ANTICLOCKWISE_DIRECTION) {
                new_level_data[i][j] = current_level[j][current_level_dim - 1 - i];
            }
        }
    }

    // Copy the new level data to the current level data
    for (i = 0; i < current_level_dim; i++) {
        for (j = 0; j < current_level_dim; j++) {
            current_level[i][j] = new_level_data[i][j];
        }
    }
}

void Game::load_next_level()
{
    textscreen.show_textscreen("Congrats! Level Completed");
    init(++current_level_id);
}
