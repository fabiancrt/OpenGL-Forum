#ifndef DEFINITII_H_
#define DEFINITII_H_

#include <GL/freeglut.h>

typedef enum {
	Welcome, Inregistrare, Logare, BlogWelcome, VizualizarePostare
} Ecran;

extern Ecran ecran;
extern int focus;

extern char bufferNume[];
extern char bufferParola[];
extern char bufferCauta[];
extern char bufferPostare[];
extern char bufferComentariu[];

extern int lgNume, lgParola, lgCauta, lgPostare, lgComentariu;

extern int cursorPostare;
extern int primaLiniePostare;
extern int nrLiniiPostare;

extern int cursorComentariu;
extern int primaLinieComentariu;
extern int nrLiniiComentariu;

extern int postVazutId;
extern int primaPostVazutId;
extern int primComentVazutId;
extern int ordineSort; /* 0 NOU -> VECHI, 1 VECHI -> NOU */
extern int cautareActiv;

#define H_ZONA_INPUT 60
#define BARA_SUS_H 35
#define SPATIU_INTRE_ELEMENTE 8
#define MARGINE_TEXT 5
#define MAX_CAUTA 100
#define SAGEATA_W 25
#define SAGEATA_H 25

#define MIN_H_POSTARE 90
#define MIN_H_COMENTARIU 70
#define H_ANTET_POSTARE 30
#define H_SUBSOL_POSTARE 30
#define H_ANTET_COMENTARIU 30
#define PAD_VERT_ELEMENT 10

#define MAX_LINII_INPUT 16
#define MAX_CHAR_PE_LINIE_INPUT 64
#define SPATIU_LINII_VIZ_INPUT 4
#define PAD_INTERN_INPUT 5

#endif
