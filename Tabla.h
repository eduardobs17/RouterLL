#ifndef ROUTER_LEGOS_TABLA_H
#define ROUTER_LEGOS_TABLA_H
#include <iostream>

using namespace std;

class Tabla {
public:
    Tabla();
    void llenarTabla();
    string idRed[6];
    string idSalida[6];
    int dist[6];
};

#endif //ROUTER_LEGOS_TABLA_H