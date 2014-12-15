#ifndef NAVEJUGADOR_H
#define NAVEJUGADOR_H
#include "Naves.h"

class NaveJugador : public Naves
{
    public:
    ALLEGRO_BITMAP* disparo;
    ALLEGRO_EVENT events;
        NaveJugador(int num_x,int num_y);
        virtual ~NaveJugador();
        void logic(ALLEGRO_KEYBOARD_STATE keyStates);
    protected:
    private:
};

#endif // NAVEJUGADOR_H
