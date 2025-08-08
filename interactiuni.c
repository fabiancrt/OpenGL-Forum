#include "interactiuni.h"
#include <GL/freeglut.h>
#include <string.h>
#include <stdio.h>
#include "prelucrare_useri.h"
#include "gestionare_continut.h"
#include "utilitati_interfata.h"
#include "definitii.h"
#include "interfata.h"

static void curatBufferAuth() {
	lgNume = 0;
	bufferNume[0] = '\0';
	lgParola = 0;
	bufferParola[0] = '\0';
}

static void curatBuffInputPost() {
	lgPostare = 0;
	bufferPostare[0] = '\0';
	cursorPostare = 0;
	primaLiniePostare = 0;
	nrLiniiPostare = 1;
}

static void curatBuffInputComm() {
	lgComentariu = 0;
	bufferComentariu[0] = '\0';
	cursorComentariu = 0;
	primaLinieComentariu = 0;
	nrLiniiComentariu = 1;
}

void tastaturaWelcome(unsigned char k, int x, int y) {
	/*Gol deoarece momentan navigarea se face cu mouse-ul in Welcome*/
}

void tastaturaInregistrare(unsigned char k, int x, int y) {
	curataMesaje();
	/*Cazul in care se introduc caractere in casuta */
	if (k >= 32 && k < 127) {
		if (focus == 1 && lgNume < MAX_IN_USER - 1) {
			bufferNume[lgNume++] = k;
			bufferNume[lgNume] = '\0';
		} else if (focus == 2 && lgParola < MAX_IN_USER - 1) {
			bufferParola[lgParola++] = k;
			bufferParola[lgParola] = '\0';
		}
		/*Cazuri particulare */
	} else if (k == 8) {/* inapoispace */
		if (focus == 1 && lgNume > 0) {
			bufferNume[--lgNume] = '\0';
		} else if (focus == 2 && lgParola > 0) {
			bufferParola[--lgParola] = '\0';
		}
	} else if (k == 9) { /* Tab */
		if (focus == 1)
			focus = focusBtnPost;
		else if (focus == 2)
			focus = focusSortNou;
		else if (focus == 3)
			focus = focusSortVechi;
		else if (focus == 4)
			focus = focusPostInput;
		else
			focus = focusPostInput;
	} else if (k == '\r' && focus == 3) { /* Enter in casuta de trimite */
		char tempNume[MAX_IN_USER], tempParola[MAX_IN_USER];
		strncpy(tempNume, bufferNume, MAX_IN_USER - 1);
		tempNume[MAX_IN_USER - 1] = '\0';
		strncpy(tempParola, bufferParola, MAX_IN_USER - 1);
		tempParola[MAX_IN_USER - 1] = '\0';

		adaugaUser(tempNume, tempParola); /* Adauga userul sau eroare. */

		if (mesajStatus[0] != '\0' && mesajEroare[0] == '\0') {
			ecran = Logare;
			lgParola = 0;
			bufferParola[0] = '\0';
			focus = focusPostInput; /*Focus pe username*/
		} else {
			if (strstr(mesajEroare, "Utilizatori")
					|| strstr(mesajEroare, "Username"))
				focus = focusPostInput;
			else if (strstr(mesajEroare, "parola"))
				focus = focusBtnPost;
		}
	} else if (k == '\r' && focus == 4) { /*Enter pe Inapoi */
		ecran = Welcome;
		curatBufferAuth();
		focus = noFocus;
	}
}

void tastaturaLogare(unsigned char k, int x, int y) {
	curataMesaje();
	if (k >= 32 && k < 127) {
		if (focus == 1 && lgNume < MAX_IN_USER - 1) {
			bufferNume[lgNume++] = k;
			bufferNume[lgNume] = '\0';
		} else if (focus == 2 && lgParola < MAX_IN_USER - 1) {
			bufferParola[lgParola++] = k;
			bufferParola[lgParola] = '\0';
		}
	} else if (k == 8) { /* inapoispace */
		if (focus == 1 && lgNume > 0) {
			bufferNume[--lgNume] = '\0';
		} else if (focus == 2 && lgParola > 0) {
			bufferParola[--lgParola] = '\0';
		}
	} else if (k == 9) {/* Tab */
		if (focus == 1)
			focus = focusBtnPost;
		else if (focus == 2)
			focus = focusSortNou;
		else if (focus == 3)
			focus = focusSortVechi;
		else if (focus == 4)
			focus = focusPostInput;
		else
			focus = focusPostInput;
	} else if (k == '\r' && focus == 3) { /*Enter cu focus pe trimite */
		int userIndex = verificaLogarea(bufferNume, bufferParola);
		if (userIndex >= 0) {
			userCurentId = userIndex;
			ecran = BlogWelcome;
			curatBufferAuth();
			curatBuffInputPost(); /*Curata si casuta de postat*/
			lgCauta = 0;
			bufferCauta[0] = '\0';
			cautareActiv = 0;
			primaPostVazutId = 0;
			sortPost();
			focus = noFocus;
			strcpy(mesajStatus, "Logare reusita!");
		} else {
			strcpy(mesajEroare, "Username sau parola incorecta!");
			lgParola = 0;
			bufferParola[0] = '\0';
			focus = focusBtnPost;
			/*bufferul de nume ramane */
		}
	} else if (k == '\r' && focus == 4) {
		ecran = Welcome;
		curatBufferAuth();
		focus = noFocus;
	}
}

void tastaturaMain(unsigned char k, int x, int y) {
	curataMesaje();
	if (focus == focusPostInput) { /*Focus input postare */
		int lungimeCursor = obtCursorCurent(bufferPostare,
				lgPostare, cursorPostare);
		if (k == '\r') {
			if (glutGetModifiers() & GLUT_ACTIVE_SHIFT) { /*Shift + Enter \n */
				if (nrLiniiPostare < MAX_LINII_INPUT
						&& lgPostare < MAX_CONT_POST - 1) {
					bufferPostare[lgPostare++] = '\n';
					bufferPostare[lgPostare] = '\0';
					nrLiniiPostare++;
					cursorPostare++;
					if (nrLiniiPostare > primaLiniePostare + 1
							&& primaLiniePostare
									< nrLiniiPostare - 2) {
						primaLiniePostare++;
					}
				}
			} else { /*Enter pentru a posta */
				adaugPost(bufferPostare, userCurentId);
				if (mesajStatus[0] != '\0' && mesajEroare[0] == '\0') {
					curatBuffInputPost();
				}
			}
		} else if (k == 8) { /*Backspace*/
			if (lgPostare > 0) {
				if (bufferPostare[lgPostare - 1] == '\n') {
					nrLiniiPostare--;
					cursorPostare--;
					if (primaLiniePostare > 0
							&& primaLiniePostare
									>= cursorPostare) {
						primaLiniePostare--;
					}
				}
				bufferPostare[--lgPostare] = '\0';
			}
		} else if (k >= 32 && k <= 126) { /*Car. printabile */
			if (k == '`' && lgPostare >= 2
					&& bufferPostare[lgPostare - 1] == '`'
					&& bufferPostare[lgPostare - 2] == '`') {
				if (lgPostare < MAX_CONT_POST - 1)
					bufferPostare[lgPostare++] = k;
			} else if (lungimeCursor < MAX_CHAR_PE_LINIE_INPUT
					&& lgPostare < MAX_CONT_POST - 1) {
				bufferPostare[lgPostare++] = k;
			} else if (nrLiniiPostare < MAX_LINII_INPUT
					&& lgPostare < MAX_CONT_POST - 2) {
				bufferPostare[lgPostare++] = '\n';
				bufferPostare[lgPostare++] = k;
				nrLiniiPostare++;
				cursorPostare++;
				if (nrLiniiPostare > primaLiniePostare + 1
						&& primaLiniePostare
								< nrLiniiPostare - 2) {
					primaLiniePostare++;
				}
			}
			bufferPostare[lgPostare] = '\0';
		} else if (k == 9) { /*Tab*/
			focus = focusBtnPost; /* "Posteaza" */
		}
	} else if (focus == focusBtnPost && k == '\r') { /* Enter "Posteaza" */
		adaugPost(bufferPostare, userCurentId);
		if (mesajStatus[0] != '\0' && mesajEroare[0] == '\0') {
			curatBuffInputPost();
			focus = focusPostInput;
		}
	} else if (focus == 6) { /* Focus pe bara cautare */
		if (k >= 32 && k <= 126 && lgCauta < MAX_CAUTA - 1) {
			bufferCauta[lgCauta++] = k;
			bufferCauta[lgCauta] = '\0';
			cautareActiv = 1;
			primaPostVazutId = 0;
		} else if (k == 8 && lgCauta > 0) {
			bufferCauta[--lgCauta] = '\0';
			cautareActiv = (lgCauta > 0);
			primaPostVazutId = 0;
		} else if (k == '\r') { /* Enter finalizeaza  cautarea */
			cautareActiv = (curataSpatiu(bufferCauta) > 0);
			primaPostVazutId = 0;
			focus = noFocus;
		} else if (k == 9) {
			focus = focusLogout; /*Butonul "Logout"*/
		}
	} else if (k == 9) { /*Navigare generala cu tab */
		if (focus == noFocus)
			focus = focusPostInput; /* Input postare */
		else if (focus == focusPostInput)
			focus = focusBtnPost; /* Buton Posteaza */
		else if (focus == focusBtnPost)
			focus = focusSortNou; /* Sort Nou */
		else if (focus == focusSortNou)
			focus = focusSortVechi; /* Sort Vechi */
		else if (focus == focusSortVechi)
			focus = focusCautare; /* Bara Cautare */
		else if (focus == focusCautare)
			focus = focusLogout; /* Logout */
		else if (focus == focusLogout)
			focus = focusPostInput; /* Inapoi la input postare */
	} else if (focus == focusSortNou && k == '\r') { /* Enter pe Sort Nou */
		ordineSort = Nou;
		sortPost();
		primaPostVazutId = 0;
	} else if (focus == focusSortVechi && k == '\r') { /* Enter sort vechi */
		ordineSort = Vechi;
		sortPost();
		primaPostVazutId = 0;
	} else if (focus == 5 && k == '\r') { /* Enter Logout */
		ecran = Welcome;
		userCurentId = -1;
		curatBufferAuth();
		curatBuffInputPost();
		lgCauta = 0;
		bufferCauta[0] = '\0';
		cautareActiv = 0;
		focus = noFocus;
		strcpy(mesajStatus, "Logout reusit.");
	}
}

void tastaturaVizPost(unsigned char k, int x, int y) {
	curataMesaje();
	if (postVazutId < 0 || postVazutId >= ctrPost)
		return;
	Postare *post = &Postari[postVazutId];
	int postEsteDeschis = !post->inchisaP;

	if (focus == 1 && postEsteDeschis) {
		int lgLinieCrt = obtCursorCurent(
				bufferComentariu, lgComentariu, cursorComentariu);
		if (k == '\r') {
			if (glutGetModifiers() & GLUT_ACTIVE_SHIFT) { /* Shift + Enter pentru newline */
				if (nrLiniiComentariu < MAX_LINII_INPUT
						&& lgComentariu < MAX_CONT_COMENT - 1) {
					bufferComentariu[lgComentariu++] = '\n';
					bufferComentariu[lgComentariu] = '\0';
					nrLiniiComentariu++;
					cursorComentariu++;
					if (nrLiniiComentariu
							> primaLinieComentariu + 1
							&& primaLinieComentariu
									< nrLiniiComentariu - 2) {
						primaLinieComentariu++;
					}
				}
			} else { /* Enter pentru a comenta */
				adaugComent(postVazutId, bufferComentariu,
						userCurentId);
				if (mesajStatus[0] != '\0' && mesajEroare[0] == '\0') {
					curatBuffInputComm();
				}
			}
		} else if (k == 8) {
			if (lgComentariu > 0) {
				if (bufferComentariu[lgComentariu - 1] == '\n') {
					nrLiniiComentariu--;
					cursorComentariu--;
					if (primaLinieComentariu > 0
							&& primaLinieComentariu
									>= cursorComentariu) {
						primaLinieComentariu--;
					}
				}
				bufferComentariu[--lgComentariu] = '\0';
			}
		} else if (k >= 32 && k <= 126) { /* Caractere printabile */
			if (k == '`' && lgComentariu >= 2
					&& bufferComentariu[lgComentariu - 1] == '`'
					&& bufferComentariu[lgComentariu - 2] == '`') {
				if (lgComentariu < MAX_CONT_COMENT - 1)
					bufferComentariu[lgComentariu++] = k;
			} else if (lgLinieCrt < MAX_CHAR_PE_LINIE_INPUT
					&& lgComentariu < MAX_CONT_COMENT - 1) {
				bufferComentariu[lgComentariu++] = k;
			} else if (nrLiniiComentariu < MAX_LINII_INPUT
					&& lgComentariu < MAX_CONT_COMENT - 2) {
				bufferComentariu[lgComentariu++] = '\n';
				bufferComentariu[lgComentariu++] = k;
				nrLiniiComentariu++;
				cursorComentariu++;
				if (nrLiniiComentariu
						> primaLinieComentariu + 1
						&& primaLinieComentariu
								< nrLiniiComentariu - 2) {
					primaLinieComentariu++;
				}
			}
			bufferComentariu[lgComentariu] = '\0';
		} else if (k == 9) {
			focus = focusBtnPost; /*Butonul "Comenteaza" */
		}
	} else if (focus == 1 && !postEsteDeschis) { /* Caz potareainchisa */
		if (k == 9)
			focus = focusSortNou;
		else if (k != 27)
			strcpy(mesajEroare, "Postarea este inchisa.");
	} else if (focus == 2 && k == '\r') {
		if (postEsteDeschis) {
			adaugComent(postVazutId, bufferComentariu,
					userCurentId);
			if (mesajStatus[0] != '\0' && mesajEroare[0] == '\0') {
				curatBuffInputComm();
				focus = focusPostInput;
			}
		} else {
			strcpy(mesajEroare, "Postarea este inchisa. Nu se poate comenta.");
		}
	} else if (k == 9) { /* Navigarea generala cu tab */
		if (focus == 0)
			focus = postEsteDeschis ? 1 : 3;
		else if (focus == 1 && postEsteDeschis)
			focus = focusBtnPost;
		else if (focus == 1 && !postEsteDeschis)
			focus = focusSortNou;
		else if (focus == 2 && postEsteDeschis)
			focus = focusSortNou;
		else if (focus == 2 && !postEsteDeschis)
			focus = focusSortNou;
		else if (focus == 3)
			focus = postEsteDeschis ? 1 : 3;
	} else if (focus == 3 && k == '\r') { /* Enter pe "Inapoi" */
		ecran = BlogWelcome;
		postVazutId = -1;
		curatBuffInputComm();
		focus = noFocus;
		cautareActiv = (lgCauta > 0);
	}
}

void tastatura(unsigned char k, int x, int y) {
	if (k == 27) {
		curataMesaje();
		if (ecran == VizualizarePostare) {
			ecran = BlogWelcome;
			postVazutId = -1;
			curatBuffInputComm();
			focus = noFocus;
			cautareActiv = (lgCauta > 0);
		} else if (ecran == BlogWelcome && focus != noFocus && focus != focusPostInput
				&& focus != focusCautare) {
			focus = noFocus;
		} else if (ecran == Logare || ecran == Inregistrare) {
			ecran = Welcome;
			curatBufferAuth();
			focus = noFocus;
		} else if (ecran == Welcome && userCurentId != -1) {
		} else if (ecran == BlogWelcome && userCurentId != -1
				&& (focus == 0 || focus == 1 || focus == 6)) {
			ecran = Welcome;
			userCurentId = -1;
			curatBufferAuth();
			curatBuffInputPost();
			lgCauta = 0;
			bufferCauta[0] = '\0';
			cautareActiv = 0;
			focus = noFocus;
			strcpy(mesajStatus, "Logout reusit.");
		}
	} else {
		switch (ecran) {
		case Welcome:
			tastaturaWelcome(k, x, y);
			break;
		case Inregistrare:
			tastaturaInregistrare(k, x, y);
			break;
		case Logare:
			tastaturaLogare(k, x, y);
			break;
		case BlogWelcome:
			tastaturaMain(k, x, y);
			break;
		case VizualizarePostare:
			tastaturaVizPost(k, x, y);
			break;
		}
	}
}

void mouseWelcome(int buton, int state, int mx, int my) {
	curataMesaje();
	int winW = glutGet(GLUT_WINDOW_WIDTH);
	int winH = glutGet(GLUT_WINDOW_HEIGHT);
	int fy = winH - my;
	int centruX = winW / 2;

	/* Replica logica dimensiunilor din DesenWelcome */
	int btnW_prop = winW * 0.3f;
	int btnW = (btnW_prop < 150) ? 150 : ((btnW_prop > 300) ? 300 : btnW_prop);
	int btnH_prop = winH * 0.06f;
	int btnH = (btnH_prop < 35) ? 35 : ((btnH_prop > 50) ? 50 : btnH_prop);
	int btnX = centruX - btnW / 2;
	int inregY_Top = winH * 0.6f;
	int logY_Top = inregY_Top - btnH - 20;

	if (mx >= btnX && mx <= btnX + btnW) {
		if (fy <= inregY_Top && fy >= inregY_Top - btnH) {
			ecran = Inregistrare;
			curatBufferAuth();
			focus = noFocus;
		} else if (fy <= logY_Top && fy >= logY_Top - btnH) {
			ecran = Logare;
			curatBufferAuth();
			focus = noFocus;
		}
	}
}

void mouseInreg(int buton, int state, int mx, int my) {
	curataMesaje();
	int winW = glutGet(GLUT_WINDOW_WIDTH);
	int winH = glutGet(GLUT_WINDOW_HEIGHT);
	int fy = winH - my;
	int centruX = winW / 2;

	/* Replica logica dimensiunilor din DesenInregistrare */
	int inputW_prop = winW * 0.5f;
	int inputW =
			(inputW_prop < 250) ?
					250 : ((inputW_prop > 500) ? 500 : inputW_prop);
	int inputH = 25;
	int inputX = centruX - inputW / 2;
	int userY_Top = winH * 0.7f;
	int passY_Top = userY_Top - inputH - 30;

	int trimiteW_prop = winW * 0.15f;
	int trimiteW =
			(trimiteW_prop < 80) ?
					80 : ((trimiteW_prop > 150) ? 150 : trimiteW_prop);
	int trimiteH = 30;
	int trimiteX = centruX - trimiteW / 2;
	int trimiteY_Top = passY_Top - inputH - 40;

	int inapoiW_prop = winW * 0.1f;
	int inapoiW =
			(inapoiW_prop < 70) ?
					70 : ((inapoiW_prop > 120) ? 120 : inapoiW_prop);
	int inapoiH_prop = BARA_SUS_H * 0.7f;
	int inapoiH = (inapoiH_prop < 20) ? 20 : inapoiH_prop;
	int inapoiX = 15;
	int inapoiY_Top = winH - BARA_SUS_H / 2 + inapoiH / 2;

	if (mx >= inputX && mx <= inputX + inputW && fy <= userY_Top
			&& fy >= userY_Top - inputH)
		focus = focusPostInput;
	else if (mx >= inputX && mx <= inputX + inputW && fy <= passY_Top
			&& fy >= passY_Top - inputH)
		focus = focusBtnPost;
	else if (mx >= trimiteX && mx <= trimiteX + trimiteW && fy <= trimiteY_Top
			&& fy >= trimiteY_Top - trimiteH) {
		focus = focusSortNou;
		tastaturaInregistrare('\r', mx, my);
	} else if (mx >= inapoiX && mx <= inapoiX + inapoiW && fy <= inapoiY_Top
			&& fy >= inapoiY_Top - inapoiH) {
		focus = focusSortVechi;
		tastaturaInregistrare('\r', mx, my);
	} else
		focus = noFocus;
}

void mouseLogare(int buton, int state, int mx, int my) {
	curataMesaje();
	int winW = glutGet(GLUT_WINDOW_WIDTH);
	int winH = glutGet(GLUT_WINDOW_HEIGHT);
	int fy = winH - my;
	int centruX = winW / 2;

	/* Replica logica dimensiunilor din DesenLogare */
	int inputW_prop = winW * 0.5f;
	int inputW =
			(inputW_prop < 250) ?
					250 : ((inputW_prop > 500) ? 500 : inputW_prop);
	int inputH = 25;
	int inputX = centruX - inputW / 2;
	int userY_Top = winH * 0.7f;
	int passY_Top = userY_Top - inputH - 30;

	int trimiteW_prop = winW * 0.15f;
	int trimiteW =
			(trimiteW_prop < 80) ?
					80 : ((trimiteW_prop > 150) ? 150 : trimiteW_prop);
	int trimiteH = 30;
	int trimiteX = centruX - trimiteW / 2;
	int trimiteY_Top = passY_Top - inputH - 30;

	int inapoiW_prop = winW * 0.1f;
	int inapoiW =
			(inapoiW_prop < 70) ?
					70 : ((inapoiW_prop > 120) ? 120 : inapoiW_prop);
	int inapoiH_prop = BARA_SUS_H * 0.7f;
	int inapoiH = (inapoiH_prop < 20) ? 20 : inapoiH_prop;
	int inapoiX = 15;
	int inapoiY_Top = winH - BARA_SUS_H / 2 + inapoiH / 2;

	if (mx >= inputX && mx <= inputX + inputW && fy <= userY_Top
			&& fy >= userY_Top - inputH)
		focus = focusPostInput;
	else if (mx >= inputX && mx <= inputX + inputW && fy <= passY_Top
			&& fy >= passY_Top - inputH)
		focus = focusBtnPost;
	else if (mx >= trimiteX && mx <= trimiteX + trimiteW && fy <= trimiteY_Top
			&& fy >= trimiteY_Top - trimiteH) {
		focus = focusSortNou;
		tastaturaLogare('\r', mx, my);
	} else if (mx >= inapoiX && mx <= inapoiX + inapoiW && fy <= inapoiY_Top
			&& fy >= inapoiY_Top - inapoiH) {
		focus = focusSortVechi;
		tastaturaLogare('\r', mx, my);
	} else
		focus = noFocus;
}

void mouseMain(int buton, int state, int mx, int my) {
	curataMesaje();
	int winW = glutGet(GLUT_WINDOW_WIDTH);
	int winH = glutGet(GLUT_WINDOW_HEIGHT);
	int fy = winH - my;

	int hElemBara_prop = BARA_SUS_H * 0.7f;
	int hElemBara =
			(hElemBara_prop < 20) ? 20 : hElemBara_prop;
	int yTopElemBara = winH - BARA_SUS_H / 2
			+ hElemBara / 2;
	int margineLaterala = 10;
	int spatiuElemBara = 15;

	int logoutW_prop = winW * 0.1f;
	int logoutW =
			(logoutW_prop < 70) ?
					70 : ((logoutW_prop > 100) ? 100 : logoutW_prop);
	int logoutX = winW - logoutW - margineLaterala;

	int sortW_prop = winW * 0.1f;
	int sortW =
			(sortW_prop < 70) ? 70 : ((sortW_prop > 110) ? 110 : sortW_prop);
	int sortVechiX = logoutX - spatiuElemBara - sortW;
	int sortNouX = sortVechiX - spatiuElemBara - sortW;

	int xStartCautare = 10 + calculWText("Forum", FONT_MARE)
			+ spatiuElemBara;
	int xEndCautare = sortNouX - spatiuElemBara;
	int wDispCautare = xEndCautare - xStartCautare;
	int clickCautare = 0;
	int inputCautaX_click = 0, wInputCalcul_click = 0;

	if (wDispCautare > 20) {
		int etichetaCautaW_temp = calculWText("Cauta:", FONT_BUTON);
		int spatiuTextInput_temp = 5;
		int wInputMinNecesar_temp = 50;

		if (wDispCautare
				< etichetaCautaW_temp + spatiuTextInput_temp
						+ wInputMinNecesar_temp) {
			inputCautaX_click = xStartCautare;
			wInputCalcul_click = wDispCautare
					- spatiuTextInput_temp;
			if (wInputCalcul_click < 0)
				wInputCalcul_click = 0;
		} else {
			inputCautaX_click = xStartCautare + etichetaCautaW_temp
					+ spatiuTextInput_temp;
			wInputCalcul_click = wDispCautare
					- etichetaCautaW_temp - spatiuTextInput_temp;
		}
		if (wInputCalcul_click < wInputMinNecesar_temp
				&& wDispCautare
						> wInputMinNecesar_temp
								+ spatiuTextInput_temp) {
			wInputCalcul_click = wInputMinNecesar_temp;
		}
		if (wInputCalcul_click > 0 && mx >= inputCautaX_click
				&& mx <= inputCautaX_click + wInputCalcul_click
				&& fy <= yTopElemBara
				&& fy >= yTopElemBara - hElemBara) {
			clickCautare = 1;
		}
	}

	/* Butpoane sageti */
	int sageataX = winW - SAGEATA_W - 5;
	int sageataUpY_Top = winH - BARA_SUS_H - SPATIU_INTRE_ELEMENTE
			- SAGEATA_H / 2;
	int sageataDownY_Calcul = H_ZONA_INPUT + SPATIU_INTRE_ELEMENTE
			+ SAGEATA_H + SAGEATA_H / 2;
	int sageataDownY_Top = sageataDownY_Calcul + SAGEATA_H;

	/* Zona input psotare */
	int inputMargine = 10;
	int postBtnW_prop = winW * 0.12f;
	int postBtnW =
			(postBtnW_prop < 80) ?
					80 : ((postBtnW_prop > 120) ? 120 : postBtnW_prop);
	int postBtnX = winW - postBtnW - inputMargine;
	int inputX_post = inputMargine;
	int inputW_post = postBtnX - inputMargine - inputX_post;
	if (inputW_post < 50)
		inputW_post = 50;
	int inputH_Box = H_ZONA_INPUT - 20;
	int elemYCasutaTop_Input = H_ZONA_INPUT
			- PAD_VERT_ELEMENT / 2;

	if (fy <= yTopElemBara
			&& fy >= yTopElemBara - hElemBara) {
		if (mx >= sortNouX && mx <= sortNouX + sortW) {
			focus = focusSortNou;
			ordineSort = 0;
			sortPost();
			primaPostVazutId = 0;
		} else if (mx >= sortVechiX && mx <= sortVechiX + sortW) {
			focus = focusSortVechi;
			ordineSort = 1;
			sortPost();
			primaPostVazutId = 0;
		} else if (mx >= logoutX && mx <= logoutX + logoutW) {
			focus = focusLogout;
			tastaturaMain('\r', mx, my);
		} else if (clickCautare) {
			focus = focusCautare;
		} else {
			focus = noFocus;
		}
		return;
	}

	if (mx >= sageataX && mx <= sageataX + SAGEATA_W) { /* Click saget scroll */
		if (fy <= sageataUpY_Top && fy >= sageataUpY_Top - SAGEATA_H) { /* Sageata sus */
			if (primaPostVazutId > 0)
				primaPostVazutId--;
			focus = noFocus;
		} else if (fy <= sageataDownY_Top && fy >= sageataDownY_Top - SAGEATA_H) { /* Sageata jos */
			int postFiltrateCtr = 0;
			for (int i = 0; i < ctrPost; ++i)
				if (!cautareActiv
						|| postSePotriveste(&Postari[i],
								bufferCauta))
					postFiltrateCtr++;

			int postPeEcran = 0;
			int tempY = winH - BARA_SUS_H - SPATIU_INTRE_ELEMENTE;
			for (int i = primaPostVazutId; i < ctrPost; ++i) {
				if (cautareActiv
						&& !postSePotriveste(&Postari[i],
								bufferCauta))
					continue;
				int hPost = 0; /* Recalculare rapida h */
				int casutaW_temp = winW - 20 - SAGEATA_W - 5;
				if (casutaW_temp < 100)
					casutaW_temp = 100;
				int btnDelW_temp_prop = casutaW_temp * 0.1f;
				int btnDelW_temp =
						(btnDelW_temp_prop < 50) ?
								50 :
								((btnDelW_temp_prop > 70) ?
										70 : btnDelW_temp_prop);
				int btnZonaW_temp =
						(Postari[i].autorIndex == userCurentId) ?
								(btnDelW_temp + 10) : 0;
				int textW_temp = casutaW_temp - btnZonaW_temp - 2 * MARGINE_TEXT;
				if (textW_temp < 50)
					textW_temp = 50;
				hPost = calculHNecElement(
						Postari[i].continutP, textW_temp, H_ANTET_POSTARE,
						H_SUBSOL_POSTARE, MIN_H_POSTARE);

				if (tempY - hPost < H_ZONA_INPUT)
					break;
				tempY -= (hPost + SPATIU_INTRE_ELEMENTE);
				postPeEcran++;
			}
			if (primaPostVazutId + postPeEcran < postFiltrateCtr) {
				primaPostVazutId++;
			}
			focus = noFocus;
		}
		return;
	}

	if (fy <= elemYCasutaTop_Input && fy >= elemYCasutaTop_Input - inputH_Box) { /* Click zona input */
		if (mx >= inputX_post && mx <= inputX_post + inputW_post) {
			focus = focusPostInput;
		} else if (mx >= postBtnX && mx <= postBtnX + postBtnW) {
			focus = focusBtnPost;
			tastaturaMain('\r', mx, my);
		} else {
			focus = noFocus;
		}
		return;
	}

	/* Click postari */
	if (fy > H_ZONA_INPUT && fy < winH - BARA_SUS_H) {
		focus = noFocus;
		int actualY_Top = winH - BARA_SUS_H - SPATIU_INTRE_ELEMENTE;
		int postProcesateScroll = 0;
		for (int i = 0; i < ctrPost; ++i) {
			if (cautareActiv
					&& !postSePotriveste(&Postari[i], bufferCauta)) {
				continue;
			}
			if (postProcesateScroll < primaPostVazutId) {
				postProcesateScroll++;
				continue;
			}

			int casutaX_postEl = 10;
			int casutaW_postEl = winW - 20 - SAGEATA_W - 5;
			if (casutaW_postEl < 100)
				casutaW_postEl = 100;
			int btnDelW_prop_postEl = casutaW_postEl * 0.1f;
			int btnDelW_postEl =
					(btnDelW_prop_postEl < 50) ?
							50 :
							((btnDelW_prop_postEl > 70) ?
									70 : btnDelW_prop_postEl);
			int btnDelH_postEl = 18;
			int esteAutorPostarii = (Postari[i].autorIndex
					== userCurentId);
			int btnZonaW_postEl = esteAutorPostarii ? (btnDelW_postEl + 10) : 0;
			int textW_postEl = casutaW_postEl - btnZonaW_postEl
					- 2 * MARGINE_TEXT;
			if (textW_postEl < 50)
				textW_postEl = 50;
			int inaltimePostareCurenta =
					calculHNecElement(Postari[i].continutP,
							textW_postEl, H_ANTET_POSTARE,
							H_SUBSOL_POSTARE, MIN_H_POSTARE);

			int postTopAbsY = actualY_Top;
			int postBottomAbsY = actualY_Top - inaltimePostareCurenta;

			if (fy <= postTopAbsY && fy >= postBottomAbsY) {
				if (mx >= casutaX_postEl
						&& mx <= casutaX_postEl + casutaW_postEl) {
					if (esteAutorPostarii) {
						int btnDelX_postEl = casutaX_postEl + casutaW_postEl
								- btnDelW_postEl - 5;
						int btnDelY_Top_postEl = postTopAbsY
								- PAD_VERT_ELEMENT;
						if (mx >= btnDelX_postEl
								&& mx <= btnDelX_postEl + btnDelW_postEl
								&& fy <= btnDelY_Top_postEl
								&& fy >= btnDelY_Top_postEl - btnDelH_postEl) {
							stergePost(Postari[i].id);
							return; /* Exit dupa stergere */
						}
					}
					postVazutId = i;
					ecran = VizualizarePostare;
					curatBuffInputComm();
					primComentVazutId = 0;
					focus = noFocus;
					return;
				}
			}
			actualY_Top -= (inaltimePostareCurenta + SPATIU_INTRE_ELEMENTE);
			postProcesateScroll++;
			if (actualY_Top - MIN_H_POSTARE < H_ZONA_INPUT)
				break;
		}
	}
}

void mouseVizPost(int buton, int state, int mx, int my) {
	curataMesaje();
	if (postVazutId < 0 || postVazutId >= ctrPost)
		return;
	int winW = glutGet(GLUT_WINDOW_WIDTH);
	int winH = glutGet(GLUT_WINDOW_HEIGHT);
	int fy = winH - my;
	Postare *post = &Postari[postVazutId];

	int postY_Top_vp = winH - 5;
	int casutaX_Post_vp = 5;

	int inapoiBtnW_prop_vp = winW * 0.08f;
	int inapoiBtnW_vp =
			(inapoiBtnW_prop_vp < 50) ?
					50 : ((inapoiBtnW_prop_vp > 80) ? 80 : inapoiBtnW_prop_vp);
	int inapoiBtnH_vp = 20;
	int inapoiX_vp = casutaX_Post_vp + MARGINE_TEXT;
	int inapoiY_Top_vp = postY_Top_vp - PAD_VERT_ELEMENT;

	int latimeTextPostare_vp = winW - 10 - (inapoiBtnW_vp + 10)
			- 2 * MARGINE_TEXT;
	if (latimeTextPostare_vp < 50)
		latimeTextPostare_vp = 50;
	int dimHeadPostVazuta_vp = (3 * PAD_VERT_ELEMENT)
			+ inapoiBtnH_vp + glutBitmapHeight(FONT_MIC);
	int hPostAfisata = calculHNecElement(
			post->continutP, latimeTextPostare_vp,
			dimHeadPostVazuta_vp,
			H_SUBSOL_POSTARE, MIN_H_POSTARE + 25);

	int inputMargineCom_vp = 10;
	int comBtnW_prop_vp = winW * 0.12f;
	int comBtnW_vp =
			(comBtnW_prop_vp < 80) ?
					80 : ((comBtnW_prop_vp > 120) ? 120 : comBtnW_prop_vp);
	int comBtnX_vp = winW - comBtnW_vp - inputMargineCom_vp;
	int inputX_Com_vp = inputMargineCom_vp;
	int inputW_Com_vp = comBtnX_vp - inputMargineCom_vp - inputX_Com_vp;
	if (inputW_Com_vp < 50)
		inputW_Com_vp = 50;
	int inputH_Box_Com_vp = H_ZONA_INPUT - 20;
	int elemYCasutaTop_Com_vp = H_ZONA_INPUT
			- PAD_VERT_ELEMENT / 2;

	/* Sageti scroll comentarii */
	int comentStartY_Top_vp = postY_Top_vp - hPostAfisata
			- SPATIU_INTRE_ELEMENTE;
	int sageataX_Com_vp = winW - SAGEATA_W - 5;
	int sageataUpY_Top_Com_vp = comentStartY_Top_vp - SAGEATA_H / 2;
	int sageataDownY_Calcul_Com_vp = H_ZONA_INPUT + SPATIU_INTRE_ELEMENTE
			+ SAGEATA_H + SAGEATA_H / 2;
	int sageataDownY_Top_Com_vp = sageataDownY_Calcul_Com_vp + SAGEATA_H;

	if (mx >= inapoiX_vp && mx <= inapoiX_vp + inapoiBtnW_vp
			&& fy <= inapoiY_Top_vp && fy >= inapoiY_Top_vp - inapoiBtnH_vp) {
		ecran = BlogWelcome;
		postVazutId = -1;
		curatBuffInputComm();
		focus = noFocus;
		cautareActiv = (lgCauta > 0);
		return;
	}

	if (mx >= sageataX_Com_vp && mx <= sageataX_Com_vp + SAGEATA_W) {
		if (fy
				<= sageataUpY_Top_Com_vp&& fy >= sageataUpY_Top_Com_vp - SAGEATA_H) {
			if (primComentVazutId > 0)
				primComentVazutId--;
			focus = noFocus;
		} else if (fy
				<= sageataDownY_Top_Com_vp&& fy >= sageataDownY_Top_Com_vp - SAGEATA_H) {
			int comentariiPeEcran = 0;
			int tempY = comentStartY_Top_vp;
			for (int i = primComentVazutId; i < post->ctrComent;
					++i) {
				int hCom = 0;
				int casutaW_temp_com = winW - 40 - SAGEATA_W - 5;
				if (casutaW_temp_com < 80)
					casutaW_temp_com = 80;
				int btnRspW_prop_temp = casutaW_temp_com * 0.1f;
				int btnRspW_temp =
						(btnRspW_prop_temp < 50) ?
								50 :
								((btnRspW_prop_temp > 70) ?
										70 : btnRspW_prop_temp);
				int esteAutorulPost_temp = (userCurentId != -1
						&& post->autorIndex == userCurentId);
				int btnZonaW_temp_com =
						(esteAutorulPost_temp && !post->inchisaP) ?
								(btnRspW_temp + 10) : 0;
				int textW_temp_com = casutaW_temp_com - btnZonaW_temp_com
						- 2 * MARGINE_TEXT;
				if (textW_temp_com < 50)
					textW_temp_com = 50;
				hCom = calculHNecElement(
						post->Comentarii[i].Continut, textW_temp_com,
						H_ANTET_COMENTARIU, PAD_VERT_ELEMENT,
						MIN_H_COMENTARIU);

				if (tempY - hCom < H_ZONA_INPUT)
					break;
				tempY -= (hCom + SPATIU_INTRE_ELEMENTE);
				comentariiPeEcran++;
			}
			if (primComentVazutId + comentariiPeEcran
					< post->ctrComent) {
				primComentVazutId++;
			}
			focus = noFocus;
		}
		return;
	}

	if (fy <= elemYCasutaTop_Com_vp
			&& fy >= elemYCasutaTop_Com_vp - inputH_Box_Com_vp) {
		if (!post->inchisaP) {
			if (mx >= inputX_Com_vp && mx <= inputX_Com_vp + inputW_Com_vp) {
				focus = focusPostInput;
			} else if (mx >= comBtnX_vp && mx <= comBtnX_vp + comBtnW_vp) {
				focus = focusBtnPost;
				tastaturaVizPost('\r', mx, my);
			} else {
				focus = noFocus;
			}
		} else {
			focus = noFocus;
		}
		return;
	}

	if (fy > H_ZONA_INPUT && fy < comentStartY_Top_vp) {
		focus = noFocus;
		int comActualY_Top = comentStartY_Top_vp;
		int comentProcPtScroll = 0;
		for (int i = 0; i < post->ctrComent; ++i) {
			if (comentProcPtScroll < primComentVazutId) {
				comentProcPtScroll++;
				continue;
			}
			Comentariu *c_ptr = &post->Comentarii[i];
			int casutaX_comEl = 20;
			int casutaW_comEl = winW - 40 - SAGEATA_W - 5;
			if (casutaW_comEl < 80)
				casutaW_comEl = 80;
			int esteAutorulPostarii = (userCurentId != -1
					&& post->autorIndex == userCurentId);
			int btnRspW_prop_comEl = casutaW_comEl * 0.1f;
			int btnRspW_comEl =
					(btnRspW_prop_comEl < 50) ?
							50 :
							((btnRspW_prop_comEl > 70) ? 70 : btnRspW_prop_comEl);
			int btnRspH_comEl = 18;
			int btnZonaW_comEl =
					(esteAutorulPostarii && !post->inchisaP) ?
							(btnRspW_comEl + 10) : 0;
			int textW_comEl = casutaW_comEl - btnZonaW_comEl - 2 * MARGINE_TEXT;
			if (textW_comEl < 50)
				textW_comEl = 50;
			int hComCurenta = calculHNecElement(
					c_ptr->Continut, textW_comEl, H_ANTET_COMENTARIU,
					PAD_VERT_ELEMENT, MIN_H_COMENTARIU);

			int comTopAbsY = comActualY_Top;
			int comBottomAbsY = comActualY_Top - hComCurenta;

			if (fy <= comTopAbsY && fy >= comBottomAbsY) {
				if (mx >= casutaX_comEl
						&& mx <= casutaX_comEl + casutaW_comEl) {
					if (esteAutorulPostarii && !post->inchisaP) {
						int btnRspX_comEl = casutaX_comEl + casutaW_comEl
								- btnRspW_comEl - 5;
						int btnRspY_Top_comEl = comTopAbsY
								- PAD_VERT_ELEMENT;
						if (mx >= btnRspX_comEl
								&& mx <= btnRspX_comEl + btnRspW_comEl
								&& fy <= btnRspY_Top_comEl
								&& fy >= btnRspY_Top_comEl - btnRspH_comEl) {
							marcheazaRaspuns(postVazutId,
									c_ptr->id);
							return;
						}
					}
					return;
				}
			}
			comActualY_Top -= (hComCurenta + SPATIU_INTRE_ELEMENTE);
			comentProcPtScroll++;
			if (comActualY_Top - MIN_H_COMENTARIU < H_ZONA_INPUT)
				break;
		}
	}
}

void mouse(int buton, int state, int mx, int my) {
	switch (ecran) {
	case Welcome:
		mouseWelcome(buton, state, mx, my);
		break;
	case Inregistrare:
		mouseInreg(buton, state, mx, my);
		break;
	case Logare:
		mouseLogare(buton, state, mx, my);
		break;
	case BlogWelcome:
		mouseMain(buton, state, mx, my);
		break;
	case VizualizarePostare:
		mouseVizPost(buton, state, mx, my);
		break;
	}
}
