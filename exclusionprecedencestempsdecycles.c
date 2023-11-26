#include "header.h"

void bfsAvecPrecedenceEtExclusionEtTemps(struct Graph* graphe, int* color, const float* tempsOperations, float tempsCycle, int mode, int sommetSpecifique) {
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleInfo);
    WORD savedAttributes = consoleInfo.wAttributes;
    int numVertices = graphe->numVertices;
    bool visited[numVertices];
    int **paths = malloc(numVertices * sizeof(int *));
    float *tempsCumule = malloc(numVertices * sizeof(float));

    // Initialisation
    for (int i = 0; i < numVertices; i++) {
        visited[i] = false;
        tempsCumule[i] = (tempsOperations[i] >= 0) ? tempsOperations[i] : 0;
        paths[i] = malloc(2 * sizeof(int));
        paths[i][0] = i;
        paths[i][1] = -1;
    }

    struct File *file = creerFile();

    // Parcours BFS avec gestion du temps de cycle
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

                        // Mise à jour du temps cumulé
                        tempsCumule[v] = tempsCumule[u] + ((tempsOperations[v] >= 0) ? tempsOperations[v] : 0);

                        // Mise à jour des chemins
                        int pathLength = 0;
                        while (paths[u][pathLength] != -1) pathLength++;
                        paths[v] = realloc(paths[v], (pathLength + 2) * sizeof(int));
                        for (int j = 0; j < pathLength; j++) {
                            paths[v][j] = paths[u][j];
                        }
                        paths[v][pathLength] = v;
                        paths[v][pathLength + 1] = -1;
                    }
                    temp = temp->next;
                }
            }
        }
    }

    // Affichage des chemins avec les stations, les temps, et vérification du temps de cycle
    for (int i = 0; i < numVertices; i++) {
        // Gestion des modes d'affichage
        if ((mode == 2 && i != sommetSpecifique) || (mode == 3 && paths[i][0] != sommetSpecifique)) {
            continue;
        }

        printf("\nPour faire l'operation ");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), savedAttributes);

        setColorIndex(color[i]);
        printf("%d", i + 1);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), savedAttributes);

        printf(", suivre le chemin : ");
        int j = 0;
        float tempsTotal = 0;
        while (paths[i][j] != -1) {
            setColorIndex(color[paths[i][j]]);
            printf("%d", paths[i][j] + 1);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), savedAttributes);

            printf(" a la station n");
            setColorIndex(color[paths[i][j]]);
            printf("%d", color[paths[i][j]] + 1);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), savedAttributes);

            float tempsOp = (tempsOperations[paths[i][j]] >= 0) ? tempsOperations[paths[i][j]] : 0;
            tempsTotal += tempsOp;
            printf(" (temps d'execution: %.2f)", tempsOp);

            j++;
            if (paths[i][j] != -1) {
                printf(", ");
            }
        }
        printf(". Temps total: %.2f", tempsTotal);
        if (tempsTotal > tempsCycle) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
            printf(" (depasse le temps de cycle!)");
        } else {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN);
            printf(" (inferieur au temps de cycle)");
        }
        printf("\n\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), savedAttributes);
        free(paths[i]);
    }

    free(tempsCumule);
    free(paths);
}
void afficherTousLesChemins(struct Graph* graphe, int* color, const float* tempsOperations, float tempsCycle, int sommetSpecifique) {
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleInfo);
    WORD savedAttributes = consoleInfo.wAttributes;
    int numVertices = graphe->numVertices;
    bool visited[numVertices];
    int **paths = malloc(numVertices * sizeof(int *));
    float *tempsCumule = malloc(numVertices * sizeof(float));

    // Initialisation
    for (int i = 0; i < numVertices; i++) {
        visited[i] = false;
        tempsCumule[i] = (tempsOperations[i] >= 0) ? tempsOperations[i] : 0;
        paths[i] = malloc((numVertices + 1) * sizeof(int));
        for (int j = 0; j <= numVertices; j++) {
            paths[i][j] = -1;
        }
        paths[i][0] = i;
    }

    struct File *file = creerFile();
    enfiler(file, sommetSpecifique);
    visited[sommetSpecifique] = true;

    // Parcours BFS à partir du sommet spécifique
    while (!estVide(file)) {
        int u = defiler(file);
        struct Node *temp = graphe->adjLists[u];

        while (temp) {
            int v = temp->vertex;
            if (!visited[v]) {
                visited[v] = true;
                enfiler(file, v);

                // Mise à jour du temps cumulé et des chemins
                tempsCumule[v] = tempsCumule[u] + ((tempsOperations[v] >= 0) ? tempsOperations[v] : 0);
                int pathLength = 0;
                while (paths[u][pathLength] != -1) pathLength++;
                for (int j = 0; j < pathLength; j++) {
                    paths[v][j] = paths[u][j];
                }
                paths[v][pathLength] = v;
                paths[v][pathLength + 1] = -1;
            }
            temp = temp->next;
        }
    }

    // Affichage des chemins pour le sommet spécifique
    for (int i = 0; i < numVertices; i++) {
        if (paths[i][0] == sommetSpecifique) {
            printf("\nPour faire l'operation %d, suivre le chemin : ", sommetSpecifique + 1);
            int j = 0;
            float tempsTotal = 0;
            while (paths[i][j] != -1) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), savedAttributes);
                setColorIndex(color[paths[i][j]]);
                printf("%d", paths[i][j] + 1);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), savedAttributes);

                printf(" a la station n");
                setColorIndex(color[paths[i][j]]);
                printf("%d", color[paths[i][j]] + 1);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), savedAttributes);

                float tempsOp = (tempsOperations[paths[i][j]] >= 0) ? tempsOperations[paths[i][j]] : 0;
                tempsTotal += tempsOp;
                printf(" (temps d'execution: %.2f)", tempsOp);

                j++;
                if (paths[i][j] != -1) {
                    printf(" -> ");
                }
            }
            printf(". Temps total: %.2f", tempsTotal);
            if (tempsTotal > tempsCycle) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
                printf(" (depasse le temps de cycle!)");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), savedAttributes);
            } else {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN);
                printf(" (inferieur au temps de cycle)");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), savedAttributes);
            }
            printf("\n");
        }
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), savedAttributes);

    // Libération de la mémoire
    for (int i = 0; i < numVertices; i++) {
        free(paths[i]);
    }
    free(tempsCumule);
    free(paths);
}