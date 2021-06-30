#ifndef _PACMAN_H_
#define _PACMAN_H_

#include "Tipos.h"
#include "mapa.h"

class Pacman{
    public:
        Pacman(Mapa m);
        ~Pacman();
        bool mover(Direccion d);
        void resetearPartida();
        
        Mapa* mapa();
        Coordenada jugador() const;
        set<Coordenada> chocolates() const;
        set<Coordenada> chocolatesActuales() const;
        Nat cantMov() const;
        Nat inmunidad() const;
        bool perdio() const;
        bool gano() const;

    private:
        Mapa _mapa;
        Nat _cantMov;
        Coordenada _coordJugador;
        vector<vector<bool>> _chocolates;
        Nat _inmunidad;
        
        Coordenada sumar_direccion(Direccion d, Coordenada cor);
};

#endif