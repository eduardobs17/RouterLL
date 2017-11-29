#include "Tabla.h"

/**
 * Constructor
 */
Tabla::Tabla() {
    llenarTabla();
}

/**
 * LLena la tabla con los datos actuales del router.
 */
void Tabla::llenarTabla() {
    //Banderas
    idRed[0] = {"12.0.0.0"};
    idSalida[0] = {"25.0.7.25"}; // Eduardo
    dist[0] = 2;

    //Carritos
    idRed[1] = {"165.8.0.0"};
    idSalida[1] = {"25.0.7.25"}; // Eduardo
    dist[1] = 1;

    //Paletas
    idRed[2] = {"200.5.0.0"};
    idSalida[2] = {"201.6.0.1"}; // Paola
    dist[2] = 2;

    //Bolinchas
    idRed[3] = {"140.90.0.0"};
    idSalida[3] = {"201.6.0.1"}; // Paola
    dist[3] = 1;

    //Luces
    idRed[4] = {"25.0.0.0"};
    idSalida[4] = {"DIRECTO"};
    dist[4] = 0;

    //Legos
    idRed[5] = {"201.6.0.0"};
    idSalida[5] = {"DIRECTO"}; //Daniel
    dist[5] = 0;
}