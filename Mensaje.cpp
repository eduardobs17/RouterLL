#include "Mensaje.h"

using namespace std;

/** Constructor. */
Mensaje::Mensaje() {
    paq = "";
}

/**
 * Establece el paquete del mensaje.
 * @param p El paquete
 * @param tipo El tipo de paquete recibido. 1 => luces. 2 => carritos
 */
void Mensaje::setPaquete(string p) {
    paq = p;
}

/** Divide la información del paquete. */
vector<string> Mensaje::obtenerInfo() {
    vector<string> info;
    int counter = 0;
    string aux;

    for (char x : paq) {
        if (x != '\n' && x != '\000') {
            aux += x;
        } else {
            info.push_back(aux);
            aux = "";
            counter++;
        }
    }

    return info;
}

/** Retorna el paquete completo, es decir, lo que se va a transmitir a otras redes. */
string Mensaje::getPaquete() {
    return paq;
}