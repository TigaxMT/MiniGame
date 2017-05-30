/*

    Copyright (C) 2017  Tiago Martins

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/


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
