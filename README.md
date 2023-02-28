# TCPFileTransfer

# Guide d'utilisation
### Étapes d'utilisation
1. Exécuter le serveur : gcc ./server {NuméroDePort}
2. Exécuter le client : gcc ./server {NomDeLHote} {NuméroDePort}
3. Le programme client vous demandera votre nom d'utilisateur. Entrer le nom d'utilisateur.
4. Le programme client vous demandera votre mot de passe. Entrer le mot de passe.
5. Le client recevra la liste des fichiers disponible (Généré de façon dynamique). Veuillez entrer le nom du fichier complet dans le terminal (ex:lab3.pdf).
6. Vous pourrez retrouver le *téléchargé* dans le dossier du client.

### Variables d'utilisation

* NuméroDePort - Le numéro de port qu'utiliseront les sockets. Ils devront communiquer sur le même port pour pouvoir établir une connexion.
* NomDeLHote - le nom de votre ordinateur. Sur windows, vous pouvez ouvrir une invite de commande et taper *hostname* pour trouver le nom de votre machine.
* Nom d'utilisateur - Il n'y a qu'un seul nom d'utilisateur générique : simon
* Mot de passe - Il n'y a qu'un seul mot de passe générique : mdp

## Séquence 
### Séquence de communication
1. Lancement du serveur.
2. lancement du client.
3. Serveur en attente de connexion.
4. Client demande une connexion.
5. Serveur répond -- tu peux te connecter, demande d'identifiant.
6. Client envoie les identifiants.
7. serveur valide les identifiants, ou non:
* SI identifiants mauvais
  * Échec de connexion
* Si identifiants bon
  * Envoie les fichiers possibles aux téléchargements (envoie la liste connue)
8. Client envoie le nom du fichier:
  * Si open file a échoué, dit que le nom du fichier est invalide et renvoie la liste
  * Si open file réussie, envoie le fichier

Maintient la connexion
serveur envoie qu'il a terminé avec un flag
client dit ok au serveur et ferme sa connexion
serveur ferme la connexion

### Séquence de vie du serveur
1. Creation - Création du socket.
2. Bind - Rattacher le socket à un port.
3. Listen - Écoute sur un port.
4. Accept - Accept la connexion.
5. send/recv - envoie et réception de la même façon qu'on peut lire ou écrire un fichier.
6. shutdown - ferme le connexion.
7. Fermeture - ferme le fichier pour mettre les données à disposition.


### Séquence de vie du client 
1. Creation - Création du socket
2. Bind - Rattacher le socket à un port 
3. Connexion - Essait de rejoindre le serveur et se connecte.
4. Demande - Serveur demande au client d'envoyer les identifiants 
5. Demande - Serveur demande quel fichier voulez-vous récupéré
6. Préparation - Un fichier à l'aide de fopen portant le même nom que le fichier demandé.
7. Réception - Écrit dans le fichier ce qui est envoyé par le serveur.




# Liens
### Répertoire

* [Repo Github - Berlingott](https://github.com/Berlingott/TCPFileTransfer)

### Références

* [Socket Programming in C/C++](https://www.geeksforgeeks.org/socket-programming-cc/)
* [Sockets - Server & Client - 2020](https://www.bogotobogo.com/cplusplus/sockets_server_client.php)
* [Sockets - Server & Client 2 - 2020](https://www.bogotobogo.com/cplusplus/sockets_server_client_2.php)
* [Linux Programmer's Manual - bzero](https://man7.org/linux/man-pages/man3/bzero.3.html)
* [TCP/IP network byte ordering convention](https://www.ibm.com/docs/en/zos/2.1.0?topic=api-tcpip-network-byte-ordering-convention)
* [other than text file](https://stackoverflow.com/questions/10222423/reading-the-content-of-file-other-than-txt-file)









