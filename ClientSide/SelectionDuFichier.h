//
// Created by Simon Duchesne on 2023-02-27.
//

#ifndef CLIENTSIDE_SELECTIONDUFICHIER_H
#define CLIENTSIDE_SELECTIONDUFICHIER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string>

#endif //CLIENTSIDE_SELECTIONDUFICHIER_H

std::string SelectionDuFichier(int socket_fileDescriptor, int nlecture,  char buffer[256]){
    //Si la sequence dIdentification est réussi, procédos au fichier

    std::string stopcode = "Code:ECHO-NOVEMBER-DELTA";
    std::string nomDuFichier;
    char stopcodechar[256];
    strcpy(stopcodechar, stopcode.c_str());


    do{
        //sequence de proposition des fichiers
        bzero(buffer, 255);
        nlecture = read(socket_fileDescriptor, buffer, 255);
        checkforerror(nlecture, "ERROR: erreur lors de l'envoie d'un nom de fichier ");
        if (strcmp(buffer,stopcodechar) != 0 ){ printf("%s\n", buffer);}
        // fin de séquence des fichiers
    }
    while(strcmp(buffer,stopcodechar) != 0 );

    //demande du nom de fichier
    bzero(buffer, 255);
    nlecture = read(socket_fileDescriptor, buffer, 255);
    checkforerror(nlecture, "ERROR:erreur lors de la demande d'un fichier ");
    printf("%s\n", buffer);

    //envoie d'un nom de fichier
    bzero(buffer,255);
    fgets(buffer,255,stdin);
    write(socket_fileDescriptor, buffer, strlen(buffer));
    nomDuFichier = buffer;
    nomDuFichier = nomDuFichier.substr(0, nomDuFichier.size()-1);
    return nomDuFichier;
}