#ifndef UTILITATI_INTERFATA_H_
#define UTILITATI_INTERFATA_H_

#include <GL/freeglut.h>
#include "prelucrare_useri.h"
#include "definitii.h"

/* Definitii Font */
#define FONT_TITLU GLUT_BITMAP_TIMES_ROMAN_24
#define FONT_MARE GLUT_BITMAP_HELVETICA_18
#define FONT_NORMAL GLUT_BITMAP_HELVETICA_12
#define FONT_MIC GLUT_BITMAP_HELVETICA_10
#define FONT_BUTON GLUT_BITMAP_HELVETICA_12
#define FONT_COD GLUT_BITMAP_9_BY_15
#define FONT_COD_DESCENDENT_APROX 2

/*Definitii culori */
#define CULOARE_FUNDAL_R 0.9f
#define CULOARE_FUNDAL_G 0.92f
#define CULOARE_FUNDAL_B 0.95f
#define CULOARE_BARA_R 0.4f
#define CULOARE_BARA_G 0.6f
#define CULOARE_BARA_B 0.8f
#define CULOARE_POST_R 0.95f
#define CULOARE_POST_G 0.97f
#define CULOARE_POST_B 1.0f
#define CULOARE_INPUT_R 0.92f
#define CULOARE_INPUT_G 0.94f
#define CULOARE_INPUT_B 0.98f
#define CULOARE_TEXT_R 0.1f
#define CULOARE_TEXT_G 0.1f
#define CULOARE_TEXT_B 0.2f
#define CULOARE_ACCENT_R 0.2f
#define CULOARE_ACCENT_G 0.4f
#define CULOARE_ACCENT_B 0.7f
#define CULOARE_EROARE_R 0.8f
#define CULOARE_EROARE_G 0.2f
#define CULOARE_EROARE_B 0.2f
#define CULOARE_SUCCES_R 0.2f
#define CULOARE_SUCCES_G 0.7f
#define CULOARE_SUCCES_B 0.2f
#define CULOARE_INCHIS_R 0.7f
#define CULOARE_INCHIS_G 0.7f
#define CULOARE_INCHIS_B 0.7f
#define CULOARE_RASPUNS_R 0.85f
#define CULOARE_RASPUNS_G 1.0f
#define CULOARE_RASPUNS_B 0.85f

/* Culori specifice block-uri text */
#define CULOARE_COD_FUNDAL_R 0.92f
#define CULOARE_COD_FUNDAL_G 0.92f
#define CULOARE_COD_FUNDAL_B 0.92f
#define CULOARE_COD_TEXT_ALBASTRU_R 0.15f
#define CULOARE_COD_TEXT_ALBASTRU_G 0.35f
#define CULOARE_COD_TEXT_ALBASTRU_B 0.8f
#define INDENTARE_COD_STANGA 8
#define PADDING_COD_VERTICAL 2

/* Functii ajutatoare pentru simplificare */
void desenCasuta(int x, int y, int w, int h);
void desenText(int x, int y, const char *s, void *font);
int calculWText(const char *s, void *font);
void desenFocus(int x, int y, int w, int h);
void desenSageata(int x, int y, int w, int h, int directie);
void desenInputText(int x, int y, int w, int h, const char *buffer, int len,
		int maxLen, int focusId, int stateFocusActal, int esteParola,
		const char *substituent);
void desenButon(int x, int y, int w, int h, const char *label, int focusId,
		int stateFocusActal, int dezactivat);

/* Procesare text si desen pentru interfata */
int calculHText(const char *text, int maxWidth, void *fontOriginal);
void desenIncadText(int x, int y_sus, int maxWidth, const char *text,
		void *fontOriginal);
void desenTextMultiLineInput(int x_casuta, int y_sus_casuta,
		int latime_casuta, int inaltime_casuta, const char *textComplet,
		int lungimeTextComplet, int primaLinieDeAfisat, void *fontNormal,
		void *fontCod, int esteFocus);
int calculHNecElement(const char *continut,
		int latimeTextDisponibila, int inaltimeAntet, int inaltimeSubsol,
		int inaltimeMinimaElement);

/* Pentru multi-line */
int calcNrLiniiBuffer(const char *buffer, int lungime);
const char* gasesteStartLinie(const char *buffer, int lungimeBuffer,
		int indexLinieDorita);
int obtCursorCurent(const char *buffer, int lungimeBuffer,
		int linieCurenta);

#endif
