//
// Created by Simon Duchesne on 2023-02-27.
//

#ifndef SERVERSIDE_SEQUENCEDIDENTIFICATION_H
#define SERVERSIDE_SEQUENCEDIDENTIFICATION_H
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <arpa/inet.h> // convertion de big-endian a little-endiaan
#endif //SERVERSIDE_SEQUENCEDIDENTIFICATION_H


bool SequenceDIdentification(int new_socket_fileDescriptor, int nlecture,  char buffer[256], std::string user,std::string mdp){
    nlecture = read(new_socket_fileDescriptor,buffer,255);
    if (nlecture < 0) MessageDErreur("ERROR reading from socket");
    printf("pseudo: ",buffer);

    if (buffer == user){// pseudo reconnu
        bzero(buffer,255); //efface le buffer ( réponse précédente)
        send(new_socket_fileDescriptor,"Pseudo reconnu. Quel est votre mot de passe?",100,0);
        nlecture = read(new_socket_fileDescriptor,buffer,255);
        printf("mdp: ",buffer);

        if(buffer == mdp){
            bzero(buffer,255); //efface le buffer ( réponse précédente)
            send(new_socket_fileDescriptor,"Mot de passe reconnu. Voici la liste des fichier disponible:",100,0);
            return true;
        }else{
            bzero(buffer,255); //efface le buffer ( réponse précédente)
            send(new_socket_fileDescriptor,"Mot de passe non-reconnu. Vous allez être déconnecté.",100,0);
            return false;
        }
    } else{//pseudo non reconnu
        bzero(buffer,255); //efface le buffer ( réponse précédente)
        send(new_socket_fileDescriptor,"Pseudo non-reconnu. Vous allez être déconnecté.",100,0);
        return false;
    }
}

