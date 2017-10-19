#include "world.h"

using namespace std;

void World::init(int current_level_dim, int current_level_data[LEVEL_DIM_MAX][LEVEL_DIM_MAX], const float game_colors[3][3],
const int target_positions[])
{
    int i, j;
    float game_bound = 1;
    float block_size = game_bound / current_level_dim;
    float x_starting_corner = game_bound / -2;
    float y_starting_corner = -0.6;
    float z_starting_corner = game_bound / -2;

    float target_x, target_y, target_z; // Coordinates of where to draw the target square

    // World is at size zero initially
    initial_world_animation_scale = 0;

    // Initialize Level
    level_world_list_id = glGenLists(1);
    glNewList(level_world_list_id, GL_COMPILE);
    glMaterialfv(GL_FRONT, GL_AMBIENT, game_colors[2]);
    for (i = 0; i < current_level_dim; i++) {
        for (j = 0; j < current_level_dim; j++) {
            draw_block_stack(x_starting_corner + j * block_size, y_starting_corner, z_starting_corner + i * block_size,
                             block_size, current_level_data[i][j]);
        }
    }
    glEndList();

    // Initialize Background
    background_list_id = glGenLists(1);
    glNewList(background_list_id, GL_COMPILE);
    glBegin(GL_QUADS);
        glColor3fv(game_colors[0]);
        glVertex2f(1.0, 1.0);
        glVertex2f(-1.0, 1.0);
        glColor3fv(game_colors[1]);
        glVertex2f(-1.0, -1.0);
        glVertex2f(1.0, -1.0);
    glEnd();
    glEndList();

    // Initialize starting positions of target square
    target_x = x_starting_corner + target_positions[0] * block_size;
    target_y = y_starting_corner / 1.001 + current_level_data[target_positions[1]][target_positions[0]] * block_size;
    target_z = z_starting_corner + target_positions[1] * block_size;

    // Initialize Target square
    target_square_list_id = glGenLists(1);
    glNewList(target_square_list_id, GL_COMPILE);
    glBegin(GL_QUADS);
        glVertex3f(target_x, target_y, target_z);
        glVertex3f(target_x + block_size, target_y, target_z);
        glVertex3f(target_x + block_size, target_y, target_z + block_size);
        glVertex3f(target_x, target_y, target_z + block_size);
    glEnd();
    glEndList();

    // Seed random function to get random colors for the target square
    srand(time((unsigned) 0));
}

// Renders the game world
void World::render_world()
{
    draw_background();

    // Handle initial animation of the world
    if (initial_world_animation_scale < 1.0) {
        glScalef(1.0, sin(initial_world_animation_scale * 90 * M_PI / 180), 1.0); // Perform a smooth animation along y axis
        initial_world_animation_scale += 0.015;
        glCallList(level_world_list_id); // Render the scaled world while animating
        draw_target_square();
    }
    else {
        // Render the game World;
        glCallList(level_world_list_id);
        draw_target_square();
    }
}

bool World::initial_animation_completed()
{
    if (initial_world_animation_scale < 1.0) {
        return false;
    }
    return true;
}

void World::draw_background()
{
    glPushMatrix();
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glCallList(background_list_id);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glPopMatrix();
}

void World::draw_target_square()
{
    float square_colors[3];
    int i;
    static int show_color; // Decides whether to show colored square in each second
    if (show_color > 60) {
        glDisable(GL_LIGHTING);
        // Set a random color first
        for (i = 0; i < 3; i++) {
            square_colors[i] = ((rand() % 300) + 200) / 500.0;
        }
        glColor3fv(square_colors);
        glCallList(target_square_list_id);
        glEnable(GL_LIGHTING);
    }
    show_color = show_color < 120 ? show_color + 1 : 0;
}

void World::draw_block_stack(float x, float y, float z, float size, int count)
{
    int i;
    for (i = 0; i < count; i++) {
        draw_block(x, y + (i * size), z, size);
    }
}

// Draws a box of having (x,y,z) as its left bottom far corner of size 'size'
void World::draw_block(float x, float y, float z, float size)
{
    // Draw sides
    glPolygonMode(GL_FRONT_AND_BACK, GL_POLYGON);
    glBegin(GL_QUADS);
        // The Left
        glNormal3f(-1.0, 0.0, 0.0);
        glVertex3f(x, y, z);
        glVertex3f(x, y + size, z);
        glVertex3f(x, y + size, z + size);
        glVertex3f(x, y, z + size);
        // The Front
        glNormal3f(0.0, 0.0, 1.0);
        glVertex3f(x, y, z + size);
        glVertex3f(x, y + size, z + size);
        glVertex3f(x + size, y + size, z + size);
        glVertex3f(x + size, y, z + size);
        // The Right
        glNormal3f(1.0, 0.0, 0.0);
        glVertex3f(x + size, y, z + size);
        glVertex3f(x + size, y + size, z + size);
        glVertex3f(x + size, y + size, z);
        glVertex3f(x + size, y, z);
        // The Back
        glNormal3f(0.0, 0.0, -1.0);
        glVertex3f(x + size, y, z);
        glVertex3f(x + size, y + size, z);
        glVertex3f(x, y + size, z);
        glVertex3f(x, y, z);
    glEnd();
    // Draw Top & Bottom
    glBegin(GL_QUADS);
        // The Bottom
        glNormal3f(0.0, -1.0, 0.0);
        glVertex3f(x, y, z);
        glVertex3f(x + size, y, z);
        glVertex3f(x + size, y, z + size);
        glVertex3f(x, y, z + size);
        // The Top
        glNormal3f(0.0, 1.0, 0.0);
        glVertex3f(x, y + size, z);
        glVertex3f(x + size, y + size, z);
        glVertex3f(x + size, y + size, z + size);
        glVertex3f(x, y + size, z + size);
    glEnd();
}
