#ifndef TEXTSCREEN_H
#define TEXTSCREEN_H

#include <GL/glut.h>
#include <string.h>

class TextScreen
{
private:
    int text_length;
    bool textscreen_enabled;
    char text_str[100];

    int text_size;
    float text_x, text_y;
    int screen_width, screen_height;

    void set_up_textscreen();
    void draw_background();
    void draw_text();
    void finish_textscreen();

public:
    TextScreen();
    void render_textscreen();
    void show_textscreen(const char *str);
    void show_credits();
    void remove_textscreen();
    bool isEnabled();
};

#endif // TEXTSCREEN_H
