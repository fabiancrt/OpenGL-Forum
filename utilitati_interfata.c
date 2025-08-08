#include "utilitati_interfata.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void desenCasuta(int x, int y, int w, int h) {
	glBegin(GL_LINE_LOOP);
	glVertex2i(x, y);
	glVertex2i(x + w, y);
	glVertex2i(x + w, y - h);
	glVertex2i(x, y - h);
	glEnd();
}

void desenText(int x, int y, const char *str, void *font) {
	if (!font)
		font = FONT_NORMAL;
	glRasterPos2i(x, y);
	for (; *str; str++) {
		glutBitmapCharacter(font, *str);
	}
}

int calculWText(const char *str, void *font) {
	if (!font)
		font = FONT_NORMAL;
	int w = 0;
	for (; *str; str++) {
		w += glutBitmapWidth(font, *str);
	}
	return w;
}

void desenFocus(int x, int y, int w, int h) {
	glLineWidth(2);
	glColor3f(CULOARE_ACCENT_R, CULOARE_ACCENT_G, CULOARE_ACCENT_B);
	desenCasuta(x - 2, y + 2, w + 4, h + 4);
	glLineWidth(1);
}

void desenSageata(int x, int y, int w, int h, int directie) {
	glColor3f(CULOARE_INPUT_R, CULOARE_INPUT_G, CULOARE_INPUT_B);
	glBegin(GL_QUADS);
	glVertex2i(x, y);
	glVertex2i(x + w, y);
	glVertex2i(x + w, y - h);
	glVertex2i(x, y - h);
	glEnd();

	glColor3f(CULOARE_ACCENT_R, CULOARE_ACCENT_G, CULOARE_ACCENT_B);
	desenCasuta(x, y, w, h);

	glColor3f(CULOARE_TEXT_R, CULOARE_TEXT_G, CULOARE_TEXT_B);
	glLineWidth(2);
	glBegin(GL_LINES);
	if (directie == 1) {
		glVertex2i(x + w / 2, y - h / 4);
		glVertex2i(x + w / 4, y - h / 2);
		glVertex2i(x + w / 2, y - h / 4);
		glVertex2i(x + 3 * w / 4, y - h / 2);
	} else {
		glVertex2i(x + w / 2, y - 3 * h / 4);
		glVertex2i(x + w / 4, y - h / 2);
		glVertex2i(x + w / 2, y - 3 * h / 4);
		glVertex2i(x + 3 * w / 4, y - h / 2);
	}
	glEnd();
	glLineWidth(1);
}

void desenInputText(int x, int y, int w, int h, const char *buffer, int lg,
		int maxLg, int focusId, int focusActual, int esteParola,
		const char *substituent) {
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glVertex2i(x, y);
	glVertex2i(x + w, y);
	glVertex2i(x + w, y - h);
	glVertex2i(x, y - h);
	glEnd();

	glColor3f(CULOARE_ACCENT_R, CULOARE_ACCENT_G, CULOARE_ACCENT_B);
	desenCasuta(x, y, w, h);

	glColor3f(CULOARE_TEXT_R, CULOARE_TEXT_G, CULOARE_TEXT_B);
	int textY = y - h / 2 - glutBitmapHeight(FONT_NORMAL) / 2;

	if (lg == 0 && substituent && substituent[0] != '\0'
			&& focusActual != focusId) {
		glColor3f(0.6f, 0.6f, 0.6f); /*Culoarea substituent */
		desenText(x + MARGINE_TEXT, textY, substituent, FONT_NORMAL);
		glColor3f(CULOARE_TEXT_R, CULOARE_TEXT_G, CULOARE_TEXT_B); /* Reset culoare */
	} else if (esteParola) { /* Parola este inlocuita cu un sir de ' * ' */
		char cenzura[MAX_IN_USER] = { 0 };
		int lgAfisaj = (lg >= MAX_IN_USER) ? MAX_IN_USER - 1 : lg;
		memset(cenzura, '*', lgAfisaj);
		cenzura[lgAfisaj] = '\0';
		desenText(x + MARGINE_TEXT, textY, cenzura, FONT_NORMAL);
	} else { /* Username */
		desenText(x + MARGINE_TEXT, textY, buffer, FONT_NORMAL);
	}

	if (focusActual == focusId) {
		desenFocus(x, y, w, h);
	}
}

void desenButon(int x, int y, int w, int h, const char *eticheta, int focusId,
		int focusActual, int dezactivat) {
	if (dezactivat) {
		glColor3f(CULOARE_INCHIS_R, CULOARE_INCHIS_G, CULOARE_INCHIS_B); /* Pentru buton dez. */
	} else {
		glColor3f(CULOARE_INPUT_R, CULOARE_INPUT_G, CULOARE_INPUT_B); /* Buton Normal */
	}
	glBegin(GL_QUADS);
	glVertex2i(x, y);
	glVertex2i(x + w, y);
	glVertex2i(x + w, y - h);
	glVertex2i(x, y - h);
	glEnd();

	if (dezactivat) {
		glColor3f(0.6f, 0.6f, 0.6f); /* Chenar dezactivat */
	} else {
		glColor3f(CULOARE_ACCENT_R, CULOARE_ACCENT_G, CULOARE_ACCENT_B); /* Chenar normal */
	}
	desenCasuta(x, y, w, h);

	if (dezactivat) {
		glColor3f(0.5f, 0.5f, 0.5f); /* Text dezactivat */
	} else {
		glColor3f(CULOARE_TEXT_R, CULOARE_TEXT_G, CULOARE_TEXT_B); /* Text normal */
	}
	int etichetaW = calculWText(eticheta, FONT_BUTON);
	int textY = y - h / 2 - glutBitmapHeight(FONT_BUTON) / 2;
	desenText(x + (w - etichetaW) / 2, textY, eticheta, FONT_BUTON);

	if (focusActual == focusId && !dezactivat) {
		desenFocus(x, y, w, h);
	}
	glColor3f(CULOARE_TEXT_R, CULOARE_TEXT_G, CULOARE_TEXT_B); /* Reseteaza culoarea textului */
}

int calculHText(const char *text, int maxW, void *fontOriginal) {
	if (!text || text[0] == '\0' || maxW <= 0)
		return 0;

	fontOriginal = fontOriginal ? fontOriginal : FONT_NORMAL; /* Resetare la default */
	int hLinieNormala = glutBitmapHeight(fontOriginal);
	if (hLinieNormala <= 0)
		hLinieNormala = 13; /* Standard */
	int hLinieCod = glutBitmapHeight(FONT_COD);
	if (hLinieCod <= 0)
		hLinieCod = 15; /* Standard */

	int totalH = 0;
	char *copieText = strdup(text); /* Duplicare pentru modificari */
	if (!copieText)
		return hLinieNormala; /* In cazul unei erori */

	char *p = copieText;
	int blockCodIn = 0;
	void *fontActual = fontOriginal;
	int linieCrtHCaract = hLinieNormala;
	int spatiereLinii = 2;
	int liniiAfisateCtr = 0;

	while (*p) {
		if (strncmp(p, "```", 3) == 0) { /* 3x '`' Activeaza scriere cod */
			blockCodIn = !blockCodIn;
			p += 3;
			linieCrtHCaract =
					blockCodIn ? hLinieCod : hLinieNormala;

			if (liniiAfisateCtr > 0) { /*Spatiere intre linii*/
				totalH += spatiereLinii;
			}
			totalH += linieCrtHCaract;
			liniiAfisateCtr++;
			continue; /*Urmatorul segment*/
		}

		fontActual = blockCodIn ? FONT_COD : fontOriginal;
		linieCrtHCaract =
				blockCodIn ? hLinieCod : hLinieNormala;
		int linieActualaLimitaW =
				blockCodIn ? (maxW - INDENTARE_COD_STANGA) : maxW;
		if (linieActualaLimitaW <= 0)
			linieActualaLimitaW = 1;

		char *segmentLinieStart = p;
		char *segmentLinieFinal = p;
		int latimeAcumulata = 0;
		char *ultimaSpatiereSegment = NULL;

		/*Se cauta finalul segmentului de linie */
		while (*segmentLinieFinal && *segmentLinieFinal != '\n'
				&& strncmp(segmentLinieFinal, "```", 3) != 0) {
			int charW = glutBitmapWidth(fontActual, *segmentLinieFinal);
			if (latimeAcumulata + charW > linieActualaLimitaW
					&& segmentLinieFinal > segmentLinieStart) {
				break;
			}
			latimeAcumulata += charW;
			if (!blockCodIn && *segmentLinieFinal == ' ') { /*Cauta ultimul space pentru incadrare */
				ultimaSpatiereSegment = segmentLinieFinal;
			}
			segmentLinieFinal++;
		}

		if (liniiAfisateCtr > 0) {
			totalH += spatiereLinii;
		}
		totalH += linieCrtHCaract;
		liniiAfisateCtr++;

		/* Mutam pointerul la inceputul urmatorului segment */
		char *p_Original_Siguranta = p; /* Pentru evitarea posibil loop infinit */
		if (*segmentLinieFinal == '\n') {
			p = segmentLinieFinal + 1;
		} else if (strncmp(segmentLinieFinal, "```", 3) == 0) {
			p = segmentLinieFinal;
		} else if (*segmentLinieFinal == '\0') {
			p = segmentLinieFinal; /*Final Text*/
		} else { /*Linie incadrata */
			if (!blockCodIn && ultimaSpatiereSegment
					&& ultimaSpatiereSegment > segmentLinieStart) {
				p = ultimaSpatiereSegment + 1; /*Se incadreaza la ultimul spatiu */
			} else {
				p = segmentLinieFinal; /* Aici se forteaza incadrarea */
			}
		}
		if (p == p_Original_Siguranta && *p != '\0') { /* Break in caz ca pointerul nu avanseaza */
			if (*p != '\n' && strncmp(p, "```", 3) != 0) {
				p++;
			} /* Se incearca avansarea cu un caracter */
			else if (*p == '\n') {
				p++;
			} /* In cazul blocarii pe newline */
		}
	}
	free(copieText);
	return totalH > 0 ?
			totalH :
			(strlen(text) > 0 ?
					(fontOriginal == FONT_COD ?
							hLinieCod : hLinieNormala) :
					0);
}

void desenIncadText(int x, int y_sus, int maxW, const char *text,
		void *fontOriginal) {
	if (!text || text[0] == '\0' || maxW <= 0)
		return;

	fontOriginal = fontOriginal ? fontOriginal : FONT_NORMAL;
	int hCaractNormal = glutBitmapHeight(fontOriginal);
	if (hCaractNormal <= 0)
		hCaractNormal = 13;
	int hCaractCod = glutBitmapHeight(FONT_COD);
	if (hCaractCod <= 0)
		hCaractCod = 15;

	GLfloat culoareTextInit[4];
	glGetFloatv(GL_CURRENT_COLOR, culoareTextInit); /* Salvez culoarea initiala text */

	char *copieText = strdup(text);
	if (!copieText) {
		desenText(x, y_sus - hCaractNormal,
				"[Eroare Alocare Incadrare]", fontOriginal);
		return;
	}

	char *p = copieText;
	int blockCodIn = 0;
	void *fontActual = fontOriginal;
	int hFontLinieCrt = hCaractNormal;
	int fontActualDescend = 0; /*pentru caracterele g, p, j, etc. */
	int spatiereLinii = 2;

	int baza_Y_Pentru_Linie = y_sus;
	int existaLinieDesen = 0;

	while (*p) {
		if (strncmp(p, "```", 3) == 0) {
			blockCodIn = !blockCodIn;
			p += 3; /* Consuma cele 3 '`' */

			fontActual = blockCodIn ? FONT_COD : fontOriginal;
			hFontLinieCrt =
					blockCodIn ? hCaractCod : hCaractNormal;
			fontActualDescend = blockCodIn ? FONT_COD_DESCENDENT_APROX : 0;

			if (existaLinieDesen) {/* Se adauga spatiu daca nu este prima linie*/
				baza_Y_Pentru_Linie -= spatiereLinii;
			}
			baza_Y_Pentru_Linie -= hFontLinieCrt;
			existaLinieDesen = 1;

			if (!blockCodIn) { /* Se restaureaza culoarea initiala */
				glColor3fv(culoareTextInit);
			}
			continue;
		}

		fontActual = blockCodIn ? FONT_COD : fontOriginal;
		hFontLinieCrt =
				blockCodIn ? hCaractCod : hCaractNormal;
		fontActualDescend = blockCodIn ? FONT_COD_DESCENDENT_APROX : 0;
		int pozDesenX = blockCodIn ? (x + INDENTARE_COD_STANGA) : x;
		int linieActualaLimitaW =
				blockCodIn ? (maxW - INDENTARE_COD_STANGA) : maxW;
		if (linieActualaLimitaW <= 0)
			linieActualaLimitaW = 1;

		char *segmentLinieStart = p;
		char *segmentLinieFinal = p;
		int latimeAcumulata = 0;
		char *ultimaSpatiereSegment = NULL;
		/* Se calculeaza latimea unui segment de linie */
		while (*segmentLinieFinal && *segmentLinieFinal != '\n'
				&& strncmp(segmentLinieFinal, "```", 3) != 0) {
			int charW = glutBitmapWidth(fontActual, *segmentLinieFinal);
			if (latimeAcumulata + charW > linieActualaLimitaW
					&& segmentLinieFinal > segmentLinieStart)
				break; /* Break daca limita este depasita */
			latimeAcumulata += charW;
			if (!blockCodIn && *segmentLinieFinal == ' ')
				ultimaSpatiereSegment = segmentLinieFinal;
			segmentLinieFinal++;
		}

		if (existaLinieDesen) {
			baza_Y_Pentru_Linie -= spatiereLinii;
		}
		baza_Y_Pentru_Linie -= hFontLinieCrt;
		existaLinieDesen = 1;

		char *finalSegmDesenat = segmentLinieFinal;
		char charLaSeparare = *finalSegmDesenat;
		char *p_Original_Siguranta = p;

		if (*segmentLinieFinal && *segmentLinieFinal != '\n'
				&& strncmp(segmentLinieFinal, "```", 3) != 0) { /*Incadrarea liniei */
			if (!blockCodIn && ultimaSpatiereSegment
					&& ultimaSpatiereSegment > segmentLinieStart) {
				finalSegmDesenat = ultimaSpatiereSegment;
				p = ultimaSpatiereSegment + 1; /*Segmentul urmator incepe dupa spatiu */
			} else {
				p = segmentLinieFinal;
			}
		} else if (*segmentLinieFinal == '\n') {
			p = segmentLinieFinal + 1; /*Segmentul incepe dupa newline */
		} else if (strncmp(segmentLinieFinal, "```", 3) == 0) {
			p = segmentLinieFinal; /* Caz '`' */
		} else { /*Final text */
			p = segmentLinieFinal;
		}
		*finalSegmDesenat = '\0'; /* Null temporar */

		/* Fundalul pentru textul ce reprezinta cod */
		if (blockCodIn && strlen(segmentLinieStart) > 0) { /* Se desenaeza doar daca avem text */
			glColor3f(CULOARE_COD_FUNDAL_R, CULOARE_COD_FUNDAL_G,
			CULOARE_COD_FUNDAL_B);
			int latimeTextLinieActuala = calculWText(segmentLinieStart,
					fontActual);
			int coordonateBottomY = baza_Y_Pentru_Linie - fontActualDescend;
			int coordonateTopY = baza_Y_Pentru_Linie + hFontLinieCrt
					- fontActualDescend;

			glBegin(GL_QUADS);
			glVertex2i(pozDesenX - PADDING_COD_VERTICAL, coordonateTopY);
			glVertex2i(
					pozDesenX + latimeTextLinieActuala + PADDING_COD_VERTICAL,
					coordonateTopY);
			glVertex2i(
					pozDesenX + latimeTextLinieActuala + PADDING_COD_VERTICAL,
					coordonateBottomY);
			glVertex2i(pozDesenX - PADDING_COD_VERTICAL, coordonateBottomY);
			glEnd();
			glColor3f(CULOARE_COD_TEXT_ALBASTRU_R, CULOARE_COD_TEXT_ALBASTRU_G,
			CULOARE_COD_TEXT_ALBASTRU_B);
		} else if (!blockCodIn) {
			glColor3fv(culoareTextInit); /* Restaurarea culorii initiale daca nu stuntem in cod */
		} else { /* Pentru liniile goale */
			glColor3f(CULOARE_COD_TEXT_ALBASTRU_R, CULOARE_COD_TEXT_ALBASTRU_G,
			CULOARE_COD_TEXT_ALBASTRU_B);
		}

		desenText(pozDesenX, baza_Y_Pentru_Linie, segmentLinieStart,
				fontActual);

		*finalSegmDesenat = charLaSeparare; /* Restauram char initial */

		if (p == p_Original_Siguranta && *p != '\0') {/* Pentru siguranta*/
			if (*p != '\n' && strncmp(p, "```", 3) != 0) {
				p++;
			} else if (*p == '\n') {
				p++;
			}
		}
	}
	free(copieText);
	glColor3fv(culoareTextInit); /* Resetarea culorii */
}

void desenTextMultiLineInput(int x_casuta, int y_sus_casuta,
		int latime_casuta, int inaltime_casuta, const char *textComplet,
		int lungimeTextComplet, int primCursorAfisat, void *fontNormal,
		void *fontCod, int esteFocus) {
	int hCaract = glutBitmapHeight(fontNormal);
	if (hCaract <= 0)
		hCaract = 13;
	/*Ajustare pentru incadrarea liniilor text in casuta input */
	int ajustVert = hCaract / 2;

	/* Calculare baseline pt prima linie vizibila + ajustare */
	int yBasePrimaLinieViz = y_sus_casuta
			- PAD_INTERN_INPUT - hCaract + ajustVert;

	if (lungimeTextComplet == 0 && !esteFocus) {
		glColor3f(0.6f, 0.6f, 0.6f); /* Culoare substituent */
		char placeholder[50] = "Scrie aici...";
		desenText(x_casuta + PAD_INTERN_INPUT,
				yBasePrimaLinieViz, placeholder, fontNormal);
		glColor3f(CULOARE_TEXT_R, CULOARE_TEXT_G, CULOARE_TEXT_B); /* Reset culoare */
		return;
	}

	const char *cursorBuffer = textComplet;
	int cursorCtrIdx = 0;
	int liniiAfisatePeEcran = 0; /* Maximul de linii vizibile in input este 2 */

	while (cursorBuffer < textComplet + lungimeTextComplet
			&& liniiAfisatePeEcran < 2) {
		const char *inceputCursorCtr = cursorBuffer;
		const char *sfarsitCursorCrt = strchr(cursorBuffer, '\n');
		int lungimeCursorCtr;

		if (sfarsitCursorCrt) {
			lungimeCursorCtr = sfarsitCursorCrt
					- inceputCursorCtr;
			cursorBuffer = sfarsitCursorCrt + 1; /* Trece peste \n */
		} else {
			lungimeCursorCtr = (textComplet + lungimeTextComplet)
					- inceputCursorCtr;
			cursorBuffer = textComplet + lungimeTextComplet; /* Final buffer */
		}

		if (cursorCtrIdx >= primCursorAfisat) {
			char linieDeAfisat[MAX_CHAR_PE_LINIE_INPUT + 4 + 1]; /* +4 pentru "```" si +1 pentru \0 */
			int lungimeDeCopiat = lungimeCursorCtr;
			if (lungimeDeCopiat > MAX_CHAR_PE_LINIE_INPUT + 4) {
				lungimeDeCopiat = MAX_CHAR_PE_LINIE_INPUT + 4;
			}
			strncpy(linieDeAfisat, inceputCursorCtr, lungimeDeCopiat);
			linieDeAfisat[lungimeDeCopiat] = '\0';

			int yBaseLinieEcran;
			if (liniiAfisatePeEcran == 0) {
				yBaseLinieEcran = yBasePrimaLinieViz;
			} else { /* A doua linie vizibila */
				yBaseLinieEcran = yBasePrimaLinieViz
						- hCaract - SPATIU_LINII_VIZ_INPUT;
			}

			/* Se proceseaza prezenta ``` din casuta de input */
			char *segmentCurent = linieDeAfisat;
			int x_offset_desenare = 0;
			int inBlocCodLocal = 0;

			while (*segmentCurent) {
				if (strncmp(segmentCurent, "```", 3) == 0) {
					inBlocCodLocal = !inBlocCodLocal;
					segmentCurent += 3; /* Consuma ``` */
					if (*segmentCurent == '\0')
						continue; /* ``` la finalul liniei */
				}

				void *fontActivPtSegment =
						inBlocCodLocal ? fontCod : fontNormal;
				char *sfarsitSegmentCurent = segmentCurent;
				while (*sfarsitSegmentCurent
						&& strncmp(sfarsitSegmentCurent, "```", 3) != 0) {
					sfarsitSegmentCurent++;
				}
				char caracterTemporar = *sfarsitSegmentCurent;
				*sfarsitSegmentCurent = '\0';

				if (inBlocCodLocal) {
					glColor3f(CULOARE_COD_TEXT_ALBASTRU_R,
					CULOARE_COD_TEXT_ALBASTRU_G,
					CULOARE_COD_TEXT_ALBASTRU_B);
				} else {
					glColor3f(CULOARE_TEXT_R, CULOARE_TEXT_G, CULOARE_TEXT_B);
				}
				desenText(
						x_casuta + PAD_INTERN_INPUT + x_offset_desenare,
						yBaseLinieEcran, segmentCurent,
						fontActivPtSegment);
				x_offset_desenare += calculWText(segmentCurent,
						fontActivPtSegment);

				*sfarsitSegmentCurent = caracterTemporar; /* Restaurare la char */
				segmentCurent = sfarsitSegmentCurent; /* Mutare la segmentul urmator */
			}
			liniiAfisatePeEcran++;
		}
		cursorCtrIdx++;
	}
}

int calculHNecElement(const char *continut,
		int wTextDisp, int hAntet, int hSubsol,
		int hMinimaElement) {
	int hContinutText = 0;
	if (continut && continut[0] != '\0') {
		hContinutText = calculHText(continut,
				wTextDisp,
				FONT_NORMAL);
	}

	int hTotalCalcul = hAntet; /* Padding top pentru antet */
	if (hContinutText > 0) {
		hTotalCalcul += hContinutText;
	}
	hTotalCalcul += hSubsol; /* Padding bottom pentru subsol */

	return (hTotalCalcul > hMinimaElement) ?
			hTotalCalcul : hMinimaElement;
}

int calcNrLiniiBuffer(const char *buffer, int lungime) {
	if (lungime == 0)
		return 1;
	int linii = 1;
	for (int i = 0; i < lungime; ++i) {
		if (buffer[i] == '\n') {
			linii++;
		}
	}
	return linii;
}

const char* gasesteLinieStart(const char *buffer, int lungimeBuffer,
		int indexLinieDorita) {
	if (indexLinieDorita == 0)
		return buffer;
	const char *p = buffer;
	int linieCurenta = 0;
	while (p < buffer + lungimeBuffer) { /* Verifica p in raport cu finalul bufferului */
		if (linieCurenta == indexLinieDorita)
			return p;
		if (*p == '\n') {
			linieCurenta++;
		}
		p++;
		if (p == buffer + lungimeBuffer && linieCurenta == indexLinieDorita)
			return p; /* Ultima linie goala dupa \n */
	}
	/* In afara limitelor: */
	if (indexLinieDorita > linieCurenta)
		return NULL;
	return NULL;
}

int obtCursorCurent(const char *buffer, int lungimeBuffer,
		int linieCurenta) {
	const char *linieStart = buffer;
	int liniiParcurse = 0;
	int i = 0;

	/* Cauta startul liniei */
	for (i = 0; i < lungimeBuffer && liniiParcurse < linieCurenta; ++i) {
		if (buffer[i] == '\n') {
			liniiParcurse++;
			if (liniiParcurse == linieCurenta) { /* S-a gasit newline */
				linieStart = &buffer[i + 1]; /*Linia  incepe dupa acest newline */
				break;
			}
		}
	}

	if (liniiParcurse < linieCurenta && linieCurenta > 0)
		return 0; /* Linia nu exista */

	int lungimePeLinie = 0;
	const char *p = linieStart;
	/* Itereaza de la linia de start pana la final buffer */
	while (p < buffer + lungimeBuffer && *p != '\n') {
		lungimePeLinie++;
		p++;
	}
	return lungimePeLinie;
}
