
#ifndef SERVERSIDE_SELECTIONDUFICHIER_H
#define SERVERSIDE_SELECTIONDUFICHIER_H
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
#include <filesystem>
#endif //SERVERSIDE_SELECTIONDUFICHIER_H

std::string SelectionDuFichier(int new_socket_fileDescriptor, int nlecture,  char buffer[256]){

    int nombredefichier;
    std::string availablefiles;
    std::string path = "/Users/berlingott/Desktop/TCPfileTransfer/ServerSide/Files";
    std::string stopcode = "Code:ECHO-NOVEMBER-DELTA";
    //Envoie le nom de tous les fichiers disponibles dans le dossier nommé FILES
    for (const auto & entry : std::__fs::filesystem::directory_iterator(path)){
        bzero(buffer,255);
        availablefiles = entry.path().filename().u8string();
        strcpy(buffer, availablefiles.c_str());
        send(new_socket_fileDescriptor, buffer, 255, 0);
        std::cout << availablefiles << std::endl;
    };
    //envoie de Code:ECHO-NOVEMBER-DELTA signiefie la fin
    // du cote client, tant que la reception n'est pas "Code:ECHO-NOVEMBER-DELTA"
    bzero(buffer,255);
    strcpy(buffer, stopcode.c_str());
    send(new_socket_fileDescriptor, buffer, 255, 0);
    std::cout << buffer << std::endl;

    //Demande du nom de fichier que le client veut
    bzero(buffer,255); //efface le buffer ( réponse précédente)
    send(new_socket_fileDescriptor,"Veuillez entrer le nom du fichier que vous voullez:",100,0);

    // Réception du nom du fichier et ajout au chemin
    nlecture = read(new_socket_fileDescriptor,buffer,255);
    std::cout << "nom du fichier demandé: " << buffer << std::endl;

    //Construction Du chemin du fichier désiré
    std::string buffertostring(buffer);
    buffertostring = buffertostring.substr(0, buffertostring.size()-1);
    std::string cheminfichiervoulu = path + "/" + buffertostring;
    std::cout << cheminfichiervoulu;


    return cheminfichiervoulu;
}
