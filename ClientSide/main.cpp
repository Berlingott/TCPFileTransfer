#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>


void MessageDErreur(const char *msg){
    perror(msg); // interprétation du message d'erreur dans la console
    exit(1); // interruption du programme
}
void TelechargementDuFichier(int socket_fileDescriptor, int SIZE){
    int n;
    FILE *fp;
    char *filename = "zambla.m4a";
    char buffer[SIZE];
    fp = fopen(filename, "w");
    while (1) {
        n = recv(socket_fileDescriptor, buffer, SIZE, 0);
        if (n <= 0){
            break;
            return;
        }
        fprintf(fp, "%s", buffer);
        bzero(buffer, SIZE);
    }
    return;
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
    //***********************essait
    nouvelle_adresse_size = sizeof(nouvelle_adresse);
    nouveau_sock = accept(socket_fileDescriptor, (struct sockaddr*)&nouvelle_adresse, &nouvelle_adresse_size);
    TelechargementDuFichier(nouveau_sock,12950111);
    //***********************essait

    printf("Quel est le fichier que vous voullez télécharger ? (ex:1): ");
    bzero(buffer,256);
    fgets(buffer,255,stdin);
    nlecture = write(socket_fileDescriptor, buffer, strlen(buffer));

    if (nlecture < 0)
        MessageDErreur("ERROR: Erreur lors de l'envoie au serveur");
    bzero(buffer,256);
    nlecture = read(socket_fileDescriptor, buffer, 255);

    if (nlecture < 0)
        MessageDErreur("ERROR: erreur lors de la lecture du serveur ");

    printf("%s\n", buffer);
    close(socket_fileDescriptor);
    return 0;

}
//12950111