#ifndef __FONCTION_BELL__
#define __FONCTION_BELL__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LEN 50
#define TABLE_SIZE 26
#define HistoryBE_SIZE 100

// Structure pour un élément du DictionnaireBE
typedef struct DictionnaireBE {
    char key[MAX_WORD_LEN];
    char value[MAX_WORD_LEN];
    struct DictionnaireBE* next;
} DictionnaireBE;

// Historique des traductions
typedef struct HistoryBE {
    char original[MAX_WORD_LEN];
    char translated[MAX_WORD_LEN];
    char direction[10];
} HistoryBE;

// Table de hachage
extern DictionnaireBE* hashTableFtoB_BE[TABLE_SIZE];
extern DictionnaireBE* hashTableBtoF_BE[TABLE_SIZE];

// Historique
extern HistoryBE History[HistoryBE_SIZE];
extern int HistoryBE_index;

void initialiser_tabl();
void menuBE();
void save_to_fileBE(DictionnaireBE* hashTableBE[], const char* filename);
void display_HistoryBE();
void add_to_HistoryBE(const char* original, const char* translated, const char* direction);
void delete_wordBE(DictionnaireBE* hashTableBE[], const char* key);
char* searchBE(DictionnaireBE* hashTableBE[], const char* key);
void insertBE(DictionnaireBE* hashTableBE[], const char* key, const char* value);
DictionnaireBE* create_DictionnaireBE(const char* key, const char* value);
int hash_functionBE(const char* key);
void to_lowercaseBE(char* str);


#endif