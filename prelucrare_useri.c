#include "prelucrare_useri.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

User Utilizatori[MAX_UTILIZATORI_COUNT];
int ctrUsers = 0;
int userCurentId = -1;
char mesajStatus[150] = { 0 };
char mesajEroare[150] = { 0 };
/* Hash-ul este preluat ci nu propriu */
long jenkinsHash(char *str) {
	long hash = 0;
	while (*str) {
		hash += (char) (*str++);
		hash += (hash << 10);
		hash ^= (hash >> 6);
	}
	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);
	return hash;
}

void curataMesaje() {
	mesajStatus[0] = '\0';
	mesajEroare[0] = '\0';
}

int curataSpatiu(char *str) {
	char *start, *final;
	int len = strlen(str);
	if (len == 0)
		return 0;
	start = str;
	while (isspace((char) *start))
		start++;
	final = str + len - 1;
	while (final > start && isspace((char) *final))
		final--;
	len = (int) (final - start + 1);
	if (len <= 0) {
		str[0] = '\0';
		return 0;
	}
	if (start != str)
		memmove(str, start, len);
	str[len] = '\0';
	return len;
}

void copiazaFisier(const char *fisierSursa, const char *fisierDestinatie) {
	FILE *sursa, *destinatie;
	int ch;
	sursa = fopen(fisierSursa, "rb");
	if (sursa == NULL)
		return;
	destinatie = fopen(fisierDestinatie, "wb");
	if (destinatie == NULL) {
		fclose(sursa);
		return;
	}
	while ((ch = fgetc(sursa)) != EOF)
		fputc(ch, destinatie);
	fclose(sursa);
	fclose(destinatie);
}

void procUseri() {
	FILE *f = fopen("users.dat", "r");
	ctrUsers = 0;
	if (!f)
		return;
	fread(&ctrUsers, sizeof(int), 1, f);
	if (ctrUsers < 0 || ctrUsers > MAX_UTILIZATORI_COUNT) {
		fclose(f);
		ctrUsers = 0;
		printf("Numar invalid de utilizatori in users.dat.\n");
		return;
	}
	if (ctrUsers > 0) {
		fseek(f, 0, SEEK_END);
		long marime = ftell(f);
		fseek(f, sizeof(int), SEEK_SET);
		long presupDateUseri = (long) ctrUsers * sizeof(User);
		long presupTotal = sizeof(int) + presupDateUseri;
		if (marime != presupTotal) {
			fclose(f);
			ctrUsers = 0;
			printf(
					"Fisier users.dat eronat. Userii au fost resetati.\n");
			return;
		}
		size_t nrUtilizatoriCititi = fread(Utilizatori, sizeof(User),
				ctrUsers, f);
		if (nrUtilizatoriCititi != (size_t) ctrUsers) {
			printf(
					"Numarul de useri cititi (%zu) difera de cel cunoscut (%d).\n",
					nrUtilizatoriCititi, ctrUsers);
			ctrUsers = (int) nrUtilizatoriCititi;
			if (ctrUsers < 0)
				ctrUsers = 0;
		}
	}
	fclose(f);
}

void salveazaUser() {
	FILE *f = fopen("users.dat", "w");
	if (!f) {
		sprintf(mesajEroare,
				"Nu s-a putut deschide users.dat!");
		return;
	}
	fwrite(&ctrUsers, sizeof(int), 1, f);
	if (ctrUsers > 0)
		fwrite(Utilizatori, sizeof(User), ctrUsers, f);
	fclose(f);
	copiazaFisier("users.dat", "users.dat.bak");
}

void adaugaUser(char *nume, char *parola) {
	for (int i = 0; i < ctrUsers; ++i)
		if (strcmp(Utilizatori[i].Username, nume) == 0) {
			sprintf(mesajEroare, "Username '%s' este deja folosit!", nume);
			return;
		}
	if (ctrUsers >= MAX_UTILIZATORI_COUNT) {
		strcpy(mesajEroare, "Numar maxim de utilizatori atins!");
		return;
	}
	char tempNume[MAX_IN_USER], tempParola[MAX_IN_USER];
	strncpy(tempNume, nume, MAX_IN_USER - 1);
	tempNume[MAX_IN_USER - 1] = '\0';
	strncpy(tempParola, parola, MAX_IN_USER - 1);
	tempParola[MAX_IN_USER - 1] = '\0';

	if (curataSpatiu(tempNume) == 0 || curataSpatiu(tempParola) == 0) {
		strcpy(mesajEroare, "Numele si parola trebuie completate!");
		return;
	}

	User *user = &Utilizatori[ctrUsers];
	strncpy(user->Username, tempNume, MAX_IN_USER - 1);
	user->Username[MAX_IN_USER - 1] = '\0';
	long passHash = jenkinsHash(tempParola);
	sprintf(user->hashedPassword, "%ld", passHash);
	ctrUsers++;
	salveazaUser();
	sprintf(mesajStatus, "User '%s' inregistrat! Va puteti loga.", tempNume);
}

int verificaLogarea(char *nume, char *parola) {
	long hash = jenkinsHash(parola);
	for (int i = 0; i < ctrUsers; i++) {
		if (strcmp(Utilizatori[i].Username, nume) == 0
				&& atol(Utilizatori[i].hashedPassword) == hash)
			return i;
	}
	return -1;
}

