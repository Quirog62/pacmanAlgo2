#include "fichin.h"

Fichin::Fichin(Mapa m): _alguienJugando(false),
                        _jugadorActual(nullptr), 
                        _mapa(m), 
                        _partidaActual(Pacman(m)), 
                        _ranking(string_map<Puntaje>()){
}

Fichin::~Fichin(){
    delete _jugadorActual;
}

const Mapa& Fichin::mapa() const{
    return _mapa;
}

bool Fichin::alguienJugando() const{
    return _alguienJugando;
}

const Jugador& Fichin::jugadorActual() const{
    return *_jugadorActual;
}

const Pacman& Fichin::partidaActual() const{
    return _partidaActual;
}


const string_map<Puntaje>& Fichin::ranking() const{
    return _ranking;
}


bool Fichin::nuevaPartida(Jugador j){
    if(!_alguienJugando){
        _partidaActual.resetearPartida();

        if(_jugadorActual != nullptr){
            delete _jugadorActual;
            _jugadorActual = new Jugador(j);
        } else {
            _jugadorActual = new Jugador(j);
        }

        if(!_partidaActual.perdio()){
            _alguienJugando = true;
        }
        return true;
    } else {
        return false;
    }
}


bool Fichin::mover(Direccion d){
    if(_alguienJugando){
        _partidaActual.mover(d);
        if(_partidaActual.gano()){
            if(_ranking.count(*_jugadorActual) == 0 || _partidaActual.cantMov() < _ranking.at(*_jugadorActual)){
                _ranking.insert(make_pair(*_jugadorActual, _partidaActual.cantMov()));
            }
            _alguienJugando = false;
        }
        if(_partidaActual.perdio()){
            _alguienJugando = false;
        }
        return true;
    } else {
        return false;
    }
}

const pair<Jugador, Puntaje> Fichin::objetivo() const{
    Jugador objetivo = oponente();
    Nat puntaje = _ranking.at(objetivo);
    return make_pair(objetivo, puntaje);
}

const Jugador Fichin::oponente() const{
    set<Jugador> claves = _ranking.claves();
    if(mejorJugador(claves) == *_jugadorActual){
        return *_jugadorActual;
    } else {
        return siguienteJugador(claves);
    }
}

const Jugador Fichin::mejorJugador(const set<Jugador>& claves) const{
    Jugador res = *_jugadorActual;
    Puntaje MejorPuntaje = _ranking.at(*_jugadorActual);
    for(Jugador j: claves){
        if(_ranking.at(j) < MejorPuntaje){
            res = j;
            MejorPuntaje = _ranking.at(j);
        }
    }
    return res;
}

const Jugador Fichin::siguienteJugador(const set<Jugador>& claves) const{
    Puntaje PuntajeJugadorActual = _ranking.at(*_jugadorActual);
    Jugador siguienteJugador = mejorJugador(claves);
    Puntaje PuntajeSiguiente = _ranking.at(siguienteJugador);
    for(Jugador j: claves){
        Puntaje puntaje = _ranking.at(j);
        if(PuntajeSiguiente < puntaje && puntaje < PuntajeJugadorActual){
            siguienteJugador = j;
            PuntajeSiguiente = puntaje;
        }
    } 
    return siguienteJugador;
}





