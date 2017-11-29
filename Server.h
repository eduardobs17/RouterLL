#ifndef ROUTER_LEGOS_SERVER_H
#define ROUTER_LEGOS_SERVER_H
#include <string>
#include "Mensaje.h"

class Server {
public:
    explicit Server(int);
    void analizarPaquete(int);
    void error(const char*);
    void socketS();

private:
    int portno;
    Mensaje* msj;
};

#endif //ROUTER_LEGOS_SERVER_H