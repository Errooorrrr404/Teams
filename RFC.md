# NWP_myteams_2019

Objectif du projet: Recoder une version simplifiée de l'outils microsft Teams.

## Pour commencer

Programme réalisé en 1 mois par Noémie DERAEDT et Benjamin BAPPEL

## Pré-requis

Pour faire fonctionner le projet...

- Avoir libuuid-devel (fedora) ou uuid (ubuntu) d'installé sur la machine
- se placer à la racine du repo et faire `export LD_LIBRARY_PATH=$PWD/libs/myteams` pour pouvoir utiliser la librairie
- `make`

## Utilisation

Pour le server:

    ./myteams_server port
exemple: ./myteams_server 8000

Pour le client:

    ./myteams_cli ip port
exemple: ./myteams_cli 127.0.0.1 8000

exemple: ./myteams_cli localhost 8000

<b>/!\\ Attention le serveur doit démarrer avant le client. /!\\</b>(logique mais il est quand même préferable de le rappeler)

## Une fois dans le serveur et le client lancé

Le serveur sert juste de recupérateur et d'analyseur de commandes. Done une fois lancé, il ne sert plus à rien d'y toucher

Pour le client, chaque commande doit s'executer de cette façon

    /nom_de_la_commande "argument_1" "argument_2" [...]

Pour voir la liste des commandes disponibles, il suffit de faire:

    /help

Liste des commandes disponibles:

- `/login`
- `/logout`
- `/help`
- `/send`
- `/messages`
- `/user`
- `/users`
- `/use`
- `/create`
- `/list`
- `/info`
- Commande Bonus pour arrêter le server: `shutdown_server_now` (cette commande va deconnecter tous les clients connectés, libérer toute la mémoire, et stopper le server)

en cas de doutes sur une commande, executer le `/help`

## Technologies utilisées

Programme réalisé en C, avec une connexion par socket et une utilisation de select pour le client et pour le server.

Le serveur et le client bloque l'usage du Controle C. Le serveur bloque également le Controle D. Pour le client, le Controle D le déconnecte du server.

Pourcentage de libération de mémoire sur le serveur: <b>100%</b>

Pourcentage de libération de mémoire sur le client: <b>100%</b>

Programme testé sur `Fedora 32`, `Fedora 30` ainsi que sur `Ubuntu 20.04` et `Ubuntu 20.10` (Le programme ne possède théoriquement pas d'erreur ou leak mémoire. Cependant, une erreur peut surbvenir en fonction de la version de votre OS)

## Version

1.0

## Auteurs

Benjamin BAPPEL (chef de groupe)

Noémie DERAEDT

## Liste des codes utilisés à messages variables

- Catégorie 2xx: La commande qui a été envoyée a été exécutée avec succès sur le serveur distant. Le serveur distant est prêt pour la commande suivante.

  - 200 -> Commande Valide sans retour d'informations
  - 210 -> Commande Valide avec retour d'informations
  - 220 -> Server prêt pour un acceuil du client
  - 221 -> Arrêt ou deconnexion
  - 230 -> Utilisateur connecté

- Catégorie 4xx: La commande n’a pas été acceptée par le serveur distant pour une raison pouvant être temporaire.

  - 403 -> Client non autorisé
  - 404 -> fichier introuvable

- Catégorie 5xx: La commande n’a pas été acceptée par le serveur distant pour une raison qui n’est pas récupérable

  - 500 -> Commande non trouvée
  - 520 -> commande mal parsée
  - 530 -> Erreur sur la connexion
