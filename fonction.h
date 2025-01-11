#ifndef FONCTION_H_INCLUDED
#define FONCTION_H_INCLUDED

#define MAX_ACCOUNTS 100
#define MAX_STRING 50
#define FILENAME "comptes.csv"

typedef struct {
    int accountNumber;
    char name[MAX_STRING];
    char email[MAX_STRING];
    char phone[MAX_STRING];
    float balance;
    int isActive;
} Account;
int choix;
Account comptes[MAX_ACCOUNTS];
int nombreComptes = 0;
int lireEntier();
float lireFlottant();
void ajouterCompte();
void afficherComptes();
void sauvegarderComptes();
void chargerComptes();
int comparerParNumero(const void *a, const void *b);
int comparerParNom(const void *a, const void *b);
int comparerParSolde(const void *a, const void *b);
void trierComptes();





#endif // FONCTION_H_INCLUDED
