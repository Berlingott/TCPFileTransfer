//
// Created by Simon Duchesne on 2023-02-27.
//

#ifndef CLIENTSIDE_SEQUENCEDIDENTIFICATION_H
#define CLIENTSIDE_SEQUENCEDIDENTIFICATION_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string>
#include "checkforerror.h"
#endif CLIENTSIDE_SEQUENCEDIDENTIFICATION_H

bool SequenceDIdentification(int socket_fileDescriptor, int nlecture,  char buffer[256]) {
//Réception de connexion + nous devons recevoir une demande de pseudeo
    bzero(buffer,255);
    nlecture = read(socket_fileDescriptor, buffer, 255);
    checkforerror(nlecture,"ERROR:  erreur lors de la lecture du serveur ");
    printf("%s\n", buffer);

    // envoie de pseudo
    bzero(buffer,255);
    fgets(buffer,255,stdin);
    nlecture = write(socket_fileDescriptor, buffer, strlen(buffer));

    //lecture de réponse de l'envoie du pseudo ( cela devrait demander le mot de passe)
    bzero(buffer,255);
    nlecture = read(socket_fileDescriptor, buffer,255);
    printf("%s\n", buffer);

    //envoie de mot de passe
    bzero(buffer,255);
    fgets(buffer,255,stdin);
    nlecture = write(socket_fileDescriptor, buffer, strlen(buffer));

    //lecture de réponse de l'envoie du mdp ( cela devrait dire que nous avons accès au fichier)
    bzero(buffer,255);
    nlecture = read(socket_fileDescriptor, buffer,255);
    checkforerror(nlecture,"ERROR: erreur lors de la lecture du serveur ");
    printf("%s\n", buffer);

    return true;
}
