#include "interfata.h"
#include <stdio.h>
#include "definitii.h"

void desenWelcome(void) {
    int winW = glutGet(GLUT_WINDOW_WIDTH);
    int winH = glutGet(GLUT_WINDOW_HEIGHT);
    int centruX = winW / 2;

    glColor3f(CULOARE_ACCENT_R, CULOARE_ACCENT_G, CULOARE_ACCENT_B);
    desenText(centruX - calculWText("Forum", FONT_TITLU) / 2,
            winH * 0.8f, "Forum", FONT_TITLU);

    int btnW_prop = winW * 0.3f;
    int btnW = (btnW_prop < 150) ? 150 : ((btnW_prop > 300) ? 300 : btnW_prop); /* Latime buton*/
    int btnH_prop = winH * 0.06f;
    int btnH = (btnH_prop < 35) ? 35 : ((btnH_prop > 50) ? 50 : btnH_prop);/* Inaltime buton */

    int btnX = centruX - btnW / 2;
    int inregY = winH * 0.6f; /* Pozitie Y buton Inregistrare */
    int logY = inregY - btnH - 20; /* Pozitie Y buton Logare */

    desenButon(btnX, inregY, btnW, btnH, "Inregistrare", 1, focus, 0);
    desenButon(btnX, logY, btnW, btnH, "Logare", 2, focus, 0);
}

void desenInregistrare(void) {
    int winW = glutGet(GLUT_WINDOW_WIDTH);
    int winH = glutGet(GLUT_WINDOW_HEIGHT);
    int centruX = winW / 2;

    glColor3f(CULOARE_ACCENT_R, CULOARE_ACCENT_G, CULOARE_ACCENT_B);
    desenText(centruX - calculWText("Inregistrare", FONT_MARE) / 2,
            winH * 0.9f, "Inregistrare", FONT_MARE);

    int inputW_prop = winW * 0.5f;
    int inputW = (inputW_prop < 250) ? 250 : ((inputW_prop > 500) ? 500 : inputW_prop);
    int inputH = 25; /* H fixata pt input */
    int inputX = centruX - inputW / 2;

    int etichetaUserW = calculWText("Username:", FONT_NORMAL);
    int etichetaPassW = calculWText("Parola:", FONT_NORMAL);
    int etichetaXUser = inputX - etichetaUserW - 10;
    int etichetaXPass = inputX - etichetaPassW - 10;

    int userY = winH * 0.7f;
    int passY = userY - inputH - 30;

    int trimiteW_prop = winW * 0.15f;
    int trimiteW = (trimiteW_prop < 80) ? 80 : ((trimiteW_prop > 150) ? 150 : trimiteW_prop);
    int trimiteH = 30; /* H fixa */
    int trimiteX = centruX - trimiteW / 2;
    int trimiteY = passY - inputH - 40;

    int inapoiW_prop = winW * 0.1f;
    int inapoiW = (inapoiW_prop < 70) ? 70 : ((inapoiW_prop > 120) ? 120 : inapoiW_prop);
    int inapoiH_prop = BARA_SUS_H * 0.7f;
    int inapoiH = (inapoiH_prop < 20) ? 20 : inapoiH_prop;
    int inapoiX = 15; /* Margine fixa */
    int inapoiY = winH - BARA_SUS_H / 2 + inapoiH / 2;

    glColor3f(CULOARE_TEXT_R, CULOARE_TEXT_G, CULOARE_TEXT_B);
    desenText(etichetaXUser,
            userY - inputH / 2 - glutBitmapHeight(FONT_NORMAL) / 2, "Username:",
            FONT_NORMAL);
    desenInputText(inputX, userY, inputW, inputH, bufferNume, lgNume,
    MAX_IN_USER, 1, focus, 0, "Nume utilizator");

    glColor3f(CULOARE_TEXT_R, CULOARE_TEXT_G, CULOARE_TEXT_B);
    desenText(etichetaXPass,
            passY - inputH / 2 - glutBitmapHeight(FONT_NORMAL) / 2, "Parola:",
            FONT_NORMAL);
    desenInputText(inputX, passY, inputW, inputH, bufferParola, lgParola,
    MAX_IN_USER, 2, focus, 1, "Parola");

    desenButon(trimiteX, trimiteY, trimiteW, trimiteH, "Trimite", 3, focus, 0);
    desenButon(inapoiX, inapoiY, inapoiW, inapoiH, "Inapoi", 4, focus, 0);
}

void desenLogare(void) {
    int winW = glutGet(GLUT_WINDOW_WIDTH);
    int winH = glutGet(GLUT_WINDOW_HEIGHT);
    int centruX = winW / 2;

    glColor3f(CULOARE_ACCENT_R, CULOARE_ACCENT_G, CULOARE_ACCENT_B);
    desenText(centruX - calculWText("Logare", FONT_MARE) / 2,
            winH * 0.85f, "Logare", FONT_MARE);

    int inputW_prop = winW * 0.5f;
    int inputW = (inputW_prop < 250) ? 250 : ((inputW_prop > 500) ? 500 : inputW_prop);
    int inputH = 25; /* H fixa */
    int inputX = centruX - inputW / 2;

    int etichetaUserW = calculWText("Username:", FONT_NORMAL);
    int etichetaPassW = calculWText("Parola:", FONT_NORMAL);
    int etichetaXUser = inputX - etichetaUserW - 10;
    int etichetaXPass = inputX - etichetaPassW - 10;

    int userY = winH * 0.7f;
    int passY = userY - inputH - 30;

    int trimiteW_prop = winW * 0.15f;
    int trimiteW = (trimiteW_prop < 80) ? 80 : ((trimiteW_prop > 150) ? 150 : trimiteW_prop);
    int trimiteH = 30; /* Inaltime fixa */
    int trimiteX = centruX - trimiteW / 2;
    int trimiteY = passY - inputH - 30;

    int inapoiW_prop = winW * 0.1f;
    int inapoiW = (inapoiW_prop < 70) ? 70 : ((inapoiW_prop > 120) ? 120 : inapoiW_prop);
    int inapoiH_prop = BARA_SUS_H * 0.7f;
    int inapoiH = (inapoiH_prop < 20) ? 20 : inapoiH_prop;
    int inapoiX = 15;
    int inapoiY = winH - BARA_SUS_H / 2 + inapoiH / 2;

    glColor3f(CULOARE_TEXT_R, CULOARE_TEXT_G, CULOARE_TEXT_B);
    desenText(etichetaXUser,
            userY - inputH / 2 - glutBitmapHeight(FONT_NORMAL) / 2, "Username:",
            FONT_NORMAL);
    desenInputText(inputX, userY, inputW, inputH, bufferNume, lgNume,
    MAX_IN_USER, 1, focus, 0, "Nume utilizator");

    glColor3f(CULOARE_TEXT_R, CULOARE_TEXT_G, CULOARE_TEXT_B);
    desenText(etichetaXPass,
            passY - inputH / 2 - glutBitmapHeight(FONT_NORMAL) / 2, "Parola:",
            FONT_NORMAL);
    desenInputText(inputX, passY, inputW, inputH, bufferParola, lgParola,
    MAX_IN_USER, 2, focus, 1, "Parola");

    desenButon(trimiteX, trimiteY, trimiteW, trimiteH, "Trimite", 3, focus, 0);
    desenButon(inapoiX, inapoiY, inapoiW, inapoiH, "Inapoi", 4, focus, 0);
}

void desenBaraCautare(int winW, int winH, int xElemStart, int wDisponibilTotal, int yElemTop, int hElem) {
    if (wDisponibilTotal <= 10) return;

    int etichetaCautaW = calculWText("Cauta:", FONT_BUTON);
    int spatiuTextInainteInput = 5;
    int wInputCalculata;
    int etichetaX = xElemStart;
    int inputCautaX;

    int wInputMinimaNecesara = 50; /* Minim absolut pentru input */
    if (wDisponibilTotal < etichetaCautaW + spatiuTextInainteInput + wInputMinimaNecesara) {
        /* Daca nuu e loc pentru eticheta, folosim tot spatiul pt. input */
        etichetaCautaW = 0; /* Ascunde eticheta */
        inputCautaX = xElemStart;
        wInputCalculata = wDisponibilTotal - spatiuTextInainteInput;
        if (wInputCalculata < 0) wInputCalculata = 0;
    } else {
        inputCautaX = xElemStart + etichetaCautaW + spatiuTextInainteInput;
        wInputCalculata = wDisponibilTotal - etichetaCautaW - spatiuTextInainteInput;
    }

    if (wInputCalculata < wInputMinimaNecesara && wDisponibilTotal > wInputMinimaNecesara + spatiuTextInainteInput) {
        /* Daca inputul calculat e prea mic, dar exista spatiu , il marim */
        wInputCalculata = wInputMinimaNecesara;
    }


    int yTextBaseline = yElemTop - hElem / 2 - glutBitmapHeight(FONT_BUTON) / 2;

    if (etichetaCautaW > 0) {
        glColor3f(CULOARE_TEXT_R, CULOARE_TEXT_G, CULOARE_TEXT_B);
        desenText(etichetaX, yTextBaseline, "Cauta:", FONT_BUTON);
    }

    if (wInputCalculata > 0) {
        desenInputText(inputCautaX, yElemTop, wInputCalculata, hElem, bufferCauta, lgCauta,
        MAX_CAUTA, 6, focus, 0, "");
    }
    glColor3f(CULOARE_TEXT_R, CULOARE_TEXT_G, CULOARE_TEXT_B); /* Reset culoare */
}

void desenMain(void) {
    int winH = glutGet(GLUT_WINDOW_HEIGHT);
    int winW = glutGet(GLUT_WINDOW_WIDTH);

    /* Bara sus */
    glColor3f(CULOARE_BARA_R, CULOARE_BARA_G, CULOARE_BARA_B);
    glBegin(GL_QUADS);
    glVertex2i(0, winH);
    glVertex2i(winW, winH);
    glVertex2i(winW, winH - BARA_SUS_H);
    glVertex2i(0, winH - BARA_SUS_H);
    glEnd();

    /* Titlu in bara de sus */
    glColor3f(1, 1, 1);
    int titluY = winH - BARA_SUS_H / 2 - glutBitmapHeight(FONT_MARE) / 2;
    desenText(10, titluY, "Forum", FONT_MARE);

    /* Elemente in bara de sus (butoane, cautare) */
    int hElementeBara_prop = BARA_SUS_H * 0.7f;
    int hElementeBara = (hElementeBara_prop < 20) ? 20 : hElementeBara_prop;
    int yTopElementeBara = winH - BARA_SUS_H / 2 + hElementeBara / 2;
    int margineLaterala = 10;
    int spatiuIntreElementeBara = 15;

    /* Buton Logout (dreapta) */
    int logoutW_prop = winW * 0.1f;
    int logoutW = (logoutW_prop < 70) ? 70 : ((logoutW_prop > 100) ? 100 : logoutW_prop);
    int logoutX = winW - logoutW - margineLaterala;
    desenButon(logoutX, yTopElementeBara, logoutW, hElementeBara, "Logout", 5, focus, 0);

    /* Butoane Sortare (la stanga de Logout) */
    int sortW_prop = winW * 0.1f;
    int sortW = (sortW_prop < 70) ? 70 : ((sortW_prop > 110) ? 110 : sortW_prop);
    int sortVechiX = logoutX - spatiuIntreElementeBara - sortW;
    desenButon(sortVechiX, yTopElementeBara, sortW, hElementeBara,
            ordineSort == 1 ? "[Sort Vechi]" : "Sort Vechi", 4, focus, 0);
    int sortNouX = sortVechiX - spatiuIntreElementeBara - sortW;
    desenButon(sortNouX, yTopElementeBara, sortW, hElementeBara,
            ordineSort == 0 ? "[Sort Nou]" : "Sort Nou", 3, focus, 0);

    /* Bara Cautare (la stanga de butoanele de sortare) */
    int xStartCautare = 10 + calculWText("Forum", FONT_MARE) + spatiuIntreElementeBara;
    int xEndCautare = sortNouX - spatiuIntreElementeBara;
    int wDisponibilaCautare = xEndCautare - xStartCautare;
    if (wDisponibilaCautare > 20) { /* Desenam cautarea doar daca avem spatiu suficient */
        desenBaraCautare(winW, winH, xStartCautare, wDisponibilaCautare, yTopElementeBara, hElementeBara);
    }

    glColor3f(CULOARE_TEXT_R, CULOARE_TEXT_G, CULOARE_TEXT_B); /*Reset culoare */

    /*Zona lista postari */
    int listaPostStartY_Top = winH - BARA_SUS_H - SPATIU_INTRE_ELEMENTE;
    int listaPostZonaH = winH - H_ZONA_INPUT - BARA_SUS_H
            - SPATIU_INTRE_ELEMENTE * 2;
    int scissorY_Bottom = H_ZONA_INPUT;
    int scissorH = listaPostZonaH;
    if (scissorH < 0)
        scissorH = 0;

    glEnable(GL_SCISSOR_TEST);
    glScissor(0, scissorY_Bottom, winW - SAGEATA_W - 5, scissorH);

    int Y_Actual_Top = listaPostStartY_Top;
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
        int hPostareCurenta = 0;
        desenElementPostare(&Postari[i], Y_Actual_Top, i,
                &hPostareCurenta);
        Y_Actual_Top -= (hPostareCurenta + SPATIU_INTRE_ELEMENTE);
        postProcesateScroll++;
        if (Y_Actual_Top - MIN_H_POSTARE < scissorY_Bottom)
            break;
    }
    glDisable(GL_SCISSOR_TEST);

    /* Sageti scroll */
    int sageataX = winW - SAGEATA_W - 5;
    int sageataUpY_Top = winH - BARA_SUS_H - SPATIU_INTRE_ELEMENTE
            - SAGEATA_H / 2;
    int sageataDownY_Top = H_ZONA_INPUT + SPATIU_INTRE_ELEMENTE
            + SAGEATA_H + SAGEATA_H / 2; /* Ajustat pt a fi mai jos */
    desenSageata(sageataX, sageataUpY_Top, SAGEATA_W, SAGEATA_H, 1);    /* Sus */
    desenSageata(sageataX, sageataDownY_Top + SAGEATA_H, SAGEATA_W, SAGEATA_H, -1); /* Jos */

    /* Zona input pentru postari */
    glColor3f(CULOARE_INPUT_R, CULOARE_INPUT_G, CULOARE_INPUT_B);
    glBegin(GL_QUADS);
    glVertex2i(0, H_ZONA_INPUT);
    glVertex2i(winW, H_ZONA_INPUT);
    glVertex2i(winW, 0);
    glVertex2i(0, 0);
    glEnd();
    glColor3f(CULOARE_ACCENT_R, CULOARE_ACCENT_G, CULOARE_ACCENT_B);
    glBegin(GL_LINES);
    glVertex2i(0, H_ZONA_INPUT);
    glVertex2i(winW, H_ZONA_INPUT);
    glEnd();

    int inputMargine = 10;
    int postBtnW_prop = winW * 0.12f;
    int postBtnW = (postBtnW_prop < 80) ? 80 : ((postBtnW_prop > 120) ? 120 : postBtnW_prop);
    int postBtnX = winW - postBtnW - inputMargine;
    int inputX_post = inputMargine;
    int inputW_post = postBtnX - inputMargine - inputX_post;
    if (inputW_post < 50) inputW_post = 50; /* Latime min. pt. input */

    int inputH_Box = H_ZONA_INPUT - 20;
    int elemYCasutaTop = H_ZONA_INPUT - PAD_VERT_ELEMENT / 2;

    glColor3f(1, 1, 1); /* Fundal casuta input */
    glBegin(GL_QUADS);
    glVertex2i(inputX_post, elemYCasutaTop);
    glVertex2i(inputX_post + inputW_post, elemYCasutaTop);
    glVertex2i(inputX_post + inputW_post, elemYCasutaTop - inputH_Box);
    glVertex2i(inputX_post, elemYCasutaTop - inputH_Box);
    glEnd();
    /* Chenar input */
    glColor3f(CULOARE_ACCENT_R, CULOARE_ACCENT_G, CULOARE_ACCENT_B);
    desenCasuta(inputX_post, elemYCasutaTop, inputW_post, inputH_Box);
    glColor3f(CULOARE_TEXT_R, CULOARE_TEXT_G, CULOARE_TEXT_B);

    /* Scissor pentru text */
    GLboolean scissorActivat_Blog;
    GLint scissorCasutaVeche_Blog[4];
    glGetBooleanv(GL_SCISSOR_TEST, &scissorActivat_Blog);
    glGetIntegerv(GL_SCISSOR_BOX, scissorCasutaVeche_Blog);
    glEnable(GL_SCISSOR_TEST);
    glScissor(inputX_post + PAD_INTERN_INPUT - 1,
            elemYCasutaTop - inputH_Box + PAD_INTERN_INPUT - 1,
            inputW_post - 2 * PAD_INTERN_INPUT + 2,
            inputH_Box - 2 * PAD_INTERN_INPUT + 2);

    desenTextMultiLineInput(inputX_post, elemYCasutaTop, inputW_post, inputH_Box,
            bufferPostare, lgPostare, primaLiniePostare,
            FONT_NORMAL, FONT_COD, (focus == 1));

    if (scissorActivat_Blog)
        glScissor(scissorCasutaVeche_Blog[0], scissorCasutaVeche_Blog[1],
                scissorCasutaVeche_Blog[2], scissorCasutaVeche_Blog[3]);
    else
        glDisable(GL_SCISSOR_TEST);

    if (focus == 1)
        desenFocus(inputX_post, elemYCasutaTop, inputW_post, inputH_Box);
    desenButon(postBtnX, elemYCasutaTop, postBtnW, inputH_Box, "Posteaza", 2,
            focus, 0);
}

void desenElementPostare(Postare *p, int yPos, int index,
        int *outInaltimeDesenata) {
    int winW = glutGet(GLUT_WINDOW_WIDTH);
    int casutaX = 10;
    int casutaW = winW - 20 - SAGEATA_W - 5;
    if (casutaW < 100) casutaW = 100; /* Latime minima */

    int btnDelW_prop = casutaW * 0.1f;
    int btnDelW = (btnDelW_prop < 50) ? 50 : ((btnDelW_prop > 70) ? 70 : btnDelW_prop);
    int btnDelH = 18; /* Inaltime fixa */

    int btnZonaW = (p->autorIndex == userCurentId) ? (btnDelW + 10) : 0;
    int textW = casutaW - btnZonaW - 2 * MARGINE_TEXT;
    if (textW < 50)
        textW = 50;

    int inaltimeCalculata = calculHNecElement(p->continutP,
            textW,
            H_ANTET_POSTARE, H_SUBSOL_POSTARE,
            MIN_H_POSTARE);
    if (outInaltimeDesenata)
        *outInaltimeDesenata = inaltimeCalculata;

    if (p->inchisaP)
        glColor3f(CULOARE_INCHIS_R, CULOARE_INCHIS_G, CULOARE_INCHIS_B);
    else
        glColor3f(CULOARE_POST_R, CULOARE_POST_G, CULOARE_POST_B);
    glBegin(GL_QUADS);
    glVertex2i(casutaX, yPos);
    glVertex2i(casutaX + casutaW, yPos);
    glVertex2i(casutaX + casutaW, yPos - inaltimeCalculata);
    glVertex2i(casutaX, yPos - inaltimeCalculata);
    glEnd();

    glColor3f(CULOARE_ACCENT_R, CULOARE_ACCENT_G, CULOARE_ACCENT_B);
    desenCasuta(casutaX, yPos, casutaW, inaltimeCalculata);

    glColor3f(CULOARE_TEXT_R, CULOARE_TEXT_G, CULOARE_TEXT_B);

    int infoY = yPos - PAD_VERT_ELEMENT - glutBitmapHeight(FONT_MIC);
    int autorW = calculWText(p->Autor, FONT_MIC);
    int separatorW = calculWText(" | ", FONT_MIC);
    desenText(casutaX + MARGINE_TEXT, infoY, p->Autor, FONT_MIC);
    desenText(casutaX + MARGINE_TEXT + autorW, infoY, " | ", FONT_MIC);
    desenText(casutaX + MARGINE_TEXT + autorW + separatorW, infoY, p->Data,
    FONT_MIC);

    int dataAutorW = autorW + separatorW
            + calculWText(p->Data, FONT_MIC);
    int statusX = casutaX + MARGINE_TEXT + dataAutorW + 10;
    if (p->inchisaP) {
        glColor3f(CULOARE_SUCCES_R, CULOARE_SUCCES_G, CULOARE_SUCCES_B);
        char mesajInchis[50];
        sprintf(mesajInchis, p->raspunsId != -1 ? "[Raspuns]" : "[Inchis]");
        desenText(statusX, infoY, mesajInchis, FONT_MIC);
        glColor3f(CULOARE_TEXT_R, CULOARE_TEXT_G, CULOARE_TEXT_B);
    }

    int continutY_Top = infoY - PAD_VERT_ELEMENT;
    desenIncadText(casutaX + MARGINE_TEXT, continutY_Top, textW,
            p->continutP,
            FONT_NORMAL);

    if (p->autorIndex == userCurentId) {
        int btnDelX = casutaX + casutaW - btnDelW - 5;
        int btnDelY_Top = yPos - PAD_VERT_ELEMENT;
        desenButon(btnDelX, btnDelY_Top, btnDelW, btnDelH, "Sterge", 0, 0, 0);
    }

    /*Contor comentarii */
    char comCtrStr[30];
    sprintf(comCtrStr, "Comentarii: %d", p->ctrComent);
    int comCtrY = yPos - inaltimeCalculata + PAD_VERT_ELEMENT;
    desenText(casutaX + MARGINE_TEXT, comCtrY, comCtrStr, FONT_MIC);
}

void desenVizPost(void) {
    if (postVazutId < 0 || postVazutId >= ctrPost)
        return;
    int winH = glutGet(GLUT_WINDOW_HEIGHT);
    int winW = glutGet(GLUT_WINDOW_WIDTH);
    Postare *post = &Postari[postVazutId];

    /*Zona afisare postarea propriu-zisa*/
    int inapoiBtnW_prop = winW * 0.08f;
    int inapoiBtnW = (inapoiBtnW_prop < 50) ? 50 : ((inapoiBtnW_prop > 80) ? 80 : inapoiBtnW_prop);
    int inapoiBtnH = 20; /* H fixa */
    int latimeTextPostare = winW - 10 - (inapoiBtnW + 10) - 2 * MARGINE_TEXT;
    if (latimeTextPostare < 50)
        latimeTextPostare = 50;

    int hHeaderPostViz = (3 * PAD_VERT_ELEMENT)
            + inapoiBtnH + glutBitmapHeight(FONT_MIC);
    int inaltimePostareAfisata = calculHNecElement(
            post->continutP, latimeTextPostare, hHeaderPostViz,
            H_SUBSOL_POSTARE,
            MIN_H_POSTARE + 25);
    int postY_Top = winH - 5;
    int casutaX_Post = 5, casutaW_Post = winW - 10;
    if (casutaW_Post < 100) casutaW_Post = 100;


    /*Background si chenar */
    if (post->inchisaP)
        glColor3f(CULOARE_INCHIS_R, CULOARE_INCHIS_G, CULOARE_INCHIS_B);
    else
        glColor3f(CULOARE_POST_R, CULOARE_POST_G, CULOARE_POST_B);
    glBegin(GL_QUADS);
    glVertex2i(casutaX_Post, postY_Top);
    glVertex2i(casutaX_Post + casutaW_Post, postY_Top);
    glVertex2i(casutaX_Post + casutaW_Post, postY_Top - inaltimePostareAfisata);
    glVertex2i(casutaX_Post, postY_Top - inaltimePostareAfisata);
    glEnd();
    glColor3f(CULOARE_ACCENT_R, CULOARE_ACCENT_G, CULOARE_ACCENT_B);
    desenCasuta(casutaX_Post, postY_Top, casutaW_Post, inaltimePostareAfisata);

    /*Butonul inapoi */
    int inapoiX = casutaX_Post + MARGINE_TEXT;
    int inapoiY_Top = postY_Top - PAD_VERT_ELEMENT;
    desenButon(inapoiX, inapoiY_Top, inapoiBtnW, inapoiBtnH, "Inapoi", 3, focus,
            0); /* Inapoi are focusul 3 */

    /* Autor data si status */
    int infoY_Baseline = inapoiY_Top - inapoiBtnH - PAD_VERT_ELEMENT
            - glutBitmapHeight(FONT_MIC);
    glColor3f(CULOARE_TEXT_R, CULOARE_TEXT_G, CULOARE_TEXT_B);
    int autorW_vp = calculWText(post->Autor, FONT_MIC);
    int separatorW_vp = calculWText(" | ", FONT_MIC);
    desenText(casutaX_Post + MARGINE_TEXT, infoY_Baseline, post->Autor,
    FONT_MIC);
    desenText(casutaX_Post + MARGINE_TEXT + autorW_vp, infoY_Baseline, " | ",
    FONT_MIC);
    desenText(casutaX_Post + MARGINE_TEXT + autorW_vp + separatorW_vp,
            infoY_Baseline, post->Data, FONT_MIC);

    int dataAutorW_vp = autorW_vp + separatorW_vp
            + calculWText(post->Data, FONT_MIC);
    int statusX_vp = casutaX_Post + MARGINE_TEXT + dataAutorW_vp + 10;
    if (post->inchisaP) {
        glColor3f(CULOARE_SUCCES_R, CULOARE_SUCCES_G, CULOARE_SUCCES_B);
        char mesajInchis_vp[50];
        sprintf(mesajInchis_vp,
                post->raspunsId != -1 ? "[Raspuns]" : "[Inchis]");
        desenText(statusX_vp, infoY_Baseline, mesajInchis_vp, FONT_MIC);
        glColor3f(CULOARE_TEXT_R, CULOARE_TEXT_G, CULOARE_TEXT_B);
    }
    /* Continut */
    int continutY_Top_vp = infoY_Baseline - PAD_VERT_ELEMENT;
    desenIncadText(casutaX_Post + MARGINE_TEXT, continutY_Top_vp,
            latimeTextPostare, post->continutP, FONT_NORMAL);

    /* Zona comentarii */
    int comentariiStartY_Top = postY_Top - inaltimePostareAfisata
            - SPATIU_INTRE_ELEMENTE;
    int zonaComentariiH = comentariiStartY_Top - H_ZONA_INPUT
            - SPATIU_INTRE_ELEMENTE;
    int scissorY_Bottom_Com = H_ZONA_INPUT;
    int scissorH_Com = zonaComentariiH;
    if (scissorH_Com < 0)
        scissorH_Com = 0;

    glEnable(GL_SCISSOR_TEST);
    glScissor(0, scissorY_Bottom_Com, winW - SAGEATA_W - 5, scissorH_Com);
    int comActualY_Top = comentariiStartY_Top;
    int comentariiProcScroll = 0;
    for (int i = 0; i < post->ctrComent; ++i) {
        if (comentariiProcScroll < primComentVazutId) {
            comentariiProcScroll++;
            continue;
        }
        int hComentCurent = 0;
        desenComentariuElement(&post->Comentarii[i], comActualY_Top,
                postVazutId, &hComentCurent);
        comActualY_Top -= (hComentCurent + SPATIU_INTRE_ELEMENTE);
        comentariiProcScroll++;
        if (comActualY_Top - MIN_H_COMENTARIU < scissorY_Bottom_Com)
            break;
    }
    glDisable(GL_SCISSOR_TEST);

    /* Sageti scroll */
    int sageataX_Com = winW - SAGEATA_W - 5;
    int sageataUpY_Top_Com = comentariiStartY_Top - SAGEATA_H / 2;
    int sageataDownY_Top_Com = H_ZONA_INPUT + SPATIU_INTRE_ELEMENTE
            + SAGEATA_H + SAGEATA_H / 2; /* Ajustat */
    desenSageata(sageataX_Com, sageataUpY_Top_Com, SAGEATA_W, SAGEATA_H, 1);
    desenSageata(sageataX_Com, sageataDownY_Top_Com + SAGEATA_H, SAGEATA_W, SAGEATA_H, -1);

    /* Zona input comentarii */
    glColor3f(CULOARE_INPUT_R, CULOARE_INPUT_G, CULOARE_INPUT_B);
    glBegin(GL_QUADS);
    glVertex2i(0, H_ZONA_INPUT);
    glVertex2i(winW, H_ZONA_INPUT);
    glVertex2i(winW, 0);
    glVertex2i(0, 0);
    glEnd();
    glColor3f(CULOARE_ACCENT_R, CULOARE_ACCENT_G, CULOARE_ACCENT_B);
    glBegin(GL_LINES);
    glVertex2i(0, H_ZONA_INPUT);
    glVertex2i(winW, H_ZONA_INPUT);
    glEnd();

    int inputMargineCom = 10;
    int comBtnW_prop = winW * 0.12f;
    int comBtnW = (comBtnW_prop < 80) ? 80 : ((comBtnW_prop > 120) ? 120 : comBtnW_prop);
    int comBtnX = winW - comBtnW - inputMargineCom;
    int inputX_Com = inputMargineCom;
    int inputW_Com = comBtnX - inputMargineCom - inputX_Com;
    if (inputW_Com < 50) inputW_Com = 50;


    int inputH_Box_Com = H_ZONA_INPUT - 20;
    int elemYCasutaTop_Com = H_ZONA_INPUT - PAD_VERT_ELEMENT / 2;

    if (post->inchisaP)
        glColor3f(CULOARE_INCHIS_R, CULOARE_INCHIS_G, CULOARE_INCHIS_B);
    else
        glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
    glVertex2i(inputX_Com, elemYCasutaTop_Com);
    glVertex2i(inputX_Com + inputW_Com, elemYCasutaTop_Com);
    glVertex2i(inputX_Com + inputW_Com, elemYCasutaTop_Com - inputH_Box_Com);
    glVertex2i(inputX_Com, elemYCasutaTop_Com - inputH_Box_Com);
    glEnd();

    if (post->inchisaP)
        glColor3f(0.6f, 0.6f, 0.6f);
    else
        glColor3f(CULOARE_ACCENT_R, CULOARE_ACCENT_G, CULOARE_ACCENT_B);
    desenCasuta(inputX_Com, elemYCasutaTop_Com, inputW_Com, inputH_Box_Com);
    glColor3f(CULOARE_TEXT_R, CULOARE_TEXT_G, CULOARE_TEXT_B);

    /* Scissor pentru textul din input */
    GLboolean scissorActivat_Com;
    GLint scissorCasutaVeche_Com[4];
    glGetBooleanv(GL_SCISSOR_TEST, &scissorActivat_Com);
    glGetIntegerv(GL_SCISSOR_BOX, scissorCasutaVeche_Com);
    glEnable(GL_SCISSOR_TEST);
    glScissor(inputX_Com + PAD_INTERN_INPUT - 1,
            elemYCasutaTop_Com - inputH_Box_Com + PAD_INTERN_INPUT - 1,
            inputW_Com - 2 * PAD_INTERN_INPUT + 2,
            inputH_Box_Com - 2 * PAD_INTERN_INPUT + 2);

    if (post->inchisaP) {
        int textY_inchis = elemYCasutaTop_Com - inputH_Box_Com / 2
                - glutBitmapHeight(FONT_NORMAL) / 2;
        desenText(inputX_Com + PAD_INTERN_INPUT, textY_inchis,
                "Postare inchisa", FONT_NORMAL);
    } else {
        desenTextMultiLineInput(inputX_Com, elemYCasutaTop_Com,
                inputW_Com, inputH_Box_Com, bufferComentariu, lgComentariu,
                primaLinieComentariu,
                FONT_NORMAL, FONT_COD, (focus == 1));
    }
    if (scissorActivat_Com)
        glScissor(scissorCasutaVeche_Com[0], scissorCasutaVeche_Com[1],
                scissorCasutaVeche_Com[2], scissorCasutaVeche_Com[3]);
    else
        glDisable(GL_SCISSOR_TEST);

    if (focus == 1 && !post->inchisaP)
        desenFocus(inputX_Com, elemYCasutaTop_Com, inputW_Com, inputH_Box_Com);
    desenButon(comBtnX, elemYCasutaTop_Com, comBtnW, inputH_Box_Com,
            "Comenteaza", 2, focus, post->inchisaP);
}

void desenComentariuElement(Comentariu *c, int yPos, int postIndex,
        int *outInaltimeDesenata) {
    int winW = glutGet(GLUT_WINDOW_WIDTH);
    int casutaX = 20;
    int casutaW = winW - 40 - SAGEATA_W - 5;
    if (casutaW < 80) casutaW = 80; /* Latime minima */

    Postare *post = &Postari[postIndex];
    int esteAutorulPost = (userCurentId != -1
            && post->autorIndex == userCurentId);

    int btnAnsW_prop = casutaW * 0.1f;
    int btnAnsW = (btnAnsW_prop < 50) ? 50 : ((btnAnsW_prop > 70) ? 70 : btnAnsW_prop);
    int btnAnsH = 18; /*Dimensiuni buton "Raspuns"*/

    int btnZonaW = (esteAutorulPost && !post->inchisaP) ? (btnAnsW + 10) : 0;
    int textW = casutaW - btnZonaW - 2 * MARGINE_TEXT;
    if (textW < 50)
        textW = 50;

    int inaltimeCalculata = calculHNecElement(c->Continut,
            textW,
            H_ANTET_COMENTARIU,
            PAD_VERT_ELEMENT,
            MIN_H_COMENTARIU);
    if (outInaltimeDesenata)
        *outInaltimeDesenata = inaltimeCalculata;

    /*Background comment */
    if (c->esteRaspuns)
        glColor3f(CULOARE_RASPUNS_R, CULOARE_RASPUNS_G, CULOARE_RASPUNS_B);
    else
        glColor3f(CULOARE_POST_R, CULOARE_POST_G, CULOARE_POST_B);
    glBegin(GL_QUADS);
    glVertex2i(casutaX, yPos);
    glVertex2i(casutaX + casutaW, yPos);
    glVertex2i(casutaX + casutaW, yPos - inaltimeCalculata);
    glVertex2i(casutaX, yPos - inaltimeCalculata);
    glEnd();
    /*Chenar casuta com */
    if (c->esteRaspuns)
        glColor3f(CULOARE_SUCCES_R, CULOARE_SUCCES_G, CULOARE_SUCCES_B);/*Chenar raspuns */
    else
        glColor3f(CULOARE_ACCENT_R, CULOARE_ACCENT_G, CULOARE_ACCENT_B);
    desenCasuta(casutaX, yPos, casutaW, inaltimeCalculata);

    /*Autor si data comentariu */
    glColor3f(CULOARE_TEXT_R, CULOARE_TEXT_G, CULOARE_TEXT_B);
    int infoY_c = yPos - PAD_VERT_ELEMENT - glutBitmapHeight(FONT_MIC);
    int autorW_c = calculWText(c->Autor, FONT_MIC);
    int separatorW_c = calculWText(" | ", FONT_MIC);
    desenText(casutaX + MARGINE_TEXT, infoY_c, c->Autor, FONT_MIC);
    desenText(casutaX + MARGINE_TEXT + autorW_c, infoY_c, " | ", FONT_MIC);
    desenText(casutaX + MARGINE_TEXT + autorW_c + separatorW_c, infoY_c,
            c->Data, FONT_MIC);

    /* Raspuns corect status */
    int dataAutorW_c = autorW_c + separatorW_c
            + calculWText(c->Data, FONT_MIC);
    int statusX_c = casutaX + MARGINE_TEXT + dataAutorW_c + 10;
    if (c->esteRaspuns) {
        glColor3f(CULOARE_SUCCES_R, CULOARE_SUCCES_G, CULOARE_SUCCES_B);
        desenText(statusX_c, infoY_c, "[RASPUNS CORECT]", FONT_MIC);
        glColor3f(CULOARE_TEXT_R, CULOARE_TEXT_G, CULOARE_TEXT_B); /*Reset culoare */
    }

    /*Continut comentariu */
    int continutY_Top_c = infoY_c - PAD_VERT_ELEMENT;
    desenIncadText(casutaX + MARGINE_TEXT, continutY_Top_c, textW,
            c->Continut,
            FONT_NORMAL);

    /* Buton raspuns */
    if (esteAutorulPost && !post->inchisaP) {
        int btnAnsX = casutaX + casutaW - btnAnsW - 5;
        int btnAnsY_Top = yPos - PAD_VERT_ELEMENT;
        desenButon(btnAnsX, btnAnsY_Top, btnAnsW, btnAnsH, "Raspuns", 0, 0, 0);
    }
}

void afisMsjStatEroare(int winW, int winH) {
    int paddingSusMsg = 15;
    int paddingJosMsg = 15;
    char *mesajAfisat = NULL;
    int esteEroare = 0;

    if (mesajEroare[0] != '\0') {
        mesajAfisat = mesajEroare;
        esteEroare = 1;
    } else if (mesajStatus[0] != '\0') {
        mesajAfisat = mesajStatus;
        esteEroare = 0;
    }

    if (mesajAfisat) {
        if (esteEroare)
            glColor3f(CULOARE_EROARE_R, CULOARE_EROARE_G, CULOARE_EROARE_B);
        else
            glColor3f(CULOARE_SUCCES_R, CULOARE_SUCCES_G, CULOARE_SUCCES_B);

        int msgH = calculHText(mesajAfisat, winW - 20,
        FONT_NORMAL);
        int msgFinalX = 10;
        int msgFinalMaxW = winW - 2 * msgFinalX;
        if (msgFinalMaxW < 10) msgFinalMaxW = 10; /* Latime minima pentru mesaj */
        int msgFinalY_Top;

        /*Pozitionare in functie de context */
        if (ecran == BlogWelcome || ecran == VizualizarePostare) {
            /* Pozitioneaza mesajul deasupra zonei de input, daca este spatiu */
            /* Daca INALTIME_ZONA_INPUT e mare, mesajul poate fi sub bara de sus */
            if (winH - BARA_SUS_H - SPATIU_INTRE_ELEMENTE > H_ZONA_INPUT + msgH + paddingSusMsg) {
                 msgFinalY_Top = H_ZONA_INPUT + paddingSusMsg + msgH;
            } else { /* Daca nu e spatiu suficient deasupra inputului, afiseaza sub bara de sus */
                 msgFinalY_Top = winH - BARA_SUS_H - SPATIU_INTRE_ELEMENTE;
            }
        } else {
            msgFinalY_Top = paddingJosMsg + msgH;
        }
        if (msgFinalY_Top > winH - 10) msgFinalY_Top = winH - 10;
        if (msgFinalY_Top - msgH < 5) msgFinalY_Top = msgH + 5;


        desenIncadText(msgFinalX, msgFinalY_Top, msgFinalMaxW, mesajAfisat,
                FONT_NORMAL);
        glColor3f(CULOARE_TEXT_R, CULOARE_TEXT_G, CULOARE_TEXT_B);
    }
}
