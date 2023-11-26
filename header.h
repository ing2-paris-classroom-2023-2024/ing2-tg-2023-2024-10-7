//
// Created by yonat on 26/11/2023.
//

#ifndef CODEPRINCIPALE2_HEADER_H
#define CODEPRINCIPALE2_HEADER_H
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <Windows.h>
// Définition de la structure Node
struct Node {
    int vertex;
    struct Node* next;
};
// Définition de la structure Graph
struct Graph {
    int numVertices;
    struct Node** adjLists;
};
// Structure pour le degré des sommets
struct VertexDegree {
    int vertex;
    int degree;
};

/// STRUCTURES FILES
struct NoeudFile {
    int donnee;
    struct NoeudFile* suivant;
};
// Définition de la structure pour la file
struct File {
    struct NoeudFile *debut, *fin;
};
/// STRUCTURES PILES
typedef struct {
    int* items;
    int top;
    int capacite;
} Pile;
/// SOUSPROGRAMME FILES
struct File* creerFile();
void enfiler(struct File* f, int valeur);
int defiler(struct File* f);
bool estVide(struct File* f);
/// SOUSPROGRAMME PILE
Pile* creerPile(int capacite);
bool estPileVide(Pile* pile);
void empiler(Pile* pile, int item);
int depiler(Pile* pile);
void afficherPile(Pile* pile);
int sommetEnHaut(Pile* pile);
/// sousprogrammes exlusion
struct Graph* ouvertureGraphexclusion();
struct Graph* createGraphexlusion(int vertices);
struct Node* createNodeexclusion(int v);
void addEdgeexlusion(struct Graph* graph, int src, int dest);
void afficherContenuFichierExclusion(struct Graph* graph);
void calculateDegreesexlusion(struct Graph* graph, struct VertexDegree degrees[]);
int compareDegreesexlusion(const void* a, const void* b);
void colorGraphWelshPowellexclusion(struct Graph* graph, int* colorAssignments);
/// sousprogrammes precedence
void ajouterArcDirige(struct Graph* graphe, int src, int dest);
struct Graph* creerGrapheDepuisPrecedences();
void bfsAvecPrecedence(struct Graph* graphe, int* color, int affichageMode, int sommetSpecifique);
void afficherPrecedencesDuGraphe(struct Graph* graphe);
void initialiserChemins(int*** chemins, int numVertices);
void mettreAJourChemin(int** chemins, int sommetSource, int sommetDestination);
void bfsEtMemoriserChemins(struct Graph* graphe, int** chemins, int sommetInitial);
void afficherChemin(int* chemin);
/// souqprogramme tempsdecycles
float lireTempsCycle();
void afficherTempsCycle();
/// souqprogramme tempsdecycles operations
float* lireOperationsEtTemps(int* numOperations);
void afficherContenuFichierOperations();
///SOUSPROGRAMME PRECEDENCE ET EXCLUSION
void bfsAvecPrecedenceEtExclusion(struct Graph* graphe, int* color, int mode, int sommetSpecifique);
void afficherTousLesCheminsDepuisSommet(struct Graph* graphe, int* color, int sommetSpecifique);
///SOUSPROGRAMME EXCLUSION, PRECEDENCE ET TEMPS DE CYCLE
void bfsAvecPrecedenceEtExclusionEtTemps(struct Graph* graphe, int* color, const float* tempsOperations, float tempsCycle, int mode, int sommetSpecifique);
void afficherTousLesChemins(struct Graph* graphe, int* color, const float* tempsOperations, float tempsCycle, int sommetSpecifique);
///SOUSPROGRAMME GRAPHIQUE
void setColor(int colorCode);
void setColorIndex(int colorIndex);
#endif //CODEPRINCIPALE2_HEADER_H
