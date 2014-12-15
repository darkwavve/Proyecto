#ifndef NAVES_H
#define NAVES_H
#include <list>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>

class Naves
{
    public:
    int x,y;
    bool shoot = false;
    int num_x,num_y;
        ALLEGRO_BITMAP* texturas,*textura_izq,*textura_der;
        ALLEGRO_BITMAP* textura_actual;
        Naves();
        virtual ~Naves();
    virtual void logic(ALLEGRO_KEYBOARD_STATE keyStates);
    protected:
    private:
};

#endif // NAVES_H
