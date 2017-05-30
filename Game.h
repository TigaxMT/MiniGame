#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h> // Message Box
#include <allegro5/allegro_image.h> // Image
#include <allegro5/allegro_acodec.h> // Audio
#include <allegro5/allegro_audio.h> // Audio
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdlib.h> // rand()

#define FPS 60.0

class Game
{
private:
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_DISPLAY_MODE disp_data;

    enum Direction{DOWN,LEFT,RIGHT,UP};

    bool done = false, draw = true, active = false, music = true, sfx = true;

    float x = 0, y = 0, moveSpeed = 3;

    int dir = DOWN, sourceX = 32,sourceY = 0,ex = 0,ey = 0, ox = 0,oy = 0, h = 0,w = 0;

public:
    Game()
    {
        init();

        setDisplay();

        game();
    }

    void game();
    bool collision(float&,float&,float,float,int,int);
    void randomize();

    void init();
    void setDisplay();

    ~Game()
    {
        al_destroy_display(display);
    }

};

#endif // GAME_H_INCLUDED
