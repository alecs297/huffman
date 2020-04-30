#include "huffman.h"

//Fonction permettant le tri du tableau, utilisée avec qsort
int compare(const void * a, const void * b)
{
    struct enc *t1 = (struct enc *)a;
    struct enc *t2 = (struct enc *)b;
    return (t1->freq > t2->freq);
}

//Fonction retournant le nombre de caractères différents avec une fréquence non nulle
int countChars(struct enc* tab, int n)
{
    int i;
    int res;
    for (i = 0; i < n; i++) {
        if (tab[i].freq > 0) {
            res++;
        }
    }
    return (res);
}

//Fonction permettant d'enlever les caractères à fréquence nulle de notre arbre
struct enc* reinitTab(struct enc* arbre, int *n, int *p)
{
    int i;
    struct enc* _arbre = NULL;
    int deb;
    qsort(arbre, *p, sizeof (struct enc), compare);
    *n = countChars(arbre, *p);
    _arbre = (struct enc*) malloc(((int) *n) * sizeof(struct enc));
    deb = *p - *n;
    for (i = deb; i < *p; i++) {
        _arbre[i - deb] = arbre[i];
    }
    *p = *n;
    return(_arbre);
}

//Fonction permettant d'extraire les caractères d'un fichier
struct enc* getChars(char* fichier, int* p)
{
    struct enc table[T];
    struct enc* arbre = NULL;
    FILE *file = fopen(fichier, "r");
    if (file == NULL) {
        printf("Un problème de lecture du fichier sélectionné est survenu.\n");
        exit(EXIT_FAILURE);
    }

    int i;
    int c;
    int n = T;

    for (i = 0; i < T; i++) {
        table[i].freq = 0;
        table[i].ch[0] = (unsigned char) (i);
    }

    while ((c = fgetc(file)) != EOF) {
        table[c].freq++;
    }
    fclose(file);

    arbre = reinitTab(table, p, &n);

    return(arbre);
}

//Fonction permettant de créer un tableau vide
char** initTab(char** tab)
{
    tab = malloc(T * sizeof(char*));
    int i;
    for (i = 0; i < T; i++) {
        tab[i] = malloc((1) * sizeof(char));
        strcpy(tab[i], "");
    }
    return(tab);
}

//Fonction permettant d'affecter un code binaire aux caractères extraits
char** getCode(struct enc* arbre, int* p)
{
    int i;
    int j;
    char** tab = NULL;
    char* temp = NULL;
    int n = 0;

    tab = initTab(tab);
    do {
        for (j = 0; j < 2; j++) {
            for (i = 0; i < (int) strlen((char*) arbre[j].ch); i++) {
                temp = malloc((strlen((char*) tab[arbre[j].ch[i]]) + 2) * sizeof(char));
                sprintf(temp, "%d%s", j, tab[arbre[j].ch[i]]);
                tab[arbre[j].ch[i]] = temp;
            }
        }

        sprintf((char*) arbre[0].ch, "%s%s", arbre[0].ch, arbre[1].ch);
        arbre[0].freq += arbre[1].freq;
        arbre[1].freq = 0;
        arbre = reinitTab(arbre, &n, p);

    } while(*p > 1);

    return(tab);
}

//Prédicat permettant d'écrire le fichier compressé
void encode(char* fichier, char* nouveaufichier, char** tab)
{
    FILE * file = fopen(fichier, "r");
    FILE * newFile = fopen(nouveaufichier, "w+");
    if (file == NULL || newFile == NULL) {
        printf("Un problème de lecture du fichier sélectionné est survenu.\n");
        exit(EXIT_FAILURE);
    }
    int c;

    while ((c = fgetc(file)) != EOF) {
        fputs(tab[c], newFile);
    }
    fclose(file);
    fclose(newFile);
}

//Prédicat permettant d'écrire le fichier décompressé
void decode(char* fichier, char* nouveaufichier, char** tab)
{
    FILE * file = fopen(fichier, "r");
    FILE * newFile = fopen(nouveaufichier, "w+");

    if (file == NULL || newFile == NULL) {
        printf("Un problème de lecture du fichier sélectionné est survenu.\n");
        exit(EXIT_FAILURE);
    }

    char* temp = (char*) malloc(10 * sizeof(char));
    strcpy(temp, "");
    int c;
    int i;
    int next = 0;

    while ((c = fgetc(file)) != EOF) {
        char* temp_ = (char*) malloc(10 * sizeof(char));
        sprintf(temp_, "%s%c", temp, (unsigned char) c);
        strcpy(temp, temp_);
        i = 0;
        while(i < T && !next) {
            if ((strcmp(temp, tab[i]) == 0) && strlen(tab[i]) > 0) {
                fputc(i, newFile);
                temp = (char*) malloc(10 * sizeof(char));
                strcpy(temp, "");
                next = 1;
            }
            i++;
        }
        next = 0;
    }

    fclose(file);
    fclose(newFile);
}

//Prédicat permettant d'écrire le fichier contenant la table de codage
void saveTab(char* fichier, char** tab)
{
    FILE * newFile = fopen(fichier, "w+");
    int i;
    for (i = 0; i < T; i++) {
        if (strlen(tab[i]) > 0) {
            fprintf(newFile, "%c:%s\n", (unsigned char) i, tab[i]);
        }
    }
    fclose(newFile);
}

//Fonction permettant d'obtenir la table de codage à partir d'un fichier
char** loadTab(char** tab, char* fichier)
{
    int c;
    unsigned char readChar = 0;
    char* temp = (char*) malloc((int) (10) * sizeof(char));
    strcpy(temp, "");

    FILE * file = fopen(fichier, "r");
    if (file == NULL) {
        printf("Un problème de lecture du fichier sélectionné est survenu.\n");
        exit(EXIT_FAILURE);
    }
    while ((c = fgetc(file)) != EOF) {
        if (!readChar) {
            readChar = (unsigned char) c;
            c = fgetc(file);

        } else {
            if (c != 10) {
                sprintf(temp, "%s%c", temp, c);

            } else {
                tab[readChar] = (char*) malloc((int) (10) * sizeof(char));
                strcpy(tab[(int) readChar], temp);
                readChar = 0;
                temp = (char*) malloc((int) (10) * sizeof(char));
                strcpy(temp, "");
            }
        }
    }
    fclose(file);
    return(tab);
}

//Prédicat affichant le menu d'aide
void showHelp()
{
    printf("\n\nUtilisation:\t huffman <paramètre> -[arguments]\n");
    printf("\n* Liste des paramètres (obligatoire):\n");
    printf("\t-c <chemin fichier>\t- Permet d'encoder un fichier\n");
    printf("\t-d <chemin fichier>\t- Permet de décoder un fichier\n");
    printf("\n* Liste des arguments:\n");
    printf("\t-h \tAffiche le menu d'aide\n");
    printf("\t-o \tChemin du nouveau fichier\n\t\tPar défaut: encoded.txt / decoded.txt\n");
    printf("\t-t \tChemin de la table d'encodage\n\t\tPar défaut: table.txt\n");
    printf("\n\n* Remarques:\n\tL'ordre des paramètres doit être respecté. \n\tLa table d'encodage se trouve dans un fichier séparé par rapport au fichier encodé.\n");
    printf("\n* Important:\n\tIl ne s'agit pas de compression réelle\n");
    printf("\n\n* Exemples:\n");
    printf("\thuffman -c beemoviescript.txt -t mytable -o compressed\n");
    printf("\thuffman -d compressed -t mytable -o new_beemoviescript.txt\n\n");
    exit(EXIT_SUCCESS);
}
