#include "Client.h"
#include <unistd.h>
#include <cstring>
#include <utility>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

/**
 * Constructor
 */
Client::Client() {
    t = new Tabla();
    ipC = const_cast<char *>("localhost");
    ipL = const_cast<char *>("localhost");
    portC = const_cast<char *>("9090");
    portL = const_cast<char *>("20000");
}

/**
 * Metodo que maneja los errores.
 *
 * @param msg: El error generado.
 */
void Client::error(const char *msg) {
    perror(msg);
    exit(0);
}

/**
 * Metodo que controla las conexiones salientes.
 *
 * @param ip Direccion ip hacia donde se va a mandar el mensaje
 * @param port Puerto del servidor
 * @param msj Mensaje que se va a transmitir
 * @return 0 si no sucede ningún error.
 */
int Client::socketC(char* ip, char* port, string msj) {
    struct sockaddr_in serv_addr{};

    //Se llena un buffer con el mensaje a transmitir
    char buffer[2048];
    for (int x = 0; x < msj.size(); x++) {
        buffer[x] = msj[x];
    }
    buffer[msj.size()] = '\000';

    printf("Enviando mensaje: estableciendo conexión con el servidor...\n");
    int portno = atoi(port);

    //Se crea el socket.
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");

    struct hostent *server = gethostbyname(ip);
    if (server == nullptr) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    //Se limpia el struct. Posteriormente, se llena.
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy(server->h_addr, (char *)&serv_addr.sin_addr.s_addr, static_cast<size_t>(server->h_length));
    serv_addr.sin_port = htons(static_cast<uint16_t>(portno));
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
        error("ERROR connecting");

    auto n = static_cast<int>(write(sockfd, buffer, strlen(buffer)));
    if (n < 0)
        error("ERROR writing to socket");
    close(sockfd);
    return 0;
}

/**
 * Prepara el paquete y lo envia a la red correspondiente.
 * @param redDest red destino.
 * @param msj mensaje que se va a enviar.
 */
void Client::prepararMensaje(string redDest, string msj) {
    //Se debe reenviar el mensaje según corresponda.
    string destino = std::move(redDest);

    //Buscamos la red destino
    string redDestino;
    int counter = 0;
    int counter2 = 0;
    int bytes = 0;
    int bytesMax = 0;
    bool terminado = false;
    while (!terminado && counter < destino.size()) {
        if (destino[counter] != '.') {
            redDestino += destino[counter];
        } else {
            if (counter2 == 0) {
                int tipoRed = atoi(redDestino.c_str());

                if (tipoRed < 128) {
                    bytesMax = 1;
                }

                if (tipoRed >= 128 && tipoRed < 192) {
                    bytesMax = 2;
                }

                if (tipoRed >= 192) {
                    bytesMax = 3;
                }
                counter2++;
            }

            bytes++;
            if (bytes == bytesMax) {
                terminado = true;
            } else {
                redDestino += destino[counter];
            }
        }

        if (!terminado) {
            counter++;
        }
    }

    if (!terminado) {
        cout << "Sucedió un error buscando la red." << endl;
        exit(-1);
    }

    //Ahora buscamos en la tabla de enrutamiento la red correspondiente.
    int x = 0;
    int i = 0;
    for (x; x < 6; x++) {
        string red = t->idRed[x];

        string aux;
        counter = 0;
        counter2 = 0;
        bytes = 0;
        bytesMax = 0;
        terminado = false;
        while (!terminado && counter < red.size()) {
            if (red[counter] != '.') {
                aux += red[counter];
            } else {
                if (counter2 == 0) {
                    int tipoRed = atoi(aux.c_str());

                    if (tipoRed < 128) {
                        bytesMax = 1;
                    }

                    if (tipoRed >= 128 && tipoRed < 192) {
                        bytesMax = 2;
                    }

                    if (tipoRed >= 192) {
                        bytesMax = 3;
                    }
                    counter2++;
                }

                bytes++;
                if (bytes == bytesMax) {
                    terminado = true;
                } else {
                    aux += red[counter];
                }
            }

            if (!terminado) {
                counter++;
            }
        }

        if (aux == redDestino) {
            i = x;
            x = 10;
        }
    }

    if (t->idSalida[i] == "165.8.6.25") { //Se envia a carritos
        socketC(ipC, portC, msj);
    } else { //Se envia a luces
        if (t->idSalida[i] == "25.25.25.25") {
            socketC(ipL, portL, msj);
        } else { //CASO "DIRECTO"
            if (redDestino == "165.8") { //Se envia a carritos
                socketC(ipC, portC, msj);
            } else { //Se envia a luces
                socketC(ipL, portL, msj);
            }
        }
    }
}