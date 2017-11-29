#ifndef ROUTER_LEGOS_CLIENT_H
#define ROUTER_LEGOS_CLIENT_H
#include <string>
#include "Tabla.h"

using namespace std;

class Client {
public:
    Client();
    void error(const char*);
    int socketC(char*, char*, string);
    void prepararMensaje(string, string);

private:
    Tabla* t;
    char* ipLegos;
    char* ipLuces;
    char* portLuces;
    char* portLegos;
};

#endif //ROUTER_LEGOS_CLIENT_H
