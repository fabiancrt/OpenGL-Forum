#Linux

CC = clang

# unused variable warnings are suppresed due to missinterpretation
FLAGS = -c -Wall -Wextra -Wno-unused-parameter

LDFLAGS = -lGL -lGLU -lglut -lm

all: ForumApp
interactiuni.o: interactiuni.c
	$(CC) $(FLAGS) interactiuni.c

prelucrare_useri.o: prelucrare_useri.c
	$(CC) $(FLAGS) prelucrare_useri.c

Forum.o: Forum.c
	$(CC) $(FLAGS) Forum.c

interfata.o: interfata.c
	$(CC) $(FLAGS) interfata.c

utilitati_interfata.o: utilitati_interfata.c
	$(CC) $(FLAGS) utilitati_interfata.c

gestionare_continut.o: gestionare_continut.c
	$(CC) $(FLAGS) gestionare_continut.c

ForumApp: interactiuni.o prelucrare_useri.o Forum.o interfata.o utilitati_interfata.o gestionare_continut.o
	$(CC) interactiuni.o prelucrare_useri.o Forum.o interfata.o utilitati_interfata.o gestionare_continut.o $(LDFLAGS) -o ForumApp

.PHONY: all clean

clean:
	rm -f *.o
	rm ForumApp
	rm -f *.dat
	rm -f *.bak

