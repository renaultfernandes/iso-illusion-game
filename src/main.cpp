#include "game.h"

#define FPS 60

using namespace std;

Game game;

void display()
{
    game.render();
    glutSwapBuffers();
}

void my_reshape(int w, int h)
{
    int offset_x, offset_y;
    offset_x = (int) ((w - GAME_SCREEN_WIDTH) / 2);
    offset_y = (int) ((h - GAME_SCREEN_HEIGHT) / 2);
    glViewport(offset_x, offset_y, GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT);
}

void my_mouse(int btn, int state, int x, int y)
{
    game.mouse_input(btn, state, x, y);
}

void my_keyboard(unsigned char key, int x, int y)
{
    game.keyboard_input(key);
}

void my_motion(int x, int y)
{
    game.motion_input(x, y);
}

// Timer used for stable framerate (60 frames per second)
void my_timer(int v)
{
    glutPostRedisplay();
    glutTimerFunc(1000/FPS, my_timer, v);
}

void myinit()
{
    GLfloat light_pos[] = {10.0 , 10.0, 10.0, 1.0};
    GLfloat ambient[] = { 1.0, 1.0, 1.0, 1.0};

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);

    glViewport(0, 0, GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT);

    // Initialize lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

    game.init(0);
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(GAME_SCREEN_WIDTH,  GAME_SCREEN_HEIGHT);
    glutInitWindowPosition(250, 0);
    glutCreateWindow("Isometric optical illusion game");
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutReshapeFunc(my_reshape);
    glutMouseFunc(my_mouse);
    glutKeyboardFunc(my_keyboard);
    glutMotionFunc(my_motion);
    glutTimerFunc(100, my_timer, FPS);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    myinit();
    glutMainLoop();
    return 0;
}
