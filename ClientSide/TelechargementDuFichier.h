//
// Created by Simon Duchesne on 2023-02-27.
//

#ifndef CLIENTSIDE_TELECHARGEMENTDUFICHIER_H
#define CLIENTSIDE_TELECHARGEMENTDUFICHIER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#endif //CLIENTSIDE_TELECHARGEMENTDUFICHIER_H

void TelechargementDuFichier(int socket_fileDescriptor, int SIZE){
    int n;
    FILE *fp;
    char *filename = "sample.txt";
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