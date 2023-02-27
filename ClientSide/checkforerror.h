//
// Created by Simon Duchesne on 2023-02-27.
//

#ifndef CLIENTSIDE_CHECKFORERROR_H
#define CLIENTSIDE_CHECKFORERROR_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string>
#include "MessageDErreur.h"
#endif CLIENTSIDE_CHECKFORERROR_H



void checkforerror(int nlecture, const char *msg){
    if (nlecture < 0) {
        MessageDErreur(msg);
    }
}