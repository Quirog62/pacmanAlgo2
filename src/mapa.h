#ifndef MAPA_H_
#define MAPA_H_

#include <tuple>
#include "Tipos.h"

class Mapa{
    public:
        Mapa(Nat largo, Nat alto, Coordenada inicio, Coordenada llegada, set<Coordenada> paredes, set<Coordenada> fantasmas, set<Coordenada> chocolates);
        ~Mapa();
        
        Nat largo() const;
        Nat alto() const;
        Coordenada inicio() const;
        Coordenada llegada() const;
        set<Coordenada> paredes() const;
        set<Coordenada> fantasmas() const;
        set<Coordenada> chocolates() const;
        bool esPared(const Coordenada c) const;
        bool esFantasma(const Coordenada c) const;
        bool esChocolate(const Coordenada c) const;
        
    private:
        vector<vector<Nat>> _mapa;
        Nat _alto;
        Nat _largo;
        Coordenada _inicio;
        Coordenada _llegada;
        set<Coordenada> _paredes;
        set<Coordenada> _fantasmas;
        set<Coordenada> _chocolates;

        Nat absAux(Nat x, Nat y);

};

#endif