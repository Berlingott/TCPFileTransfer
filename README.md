# TCPFileTransfer

## Séquence 
### Séquence de communication
Lancement du coté serveur
lancement du côté client 
Serveur en attente de connexion
Client demande une connexion
Serveur répond -- tu peux te connecter, demande d'identifiant
Client envoie les identifiants
serveur valide les ideentifiants, ou non
    SI identifiants mauvais
        Échec de connexion
    Si identifiants bon
        envoie les fichiers possibles aux téléchargents ( envoie la liste connue)
Client envoie le nom du fichier
si open file a échoué, dit que le nom du fichier est invalide et réenvoie la liste
si open fil réussi, envoie le fichier

maintient la connexion
serveur envoie qu'il a terminé avec un flag
client dit ok au serveur et ferme sa connexion
serveur ferme la connexio

### Séquence de vie du serveur
* Creation - Création du socket.
* Bind - Rattacher le socket à un port.
* Listen - Écoute sur un port.
* Accept - Accept la connexion.
* send/recv - envoie et reçoie de la même façon qu'on peut lire ou écrire un fichier.
* shutdown - ferme le connexion.
* close - ferme le fichier pour mettre les données à disposition.


### Séquence de vie du client 
* Creation - Création du socket
* Bind - Rattacher le socket à un port 
* 
    create a socket.
    bind* - this is probably be unnecessary because you're the client, not the server.
    connect to a server.
    send/recv - repeat until we have or receive data
    shutdown to end read/write.
    close to releases data.


## Références

[Socket Programming in C/C++](https://www.geeksforgeeks.org/socket-programming-cc/)


[Sockets - Server & Client - 2020](https://www.bogotobogo.com/cplusplus/sockets_server_client.php)