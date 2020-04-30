#include "huffman.h"


// Fonction principale du programme
int main(int argc, char const *argv[])
{
    char* raw;
    char* encoded = "encoded.txt";
    char* decoded = "decoded.txt";
    char* enctable = "table.txt";
    char** tab = NULL;
    struct enc* arbre = NULL;
    int n;
    int i;
    // Traitement des arguments
    if (argc < 3) {
        showHelp();
    }

    raw = malloc((strlen(argv[2])) * sizeof(char));
    strcpy(raw, argv[2]);
    // Traitement des options
    for (i = 1; i < argc; i++) {
        if ((i + 1 != argc) && (argv[i + 1][0] != '-')) {
            if (strcmp(argv[i], "-o") == 0) {
                encoded = malloc((strlen(argv[i + 1])) * sizeof(char));
                strcpy(encoded, argv[i+1]);
                decoded = malloc((strlen(argv[i + 1])) * sizeof(char));
                strcpy(decoded, argv[i+1]);
            }
            if (strcmp(argv[i], "-t") == 0) {
                enctable = malloc((strlen(argv[i + 1])) * sizeof(char));
                strcpy(enctable, argv[i+1]);
            }
            if ((strcmp(argv[i], "-h") == 0) || strcmp(argv[i], "--h") == 0) {
                showHelp();
            }
        }
    }
    // Début du timer
    clock_t debut = clock();

    // Compression ou décompression
    if (strcmp(argv[1], "-c") == 0) {
        arbre = getChars(raw, &n);
        if (n > 1) {
            printf("\nFichier traité depuis         %s\n", raw);
            tab = getCode(arbre, &n);
            printf("Table créée.\n");
            encode(raw, encoded, tab);
            printf("Table extraite dans           %s\n", enctable);
            saveTab(enctable, tab);
            printf("Fichier encodé dans           %s\n", encoded);

        } else {
            printf("Le fichier choisi est vide.\n");
            exit(EXIT_FAILURE);
        }

    } else if (strcmp(argv[1], "-d") == 0) {
        tab = initTab(tab);
        tab = loadTab(tab, enctable);
        printf("\nTable extraite depuis         %s\n", enctable);
        decode(raw, decoded, tab);
        printf("Fichier décodé dans           %s.\n", decoded);
    } else {
        showHelp();
    }
    // Affichage du temps mis par le programme à effectuer l'action
    printf("Terminé sous                  %lfsec\n\n", (double)(clock() - debut) / CLOCKS_PER_SEC);

    free(arbre);
    free(tab);
    return 0;
}
