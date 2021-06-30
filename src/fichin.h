#ifndef _FICHIN_H_
#define _FICHIN_H_

#include "pacman.h"
#include "string_map.h"

class Fichin{
    public:
        Fichin(Mapa m);

        ~Fichin();
        bool mover(Direccion d);
        bool nuevaPartida(Jugador j);

        const Mapa& mapa() const;
        const Jugador& jugadorActual() const;
        const Pacman& partidaActual() const;
        const string_map<Puntaje>& ranking() const;
        const pair<Jugador, Puntaje> objetivo() const;

        bool alguienJugando() const;


    private:
        Mapa _mapa;
        string_map<Puntaje> _ranking;       
        bool _alguienJugando;
        Jugador* _jugadorActual;
        Pacman _partidaActual;

        const Jugador oponente() const;
        const Jugador mejorJugador(const set<Jugador>& claves) const;
        const Jugador siguienteJugador(const set<Jugador>& claves) const;
};

#endif