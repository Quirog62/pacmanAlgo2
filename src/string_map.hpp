#include "string_map.h"

template <typename T>
string_map<T>::string_map() : raiz(nullptr), _size(0){
}

template <typename T>
string_map<T>::string_map(const string_map<T>& aCopiar) : string_map() {
    *this = aCopiar;
}

template <typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& d) {
    _size = d._size;
    if(d.raiz == nullptr){
        raiz = nullptr;
    } else {
        recrear(&raiz, *d.raiz);
    }
    return *this;
}

template <typename T>
void string_map<T>::recrear(Nodo** nuevo, const Nodo& ref){
    if(*nuevo != nullptr){
        delete *nuevo;
    }
    *nuevo = new Nodo();

    if(ref.definicion != nullptr){
        (*nuevo)->definicion = new T(*ref.definicion);
    }

    for(int i = 0; i < ref.siguientes.size(); i++){
        if(ref.siguientes.at(i) != nullptr){
            recrear(&((*nuevo)->siguientes.at(i)), *ref.siguientes.at(i));
        }
    }
}

template <typename T>
string_map<T>::~string_map(){
    if(raiz != nullptr){
        borrado(raiz);
    }
}

template <typename T>
void string_map<T>::borrado(Nodo* nod) {

    if(nod->definicion != nullptr){
        delete(nod->definicion);
        nod->definicion = nullptr;
    }

    for(int i = 0; i < nod->siguientes.size(); i++){
        if(nod->siguientes.at(i) != nullptr){
            borrado(nod->siguientes.at(i));
            nod->siguientes.at(i) = nullptr;
        }
    }

    delete nod;
}

template <typename T>
T& string_map<T>::operator[](const string& clave){
    if(count(clave) == 1){
        return at(clave);
    } else {
        T* nuevoValor = new T();
        insert(make_pair(clave, *nuevoValor));

        return at(clave);
    }
}

template <typename T>
void string_map<T>::insert(const pair<string, T>& par){

    T* val = new T(par.second);
    if(raiz == nullptr){
        if(par.first == ""){
            raiz = new Nodo(val);
            _size++;
        } else {
            raiz = new Nodo();
        }
    }

    int i = 0;
    Nodo* actual = raiz;
    while (i < par.first.size()){

        int asciiLetra = int(par.first.at(i));

        if(i == par.first.size()-1){
            //el nodo no existia
            if(actual->siguientes[asciiLetra] == nullptr){
                actual->siguientes[asciiLetra] = new Nodo(val);
            } else {
                //el nodo existia pero sin clave
                Nodo* temp = actual->siguientes[asciiLetra];
                if(temp->definicion == nullptr){
                    temp->definicion = val;
                } else {
                    //el nodo existia con clave, sobreescribir
                    delete temp->definicion;
                    temp->definicion = val;
                }
            }
            _size++;
        } else {
            if(actual->siguientes[asciiLetra] == nullptr){
                actual->siguientes[asciiLetra] = new Nodo();
            }
        }

        actual = actual->siguientes[asciiLetra];

        i++;
    }

}

template <typename T>
int string_map<T>::count(const string& clave) const{
    int res = 0;

    int i = 0;
    Nodo* actual = raiz;

    while(i < clave.size()){
        int asciiLetra = int(clave.at(i));

        if(actual == nullptr){
            break;
        } else {
            actual = actual->siguientes[asciiLetra];
        }

        i++;
    }

    if(actual != nullptr && actual->definicion != nullptr){
        res = 1;
    }

    return res;
}

template <typename T>
const T& string_map<T>::at(const string& clave) const {
    int i = 0;
    Nodo* actual = raiz;

    while(i < clave.size()){
        int asciiLetra = int(clave.at(i));
        actual = actual->siguientes[asciiLetra];
        i++;
    }

    return *(actual->definicion);
}

template <typename T>
T& string_map<T>::at(const string& clave) {
    int i = 0;
    Nodo* actual = raiz;

    while(i < clave.size()){
        int asciiLetra = int(clave.at(i));
        actual = actual->siguientes[asciiLetra];
        i++;
    }

    return *(actual->definicion);
}

template <typename T>
void string_map<T>::erase(const string& clave) {
    _size--;

    //Ultimo al que no hay que borrar
    Nodo* ultConHijos = raiz;
    Nodo* ultClave = raiz;

    int i = 0;
    int letraSiguiente = int(clave.at(0));

    while(i < clave.size()){
        int asciiLetra = int(clave.at(i));

        if(cantHijos(ultClave) > 1 || ultClave->definicion != nullptr){
            ultConHijos = ultClave;
            letraSiguiente = asciiLetra;
        }

        ultClave = ultClave->siguientes.at(asciiLetra);
        i++;
    }

    delete ultClave->definicion;
    ultClave->definicion = nullptr;

    if(cantHijos(ultClave) == 0){
        borrado(ultConHijos->siguientes.at(letraSiguiente));
        ultConHijos->siguientes.at(letraSiguiente) = nullptr;
    }
}

template <typename T>
int string_map<T>::cantHijos(Nodo *nodo){
    int cant = 0;
    for(int j = 0; j < nodo->siguientes.size(); j++){
        if(nodo->siguientes.at(j) != nullptr){
            cant++;
        }
    }
    return cant;
}

template <typename T>
int string_map<T>::size() const{
    return _size;
}

template <typename T>
bool string_map<T>::empty() const{
    bool res = false;

    if(raiz == nullptr){
        res = true;
    }

    return res;
}

//////////////////////////////////////////
template <typename  T>
set<string> string_map<T>::claves() const{

    set<string> conjClaves;
    if(raiz!= nullptr) {
        for (int i = 0; i < raiz->siguientes.size(); i++) {
            if (raiz->siguientes.at(i) != nullptr) {
                string letra;
                letra.push_back(char(i));
                clavesEn(raiz->siguientes.at(i), letra, conjClaves);
            }
        }
    }
    return conjClaves;
}

template <typename T>
void string_map<T>::clavesEn(Nodo* nodo, string cadena, set<string>& claves) const{

    if(nodo->definicion != nullptr){
        claves.insert(cadena);
    }

    for(int i = 0; i < nodo->siguientes.size(); i++){

        if(nodo->siguientes.at(i) != nullptr){
            string nuevaRama;
            string letra;
            letra.push_back(char(i));

            nuevaRama = cadena + letra;

            clavesEn(nodo->siguientes.at(i), nuevaRama, claves);
        }
    }
}