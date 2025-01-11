#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_ACCOUNTS 100
#define MAX_STRING 50
#define FILENAME "comptes.csv"

// Structure pour repr�senter un compte client
typedef struct {
    int accountNumber;
    char name[MAX_STRING];
    char email[MAX_STRING];
    char phone[MAX_STRING];
    float balance;
    int isActive;
} Account;

Account comptes[MAX_ACCOUNTS];
int nombreComptes = 0;

// Fonction pour valider l'entr�e d'un entier
int lireEntier() {
    int valeur;
    while (scanf("%d", &valeur) != 1) {
        printf("Entr�e invalide. Veuillez entrer un nombre entier : ");
        while (getchar() != '\n');  // Nettoie le buffer d'entr�e
    }
    return valeur;
}

// Fonction pour valider l'entr�e d'un flottant
float lireFlottant() {
    float valeur;
    while (scanf("%f", &valeur) != 1) {
        printf("Entr�e invalide. Veuillez entrer un nombre d�cimal : ");
        while (getchar() != '\n');  // Nettoie le buffer d'entr�e
    }
    return valeur;
}

// Fonction pour ajouter un compte
void ajouterCompte() {
    if (nombreComptes >= MAX_ACCOUNTS) {
        printf("Limite de comptes atteinte.\n");
        return;
    }

    Account nouveauCompte;
    printf("Entrez les d�tails du nouveau compte :\n");
    printf("Num�ro de compte : ");
    nouveauCompte.accountNumber = lireEntier();
    printf("Nom : ");
    scanf("%s", nouveauCompte.name);
    printf("Email : ");
    scanf("%s", nouveauCompte.email);
    printf("T�l�phone : ");
    scanf("%s", nouveauCompte.phone);
    printf("Solde initial : ");
    nouveauCompte.balance = lireFlottant();
    nouveauCompte.isActive = 1;  // Actif par d�faut

    comptes[nombreComptes++] = nouveauCompte;
    printf("Compte ajout� avec succ�s !\n");
}

// Fonction pour afficher les comptes
void afficherComptes() {
    if (nombreComptes == 0) {
        printf("Aucun compte disponible.\n");
        return;
    }

    printf("\nListe des comptes :\n");
    printf("Num�ro de Compte | Nom | Email | T�l�phone | Solde | Statut\n");
    printf("----------------------------------------------------------\n");

    for (int i = 0; i < nombreComptes; i++) {
        printf("%d | %s | %s | %s | %.2f | %s\n", comptes[i].accountNumber, comptes[i].name, comptes[i].email, comptes[i].phone, comptes[i].balance, comptes[i].isActive ? "Actif" : "Inactif");
    }
}

// Fonction pour sauvegarder les comptes dans un fichier CSV
void sauvegarderComptes() {
    FILE *fichier = fopen(FILENAME, "w");

    if (fichier == NULL) {
        printf("Erreur d'ouverture du fichier pour sauvegarde.\n");
        return;
    }

    fprintf(fichier, "accountNumber,name,email,phone,balance,isActive\n");
    for (int i = 0; i < nombreComptes; i++) {
        fprintf(fichier, "%d,%s,%s,%s,%.2f,%d\n", comptes[i].accountNumber, comptes[i].name, comptes[i].email, comptes[i].phone, comptes[i].balance, comptes[i].isActive);
    }

    fclose(fichier);
    printf("Les comptes ont �t� sauvegard�s dans '%s'.\n", FILENAME);
}

// Fonction pour charger les comptes � partir d'un fichier CSV
void chargerComptes() {
    FILE *fichier = fopen(FILENAME, "r");

    if (fichier == NULL) {
        printf("Aucun fichier de sauvegarde trouv�. Aucun compte n'a �t� charg�.\n");
        return;
    }

    char ligne[200];
    fgets(ligne, sizeof(ligne), fichier);  // Lire et ignorer l'en-t�te CSV

    while (fgets(ligne, sizeof(ligne), fichier)) {
        Account nouveauCompte;
        sscanf(ligne, "%d,%[^,],%[^,],%[^,],%f,%d", &nouveauCompte.accountNumber, nouveauCompte.name, nouveauCompte.email, nouveauCompte.phone, &nouveauCompte.balance, &nouveauCompte.isActive);
        comptes[nombreComptes++] = nouveauCompte;
    }

    fclose(fichier);
    printf("Les comptes ont �t� charg�s � partir du fichier '%s'.\n", FILENAME);
}

// Fonction pour comparer les comptes par num�ro de compte
int comparerParNumero(const void *a, const void *b) {
    Account *compteA = (Account *)a;
    Account *compteB = (Account *)b;
    return compteA->accountNumber - compteB->accountNumber;
}

// Fonction pour comparer les comptes par nom
int comparerParNom(const void *a, const void *b) {
    Account *compteA = (Account *)a;
    Account *compteB = (Account *)b;
    return strcmp(compteA->name, compteB->name);
}

// Fonction pour comparer les comptes par solde
int comparerParSolde(const void *a, const void *b) {
    Account *compteA = (Account *)a;
    Account *compteB = (Account *)b;
    if (compteA->balance > compteB->balance) return 1;
    if (compteA->balance < compteB->balance) return -1;
    return 0;
}

// Fonction pour trier les comptes
void trierComptes() {
    int choix;
    printf("Choisissez le crit�re de tri :\n");
    printf("1. Par num�ro de compte\n");
    printf("2. Par nom\n");
    printf("3. Par solde\n");
    printf("Entrez votre choix : ");
    choix = lireEntier();

    switch (choix) {
        case 1:
            qsort(comptes, nombreComptes, sizeof(Account), comparerParNumero);
            printf("Comptes tri�s par num�ro de compte.\n");
            break;
        case 2:
            qsort(comptes, nombreComptes, sizeof(Account), comparerParNom);
            printf("Comptes tri�s par nom.\n");
            break;
        case 3:
            qsort(comptes, nombreComptes, sizeof(Account), comparerParSolde);
            printf("Comptes tri�s par solde.\n");
            break;
        default:
            printf("Choix invalide. Aucun tri effectu�.\n");
            break;
    }
}

// Fonction principale avec le menu
int main() {
    int choix;
    printf("Bienvenue dans le systeme de gestion bancaire !\n");
    while (1) {
        printf("\nMenu :\n");
        printf("1. Afficher les comptes\n");
        printf("2. Ajouter un compte\n");
        printf("3. Deposer de l'argent\n");
        printf("4. Retirer de l'argent\n");
        printf("5. Transferer de l'argent\n");
        printf("6. Sauvegarder les comptes\n");
        printf("7. Trier les comptes\n");
        printf("8. Quitter\n");
        printf("Entrez votre choix : ");
        choix = lireEntier();

        switch (choix) {
            case 1:
                afficherComptes();
                break;
            case 2:
                ajouterCompte();
                break;
            case 6:
                sauvegarderComptes();
                break;
            case 7:
                trierComptes();
                break;
            case 8:
                sauvegarderComptes();  // Sauvegarde automatique avant de quitter
                printf("Sortie du syst�me. Au revoir !\n");
                return 0;
            default:
                printf("Choix invalide. Veuillez r�essayer.\n");
        }
    }
    return 0;
}

