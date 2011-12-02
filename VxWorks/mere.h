/*RESSOURCES Critiques*/
int mode; /*initial*/
/* 2 types de modes
0 : Automatique
1 : Manuel */

int commande; /*initial*/
/* 4 types de deplacement
0 : arret
1 : avant
2 : gauche
3 : droite
4 : reculer */

int duree; /*duree du deplacement en secondes*/

int delai; /*Par defaut, il est en mode automatique
Cette variable permet de changer de mode si immobile depuis plus de 30secondes */

/*Variables des capteurs*/
int capteur_avant; /*initial : un obstacle*/
int capteur_arriere; /*initial : un obstacle*/

/*ID des semaphores*/
SEM_ID semCommunication;
SEM_ID semMode;
SEM_ID semObstacle;
SEM_ID semCommande;

/*TID des taches*/
int tid_main;
int tid_menu;
int tid_capteur;
int tid_deplacer;



/*ID de l'alarme*/
WDOG_ID alarme;


/* Creation des variables*/
unsigned char instring[100];
unsigned char outstring[50];
/*Les chaînes de caractères sont en fait stockées dans un tableau de char 
dont la fin est marquée par un caractère nul, de valeur 0 et représenté
par le caractère '\0' ou '\x0' ou la valeur 0 directement. */
int ecran;

void temporisation();
void ecrire(unsigned char *str, unsigned char *buffer);
void nettoyage_ecran();