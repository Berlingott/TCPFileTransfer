

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string>

#define USERNAME = Simon
#define PASSWORD = MotDePasse

#define PORT 8080 //Déclaration de la constante PORT = 8080
void OuvertureDeFichier(){

}

int main(int argc, char const* argv[]){
    int server_fd, new_socket, valread;
    struct sockaddr_in address{}; // structure se trouvant dans la librairie socket, voir https://learn.microsoft.com/en-us/windows/win32/api/ws2def/ns-ws2def-sockaddr_in pour son contenu
    int opt = 1;
    int addrlen = sizeof (address);
    char buffer[1024] = {0};
    const void *hello = "Hello from server";

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR , &opt, sizeof(opt))){
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket
                 = accept(server_fd, (struct sockaddr*)&address,
                          (socklen_t*)&addrlen))
        < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }


}

//