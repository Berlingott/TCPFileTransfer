//
// Created by Simon Duchesne on 2023-02-27.
//

#ifndef CLIENTSIDE_MESSAGEDERREUR_H
#define CLIENTSIDE_MESSAGEDERREUR_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#endif CLIENTSIDE_MESSAGEDERREUR_H



void MessageDErreur(const char *msg){
    perror(msg); // interprétation du message d'erreur dans la console
    exit(1); // interruption du programme
}