/**
 * @file huffman.h
 * @author Moldovan Alexandru & Bouillon Quentin
 * @date  : Fri Jan 24
 *
 * @version 0.1
 * @brief Signatures de fonctions pour le projet huffman
 */

#ifndef __HUFF__
#define __HUFF__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define T 255

/**
 * @brief Structure contenant une chaîne de caractères ainsi qu'une fréquence
 * @author Moldovan Alexandru
 */

struct enc {
    long freq;
    unsigned char ch[255];
};

/**
 * @fn int compare(const void * a, const void * b)
 * @author Bouillon Quentin
 * @version 0.1
 * @date Fri Jan 24
 *
 * @brief Comparer deux termes d'un tableau
 * @param a Premier terme, structure de caractères
 * @param b Deuxième terme, structure de caractères
 *
 * @return 0 ou 1 en fonction de si fréquence de a > fréquence de b
 */

int compare(const void * a, const void * b);

/**
 * @fn int countChars(struct enc* tab, int n)
 * @author Moldovan Alexandru
 * @version 0.1
 * @date Fri Jan 24
 *
 * @brief Compte le nombre de caractères différents de notre tableau de structures, avec une fréquence > 1
 * @param tab Tableau de structures de caractères
 * @param n Taille du tableau de structures
 *
 * @return Nombre de caractères différents
 */

int countChars(struct enc* tab, int n);

/**
 * @fn struct enc* reinitTab(struct enc* arbre, int *n, int *p)
 * @author Moldovan Alexandru
 * @version 0.1
 * @date Fri Jan 24
 *
 * @brief Recrée un 'arbre binaire' en enlevant les caractères dont la fréquence est nulle
 * @param arbre tableau de structures de caractères, 'arbre binaire'
 * @param n Nouvelle taille de l'arbre
 * @param p Taille actuelle de l'arbre
 *
 * @return Tableau de structures de caractères sans caractères à fréquence nulle
 */

struct enc* reinitTab(struct enc* arbre, int *n, int *p);

/**
 * @fn struct enc* getChars(char* fichier, int* p)
 * @author Moldovan Alexandru
 * @version 0.1
 * @date Fri Jan 24
 *
 * @brief Extrait les différents caractères d'un fichier, met à jour le nombre de caractères via pointeur
 * @param fichier Chemin du fichier à lire
 * @param p Pointeur du nombre de caractères présents
 *
 * @return Tableau de structures de caractères du fichier
 */

struct enc* getChars(char* fichier, int* p);

/**
 * @fn char** initTab(char** tab)
 * @author Moldovan Alexandru
 * @version 0.1
 * @date Fri Jan 24
 *
 * @brief Initialise un tableau permettant de stocker les codes des différents caractères
 * @param tab Pointeur du tableau à créer
 *
 * @return Tableau de chaînes de caractères
 */

char** initTab(char** tab);

/**
 * @fn char** getCode(struct enc* arbre, int* p)
 * @author Bouillon Quentin
 * @version 0.1
 * @date Fri Jan 24
 *
 * @brief Traite un tableau de structures pour assigner un code binaire à chaque caractère
 * @param arbre Tableau de structures à traiter
 * @param p Taille du tableau à traiter
 *
 * @return Tableau de chaînes de caractères avec caractère et code correspondant
 */

char** getCode(struct enc* arbre, int* p);

/**
 * @fn void encode(char* fichier, char* nouveaufichier, char** tab)
 * @author Moldovan Alexandru
 * @version 0.1
 * @date Fri Jan 24
 *
 * @brief Permet d'écrire le fichier sous forme binaire
 * @param fichier Chemin du fichier original
 * @param nouveaufichier Chemin du fichier à écrire
 * @param tab Table de codage du fichier original
 *
 */

void encode(char* fichier, char* nouveaufichier, char** tab);

/**
 * @fn void decode(char* fichier, char* nouveaufichier, char** tab)
 * @author Bouillon Quentin
 * @version 0.1
 * @date Fri Jan 24
 *
 * @brief Permet d'écrire le fichier "binaire" sous forme originale
 * @param fichier Chemin du fichier compressé
 * @param nouveaufichier Chemin du fichier à écrire
 * @param tab Table de codage du fichier binaire
 *
 */

void decode(char* fichier, char* nouveaufichier, char** tab);

/**
 * @fn void saveTab(char* fichier, char** tab)
 * @author Moldovan Alexandru
 * @version 0.1
 * @date Fri Jan 24
 *
 * @brief Permet d'écrire la table d'encodage dans un fichier
 * @param fichier Chemin du fichier à écrire
 * @param tab Table de codage
 *
 */

void saveTab(char* fichier, char** tab);

/**
 * @fn char** loadTab(char** tab, char* fichier)
 * @author Bouillon Quentin
 * @version 0.1
 * @date Fri Jan 24
 *
 * @brief Permet de charger la table de codage à partir d'un fichier
 * @param fichier Chemin de la table de codage
 * @param tab Table de codage
 *
 */

char** loadTab(char** tab, char* fichier);

/**
 * @fn void showHelp()
 * @author Moldovan Alexandru
 * @version 0.1
 * @date Fri Jan 24
 *
 * @brief Permet d'afficher le menu d'aide
 *
 */

void showHelp();

#endif
