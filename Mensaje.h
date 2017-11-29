#ifndef ROUTER_LEGOS_MENSAJE_H
#define ROUTER_LEGOS_MENSAJE_H
#include <vector>
#include <string>

using namespace std;

class Mensaje {
public:
    Mensaje();
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
};

#endif //ROUTER_LEGOS_MENSAJE_H