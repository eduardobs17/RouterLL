#include <iostream>
#include <thread>
#include "Server.h"

using namespace std;

//Puertos
//Legos recibe de Luces en 2004
//Luces recibe de Legos en 8001
//Terminal recibe de RouterLegos en 2003
//RouterLegos recibe de Terminal en 2002

void interfazLuces() {
    auto * sL = new Server(2002);
    sL->socketS();
}

void interfazLegos() {
    auto * sC = new Server(8001);
    sC->socketS();
}

int main() {
    cout << endl << "Esperando conexiones..." << endl << endl;

    thread hiloLuces(interfazLuces);
    thread hiloLegos(interfazLegos);

    hiloLuces.join();
    hiloLegos.join();
    return 0;
}