#include <iostream>
#include <thread>
#include "Server.h"

using namespace std;

//Puertos
//Legos recibe de Luces en 2004
//Luces recibe de Legos en 2005
//Terminal recibe de RouterLegos en 2003
//RouterLegos recibe de Terminal en 2002

void interfazLuces() {
    auto * sL = new Server(2002);
    sL->socketS();
}

void interfazLegos() {
    auto * sC = new Server(2005);
    sC->socketS();
}

int main() {
    cout << endl;

    thread hiloLuces(interfazLuces);
    thread hiloLegos(interfazLegos);

    hiloLegos.join();
    hiloLuces.join();
    return 0;
}