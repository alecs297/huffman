# Programme Huffman, 
développé par Moldovan Alexandru et Bouillon Quentin.

***


> Il s'agit d'un algorithme de compression (non réelle) permettant de coder un fichier texte sur un nombre de bits variable plutôt que sur un octet.
Le programme associe à chaque caractère un code binaire, de la taille la plus petite pour un caractère fréquent à une taille plus grande pour un caractère moins fréquent.
Le programme permet de compresser ou de décompresser un fichier texte et associe à celui-ci une table de codage spécifique (dans un fichier séparé).

***


## Compilation (gcc)

Pour compiler le programme, exécutez "make" dans le dossier.

***

## Quelques fichiers exemples se situent dans le dossier associé

```
Source: 
	-exemple_1: https://gist.github.com/MattIPv4/045239bc27b16b2bcf7a3a9a4648c08a
	-exemple_2: http://patorjk.com/software/taag/
```
***


## Utilisation:

> huffman <paramètre> -[arguments]
```
* Liste des paramètres (obligatoire):
	-c <chemin fichier>	- Permet d'encoder un fichier
	-d <chemin fichier>	- Permet de décoder un fichier

* Liste des arguments:
	-h	Affiche le menu d'aide
	-o	Chemin du nouveau fichier
		Par défaut: encoded.txt / decoded.txt
	-t	Chemin de la table d'encodage
		Par défaut: table.txt


* Remarques:
	L'ordre des paramètres doit être respecté. 
	La table d'encodage se trouve dans un fichier séparé par rapport au fichier encodé.

* Important:
	Il ne s'agit pas de compression réelle

```
## Exemples:
```
	huffman -c beemoviescript.txt -t mytable -o compressed
	huffman -d compressed -t mytable -o new_beemoviescript.txt
```
