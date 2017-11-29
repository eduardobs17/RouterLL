#include <iostream>
#include <thread>
#include "Server.h"

using namespace std;

//Puertos
//Carritos recibe de Luces en 9090
//Luces recibe de Carritos en 2626
//Terminal recibe de RouterCarritos en 20000
//RouterCarritos recibe de Terminal en 20001

void interfazLuces() {
    auto * sL = new Server(20001);
    sL->socketS();
}

void interfazCarritos() {
    auto * sC = new Server(2626);
    sC->socketS();
}

int main() {
    cout << endl;

    thread hiloL(interfazLuces);
    thread hiloC(interfazCarritos);

    hiloC.join();
    hiloL.join();
    return 0;
}