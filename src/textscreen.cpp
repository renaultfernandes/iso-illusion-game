#include "textscreen.h"

using namespace std;

TextScreen::TextScreen()
{
    textscreen_enabled = false;
    text_length = 0;
    screen_width = 700;
    screen_height = 700;
    text_size = 24;
    text_y = 0;
    text_x = 0;
}

void TextScreen::draw_background()
{
    glPushMatrix();
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Barkground
    glBegin(GL_QUADS);
        glColor3f(0.95, 0.95, 0.95);
        glVertex2f(1.0, 1.0);
        glVertex2f(-1.0, 1.0);
        glColor3f(0.75, 0.75, 0.8);
        glVertex2f(-1.0, -1.0);
        glVertex2f(1.0, -1.0);
    glEnd();

    // Decorations
    glBegin(GL_POLYGON);
        glColor3f(0.6, 0.6, 0.6);
        glVertex2f(-1.0, 0.2);
        glVertex2f(0, -0.2);
        glVertex2f(0, -1.0);
        glVertex2f(-1.0, -1.0);
    glEnd();
    glBegin(GL_POLYGON);
        glColor3f(0.7, 0.7, 0.7);
        glVertex2f(0, -0.2);
        glVertex2f(1.0, 0.2);
        glVertex2f(1.0, -1.0);
        glVertex2f(0, -1.0);
    glEnd();

    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glPopMatrix();
}

void TextScreen::draw_text()
{
    char *c;
    glRasterPos3f(text_x, text_y, 0);
    for (c = text_str; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}

void TextScreen::render_textscreen()
{
    if (textscreen_enabled) {
        draw_background();
        draw_text();
    }
}

void TextScreen::show_textscreen(const char *str)
{
    if (textscreen_enabled) // If some text is already shown
        return;
    textscreen_enabled = true;
    strcpy(text_str, str);
    text_length = strlen(text_str);
    text_x = -0.5;
}

void TextScreen::show_credits()
{
    if (textscreen_enabled) // If some text is already shown
        return;
    textscreen_enabled = true;
    text_x = -0.8;
    strcpy(text_str, "Thank You for playing, Created by Renault J. F.");
    text_length = strlen(text_str);
}

void TextScreen::remove_textscreen()
{
    textscreen_enabled = false;
}

bool TextScreen::isEnabled()
{
    if (textscreen_enabled) {
        return true;
    }
    return false;
}
