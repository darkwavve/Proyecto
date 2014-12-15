#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include "NaveJugador.h"
#include <list>
#include <iostream>

using namespace std;

#define ScreenWidth   800
#define ScreenHeight  600

string comenzar = "assets/botones/comenzar.png",p_comenzar = "assets/botones/s_comenzar.png";
string high_scores = "assets/botones/highscore.png",p_high_scores = "assets/botones/s_highscore.png";
string instrucciones = "assets/botones/instrucciones.png",p_instrucciones = "assets/botones/s_instrucciones.png";
string salir = "assets/botones/salir.png",p_salir = "assets/botones/s_salir.png";
string arrow = "assets/botones/arrow.png",p_arrow = "assets/botones/arrow1.png";
string background_1 ="assets/POL-parallel-fields-short.wav";

bool done = false,done_inst = false,done_game = false,shoot =false,done_sh = false,boss_shoot = false, done_ganar = false,done_perder;
int moveSpeed = 5,num = 0;
int x = 0, y = 0;

string boton1 = comenzar,boton2 = high_scores,boton3 = instrucciones, boton4 = salir,botonflecha = arrow;

int main();

bool Colision(int x,int y, int w,int h,int x1,int y1,int w1,int h1)
{
    return x + w > x1 && x < x1 + w1
            && y + h > y1 && y < h1 + y1;
}

void perder(ALLEGRO_EVENT_QUEUE* event,ALLEGRO_EVENT events, ALLEGRO_TIMER* timer,ALLEGRO_DISPLAY* display)
{
    done_perder = false;
    ALLEGRO_BITMAP* fondo = al_load_bitmap("assets/background.png");
    ALLEGRO_FONT* font = al_load_ttf_font("assets/BaseOne-Bold.otf",60,NULL);

    while(!done_perder)
    {
        ALLEGRO_EVENT events;
        al_wait_for_event(event,&events);
        if(events.type == ALLEGRO_EVENT_KEY_DOWN)
            {
                switch(events.keyboard.keycode)
                {
                    case ALLEGRO_KEY_ENTER:
                        done_perder = true;
                        break;
                }
            }
        al_flip_display();
        al_clear_to_color(al_map_rgb(0,0,0));
        al_draw_bitmap(fondo,0,0,NULL);
        al_draw_textf(font, al_map_rgb(44,117,255),ScreenWidth / 2,ScreenHeight / 2, ALLEGRO_ALIGN_CENTRE,"PERDISTES");
    }

}

void ganar(ALLEGRO_EVENT_QUEUE* event,ALLEGRO_EVENT events, ALLEGRO_TIMER* timer,ALLEGRO_DISPLAY* display)
{
    done_ganar = false;
    ALLEGRO_BITMAP* fondo = al_load_bitmap("assets/background.png");
    ALLEGRO_FONT* font = al_load_ttf_font("assets/BaseOne-Bold.otf",60,NULL);

    while(!done_ganar)
    {
        ALLEGRO_EVENT events;
        al_wait_for_event(event,&events);
        if(events.type == ALLEGRO_EVENT_KEY_DOWN)
            {
                switch(events.keyboard.keycode)
                {
                    case ALLEGRO_KEY_ENTER:
                        done_ganar = true;
                        break;
                }
            }
        al_flip_display();
        al_clear_to_color(al_map_rgb(0,0,0));
        al_draw_bitmap(fondo,0,0,NULL);
        al_draw_textf(font, al_map_rgb(44,117,255),ScreenWidth / 2,ScreenHeight / 2, ALLEGRO_ALIGN_CENTRE,"GANASTES");
    }
}

void comenzarJuego(ALLEGRO_EVENT_QUEUE* event,ALLEGRO_EVENT events, ALLEGRO_TIMER* timer,ALLEGRO_DISPLAY* display)
{
    done_game = false;
    int num_x = 360,num_y = 500;
    int boss_hp = 500,vidas = 3;
    bool mode = false;
    int boss_x = 150,boss_y = 300;

    ALLEGRO_KEYBOARD_STATE keyStates;
    ALLEGRO_BITMAP* fondo = al_load_bitmap("assets/background.png"),*nave = al_load_bitmap("assets/64_2.png"),
                  * bullet = al_load_bitmap("assets/bullet.png"),*boss = al_load_bitmap("assets/sprite_angleboss.png");
    ALLEGRO_FONT* font = al_load_ttf_font("assets/BaseOne-Bold.otf",60,NULL);

    al_reserve_samples(1);
    ALLEGRO_SAMPLE* soundEffect = al_load_sample("assets/SHOOT011.mp3");
    while(!done_game)
    {
        ALLEGRO_EVENT events;
        al_wait_for_event(event,&events);
        if(events.type == ALLEGRO_EVENT_KEY_DOWN)
            {
                switch(events.keyboard.keycode)
                {
                    case ALLEGRO_KEY_ESCAPE:
                        done_game = true;
                        break;
                }
            }

        if(events.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            int value = al_show_native_message_box(display,"SALIR","SALIR","Esta seguro que desea SALIR?",NULL,ALLEGRO_MESSAGEBOX_WARN | ALLEGRO_MESSAGEBOX_YES_NO);

                if(value == 1)
                    done = true;
        }

        if(events.type == ALLEGRO_EVENT_TIMER)
        {
        al_get_keyboard_state(&keyStates);
           if(al_key_down(&keyStates,ALLEGRO_KEY_DOWN))
                num_y += moveSpeed;
           if(al_key_down(&keyStates,ALLEGRO_KEY_UP))
                num_y -= moveSpeed;
           if(al_key_down(&keyStates,ALLEGRO_KEY_RIGHT))
                num_x += moveSpeed;
           if(al_key_down(&keyStates,ALLEGRO_KEY_LEFT))
                num_x -= moveSpeed;
           if(al_key_down(&keyStates,ALLEGRO_KEY_SPACE) && !shoot)
            {
                al_play_sample(soundEffect,3.0F,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,0);
                shoot = true;
                x = num_x;
                y = num_y;
            }
        }
        al_flip_display();
        al_clear_to_color(al_map_rgb(0,0,0));
        al_draw_bitmap(fondo,0,0,NULL);
        if(!mode)
        {
            boss_shoot =true;
            if(boss_shoot)
            {
                al_draw_bitmap(bullet,boss_x,boss_y+=2,NULL);
                al_draw_bitmap(bullet,boss_x+250,boss_y+=2,NULL);
                al_draw_bitmap(bullet,boss_x+500,boss_y+=2,NULL);

                if(boss_y > 600)
                 {
                  boss_y =  300;
                  boss_shoot = false;
                 }
                 else
                    boss_shoot =true;
            }
            boss_x+=2;
                if(boss_x > 300)
                    mode = true;
        }
            else
        {
           if(boss_shoot)
            {
                al_draw_bitmap(bullet,boss_x,boss_y+=2,NULL);
                al_draw_bitmap(bullet,boss_x+250,boss_y+=2,NULL);
                al_draw_bitmap(bullet,boss_x+500,boss_y+=2,NULL);
                if(boss_y > 600)
                 {
                  boss_y =  300;
                  boss_shoot = false;
                 }
                 else
                    boss_shoot =true;

        if(Colision(boss_x,boss_y,15,20,num_x,num_y,80,80) || Colision(boss_x+250,boss_y,15,20,num_x,num_y,80,80)
                || Colision(boss_x+500,boss_y,15,20,num_x,num_y,80,80) )
        {
            vidas--;
            boss_shoot = false;
        }
            }
            boss_x-=2;
            if(vidas == 0)
            {
            perder(event,events,timer,display);
            done_game =true;
            }
                if(boss_x < 0)
                    mode = false;
        }
        al_draw_bitmap(boss,boss_x,0,NULL);
        al_draw_bitmap(nave,num_x ,num_y,NULL);

        if(shoot)
        {
            al_draw_bitmap(bullet,x+35,y-=5,NULL);

        if(Colision(x,y,15,20,boss_x,0,500,300))
        {
            boss_hp -=10;
            if(boss_hp > 0)
            num +=10;
            if(boss_hp<0)
            {
            boss_hp = 0;
            ganar(event,events,timer,display);
            done_game =true;
            }

            shoot = false;
        }

            if(y<0)
                shoot = false;
        }
        al_draw_textf(font, al_map_rgb(44,117,255),100, 0, ALLEGRO_ALIGN_CENTRE,"SCORE : %d",num);
        al_draw_textf(font, al_map_rgb(44,117,255),700, 0, ALLEGRO_ALIGN_CENTRE,"HP : %d",boss_hp);
        al_draw_textf(font, al_map_rgb(44,117,255),400, 0, ALLEGRO_ALIGN_CENTRE,"Vidas x %d",vidas);
     }
     al_destroy_sample(soundEffect);
     al_destroy_bitmap(bullet);
     al_destroy_bitmap(nave);
     al_destroy_font(font);
     al_destroy_bitmap(fondo);
}
void high_score(ALLEGRO_EVENT_QUEUE* event,ALLEGRO_EVENT events, ALLEGRO_TIMER* timer,ALLEGRO_DISPLAY* display)
{
    done_sh = false;
    ALLEGRO_BITMAP* flecha = al_load_bitmap(botonflecha.c_str()),* fondo = al_load_bitmap("assets/background.png");
    ALLEGRO_FONT* font = al_load_ttf_font("assets/BaseOne-Bold.otf",60,NULL);

     while(!done_sh)
    {
    ALLEGRO_EVENT events;
        al_wait_for_event(event,&events);

        if(events.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            int value = al_show_native_message_box(display,"SALIR","SALIR","Esta seguro que desea SALIR?",NULL,ALLEGRO_MESSAGEBOX_WARN | ALLEGRO_MESSAGEBOX_YES_NO);

                if(value == 1)
                    done = true;
        }
        else if(events.type == ALLEGRO_EVENT_MOUSE_AXES)
        {
            x = events.mouse.x;
            y = events.mouse.y;
        }
        else if(events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            if(events.mouse.button & 1 && x > 100 && x < 300 && y > 450 && y < 550)
                done_sh = true;
        }
        al_flip_display();
        al_clear_to_color(al_map_rgb(0,0,0));
        al_draw_bitmap(fondo,0,0,NULL);
        al_draw_textf(font, al_map_rgb(44,117,255) ,ScreenWidth / 2, 50, ALLEGRO_ALIGN_CENTRE,"High Scores");
        al_draw_bitmap(flecha,100,ScreenHeight  - 150,NULL);
        }
        al_destroy_bitmap(fondo);
        al_destroy_bitmap(flecha);
        al_destroy_font(font);
}

void instruccion(ALLEGRO_EVENT_QUEUE* event,ALLEGRO_EVENT events, ALLEGRO_TIMER* timer,ALLEGRO_DISPLAY* display)
{
    done_inst= false;
    ALLEGRO_BITMAP* flecha = al_load_bitmap(botonflecha.c_str()), * direccion = al_load_bitmap("assets/botones/direccion.png"),
                    * spacebar = al_load_bitmap("assets/botones/spacebar.png"),* fondo = al_load_bitmap("assets/background.png");
    ALLEGRO_FONT* font = al_load_ttf_font("assets/BaseOne-Bold.otf",60,NULL);

     while(!done_inst)
    {
    ALLEGRO_EVENT events;
        al_wait_for_event(event,&events);

        if(events.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            int value = al_show_native_message_box(display,"SALIR","SALIR","Esta seguro que desea SALIR?",NULL,ALLEGRO_MESSAGEBOX_WARN | ALLEGRO_MESSAGEBOX_YES_NO);

                if(value == 1)
                    done = true;
        }
        else if(events.type == ALLEGRO_EVENT_MOUSE_AXES)
        {
            x = events.mouse.x;
            y = events.mouse.y;
        }
         else if(events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            if(events.mouse.button & 1 && x > 100 && x < 300 && y > 450 && y < 550)
                done_inst = true;
        }

        al_flip_display();
        al_clear_to_color(al_map_rgb(0,0,0));
        al_draw_bitmap(fondo,0,0,NULL);
        al_draw_textf(font, al_map_rgb(44,117,255) ,ScreenWidth / 2, 50, ALLEGRO_ALIGN_CENTRE,"INSTRUCCIONES");
        al_draw_textf(font, al_map_rgb(44,117,255) ,(ScreenWidth / 4)+50,(ScreenHeight  / 2) , ALLEGRO_ALIGN_CENTRE,"MOVER");
        al_draw_textf(font, al_map_rgb(44,117,255) ,(ScreenWidth / 1.5)+50,(ScreenHeight  / 2), ALLEGRO_ALIGN_CENTRE,"DISPARAR");
        al_draw_bitmap(direccion,(ScreenWidth / 4) -50,(ScreenHeight  / 2) - 100,NULL);
        al_draw_bitmap(spacebar,(ScreenWidth/1.5) -50,(ScreenHeight / 2) - 100,NULL);
        al_draw_bitmap(flecha,100,ScreenHeight  - 150,NULL);
    }
    al_destroy_bitmap(fondo);
    al_destroy_bitmap(flecha);
    al_destroy_bitmap(direccion);
    al_destroy_bitmap(spacebar);
    al_destroy_font(font);
}

int main()
{
    if(!al_init())
    {
        al_show_native_message_box(NULL,NULL,NULL,"Could Not Initialize",NULL,NULL);
        return -1;
    }

    ALLEGRO_DISPLAY* display = al_create_display(ScreenWidth,ScreenHeight);

    const float FPS = 60;

     al_set_new_display_flags(ALLEGRO_WINDOWED | ALLEGRO_RESIZABLE);
     al_set_window_position(display,200,100);
     al_set_window_title(display,"Space Invader");

     if(!display)
    {
        al_show_native_message_box(display,"Sample Text","Display Settings","Display Window Could Not Initialize",NULL,NULL);
        return -1;
    }
    al_init_primitives_addon();
    al_install_keyboard();
    al_install_mouse();
    al_install_audio();
    al_init_acodec_addon();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    al_reserve_samples(1);


    ALLEGRO_BITMAP* boton_1 = al_load_bitmap(boton1.c_str()),* boton_2 = al_load_bitmap(boton2.c_str()),
                  * boton_3 = al_load_bitmap(boton3.c_str()),* boton_4 = al_load_bitmap(boton4.c_str()),
                  * fondo = al_load_bitmap("assets/background.png");

    ALLEGRO_EVENT_QUEUE* event = al_create_event_queue();
    ALLEGRO_TIMER* timer = al_create_timer(1.0/FPS);
    ALLEGRO_COLOR electricBlue = al_map_rgb(44,117,255);
    ALLEGRO_FONT* font = al_load_ttf_font("assets/BaseOne-Bold.otf",60,NULL);
    ALLEGRO_SAMPLE* background_music = al_load_sample(background_1.c_str());
    ALLEGRO_SAMPLE_INSTANCE* backgroundInstance = al_create_sample_instance(background_music);
    al_set_sample_instance_playmode(backgroundInstance,ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(backgroundInstance,al_get_default_mixer());

    al_register_event_source(event,al_get_keyboard_event_source());
    al_register_event_source(event,al_get_timer_event_source(timer));
    al_register_event_source(event,al_get_display_event_source(display));
    al_register_event_source(event,al_get_mouse_event_source());
//    al_hide_mouse_cursor(display);

    al_play_sample_instance(backgroundInstance);

    al_start_timer(timer);

     while(!done)
    {
        ALLEGRO_EVENT events;
        al_wait_for_event(event,&events);
        if(events.type == ALLEGRO_EVENT_KEY_DOWN)
            {
                switch(events.keyboard.keycode)
                {
                    case ALLEGRO_KEY_ESCAPE:
                        int value = al_show_native_message_box(display,"SALIR","SALIR","Esta seguro que desea SALIR?",NULL,ALLEGRO_MESSAGEBOX_WARN | ALLEGRO_MESSAGEBOX_YES_NO);

                        if(value == 1)
                            done = true;
                        break;
                }
            }
        else if(events.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
         int value = al_show_native_message_box(display,"SALIR","SALIR","Esta seguro que desea SALIR?",NULL,ALLEGRO_MESSAGEBOX_WARN | ALLEGRO_MESSAGEBOX_YES_NO);

            if(value == 1)
                done = true;
        }
        else if(events.type == ALLEGRO_EVENT_MOUSE_AXES)
        {
            x = events.mouse.x;
            y = events.mouse.y;

            if(x > 250 && x < 550 && y > 150 && y < 250)
                boton_1 = al_load_bitmap(p_comenzar.c_str());
            else
                boton_1 = al_load_bitmap(comenzar.c_str());
            if(x > 250 && x < 550 && y > 350 && y < 450)
                boton_3 = al_load_bitmap(p_instrucciones.c_str());
            else
                boton_3 = al_load_bitmap(instrucciones.c_str());
            if(x > 250 && x < 550 && y > 250 && y < 350)
                boton_2 = al_load_bitmap(p_high_scores.c_str());
            else
                boton_2 = al_load_bitmap(high_scores.c_str());
            if(x > 250 && x < 550 && y > 450 && y < 550)
                boton_4 = al_load_bitmap(p_salir.c_str());
            else
                boton_4 = al_load_bitmap(salir.c_str());
        }
        else if(events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            if(events.mouse.button & 1 && x > 250 && x < 550 && y > 150 && y < 250)
            {
                comenzarJuego(event,events,timer,display);
            }
            if(events.mouse.button & 1 && x > 250 && x < 550 && y > 250 && y < 350)
            {
                high_score(event,events,timer,display);
            }
            if(events.mouse.button & 1 && x > 250 && x < 550 && y > 350 && y < 450)
            {
                instruccion(event,events,timer,display);
            }

            if(events.mouse.button & 1 &&x > 250 && x < 550 && y > 450 && y < 550)
            {
                int value = al_show_native_message_box(display,"SALIR","SALIR","Esta seguro que desea SALIR?",NULL,ALLEGRO_MESSAGEBOX_WARN | ALLEGRO_MESSAGEBOX_YES_NO);

                if(value == 1)
                    done = true;
            }
        }
        al_flip_display();
        al_clear_to_color(al_map_rgb(0,0,0));
        al_draw_bitmap(fondo,0,0,NULL);
        al_draw_textf(font, electricBlue,ScreenWidth / 2, 50, ALLEGRO_ALIGN_CENTRE,"SPACE INVADER");
        al_draw_bitmap(boton_4,(ScreenWidth / 2) - 150,(ScreenHeight / 2) + 150,NULL);
        al_draw_bitmap(boton_3,(ScreenWidth / 2) - 150,(ScreenHeight / 2) + 50 ,NULL);
        al_draw_bitmap(boton_2,(ScreenWidth / 2) - 150,(ScreenHeight / 2) - 50,NULL);
        al_draw_bitmap(boton_1,(ScreenWidth / 2) - 150,(ScreenHeight / 2) - 150,NULL);
    }
    al_destroy_bitmap(boton_1);
    al_destroy_bitmap(boton_2);
    al_destroy_bitmap(boton_3);
    al_destroy_bitmap(boton_4);
    al_destroy_font(font);
    al_destroy_sample(background_music);
    al_destroy_sample_instance(backgroundInstance);
    al_destroy_display(display);
    al_destroy_event_queue(event);
    return 0;
}
