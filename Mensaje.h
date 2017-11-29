#ifndef ROUTER_LEGOS_MENSAJE_H
#define ROUTER_LEGOS_MENSAJE_H
#include <vector>
#include <string>

using namespace std;

class Mensaje {
public:
    Mensaje();

    void setDirFuente(string);
    void setDirDestino(string);
    void setAccion(string);
    void setIdAccion(int);
    void setMensaje(string);
    void setPaquete(string);

    string getPaquete();
    vector<string> obtenerInfo();

private:
    //ipFuente
    //ipDestino
    //accion
    //idAccion
    //mensaje
    string paq;

    string contenido;
};

#endif //ROUTER_LEGOS_MENSAJE_H