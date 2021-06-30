#include "mapa.h"
#include <cmath>

Mapa::Mapa(Nat largo, Nat alto, Coordenada inicio, Coordenada llegada, set<Coordenada> paredes, set<Coordenada> fantasmas, set<Coordenada> chocolates) :
    _largo(largo), _alto(alto), _inicio(inicio), _llegada(llegada), _paredes(paredes), _fantasmas(fantasmas), _chocolates(chocolates){

    for(Nat i = 0; i < largo+1; i++){

        vector<Nat> col(alto+1, ESPACIO);
        
        for(Nat j = 0; j < alto+1; j++){
        
            for(Coordenada c : fantasmas){
                if(absAux(i, c.first) + absAux(j, c.second) <= 3){
                    col[j] = FANTASMA;
                }
            }
            if(paredes.count(make_pair(i,j))==1){
                col[j] = PARED;
            }
        }
        
        _mapa.push_back(col);
    
    }

}

Nat Mapa::absAux(Nat x, Nat y){
    int res = x - y;
    if(res < 0){
        return res *-1;
    }
    return res;
}

Mapa::~Mapa(){
}
        
Nat Mapa::largo() const {
    return _largo;
}

Nat Mapa::alto() const {
    return _alto; 
}

Coordenada Mapa::inicio() const {
    return _inicio;
}
        
Coordenada Mapa::llegada() const {
    return _llegada;
}
        
set<Coordenada> Mapa::paredes() const{
    return _paredes;
}

set<Coordenada> Mapa::fantasmas() const{
    return _fantasmas;
}

set<Coordenada> Mapa::chocolates()const{
    return _chocolates;
}
        
//quizá no van los Mapa
bool Mapa::esPared(const Coordenada c) const{
    return _mapa[c.first][c.second] == PARED;
}
    
bool Mapa::esFantasma(const Coordenada c) const{
    return _mapa[c.first][c.second] == FANTASMA;
}
        
bool Mapa::esChocolate(const Coordenada c) const{
    bool res = false;
    for(Coordenada choco: _chocolates){
        if(c == choco){
            res = true;
        }
    }
    return res;
}