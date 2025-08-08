#ifndef PRELUCRARE_USERI_H_
#define PRELUCRARE_USERI_H_

#include <time.h>

#define MAX_IN_USER 32
#define HASH_PAROLA_USER 64
#define MAX_UTILIZATORI_COUNT 100

typedef struct {
	char Username[MAX_IN_USER];
	char hashedPassword[HASH_PAROLA_USER];
} User;

extern User Utilizatori[MAX_UTILIZATORI_COUNT];
extern int ctrUsers;
extern int userCurentId;
extern char mesajStatus[150];
extern char mesajEroare[150];

void procUseri(void);
void salveazaUser(void);
void adaugaUser(char *nume, char *parola);
int verificaLogarea(char *nume, char *parola);
long jenkinsHash(char *s);
int curataSpatiu(char *str);
void curataMesaje(void);
void copiazaFisier(const char *fisierSursa, const char *fisierDestinatie);

#endif
