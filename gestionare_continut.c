#include "gestionare_continut.h"
#include "prelucrare_useri.h"
#include "definitii.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

Postare Postari[MAX_POSTARI];
int ctrPost = 0;
int urmPostId = 0;

int calcNrLiniiBufferGC(const char *buffer, int lungime) {
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

static int comparPostNouVechi(const void *a, const void *b) {
	Postare *pA = (Postare*) a;
	Postare *pB = (Postare*) b;
	if (pA->timestamp < pB->timestamp)
		return 1;
	if (pA->timestamp > pB->timestamp)
		return -1;
	return 0;
}

static int comparPostVechiNou(const void *a, const void *b) {
	Postare *pA = (Postare*) a;
	Postare *pB = (Postare*) b;
	if (pA->timestamp > pB->timestamp)
		return 1;
	if (pA->timestamp < pB->timestamp)
		return -1;
	return 0;
}
/* Insertion sort modificat */
void shellSort(void *start, size_t nrelem, size_t dimensiune,
                 int (*cmp)(const void*, const void*))
{
    char *vec = (char*)start;
    for (size_t dist = nrelem/2; dist > 0; dist /= 2) {
        for (size_t i = dist; i < nrelem; i++) {
            char *temp = malloc(dimensiune);
            memcpy(temp, vec + i*dimensiune, dimensiune);

            size_t j = i;
            while (j >= dist
                   && cmp(vec + (j - dist)*dimensiune, temp) > 0)
            {
                memcpy(vec + j*dimensiune,
                       vec + (j - dist)*dimensiune,
					   dimensiune);
                j -= dist;
            }
            memcpy(vec + j*dimensiune, temp, dimensiune);
            free(temp);
        }
    }
}
void sortPost(void) {
	if (ctrPost > 1) {
		shellSort(Postari, ctrPost, sizeof(Postare),
				(ordineSort == 0) ?
						comparPostNouVechi :
						comparPostVechiNou);
	}
	/*0 NOU -> VECHI ; 1 VECHI -> NOU */
}
int postSePotriveste(const Postare *p, const char *termen) {
	if (!termen || termen[0] == '\0')
		return 1;
	char termenCautLocal[MAX_CAUTA];
	strncpy(termenCautLocal, termen, MAX_CAUTA - 1);
	termenCautLocal[MAX_CAUTA - 1] = '\0';
	curataSpatiu(termenCautLocal);
	if (termenCautLocal[0] == '\0')
		return 1;

	const char *continut = p->continutP;
	int lenTermen = strlen(termenCautLocal);
	int lenContinut = strlen(continut);

	if (lenTermen == 0)
		return 1;
	if (lenTermen > lenContinut)
		return 0;

	for (int i = 0; i <= lenContinut - lenTermen; ++i) {
		int ok = 1;
		for (int j = 0; j < lenTermen; ++j) {
			if (tolower((char) continut[i + j])
					!= tolower((char) termenCautLocal[j])) {
				ok = 0;
				break;
			}
		}
		if (ok)
			return 1;
	}
	return 0;
}

void incarcaPost(void) {
	FILE *f = fopen("posts.dat", "r");
	ctrPost = 0;
	urmPostId = 0;
	if (!f)
		return;

	size_t freadId = fread(&urmPostId, sizeof(int), 1, f);
	size_t freadCtr = fread(&ctrPost, sizeof(int), 1, f);

	if (freadId
			< 1|| freadCtr < 1 || ctrPost < 0 || ctrPost > MAX_POSTARI) {
		fclose(f);
		ctrPost = 0;
		urmPostId = 0;
		printf("Fisier posts.dat corupt, nu se afiseaza postari.\n");
		return;
	}

	if (ctrPost > 0) {
		size_t freadNumar = fread(Postari, sizeof(Postare), ctrPost, f);
		if (freadNumar != (size_t) ctrPost) {
			printf(
					"Numarul de postari citite (%zu) diferit de cel cunoscut (%d), fisier posibil corupt.\n",
					freadNumar, ctrPost);
			ctrPost = (int) freadNumar;
			if (ctrPost < 0)
				ctrPost = 0;
			if (ctrPost == 0)
				urmPostId = 0;
		}
	}
	fclose(f);
	if (ctrPost > 0)
		sortPost();
}

void salvezPost(void) {
	FILE *f = fopen("posts.dat", "w");
	if (!f) {
		printf("Nu s-a putut deschide posts.dat!\n");
		return;
	}
	fwrite(&urmPostId, sizeof(int), 1, f);
	fwrite(&ctrPost, sizeof(int), 1, f);
	if (ctrPost > 0) {
		fwrite(Postari, sizeof(Postare), ctrPost, f);
	}
	fclose(f);
	copiazaFisier("posts.dat", "posts.dat.bak");
}

void adaugPost(const char *continut, int autorId) {
	if (ctrPost >= MAX_POSTARI) {
		strcpy(mesajEroare, "Numar maxim de postari atins!");
		return;
	}
	if (autorId < 0 || autorId >= ctrUsers) {
		strcpy(mesajEroare, "Utilizator invalid.");
		return;
	}

	char tempContinut[MAX_CONT_POST];
	strncpy(tempContinut, continut, MAX_CONT_POST - 1);
	tempContinut[MAX_CONT_POST - 1] = '\0';

	char *start = tempContinut;
	while (*start && isspace((char) *start) && *start != '\n')
		start++;
	char *end = tempContinut + strlen(tempContinut) - 1;
	while (end > start && isspace((char) *end) && *end != '\n')
		end--;
	*(end + 1) = '\0';

	if (strlen(start) == 0) {
		strcpy(mesajEroare,
				"Continutul postarii nu poate fi gol.");
		return;
	}
	if (start != tempContinut) {
		memmove(tempContinut, start, strlen(start) + 1);
	}

	int nrLinii = calcNrLiniiBufferGC(tempContinut,
			strlen(tempContinut));
	if (nrLinii > MAX_LINII_INPUT) {
		sprintf(mesajEroare,
				"Continutul postarii depaseste %d linii.",
				MAX_LINII_INPUT);
		return;
	}

	Postare *p = &Postari[ctrPost];
	p->id = urmPostId++;
	p->timestamp = time(NULL);
	p->autorIndex = autorId;
	strncpy(p->Autor, Utilizatori[autorId].Username, MAX_IN_USER - 1);
	p->Autor[MAX_IN_USER - 1] = '\0';
	strncpy(p->continutP, tempContinut, MAX_CONT_POST - 1);
	p->continutP[MAX_CONT_POST - 1] = '\0';
	p->ctrComent = 0;
	p->urmComentId = 0;
	p->inchisaP = 0;
	p->raspunsId = -1;
	strftime(p->Data, sizeof(p->Data), "%d-%m-%y %H:%M",
			localtime(&p->timestamp));

	ctrPost++;
	sortPost();
	salvezPost();

	strcpy(mesajStatus, "Postare adaugata!");
}

void adaugComent(int postIndex, const char *continut, int autorId) {
	if (postIndex < 0 || postIndex >= ctrPost) {
		strcpy(mesajEroare, "Postare invalida.");
		return;
	}
	if (autorId < 0 || autorId >= ctrUsers) {
		strcpy(mesajEroare, "Utilizator invalid.");
		return;
	}

	Postare *post = &Postari[postIndex];
	if (post->inchisaP) {
		strcpy(mesajEroare,
				"Nu se pot adauga comentarii la o postare inchisa.");
		return;
	}
	if (post->ctrComent >= MAX_COMENTARII) {
		strcpy(mesajEroare, "Numarul maxim de comentarii atins.");
		return;
	}

	char tempContinut[MAX_CONT_COMENT];
	strncpy(tempContinut, continut, MAX_CONT_COMENT - 1);
	tempContinut[MAX_CONT_COMENT - 1] = '\0';

	char *start = tempContinut;
	while (*start && isspace((char) *start) && *start != '\n')
		start++;
	char *end = tempContinut + strlen(tempContinut) - 1;
	while (end > start && isspace((char) *end) && *end != '\n')
		end--;
	*(end + 1) = '\0';

	if (strlen(start) == 0) {
		strcpy(mesajEroare,
				"Continutul comentariului nu poate fi gol.");
		return;
	}
	if (start != tempContinut) {
		memmove(tempContinut, start, strlen(start) + 1);
	}

	int nrLinii = calcNrLiniiBufferGC(tempContinut,
			strlen(tempContinut));
	if (nrLinii > MAX_LINII_INPUT) {
		sprintf(mesajEroare,
				"Continutul comentariului depaseste %d linii.",
				MAX_LINII_INPUT);
		return;
	}

	Comentariu *com = &post->Comentarii[post->ctrComent];
	com->id = post->urmComentId++;
	com->timestamp = time(NULL);
	com->autorIndex = autorId;
	strncpy(com->Autor, Utilizatori[autorId].Username, MAX_IN_USER - 1);
	com->Autor[MAX_IN_USER - 1] = '\0';
	strncpy(com->Continut, tempContinut, MAX_CONT_COMENT - 1);
	com->Continut[MAX_CONT_COMENT - 1] = '\0';
	com->esteRaspuns = 0;
	strftime(com->Data, sizeof(com->Data), "%d-%m-%y %H:%M",
			localtime(&com->timestamp));

	post->ctrComent++;
	salvezPost();
	strcpy(mesajStatus, "Comentariu adaugat.");
}

void stergePost(int postId) {
	int gasitId = -1;
	for (int i = 0; i < ctrPost; ++i) {
		if (Postari[i].id == postId) {
			if (Postari[i].autorIndex == userCurentId) {
				gasitId = i;
				break;
			} else {
				strcpy(mesajEroare,
						"Nu aveti permisiunea sa stergeti postarea.");
				return;
			}
		}
	}

	if (gasitId != -1) {
		int vizVechiIndx = postVazutId;
		int vizVechiId =
				(vizVechiIndx != -1) ?
						Postari[vizVechiIndx].id : -1;

		memmove(&Postari[gasitId], &Postari[gasitId + 1],
				(size_t)(ctrPost - gasitId - 1) * sizeof(Postari[0]));
		ctrPost--;
		salvezPost();
		strcpy(mesajStatus, "Postare stearsa.");

		if (ecran == VizualizarePostare && vizVechiId == postId) {
			ecran = BlogWelcome;
			postVazutId = -1;
			primaPostVazutId = 0;
			primComentVazutId = 0;
			focus = 0;
			cautareActiv = (lgCauta > 0);
		} else if (ecran == VizualizarePostare
				&& vizVechiIndx > gasitId) {
			postVazutId--;
		} else if (ecran == BlogWelcome) {
			int postFiltrateCtr = 0;
			for (int i = 0; i < ctrPost; ++i) {
				if (!cautareActiv
						|| postSePotriveste(&Postari[i],
								bufferCauta)) {
					postFiltrateCtr++;
				}
			}
			if (primaPostVazutId >= postFiltrateCtr
					&& postFiltrateCtr > 0) {
				primaPostVazutId = postFiltrateCtr - 1;
			}
			if (postFiltrateCtr == 0) {
				primaPostVazutId = 0;
			}
		}
	} else if (mesajEroare[0] == '\0') {
		strcpy(mesajEroare,
				"Postarea nu a fost gasita pentru stergere.");
	}
}

void marcheazaRaspuns(int postIndex, int comentariuId) {
	if (postIndex < 0 || postIndex >= ctrPost) {
		strcpy(mesajEroare, "Postare invalida.");
		return;
	}
	if (userCurentId < 0) {
		strcpy(mesajEroare, "Utilizator nelogat.");
		return;
	}

	Postare *post = &Postari[postIndex];
	if (post->autorIndex != userCurentId) {
		strcpy(mesajEroare, "Doar autorul postarii poate marca un raspuns.");
		return;
	}
	if (post->inchisaP && post->raspunsId != comentariuId) {
		strcpy(mesajEroare, "Postarea este deja inchisa cu un alt raspuns.");
		return;
	}
/*Post Id = -1 inseamna post. are deja rasp */
	int foundComment = 0;
	for (int i = 0; i < post->ctrComent; ++i) {
		if (post->Comentarii[i].id == comentariuId) {
			if (post->raspunsId != -1 && post->raspunsId != comentariuId) {
				for (int j = 0; j < post->ctrComent; ++j) {
					if (post->Comentarii[j].id == post->raspunsId) {
						post->Comentarii[j].esteRaspuns = 0;
						break;
					}
				}
			}
			post->Comentarii[i].esteRaspuns = 1;
			foundComment = 1;
			post->raspunsId = comentariuId;
			break;
		}
	}

	if (foundComment) {
		post->inchisaP = 1;
		salvezPost();
		strcpy(mesajStatus,
				"Comentariu marcat ca raspuns.");
	} else {
		strcpy(mesajEroare, "Comentariul nu a fost gasit.");
	}
}
