#ifndef INTERACTIUNI_H_
#define INTERACTIUNI_H_

#include "definitii.h"
#include "prelucrare_useri.h"
#include "gestionare_continut.h"
#include "utilitati_interfata.h"

typedef enum {
    noFocus = 0,
    focusPostInput = 1,
    focusBtnPost = 2,
    focusSortNou = 3,
    focusSortVechi = 4,
    focusLogout = 5,
    focusCautare = 6

} elementFocus;

typedef enum {
	Nou = 0,
	Vechi = 1
} ordineSortare;
void tastatura(unsigned char k, int x, int y);
void mouse(int buton, int state, int mx, int my);

/*Pt. tastatura */
void tastaturaWelcome(unsigned char k, int x, int y);
void tastaturaInregistrare(unsigned char k, int x, int y);
void tastaturaLogare(unsigned char k, int x, int y);
void tastaturaMain(unsigned char k, int x, int y);
void tastaturaVizPost(unsigned char k, int x, int y);

/*Pt. mouse */
void mouseWelcome(int buton, int state, int mx, int my);
void mouseInreg(int buton, int state, int mx, int my);
void mouseLogare(int buton, int state, int mx, int my);
void mouseMain(int buton, int state, int mx, int my);
void mouseVizPost(int buton, int state, int mx, int my);

#endif
