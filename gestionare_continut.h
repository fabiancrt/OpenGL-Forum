#ifndef GESTIONARE_CONTINUT_H_
#define GESTIONARE_CONTINUT_H_

#include <time.h>
#include "prelucrare_useri.h"
#include "definitii.h"

#define MAX_POSTARI 1024
#define MAX_COMENTARII 50
#define MAX_CONT_POST 1024
#define MAX_CONT_COMENT 256

typedef struct {
	int id;
	time_t timestamp;
	char Data[20];
	char Continut[MAX_CONT_COMENT];
	char Autor[MAX_IN_USER];
	int autorIndex;
	int esteRaspuns;
} Comentariu;

typedef struct {
	int id;
	time_t timestamp;
	char Data[20];
	char continutP[MAX_CONT_POST];
	char Autor[MAX_IN_USER];
	int autorIndex;
	Comentariu Comentarii[MAX_COMENTARII];
	int ctrComent;
	int urmComentId;
	int inchisaP;
	int raspunsId;
} Postare;

extern Postare Postari[MAX_POSTARI];
extern int ctrPost;
extern int urmPostId;

void incarcaPost(void);
void salvezPost(void);
void shellSort(void *base, size_t nmemb, size_t size,
		int (*cmp)(const void*, const void*));
void adaugPost(const char *continut, int autorIdx);
void adaugComent(int postIndex, const char *continut, int autorIdx);
void stergePost(int postId);
void marcheazaRaspuns(int postIndex, int comentariuId);
void sortPost(void);
int postSePotriveste(const Postare *p, const char *termen);

#endif

