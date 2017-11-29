#include <unistd.h>
#include <cstring>
#include <netinet/in.h>
#include <iostream>
#include "Server.h"
#include "Client.h"

/**
 * Constructor
 *
 * @param numPort: el numero del puerto que el servidor va a escuchar.
 */
Server::Server(int numPort) {
    portno = numPort;
}

/**
 * Metodo que maneja los errores.
 *
 * @param msg: El error generado.
 */
void Server::error(const char *msg) {
    perror(msg);
    exit(1);
}

/**
 * Metodo que controla las conexiones entrantes.
 *
 * @param tipoMensaje: El tipo del mensaje que se recibe. 1 => luces, 2 => carritos
 */
void Server::socketS() {
    int sockfd, newsockfd, pid;
    struct sockaddr_in serv_addr{}, cli_addr{};

    //Se crea el socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) { error("ERROR opening socket"); }

    //Se limpia el struct. Posteriormente, se llena.
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(static_cast<uint16_t>(portno));
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) { error("ERROR on binding"); }

    cout << "Esperando conexiones..." << endl;

    listen(sockfd, 5);
    socklen_t clilen = sizeof(cli_addr);

    while (true) {
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0) { error("ERROR on accept"); }
        pid = fork();
        if (pid < 0) { error("ERROR on fork"); }
        if (pid == 0)  {
            close(sockfd);
            analizarPaquete(newsockfd);
            exit(0);
        } else {
            close(newsockfd);
        }
    }
}

/**
 * Método que analiza el paquete y reenvia el paquete.

 * @param sock: Id del socket
 * @param tipoMensaje: El tipo del mensaje que se recibe. 1 => luces, 2 => carritos
 */
void Server::analizarPaquete (int sock) {
    cout << endl;
    //Se inicializa la variable
    msj = new Mensaje();

    //Se limpia el buffer llenandolo con 0's.
    char buffer[256];
    bzero(buffer, 256);

    //Se lee el mensaje recibido.
    auto n = static_cast<int>(read(sock, buffer, 255));
    if (n < 0) error("ERROR reading from socket");

    //Se obtiene el paquete y se divide para analizarlo.
    msj->setPaquete(&buffer[0]);
    vector<string> v = msj->obtenerInfo();

    if (v[1] == "25.25.25.25") {
        cout << "Mensaje recibido desde " << v[0] << ": " << v[4] << endl << endl;
    } else {
        cout << "Paquete recibido desde " << v[0] << ": ";
        cout << "[" << v[0] << ", " << v[1] << ", " << v[2] << ", " << v[3] << ", " << v[4] << "]" << endl << endl;

        auto *c = new Client();
        c->prepararMensaje(v[1], msj->getPaquete());

        cout << "Paquete enviado a " << v[1] << ": ";
        cout << "[" << v[0] << ", " << v[1] << ", " << v[2] << ", " << v[3] << ", " << v[4] << "]" << endl << endl;
        cout << "Esperando nuevas conexiones..." << endl << endl;
    }
}