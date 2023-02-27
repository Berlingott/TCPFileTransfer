//
// Created by Simon Duchesne on 2023-02-27.
//

#ifndef SERVERSIDE_MESSAGEDERREUR_H
#define SERVERSIDE_MESSAGEDERREUR_H

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <arpa/inet.h> // convertion de big-endian a little-endiaan

#endif //SERVERSIDE_MESSAGEDERREUR_H

void MessageDErreur(const char *msg){
    perror(msg); // interprétation du message d'erreur dans la console
    exit(1); // interruption du programme
}