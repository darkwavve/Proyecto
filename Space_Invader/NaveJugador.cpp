#include "NaveJugador.h"

NaveJugador::NaveJugador(int num_x,int num_y)
{
    this->num_x = num_x;
    this->num_y = num_y;
    texturas = al_load_bitmap("assets/64_2.png");
    textura_der = al_load_bitmap("assets/64_2_strife_r.png");
    textura_izq = al_load_bitmap("assets/64_2_strife_l.png");
    textura_actual = texturas;
}

NaveJugador::~NaveJugador()
{
    //dtor
}

void NaveJugador::logic(ALLEGRO_KEYBOARD_STATE keyStates)
{
    if(events.type == ALLEGRO_EVENT_TIMER)
    {
        al_get_keyboard_state(&keyStates);
           if(al_key_down(&keyStates,ALLEGRO_KEY_DOWN))
                num_y += 5;
           if(al_key_down(&keyStates,ALLEGRO_KEY_UP))
                num_y -= 5;
           if(al_key_down(&keyStates,ALLEGRO_KEY_RIGHT))
                num_x += 5;
           if(al_key_down(&keyStates,ALLEGRO_KEY_LEFT))
                num_x -= 5;
           if(al_key_down(&keyStates,ALLEGRO_KEY_SPACE) && !shoot)
            {
                shoot = true;
                x++;
                y++;
            }
    }
    al_draw_bitmap(textura_actual,x,y,NULL);
}
