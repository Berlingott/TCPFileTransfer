#define _BSD_SOURCE
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <arpa/inet.h> // convertion de big-endian a little-endiaan
#include "MessageDErreur.h"
#include "SequenceDIdentification.h"
#include <filesystem>
#include "SelectionDuFichier.h"
//Hardcoded Identified
const std::string user = "simon\n";
const std::string mdp = "mdp\n";


void SequenceDeCommunication(int new_socket_fileDescriptor, int nlecture,  char buffer[256]){
    if(SequenceDIdentification(new_socket_fileDescriptor, nlecture, buffer, user, mdp)){ // les identifiants sont bon, les fichiers peuvent être donné
    std::string cheminfichiervoulu = SelectionDuFichier(new_socket_fileDescriptor, nlecture, buffer);

         //todo envoyé ce fichier
        //lister tous les noms de fichiers disponible dans le dossier Files

    }
}
void EnvoieDeFichier(FILE *fp, int socket_fileDescriptor){
    int SIZE = 0;
    int n;

    fseek(fp, 0L, SEEK_END);
    SIZE = ftell(fp);
    std::cout << "Taille du fichier: " << SIZE << std::endl;

    char data[12950111];

    while(fgets(data, SIZE, fp) != NULL) {
        if (send(socket_fileDescriptor, data, sizeof(data), 0) == -1) {
            perror("[-]Error in sending file.");
            exit(1);
        }
        bzero(data, SIZE);
    }
}

int main(int argc, char const* argv[]){
    int socket_fileDescriptor, new_socket_fileDescriptor, portNumber;
    int nlecture;
    socklen_t clientlenght;
    char buffer[256]; //buffer pour le client
    struct sockaddr_in server_address, client_address;  // initialization de deux structure
                                                        // structure sockaddre_in pour les adress server_address et client_address
    if (argc < 2){
        fprintf(stderr, "ERROR: Argument manquant lors du lancement du programme.");
        exit(1);
    }
    //Création d'un SOCKET
    //int = socket_fileDescriptor
    //domain = AF_INET      -- domain dans l'IPv4
    //type = SOCK_STREAM    -- type TCP (doit maintenir la connexion
    //protocol = 0          -- Protocol par défaut est à utiliser
    socket_fileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fileDescriptor < 0 ){// tous les code d'erreur dont négatif lors de la création d'un socket
        MessageDErreur("ERROR: Erreur lors de la création du SOCKET"); // on envoie notre raison à la fonction d'erreur
    }

    //Nettoyer notre structure d'address
    bzero((char *) &server_address,sizeof(server_address));

    portNumber = atoi(argv[1]); // Converti l'argument string donnée en lançant le programme en INT

    //Création de l'hôte et son address
    //Big ENDIAN pour l'ordre TCP ip
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(portNumber);

    // bind(int filedescriptor, struct sockaddr addresse_locale, socklen_t longueur_de_ladresse)
    if (bind(socket_fileDescriptor, (struct sockaddr *) &server_address, sizeof(server_address)) < 0){
        MessageDErreur("ERROR: Problème lors du BIND");
    }
    // Début de l'écoute des possibles connexions
    // Toutes les entrées de connexions seront ajouter à la file d'attente
    // Maximum de file d'attente sera de 10 clients
    // listen(socket, nombre_de_clients_en_file_dattente)

    listen(socket_fileDescriptor,10);

    //accept une connexion
    clientlenght = sizeof (client_address);
    //Acceptons la connexion
    // la fonction accept() sauvegardera les information du client (adress) dans la structure
    // new_socket_fileDescriptor et la longueur dans clientlenght
    //Le socket d'origine pourra retourner à accepter des connexion comme celle-ci se retrouve dans
    // une autre stucture

    new_socket_fileDescriptor = accept(socket_fileDescriptor, (struct sockaddr *) &client_address, &clientlenght);

    if (new_socket_fileDescriptor < 0){
        MessageDErreur("ERROR: Erreur lors de la fonction accept()");
    }
    printf("server: got connection from %s port %d\n", inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));

    /*
    //Ouverture du fichier voulu
    //****************************Ouverture du fichier ************************** new shit
    FILE *fp = fopen("/Users/berlingott/Desktop/TCPfileTransfer/ServerSide/sample.txt", "rb");
    if (fp == NULL) {
        MessageDErreur("Error: Erreur lors de l'ouverture de fichier");
        exit(1);
    }

    EnvoieDeFichier(fp, socket_fileDescriptor);
    printf("[+]File data sent successfully.\n");
    //****************************************************** new shit
    */

    //send() pour envoyer une string de x bytes avec le protocol par default 0 au socket sauvegardé
    //send(socket,string,x,0)

    //Sequence de communication
    SequenceDeCommunication(new_socket_fileDescriptor, nlecture, buffer);


    //Fermeture de tous les sockets
    close(new_socket_fileDescriptor);
    close(socket_fileDescriptor);
    return 0;
}


// todo transfer username
// todo transfert de mot de passe
// todo confirmation d'identifiant
// todo envoie liste de fichier
// todo reception de quel fichier
// todo envoie du fichier
// todo reprise de connection
// todo
// todo
// todo
//