Projet Space Invader

Groupe 19 :

Etudiant :
Govindarajalou Sasikumar
Bayol Thibaud

Commandes du jeux :

Déplacement horizontale du joueur : Flèches droite, gauche. 
Tirer : Fléche du haut.
Quitter : Flèche du bas.

Fichier "jeux.c" 

FONCTIONS :

1.non_canonique:
Paremètre :
-struct termios

Cela sauvegarde le terminal actif et le met en mode non canonique.

2.canonique:
Paremètre :
-struct termios

Cela restore l'ancien terminal et le met en mode canonique.

3.changePos:
Paremètre :
-Vaisseau** troup, int niv

IMPORTANT : le if(l.49) à activer seulement si on souhaite un déplacement indépendant des vaisseaux en fonction de leur temps d'apparition.

Il déplace les vaisseux enemies en fonctions de leur trajectoire prédéfinis dans les fichiers des niveaux.

4.vaisseaux:
Paremètre :
-char** carte, Vaisseau*** coord, Vaisseau** troup, Tire* tires, struct timespec* start, struct timespec* told, int niv, struct winsize w

fonction qui met à jour les coordonnées des vaisseaux(troup) du niveau(niv) sur la carte d'affichage(carte, w) ainsi que sur le tableau des données enregistré(coord) et il permet aux vaisseaux de tirer(tires) en fonction de leurs fréquence de tires tous les x temps(told).Il permet aussi l'apparition selon le temps prédéfinie(start). 


5.gamewon:
Paremètre :
-char** carte, Vaisseau*** coord, struct winsize w

Il utilise la carte(carte, w) pour affiché un message de réussite d'un niveau et met à NULL toutes les positions des vaisseaux(coord) pour éviter l'affichage des vaisseaux sur l'ecran du gamewon. 

6.gameover:
Paremètre :
-char** carte, Vaisseau*** coord, struct winsize w

Il utilise la carte(carte, w) pour affiché un message de défaite d'un niveau et met à NULL toutes les positions des vaisseaux(coord) pour éviter l'affichage des vaisseaux sur l'ecran du gameover.

7.gameend:
Paremètre :
-char** carte, Vaisseau*** coord, struct winsize w

Il utilise la carte(carte, w) pour affiché un message de fin du mod et met à NULL toutes les positions des vaisseaux(coord) pour éviter l'affichage des vaisseaux sur l'ecran du gameover.

8.design:
Paremètre :
char** carte, Vaisseau*** coord, Vaisseau** vais, Vaisseau* joueur, Tire* tires, struct timespec* start, struct timespec* told, int x, int niv, struct winsize w

fonction qui dessine le cadre de la carte(carte) ainsi que tous les vaisseaux du jeu(cf. fonction vaisseau). Il dessine également le joueur principale selon la direction donné par le joueur tout en vérifiant qu'il n'est pas touché par des tirs enemies ou les enemenies directement(tire, joueur) auquel cas il lance la fonction gameover ou gamewon si on gagne.


9.show:
Paramètre : 
-char** carte, char* affiche, struct winsize w

Il prend en paremetre la carte(carte) avec toutes ses données qu'il le transmet sur un tableau à une dimension(affiche) pour effectué qu'un seule appel système pour l'afficher.

Fichier "fonciton.c"

FONCTIONS :

1.deroulement:

Lecture du fichier deroulement pour envoyer un tableau de chaine de caractère contenant tous les différent nivaux à executé.

2.lire:
Paramètre : 
char** tt

Lecture d'un tableau(tt) de char jusqu'à l'espace et l'envoi en format int tout en incrementant le pointeur du tableau pour pouvoir sauté l'esapce lu et ainsi lire le tableau à la bonne position pour la prochaine lecture.

3.lire2:
Paramètre : char** tt

Lecture d'un tableau(tt) de char jusqu'à l'espace et l'envoi en format int tout en incrementant le pointeur du tableau pour pouvoir sauté l'esapce lu et ainsi lire le tableau à la bonne position pour la prochaine lecture.

4.type:
Paramètre = int* max

Il lit le fichier contenus dans le répertoire vaisseux qu'il envoi dans un double tableau et le nombre de types de vaisseaux via le pointeur max.

5.type01:
Paramètre : int fd_v

il prend un descripteur de fichier(fd_v) d'un type de vaisseux et il renvoi une structure Type contenant toutes les informations du type de vaisseau.

6.creerUneArmer:
Paramètre : int* max, Type** T

Il renvoi un tableau de structure Vaisseaux contenant tous les vaisseaux(T) de tous les niveaux.

7.liberer:
Paramètre : Tire* t

Fonction qui permet de libérer tous les tires(t) sur la carte.

8.tire:
Paramètre : int x,int y,Vaisseau* A,int perso,Tire* t

Fonction qui ajoute un tire avec des coordonnées précises(x,y) sur le tableau de tires(t) selon la disponibilité des tirs et selon la cadence autorisé du vaisseau(Vaisseau* A) et selon que le tir soit effectué par le joueur ou l'ennemie(perso).

9.majTire:
Paramètre : char** carte, Vaisseau*** coord, Tire* t, struct winsize w

Fonction qui met à jour le déplacement des tirs(t) sur la carte(carte) en fonction de son appartenance à un vaisseau ou un type de vaisseau et de sa vitesse de tir. Il enleve également les point de vie des vaisseaux touchés par le tir en libérant le tir du tableau de tir si le tir touche un vaisseau ou sort de la carte.

10.melange:
Paramètre : int a, int b

Fonction qui prend un intervalle entre deux entiers(a,b) et retourne un entier aléatoire appartenant à l'intervalle[a;b[.

11.powerUpdate:
Paramètre : char** carte, Vaisseau*** coord, Vaisseau* joueur, Power* powerUp, struct winsize w

Fonction qui met à jour l'affichage(carte) du powerUp de la carte et attrbue le bonus du powerUp(powerUp) si le joueur(joueur) rentre en contact(coord) avec celui-ci dans le temps imparti d'affichage d'un powerUp(3 secondes).

12.powerLanch:
Paramètre : Power* powerUp, struct winsize w

Lance une chance(10%) de créé powerUp à chaque fois que le joueur tire. Il ajoute le powerUp sur la carte si il n'existe pas dejà.


13.infos:
Paramètre : char** carte, Vaisseau* player, struct winsize w, int n

Fonction qui affiche les informations(player) sur le joueur(vitesse, dégât, cadence, vie) ainsi que le niveau courant sur le haut de la carte(carte) 






