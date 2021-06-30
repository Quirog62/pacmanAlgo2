#include "pacman.h"

Pacman::Pacman(Mapa m) : _mapa(m), 
                        _cantMov(0),      
                          _coordJugador(m.inicio()){
                              
    vector<vector<bool>> fil;
    for(Nat i = 0; i < m.largo()+1; i++){
        vector<bool> col(m.alto()+1,0);
        
        for(Nat j = 0; j < m.alto()+1; j++){
            for(Coordenada c: m.chocolates()){
                if(m.chocolates().count(make_pair(i,j))==1){
                    col[j]=true;
                }  
            }
        }
        fil.push_back(col);
    }
    _chocolates=fil;
    if(m.esChocolate(_coordJugador)){
        _inmunidad=10;
        _chocolates[_coordJugador.first][_coordJugador.second]=false;
    }
    else {
        _inmunidad=0;
    }
}

Pacman::~Pacman(){
}

Coordenada Pacman::sumar_direccion(Direccion d, Coordenada cor){
    if(d == ARRIBA){
        cor.second++;
    }
    else if(d == ABAJO){
        cor.second--;
    }
    else if(d == DERECHA){
        cor.first++;
    }
    else{
        cor.first--;
    }

    return cor;
}

bool Pacman::mover(Direccion d){
    bool res = false;
    Coordenada prox = sumar_direccion(d, _coordJugador);

    if(!(gano() || perdio())){

        if(prox.first > 0 && prox.first < _mapa.largo()+1 && prox.second > 0 && prox.second < _mapa.alto()+1){
            if(!_mapa.esPared(prox)){
                _coordJugador = prox;
                _cantMov++;
                res = true;
                if(_chocolates[_coordJugador.first][_coordJugador.second]){
                    _inmunidad = 10;
                    _chocolates[_coordJugador.first][_coordJugador.second] = false;
                } else {
                    if(_inmunidad > 0){
                        _inmunidad--;
                    }
                }
            }
        } 
    }
    return res;
}

void Pacman::resetearPartida(){
    _cantMov = 0;
    _coordJugador = _mapa.inicio();
    for(Coordenada c: _mapa.chocolates()){
        _chocolates[c.first][c.second] = true;
    }
    if(_chocolates[_coordJugador.first][_coordJugador.second]){
        _inmunidad = 10;
        _chocolates[_coordJugador.first][_coordJugador.second] = false;
    } else {
        _inmunidad = 0;
    }
}

Mapa* Pacman::mapa(){
    return &_mapa;
}  

Coordenada Pacman::jugador() const{
    return _coordJugador;
}

set<Coordenada> Pacman::chocolates() const{
    return _mapa.chocolates();
}

set<Coordenada> Pacman::chocolatesActuales() const{
    set<Coordenada> res;
    for(Nat i = 0; i < _chocolates.size(); i++){
        for(Nat j = 0; j < _chocolates[0].size(); j++){
            if(_chocolates[i][j]){
                res.insert(make_pair(i, j));
            }
        }
    }
    return res;
}

Nat Pacman::cantMov() const{
    return _cantMov;
}

bool Pacman::perdio() const {
    return _mapa.esFantasma(_coordJugador) && _inmunidad == 0 && !gano();
}

bool Pacman::gano() const {
    return _coordJugador == _mapa.llegada();
}

Nat Pacman::inmunidad() const{
    return _inmunidad;
}

