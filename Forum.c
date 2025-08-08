#include <GL/freeglut.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

#include "definitii.h"
#include "prelucrare_useri.h"
#include "gestionare_continut.h"
#include "utilitati_interfata.h"
#include "interfata.h"
#include "interactiuni.h"


/*Ecran si focus default */
Ecran ecran = Welcome;
int focus = 0;

/*Bufere input si dimensiunile lor*/
char bufferNume[MAX_IN_USER] = { 0 };
char bufferParola[MAX_IN_USER] = { 0 };
char bufferCauta[MAX_CAUTA] = { 0 };
char bufferPostare[MAX_CONT_POST] = { 0 };
char bufferComentariu[MAX_CONT_COMENT] = { 0 };

int lgNume = 0;
int lgParola = 0;
int lgCauta = 0;
int lgPostare = 0;
int lgComentariu = 0;

/*Linii pentru postari */
int cursorPostare = 0;
int primaLiniePostare = 0;
int nrLiniiPostare = 1;

/*Linii pentru comentarii*/
int cursorComentariu = 0;
int primaLinieComentariu = 0;
int nrLiniiComentariu = 1;

/* Vizualizare continut si navigatii */
int postVazutId = -1;
int primaPostVazutId = 0;
int primComentVazutId = 0;
int ordineSort = 0; /* 0 nou -> vechi , 1 vechi -> nou */
int cautareActiv = 0;

	/* FUNCTII GLUT */

void onDisplay() {
	int winW = glutGet(GLUT_WINDOW_WIDTH);
	int winH = glutGet(GLUT_WINDOW_HEIGHT);

	/*Culoare background */
	glClearColor(CULOARE_FUNDAL_R, CULOARE_FUNDAL_G, CULOARE_FUNDAL_B,
			1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	/* Proiectie ortografica */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, winW, 0, winH);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	/*Culoarea text default */
	glColor3f(CULOARE_TEXT_R, CULOARE_TEXT_G, CULOARE_TEXT_B);

	/*Deseneaza ecranul curent */
	switch (ecran) {
	case Welcome:
		desenWelcome();
		break;
	case Inregistrare:
		desenInregistrare();
		break;
	case Logare:
		desenLogare();
		break;
	case BlogWelcome:
		desenMain();
		break;
	case VizualizarePostare:
		desenVizPost();
		break;
	default:
		desenText(10, winH - 20, "Ecran invalid!", FONT_MARE);
		break;
	}

	/*Afiseaza mesajele de eroare sau de status */
	afisMsjStatEroare(winW, winH);

	glutSwapBuffers();
}

void onReshape(int w, int h) {
	if (h == 0)
		h = 1; /*Previne impartirea la 0*/
	glViewport(0, 0, w, h);
}

void onTastatura(unsigned char key, int x, int y) {
	tastatura(key, x, y);
	glutPostRedisplay();
}

void onMouse(int buton, int state, int mx, int my) {
	/*Interactiunea se face prin apasarea butonului stang al mouse-ului */
	if (buton == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		mouse(buton, state, mx, my);
	}
	glutPostRedisplay();
}

	/* Functia Main */

int main(int argc, char **argv) {
	/* Initializam un seed random pentru sesiune */
	srand((unsigned int) time(NULL));

	procUseri();
	incarcaPost();

	/*Initializam GLUT */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); /*Dublu buffer , culori RGBA */
	glutInitWindowSize(800, 700); /*Dimensiune ecran */
	glutInitWindowPosition(100, 100);  /* Pozitia initiala */
	glutCreateWindow("Forum");	/* Titlu */

	/* Functii Glut */
	glutDisplayFunc(onDisplay);
	glutReshapeFunc(onReshape);
	glutKeyboardFunc(onTastatura);
	glutMouseFunc(onMouse);

	glutMainLoop();

	return 0;
}
