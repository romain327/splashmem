# splashmem
ce projet contient en réalité 2 projets :
- le splashmem "de base" qui est suffisant pour avoir 15, qui se trouve dans le dossier ```splashmem```
- le splashmem avancé avec des modifications, dans le dossier ```splashmem_enhanced```

## splashmem_enhanced
Cette version de splashmeme est assez lourdement modifiée. On y trouve d'abord deux fichiers en plus de la version de base : client.c et server.c ... Eh oui une implémentation du jeu en mode client-server !
On va, pour le bon fonctionnement du programme, se limiter à 4 clients. La raison c'est que le serveur peut évidemment en accepter plus, mais on a gardé les 4 joueurs de base sans implémenter un nombre de joueur dépendant du nombre de clients connectés au serveur. On n'a pas testé ce qu'il se passerait si on essayait de connecter un 5eme client, et on a pas vraiment envie de savoir (ça plante).
Mais avec 4 clients max ça marche niquel donc on va rester la dessus :)
On a donc une connexion client-serveur à base de sockets. On va maintenant détailler un peu plus le fonctionnement du code pour que vous puissiez vous y retrouver :

### Programme principal
On a bien évidemment le splashmem de base, ici rien ne change mise a part les librairies des joueurs. La fonction get_action() est juste un switch case qui renvoi la bonne action en fonction du char passé en paramètre. Ca permet de bind nos actions sur les touches de notre clavier.
On a au tout début du main, une création de segment de mémoire partagée. Cela permet au serveur, qui tourne dans un processus séparé du programme principal, de transmettre au programme principal les touches enfoncées par les clients. On est sur de la communication IPC, mais rien de bien compliqué.
Ensuite on fork notre processus main, et on execute le serveur dans le processus enfant. C'est la solution trouvée pour palier au problème rencontré lorsque le serveur tournait dans le processus principal, on avait des erreurs de render SDL a cause du serveur qui écoutait en permanance.

### Serveur
On a deux éléments interessants dans ce processus serveur, la première c'est la gestion des clients, qui se fait en continue. La deuxième, c'est la fonction sigterm_handler, qui gère la fermeture de la socket serveur. En effet, en envoyant un bête SIGKILL, la socket n'est pas fermée correctement, et en relançant le processus le port était indiqué comme déjà utilisé.

### Client
Le processus client gère l'envoi des touches au serveur dès qu'elles sont tapées au clavier.

### Test
Tester le programme peut-être un peu long et fastidieux donc on vous a mis une vidéo de démonstration également.

Pour lancer le programme, ouvrir un terminal, se placer dans le dossier splashmem_enhanced et taper la commande ```make all```, puis ```./run.sh```

Pour les clients, ouvrir d'autres terminaux, dans chacun d'eux, se placer dans le dossier splashmem_enhanced/cl et taper la commande ```./client```

Ensuite pour chacun des processus client, appuyer sur les touches correspondant aux déplacements.

La touche pour fermer la fenêtre SDL est la touche q.
