#include "fonction_bell.h"

// Table de hachage
DictionnaireBE* hashTableFtoB_BE[TABLE_SIZE];
DictionnaireBE* hashTableBtoF_BE[TABLE_SIZE];

// Historique
HistoryBE History[HistoryBE_SIZE];
int HistoryBE_index = 0;

int main() {
    // Initialiser les tables de hachage
    initialiser_tabl();

    // Lancer le menuBE
    menuBE();
    return 0;
}