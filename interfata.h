#ifndef INTERFATA_H_
#define INTERFATA_H_

#include "definitii.h"
#include "utilitati_interfata.h"
#include "gestionare_continut.h"
#include "prelucrare_useri.h"

/* Desen pentru fiecare ecran si element */
void desenWelcome(void);
void desenInregistrare(void);
void desenLogare(void);
void desenMain(void);
void desenElementPostare(Postare *p, int yPos, int index,
		int *outInaltimeDesenata);
void desenVizPost(void);
void desenComentariuElement(Comentariu *c, int yPos, int postIndex,
		int *outInaltimeDesenata);
void desenBaraCautare(int winW, int winH, int xElemStart, int latimeDisponibilaTotal, int yElemTop, int hElem);
void afisMsjStatEroare(int winW, int winH);

#endif
