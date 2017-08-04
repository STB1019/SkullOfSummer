#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DIM 500
#define ARRAY_SIZE 16777216
#define FILENAME "schifo.bmp"

typedef struct pixel pxl;
typedef struct pxlCounter counter;

//struttura per associare la terna RGB al pixel
struct pixel {
	int r;
	int g;
	int b;
};

//struttura per associare il colore di un pixel al numero di volte in cui compare 
struct pxlCounter {
	pxl color;
	int counter;
};

pxl matrix[DIM][DIM];
counter colors[ARRAY_SIZE];

//funzione che ritorna lunghezza in pixel dell'immagine
int imgL(char *filename) {
	FILE *fp;
	int n, int_var, l;
	fp = fopen(filename, "r");
	fseek(fp, 18, 0);
	n = fread(&int_var, sizeof(int), 1, fp);
	l = int_var;
	fclose(fp);
	return l;
}

//funzione che ritorna l'altezza in pixel dell'immagine
int imgH(char *filename) {
	FILE *fp;
	int n, int_var, h;
	fp = fopen(filename, "r");
	fseek(fp, 22, 0);
	n = fread(&int_var, sizeof(int), 1, fp);
	h = int_var;
	fclose(fp);
	return h;
}

//funzione che ritorna il numero di bit per pixel
int nBit(char *filename) {
	FILE *fp;
	short short_var;
	int n, nBit;
	fp = fopen(filename, "r");
	fseek(fp, 28, 0);
	n = fread(&short_var, sizeof(short), 1, fp);
	nBit = short_var;
	fclose(fp);
	return nBit;
}

//funzione che ritorna l'offset, punto dal quale iniziano le informazioni riguardanti la codifica dei pixel
int getOffset(char *filename) {
	FILE *fp;
	int n, int_var, offset;
	fp = fopen(filename, "r");
	fseek(fp, 10, 0);
	n = fread(&int_var, sizeof(int), 1, fp);
	offset = int_var;
	fclose(fp);
	return offset;
}

//funzione che ritorna la lunghezza della riga in byte
int rowL(char *filename) {
	int w = imgL(filename);
	int bit = nBit(filename);
	int l = ((w * bit) + (32 - (w * bit) % 32)) / 8;
	return l;
}

//totale byte necessari per memorizzare un array di pixel per un'immagine a n bit
/*int pixelArraySize(char *filename) {
	int l = rowL(filename);
	int h = imgH(filename);
	int pxlArraySize = l * h;
	return pxlArraySize;
}*/

//funzione che ritorna il numero di byte di padding
int getPadding(char *filename) {
	int rowSize = rowL(filename);
	int bit = nBit(filename);
	int l = imgL(filename);
	int nByte = l * bit / 8;
	if(nByte % 4 == 0) return 0;
	else {
		int nPadding = rowSize % (nByte);
		return nPadding;
	}
}

//funzione che stampa il colore di ogni singolo pixel dell'immagine
void readRow(char *filename) {
	FILE *fp;
	fp = fopen(filename, "r");
	unsigned char BitMap[3];
	int h = imgH(filename);
	int l = imgL(filename);

	fseek(fp, getOffset(filename), 0);
	
	for(int j = 0; j < l; j++) {
		for(int i = 0; i < h; i++) {
			fread(BitMap, sizeof(char), 3, fp);
			printf("%03d %03d %03d\n", BitMap[0], BitMap[1], BitMap[2]);
			}
			fread(BitMap, sizeof(char), getPadding(filename), fp);
	}

	fclose(fp);
}

//funzione per controllare che il file esista all'interno della cartella e che sia del formato corretto
bool checkSignature(char *filename) {
	FILE *fp;
	char signature[2];
	fp = fopen(filename, "r");
	
	if(fp == NULL) {
		printf("File non trovato!\n");
		return false;
	}
	
	fseek(fp, 0, 0);
	fread(signature, sizeof(char), 2, fp);
	
	if(signature[0] == 'B' && signature[1] == 'M') return true;
	else {
		printf("Codifica file errata!\n");
		return false;
	}
	fclose(fp);
}

//funzione per controllare che l'immagine sia codificata a 24 bit
bool checkBit(char *filename) {
	if(nBit(filename) == 24) return true;
	else{
		printf("L'immagine non è a 24-bit");
		return false;
	}
}

//funzione per controllare che l'immagine sia quadrata
bool checkDimension(char *filename) {
	if(imgL(filename) == imgH(filename) && imgL(filename) <= DIM) return true;
	else {
		printf("L'immagine non rispetta le dimensioni!\n");
		return false;
	}
}

//funzione che esegue tutti i controlli
bool checkImage(char *filename) {
	if(checkSignature(filename) && checkBit(filename) && checkDimension(filename)) return true;
	else return false;
}

//funzione che riempie una matrice con i pixel dell'immagine
void createMatrix(char *filename, pxl matrix[DIM][DIM]) {
	if(checkImage(filename)) {
		FILE *fp;
		fp = fopen(filename, "r");
		unsigned char BitMap[3];
		int h = imgH(filename);
		int l = imgL(filename);
	
		fseek(fp, getOffset(filename), 0);
		for(int j = 0; j < l; j++) {
			for(int i = 0; i < h; i++) {
				fread(BitMap, sizeof(char), 3, fp);
				pxl tmp;
				tmp.b = BitMap[0];
				tmp.g = BitMap[1];
				tmp.r = BitMap[2];
				matrix[j][i] = tmp;
			}
			
			fread(BitMap, sizeof(char), getPadding(filename), fp);
		}

		fclose(fp);
	}
}

//funzione che compara 2 pixel
bool pxlComparison(pxl pxl1, pxl pxl2) {
	if(pxl1.r == pxl2.r && pxl1.g == pxl2.g && pxl1.b == pxl2.b)
		return true;
	else return false;
}

//funzione che ritorna true se un pixel è uguale a quello contenuto in un array e ne aumenta il relativo contatore
bool checkColors(pxl _pxl, counter *array, int c) {
	for(int i = 0; i <= c; i++) {
		if(pxlComparison(_pxl, array[i].color)) {
			array[i].counter += 1;
			return true;
		}
	}
	return false;
}

//funzione che stampa a schermo l'istogramma
void istoStamp(counter *array, int c) {
	for(int i = 0; i <= c; i++) {
		printf("%03d %03d %03d: ", array[i].color.r, array[i].color.g, array[i].color.b);
		for(int j = 0; j < array[i].counter; j++) {
			printf("*");
		}
		printf("\n");
	}
}

//funzione che stampa i diversi pixel e il numero di volte che compaiono
void matrixCounter(char *filename) {
	//pxl matrix[DIM][DIM];
	int h = imgH(filename);
	int l = imgL(filename);
	int c = 0;
	
	if(!checkImage(filename)) printf("\nCambiare immagine, per favore\n");
		else {
		createMatrix(filename, matrix);
	
		colors[c].color = matrix[0][0];
	
		for(int j = 0; j < l; j++) {
			for(int i = 0; i < h; i++) {
				if(!(checkColors(matrix[j][i], colors, c))) {
					c++;
					colors[c].color = matrix[j][i];
					colors[c].counter += 1;
				}
			}
		}
	
	for(int i = 0; i <= c; i++) {
		printf("%03d %03d %03d: ", colors[i].color.r, colors[i].color.g, colors[i].color.b);
		printf("%d\n", colors[i].counter);
	}
		printf("\nColori trovati: %d\n", c+1);
	}
	istoStamp(colors, c);
}

//main
int main(int argn, char *argv[]) {

	/*printf("\n%s\n", argv[0]);
	printf("\n%s\n", argv[1]);
	printf("\n%d\n", argn);
	printf("\nInserire nome del file da caricare\n");*/

	
	/*print di controllo
	printf("length: %d heigth: %d nBit: %d\n", imgL(FILENAME), imgH(FILENAME), nBit(FILENAME));
	readRow(FILENAME);
	readMatrix(FILENAME);
	printf("%d\n", getOffset(FILENAME));
	printf("padding: %d\n", getPadding(FILENAME));
	printf("%d\n", pixelArraySize(FILENAME));*/
	matrixCounter(FILENAME);
	return 0;
}
