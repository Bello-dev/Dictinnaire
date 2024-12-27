#include "fonction_bell.h"

// Fonctions pour manipuler les chaînes
void to_lowercaseBE(char* str)
{
    for (int i = 0; str[i]; i++)
        str[i] = tolower(str[i]);
}

// Fonction de hachage
int hash_functionBE(const char* key)
{
    return tolower(key[0]) - 'a';
}

// Création d'un nœud
DictionnaireBE* create_DictionnaireBE(const char* key, const char* value)
{
    DictionnaireBE* newDictionnaireBE = (DictionnaireBE*)malloc(sizeof(DictionnaireBE));
    strcpy(newDictionnaireBE->key, key);
    strcpy(newDictionnaireBE->value, value);
    newDictionnaireBE->next = NULL;
    return newDictionnaireBE;
}

// insertion
void insertBE(DictionnaireBE* hashTableBE[], const char* key, const char* value)
{
    int index = hash_functionBE(key);
    DictionnaireBE* newDictionnaireBE = create_DictionnaireBE(key, value);

    if (hashTableBE[index] == NULL) {
        hashTableBE[index] = newDictionnaireBE;
    } else
    {
        DictionnaireBE* currentBE = hashTableBE[index];
        while (currentBE->next != NULL)
        {
            if (strcasecmp(currentBE->key, key) == 0)
            {
                strcpy(currentBE->value, value); // Met à jour si la clé existe
                free(newDictionnaireBE);
                return;
            }
            currentBE = currentBE->next;
        }
        currentBE->next = newDictionnaireBE;
    }
}

// Recherche
char* searchBE(DictionnaireBE* hashTableBE[], const char* key)
{
    int index = hash_functionBE(key);
    DictionnaireBE* currentBE = hashTableBE[index];
    while (currentBE != NULL) {
        if (strcasecmp(currentBE->key, key) == 0)
            return currentBE->value;

        currentBE = currentBE->next;
    }
    return NULL;
}

// Suppression d'un mot
void delete_wordBE(DictionnaireBE* hashTableBE[], const char* key)
{
    int index = hash_functionBE(key);
    DictionnaireBE* currentBE = hashTableBE[index];
    DictionnaireBE* prev = NULL;

    while (currentBE != NULL)
    {
        if (strcasecmp(currentBE->key, key) == 0)
        {
            if (prev == NULL)
                hashTableBE[index] = currentBE->next;
            else
                prev->next = currentBE->next;

            free(currentBE);
            printf("Mot supprimé avec succès !\n");
            return;
        }
        prev = currentBE;
        currentBE = currentBE->next;
    }
    printf("Mot non trouvé.\n");
}

// Historique des traductions
void add_to_HistoryBE(const char* original, const char* translated, const char* direction)
{
    if (HistoryBE_index >= HistoryBE_SIZE)
        HistoryBE_index = 0; // Écrase les anciens éléments si l'historique est plein

    strcpy(History[HistoryBE_index].original, original);
    strcpy(History[HistoryBE_index].translated, translated);
    strcpy(History[HistoryBE_index].direction, direction);
    HistoryBE_index++;
}

// Affichage de l'historique
void display_HistoryBE()
{
    printf("\n=== Historique des Traductions ===\n");
    for (int i = 0; i < HistoryBE_index; i++)
        printf("%s -> %s (%s)\n", History[i].original, History[i].translated, History[i].direction);
}

// Sauvegarde et chargement
void save_to_fileBE(DictionnaireBE* hashTableBE[], const char* filename)
{
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Erreur : Impossible d'ouvrir le fichier %s.\n", filename);
        return;
    }
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        DictionnaireBE* currentBE = hashTableBE[i];
        while (currentBE != NULL)
        {
            fprintf(file, "%s %s\n", currentBE->key, currentBE->value);
            currentBE = currentBE->next;
        }
    }
    fclose(file);
}

void load_from_fileBE(DictionnaireBE* hashTableBE[], const char* filename)
{
    FILE* file = fopen(filename, "r");
    if (!file)
    {
        printf("Erreur : Impossible de lire le fichier %s.\n", filename);
        return;
    }
    char key[MAX_WORD_LEN], value[MAX_WORD_LEN];
    while (fscanf(file, "%[^ ] %[^\n]\n", key, value) != EOF)
    {
        insertBE(hashTableBE, key, value);
    }
    fclose(file);
}

// menu principal
void menuBE()
{
    int choix;
    char mot[MAX_WORD_LEN], traduction[MAX_WORD_LEN];

    system("clear");

    load_from_fileBE(hashTableFtoB_BE, "data/french_to_bamoun.txt");
    load_from_fileBE(hashTableBtoF_BE, "data/bamoun_to_french.txt");

    debut:
    do {
        printf("\n=== DictionnaireBE Bamoun-Français ===\n");
        printf("\t1. Ajouter un mot\n");
        printf("\t2. Traduire (Français -> Bamoun)\n");
        printf("\t3. Traduire (Bamoun -> Français)\n");
        printf("\t4. Supprimer un mot\n");
        printf("\t5. Afficher l'historique des traductions\n");
        printf("\t0. Quitter\n");
        printf("Choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                ajouter:
                printf("Pour pouvoir ajouter un mot dans le dictionnare vous devez disposer des droits necessaires\n");
                int chx = -1;
                printf("\t1. Je possède une clée d'accès\n\t2. Contacter le developpeur pour obtenir les droits d'accès\n\t0. Retour.\nchoix : ");
                scanf("%d", &chx);
                switch(chx)
                {
                case 1:
                    system("clear");
                    char pwd[255];
                    const char *pasword = "bello-dev@207"; 
                    printf("Entrrez le mot de passe\n");
                    fscanf(stdin, "%s", pwd);
                    fflush(stdin);
                    if(strcmp(pwd, pasword) != 0)
                        goto ajouter;
                    else
                        goto continuer;
                case 2:
                    system("clear");

                    printf("Email : aqil.bell@facsciences-uy1.cm\nWhatsApp : +237621215284\n");
                    goto debut;
                default:
                    goto ajouter;


                }
                continuer:
                printf("Entrez le mot en français : ");
                scanf("%s", mot);
                printf("Entrez la traduction en bamoun : ");
                scanf("%s", traduction);
                insertBE(hashTableFtoB_BE, mot, traduction);
                insertBE(hashTableBtoF_BE, traduction, mot);
                save_to_fileBE(hashTableFtoB_BE, "data/french_to_bamoun.txt");
                save_to_fileBE(hashTableBtoF_BE, "data/bamoun_to_french.txt");
                printf("Mot ajouté avec succès !\n");
                break;

            case 2:
                system("clear");

                printf("Entrez le mot en français : ");
                scanf("%s", mot);
                char* res = searchBE(hashTableFtoB_BE, mot);
                if (res) {
                    printf("Traduction en bamoun : %s\n", res);
                    add_to_HistoryBE(mot, res, "Fr->Bm");
                } else {
                    ref:
                    printf("\tMot non trouvé.\n");
                    printf("Voulez-vous ajouter un mot au dictionnaire ?(O/N) : ");
                    char ch;
                    scanf(" %c", &ch);
                    if(ch == 'o' || ch == 'O')
                    	goto ajouter;
                    else if(ch == 'n' || ch == 'N')
                    	printf("Merci !\n");
                    else
                    	goto ref;
                }
                break;

            case 3:
                system("clear");
                printf("Entrez le mot en bamoun : ");
                scanf("%s", mot);
                res = searchBE(hashTableBtoF_BE, mot);
                if (res) {
                    printf("Traduction en français : %s\n", res);
                    add_to_HistoryBE(mot, res, "Bm->Fr");
                } else {
                	ref1:
                    printf("\tMot non trouvé.\n");
                    printf("Voulez-vous ajouter un mot au dictionnaire ?(O/N) : ");
                    char ch;
                    scanf(" %c", &ch);
                    if(ch == 'o' || ch == 'O')
                    	goto ajouter;
                    else if(ch == 'n' || ch == 'N')
                    	printf("Merci !\n");
                    else
                    	goto ref1;
                }
                break;

            case 4:
                system("clear");
                supprimer:
                printf("Pour pouvoir supprimer un mot dans le dictionnaire vous devez disposer des droits necessaires\n");
                int cx = -1;
                printf("\t1. Je possède une clée d'accès\n\t2. Contacter le developpeur pour obtenir les droits d'accès\n\t0. Retour.\nchoix : ");
                scanf("%d", &cx);
                switch(cx)
                {
                case 1:
                    system("clear");
                    char pwd[255];
                    const char *pasword = "bello-dev@207"; 
                    printf("Entrrez le mot de passe\n");
                    fscanf(stdin, "%s", pwd);
                    fflush(stdin);
                    if(strcmp(pwd, pasword) != 0)
                        goto supprimer;
                    else
                        goto continuer2;
                case 2:
                    system("clear");

                    printf("Email : aqil.bell@facsciences-uy1.cm\nWhatsApp : +237621215284\n");
                    goto debut;
                default:
                    goto supprimer;
                }
                continuer2:
                printf("Entrez le mot à supprimer (français ou bamoun) : ");
                scanf("%s", mot);
                delete_wordBE(hashTableFtoB_BE, mot);
                delete_wordBE(hashTableBtoF_BE, mot);
                save_to_fileBE(hashTableFtoB_BE, "data/french_to_bamoun.txt");
                save_to_fileBE(hashTableBtoF_BE, "data/bamoun_to_french.txt");
                break;

            case 5:
                system("clear");
                display_HistoryBE();
                break;

            case 0:
                system("clear");
                printf("Au revoir !\n");
                break;

            default:
                system("clear");
                printf("Option invalide. Veuillez réessayer.\n");
        }
    } while ( choix != 0);

    // Libérer la mémoire
    for (int i = 0; i < TABLE_SIZE; i++) {
        DictionnaireBE* currentBE = hashTableFtoB_BE[i];
        while (currentBE != NULL) {
            DictionnaireBE* temp = currentBE;
            currentBE = currentBE->next;
            free(temp);
        }
        hashTableFtoB_BE[i] = NULL;

        currentBE = hashTableBtoF_BE[i];
        while (currentBE != NULL) {
            DictionnaireBE* temp = currentBE;
            currentBE = currentBE->next;
            free(temp);
        }
        hashTableBtoF_BE[i] = NULL;
    }
}

    // Initialiser les tables de hachage
void initialiser_tabl()
{
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTableFtoB_BE[i] = NULL;
        hashTableBtoF_BE[i] = NULL;
    }
}