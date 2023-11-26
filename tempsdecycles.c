#include "header.h"
float lireTempsCycle() {
    FILE *fichier = fopen("FICHIER_TEXTE\\temps_cycle.txt", "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier temps_cycle.txt");
        exit(EXIT_FAILURE);
    }

    float tempsCycle;
    fscanf(fichier, "%f", &tempsCycle);
    fclose(fichier);

    return tempsCycle;
}
void afficherTempsCycle()
{
    float tempsCycle = lireTempsCycle();
    printf("Temps de cycle: %f\n", tempsCycle);
}