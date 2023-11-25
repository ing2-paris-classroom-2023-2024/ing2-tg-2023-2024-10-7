#include "header.h"
void setColorIndex(int colorIndex) {
    switch (colorIndex) {
        case 0:
            setColor(FOREGROUND_RED); // Rouge
            break;
        case 1:
            setColor(FOREGROUND_BLUE); // Bleu
            break;
        case 2:
            setColor(FOREGROUND_GREEN); // Bleu
            break;


        default:
            setColor(FOREGROUND_GREEN); // Vert ou autre couleur par défaut
            break;
    }
}
void bfsAvecPrecedenceEtExclusion(struct Graph* graphe, int* color) {
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleInfo);
    WORD savedAttributes = consoleInfo.wAttributes;
    int numVertices = graphe->numVertices;
    bool visited[numVertices];
    int **paths = malloc(numVertices * sizeof(int *)); // Allocation dynamique pour le tableau de chemins

    // Initialisation
    for (int i = 0; i < numVertices; i++) {
        visited[i] = false;
        paths[i] = malloc(2 * sizeof(int)); // Allouer de la mémoire pour le chemin initial
        paths[i][0] = i; // Le chemin commence par le sommet lui-même
        paths[i][1] = -1; // Marquer la fin du chemin
    }

    struct File *file = creerFile();

    /// Parcour de tous les sommets
    for (int i = 0; i < numVertices; i++) {
        if (!visited[i]) {
            enfiler(file, i);
            visited[i] = true;

            while (!estVide(file)) {
                int u = defiler(file);

                struct Node *temp = graphe->adjLists[u];
                while (temp) {
                    int v = temp->vertex;
                    if (!visited[v]) {
                        visited[v] = true;
                        enfiler(file, v);

                        // Calculer la longueur du chemin actuel
                        int pathLength = 0;
                        while (paths[u][pathLength] != -1) pathLength++;

                        // Allouer un nouveau chemin avec une taille supplémentaire
                        paths[v] = realloc(paths[v], (pathLength + 2) * sizeof(int));
                        for (int j = 0; j < pathLength; j++) {
                            paths[v][j] = paths[u][j]; // Copier le chemin
                        }
                        paths[v][pathLength] = v; // Ajouter le sommet actuel à la fin
                        paths[v][pathLength + 1] = -1; // Marquer la fin du chemin
                    }
                    temp = temp->next;
                }
            }
        }
    }

    /// Affichage des chemins avec les stations
    for (int i = 0; i < numVertices; i++) {

        printf("Pour faire l'operation ");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), savedAttributes); // Réinitialiser la couleur


        setColorIndex(color[i]);
        printf("%d", i + 1);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), savedAttributes); // Réinitialiser la couleur

        printf(", suivre le chemin : ");
        int j = 0;
        while (paths[i][j] != -1) {

            setColorIndex(color[paths[i][j]]);
            printf("%d", paths[i][j] + 1);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), savedAttributes); // Réinitialiser la couleur


            printf(" a la station n");
            setColorIndex(color[paths[i][j]]);
            printf("%d", color[paths[i][j]] + 1);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), savedAttributes); // Réinitialiser la couleur

            j++;

            if (paths[i][j] != -1) {
                printf(", ");
            }
        }
        printf("\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), savedAttributes);
        free(paths[i]); // Libérer la mémoire allouée pour le chemin
    }
}