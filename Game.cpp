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


#include "Game.h"

void Game::randomize()
{
    do
    {
        ey = rand() % (disp_data.height-32) + 0;
        ex = rand() % (disp_data.width - 32) + 0;

    }while(ex < 0 || ex > disp_data.width || ey < 0 || ey > disp_data.height || ey%3!=0 || ex%3!=0);
}

bool Game::collision(float &x,float &y,float ex,float ey,int width,int height)
{
    if(x + width < ex || x > ex + width || y + height < ey || y > ey + height)
    {
        // No collision
        return false;
    }

    return true;
}

void Game::init()
{
    if(!al_init())
    {
        al_show_native_message_box(NULL,NULL,NULL,"Could not initialize Allegro",NULL,NULL);

        exit(1);
    }
}

void Game::setDisplay()
{
    al_init_primitives_addon();

    al_get_display_mode(0, &disp_data);

    al_set_new_display_flags(ALLEGRO_FULLSCREEN);
    display = al_create_display(disp_data.width, disp_data.height);

    h = disp_data.height;
    w = disp_data.width;

    al_set_window_position(display,200,100);
    al_set_window_title(display,"MiniGame");

    if(!display)
    {
        al_show_native_message_box(display,"Error","Warning","Could not initialize display",NULL,ALLEGRO_MESSAGEBOX_WARN);

        exit(2);
    }
}

void Game::game()
{
    int i = 0;

    x = disp_data.width/2;
    y = disp_data.height/2;

    al_install_keyboard();
    al_install_audio();
    al_install_mouse();


    al_init_image_addon();
    al_init_acodec_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    al_reserve_samples(2);

    al_hide_mouse_cursor(display);

    ALLEGRO_BITMAP *player = al_load_bitmap("img/player.png");
    ALLEGRO_BITMAP *coin = al_load_bitmap("img/coin.png");

    ALLEGRO_KEYBOARD_STATE keyState;

    ALLEGRO_FONT *font = al_load_font("fonts/leadcoat.ttf",20,NULL);
    ALLEGRO_FONT *font2 = al_load_font("fonts/leadcoat.ttf",100,NULL);
    ALLEGRO_FONT *copyright = al_load_font("fonts/atwriter.ttf",17,NULL);

    ALLEGRO_SAMPLE *soundEffect = al_load_sample("songs/Coin_Sound.wav");
    ALLEGRO_SAMPLE *song = al_load_sample("songs/Music.ogg");
    ALLEGRO_SAMPLE_INSTANCE *songInstance = al_create_sample_instance(song);

    al_set_sample_instance_playmode(songInstance,ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(songInstance,al_get_default_mixer());

    ALLEGRO_TIMER *timer = al_create_timer(1.0/FPS);

    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();

    al_register_event_source(event_queue,al_get_timer_event_source(timer));
    al_register_event_source(event_queue,al_get_display_event_source(display));
    al_register_event_source(event_queue,al_get_keyboard_event_source());

	al_set_sample_instance_gain(songInstance,0.25);
    al_play_sample_instance(songInstance);

    al_start_timer(timer);

    while(!done)
    {
        ALLEGRO_EVENT events;

        al_wait_for_event(event_queue, &events);

        al_get_keyboard_state(&keyState);

        if(events.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
                done = true;
        else
            if(al_key_down(&keyState,ALLEGRO_KEY_ESCAPE))
                done = true;
            else
                if(events.type == ALLEGRO_EVENT_TIMER)
                {
                    draw = true;

                    active = true;

                     al_draw_text(copyright,al_map_rgb(255,255,255),w - 700,h - 50,ALLEGRO_ALIGN_CENTER,"Copyright (C) 2016 Tiago Martins");

                    if(moveSpeed >= 3 && moveSpeed <= 15)
                    {
                        al_draw_text(font,al_map_rgb(44,117,255),w -  100,h - 755,ALLEGRO_ALIGN_RIGHT,"Your Score is Lower!");

                    }
                    else
                        if(moveSpeed > 15 && moveSpeed <= 30)
                        {
                            al_draw_text(font,al_map_rgb(44,117,255),w -  100,h - 755,ALLEGRO_ALIGN_RIGHT,"Your Score is Medium!");


                        }
                        else
                            if(moveSpeed > 30 && moveSpeed <= 60)
                            {
                                al_draw_text(font,al_map_rgb(44,117,255),w -  100,h - 755,ALLEGRO_ALIGN_RIGHT,"Your Score is Higher!");
                            }
                            else
                                if(moveSpeed >= 100)
                                {

                                    al_draw_text(font,al_map_rgb(44,117,255),w -  100,h - 755,ALLEGRO_ALIGN_RIGHT,"YOU ARE FABULOUS!!");

                                }
                                else
                                {

                                     al_draw_text(font,al_map_rgb(44,117,255),w -  100,h - 755,ALLEGRO_ALIGN_RIGHT,"Your Score is Very Higher");
                                }

                    if(al_key_down(&keyState,ALLEGRO_KEY_DOWN))
                    {

                        y += moveSpeed;
                        dir = DOWN;

                        if(y > disp_data.height)
                            y = 0;
                    }
                    else
                        if(al_key_down(&keyState,ALLEGRO_KEY_LEFT))
                        {
                            x -= moveSpeed;
                            dir = LEFT;

                            if(x < 0)
                                x = disp_data.width;
                        }
                        else
                            if(al_key_down(&keyState,ALLEGRO_KEY_RIGHT))
                            {
                                x += moveSpeed;
                                dir = RIGHT;

                                if(x > disp_data.width)
                                    x = 0;
                            }
                            else
                                if(al_key_down(&keyState,ALLEGRO_KEY_UP))
                                {
                                    y -= moveSpeed;
                                    dir = UP;

                                    if(y < 0)
                                        y = disp_data.height;
                                }
                                else
                                    if(al_key_down(&keyState,ALLEGRO_KEY_R))
                                    {
                                        ex = rand() % w + 10;
                                        ey = rand() % h + 10;
                                    }
                                    else
                                        if(al_key_down(&keyState,ALLEGRO_KEY_M))
                                        {
                                            if(music)
                                            {
                                                music = false;

                                                al_stop_sample_instance(songInstance);
                                            }
                                            else
                                                if(!music)
                                                {
                                                    music = true;

                                                    al_set_sample_instance_playmode(songInstance,ALLEGRO_PLAYMODE_LOOP);

                                                    al_attach_sample_instance_to_mixer(songInstance,al_get_default_mixer());

                                                    al_set_sample_instance_gain(songInstance,0.25);

                                                    al_play_sample_instance(songInstance);
                                                }
                                        }

                                        else
                                        {
                                            active = false;
                                            al_draw_text(font,al_map_rgb(44,117,255),w - 100,h - 60,ALLEGRO_ALIGN_RIGHT,"Press 'M' to stop Music");
                                            al_draw_text(font,al_map_rgb(44,117,255),w - 65,h - 40,ALLEGRO_ALIGN_RIGHT,"Press 'R' to respawn the coin");
                                            al_draw_text(font,al_map_rgb(44,117,255),w - 1150,h - 60,ALLEGRO_ALIGN_RIGHT,"Press 'ESC' to exit");


                                        }

                                if(moveSpeed>=103)
                                    ++i;

                                if(!collision(x,y,ex,ey,32,32) && moveSpeed < 103)
                                {
                                    al_draw_bitmap_region(coin,0,0,32,32,ex,ey,NULL);
                                }
                                else
                                {
                                    al_play_sample(soundEffect,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,0);

                                    ++moveSpeed;

                                    randomize();
                                }
                                if(active)
                                    sourceX += al_get_bitmap_width(player)/3;
                                else
                                    sourceX = 32;

                                if(sourceX >= al_get_bitmap_width(player))
                                    sourceX = 0;

                                sourceY = dir;
                }

                if(draw && moveSpeed < 103)
                {
                    draw = false;
                    al_draw_bitmap_region(player,sourceX,dir*al_get_bitmap_height(player)/4,32,32,x,y,NULL);
                    al_flip_display();
                    al_clear_to_color(al_map_rgb(47,79,47));
                }
                else
                    if(draw && moveSpeed >= 103)
                    {
                        draw = false;
                        al_draw_bitmap_region(player,sourceX,dir*al_get_bitmap_height(player)/4,32,32,x,y,NULL);
                        randomize();
                        al_draw_text(font,al_map_rgb(44,117,255),ex,ey,ALLEGRO_ALIGN_RIGHT,"YOU ARE FABULOUS!!");

                        h = disp_data.height;
                        w = disp_data.width;

                        al_draw_text(font2,al_map_rgb(255,36,0),w - 700,h - 500,ALLEGRO_ALIGN_CENTER,"ERROR!!!!!");
                        al_draw_text(font2,al_map_rgb(255,36,0),w - 700,h - 400,ALLEGRO_ALIGN_CENTER,"PRESS 'ESC'!!!!!");

                        al_flip_display();

                        if(i == 1000)
                            done = true;
                    }
    }

    al_destroy_sample(soundEffect);
    al_destroy_sample(song);
    al_destroy_sample_instance(songInstance);
    al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);
    al_destroy_bitmap(player);
    al_destroy_bitmap(coin);
    al_destroy_font(font);
    al_destroy_font(font2);
    al_destroy_font(copyright);

}
