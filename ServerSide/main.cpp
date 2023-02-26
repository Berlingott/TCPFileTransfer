#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>

#define USERNAME = Simon
#define PASSWORD = MotDePasse

#define PORT 8080 //Déclaration de la constante PORT = 8080
void OuvertureDeFichier(){

}

void MessageDErreur(const char *msg){
    perror(msg); // interprétation du message d'erreur dans la console
    exit(1); // interruption du programme
}

int main(int argc, char const* argv[]){
    int socket_fileDescriptor, new_socket_fileDescriptor, portNumber;
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






}


//