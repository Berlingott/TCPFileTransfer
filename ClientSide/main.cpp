
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string>
#include <iostream>
#include "TelechargementDuFichier.h"
#include "SequenceDIdentification.h"
#include "SelectionDuFichier.h"

void SequenceDeCommunication(char buffer[256], int socket_fileDescriptor){
    int nlecture = 0;
    if(SequenceDIdentification(socket_fileDescriptor, nlecture, buffer)){
        std::string nomDuFichier = SelectionDuFichier(socket_fileDescriptor, nlecture, buffer);
        // DEBUT TELECHARGEMENT FICHIER
        bzero(buffer, 255);
        int n;
        FILE *fp;
        const char *filename = nomDuFichier.c_str();
        char buffer[255];

        fp = fopen(filename, "w+b");
        while (1) {
            n = recv(socket_fileDescriptor, buffer, 255, 0);
            std::cout << buffer;
            if (n <= 0){
                break;
                return;
            }
            fprintf(fp, "%s", buffer);
            bzero(buffer, 255);
        }
        return;


        // FIN TELECHARGEMENT DE FICHIER
    }
}



int main(int argc, char *argv[]){
    int socket_fileDescriptor, portNumber, nlecture, nouveau_sock;
    socklen_t nouvelle_adresse_size;
    struct sockaddr_in server_address, nouvelle_adresse;
    struct hostent *server;

    char buffer[256];
    if (argc < 3){
        fprintf(stderr,"usage %s hostname port\n", argv[0]);
        exit(0);
    }
    portNumber = atoi(argv[2]);
    socket_fileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fileDescriptor < 0) {
        MessageDErreur("Error: erreur lors de l'ouverture du socket_fileDescriptor");
        exit(1);
    }
    server = gethostbyname(argv[1]);
    if (server == NULL){
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&server_address.sin_addr.s_addr,
            server->h_length);
    server_address.sin_port = htons(portNumber);
    if (connect(socket_fileDescriptor, (struct sockaddr *) &server_address, sizeof(server_address)) < 0){
        MessageDErreur("ERROR: erreur de connexion");
    }
    /*
    ***********************essait
    nouvelle_adresse_size = sizeof(nouvelle_adresse);
    nouveau_sock = accept(socket_fileDescriptor, (struct sockaddr*)&nouvelle_adresse, &nouvelle_adresse_size);
    TelechargementDuFichier(nouveau_sock,91);
    ***********************essait
    */

    SequenceDeCommunication(buffer, socket_fileDescriptor);

    close(socket_fileDescriptor);
    return 0;

}
//12950111