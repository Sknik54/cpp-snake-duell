#include "Spielzustand.h"

void Spielzustand::neuesFutter() { //erzeugt neues Futter
    const Schlangenglied& kopf = python.gibschlange()[0];
    futter.px = ((17 * kopf.x) % spielbreite) + 1;
    futter.py = ((13 * kopf.y) % spielhoehe) + 1;
}

bool Spielzustand::neuerNPC() { //fügt NPC kopf ein
    NPC.gibschlange().clear();
    int versuche = 0;
    while (versuche < 5) {
        int leben = NPC.gibleben();
        int posx = ((python.gibschlange()[0].x + leben * 2) % spielbreite) + 1;
        int posy = ((python.gibschlange()[0].y + leben * 3) % spielhoehe) + 1;

        bool belegt = false;


        for (int i = 0; i < python.gibschlange().size(); i++) {
            if (python.gibschlange()[i].x == posx
                && python.gibschlange()[i].y == posy) {
                belegt = true;
                break;
            }
        }


        if (futter.px == posx && futter.py == posy) {
            belegt = true;
        }

        if (!belegt) {

            NPC.gibschlange().push_back(Schlangenglied(posx, posy));
            return true;
        }


        NPC.erhoeheleben();
        versuche++;
    }


    return false;
}
Point2d Spielzustand::berechneNPCBewegung() { //Bewegungslogik der NPC Schlange
    Schlangenglied kopf = NPC.gibschlange()[0];
    Point2d neukopf;
    int x = futter.px - kopf.x;
    int y = futter.py - kopf.y;

    if (x >  spielbreite/2)  x -= spielbreite;
    if (x < -spielbreite/2)  x += spielbreite;

    if (y >  spielhoehe/2)   y -= spielhoehe;
    if (y < -spielhoehe/2)   y += spielhoehe;

    bool belegt = false;
    if (abs(x) >= abs(y)) {
        neukopf = NeuerKopfpunkt(kopf, x > 0 ? 'd' : 'a');
        if (NPC.gibschlange().size() > 1
            && neukopf.px == NPC.gibschlange()[1].x
            && neukopf.py == NPC.gibschlange()[1].y) {
                belegt = true;
        }

    if (belegt && y!=0) {
        return NeuerKopfpunkt(kopf, y > 0 ? 's' : 'w');
    } else if (belegt){
        return NeuerKopfpunkt(kopf, 'w');
    } else {
        return NeuerKopfpunkt(kopf, x > 0 ? 'd' : 'a');
    }

    } else {
        neukopf = NeuerKopfpunkt(kopf, y > 0 ? 's' : 'w');
        if (NPC.gibschlange().size() > 1
            && neukopf.px == NPC.gibschlange()[1].x
            && neukopf.py == NPC.gibschlange()[1].y) {
                belegt = true;
        }

        if (belegt && x!=0) {
            return NeuerKopfpunkt(kopf, x > 0 ? 'd' : 'a');
        } else if (belegt){
            return NeuerKopfpunkt(kopf, 'a');
        } else {
            return NeuerKopfpunkt(kopf, y > 0 ? 's' : 'w');
        }
    }
}

bool Spielzustand::NPCKollision(const Point2d& ziel) { //Kollision mit der NPC Schlange
    for (int i = 1; i < NPC.gibschlange().size(); i++) {
        if (ziel.px == NPC.gibschlange()[i].x
            && ziel.py ==NPC.gibschlange()[i].y) {
            return true;
            }
    }

    for(int i = 1; i < python.gibschlange().size(); i++){
        if (ziel.px == python.gibschlange()[i].x
        && ziel.py ==python.gibschlange()[i].y) {
            return true;
        }
    }
    return false;
}

Point2d Spielzustand::NeuerKopfpunkt(Schlangenglied kopf, char r) { //rechnet Neuen Kopfpunkt für beliebige Schlange
    Point2d neu;
    neu.px = kopf.x;
    neu.py = kopf.y;

    if (r == 'w') neu.py -= 1;
    if (r == 's') neu.py += 1;
    if (r == 'a') neu.px -= 1;
    if (r == 'd') neu.px += 1;

    if (neu.px < 1) {
        neu.px = spielbreite ;
    }
    if (neu.px > spielbreite ) {
        neu.px = 1;
    }
    if (neu.py < 1) {
        neu.py = spielhoehe ;
    }
    if (neu.py > spielhoehe ) {
        neu.py = 1;
    }
    return neu;
}

bool Spielzustand::gameOverDurchKollision(const Point2d &kopf) { //Kollisionsüberprüfung von Der Spielerschlange
    int schlangengroesse = python.gibschlange().size();
    int npcschlangengroesse = NPC.gibschlange().size();
    if (!gegessen) {
        schlangengroesse = schlangengroesse-1;
    }
    if (!npcgegessen) {
        npcschlangengroesse = npcschlangengroesse-1;
    }
    for (int i = 1; i < schlangengroesse; i++) {
        if (python.gibschlange()[i].x == kopf.px &&
            python.gibschlange()[i].y == kopf.py)
            return true;
    }
    for (int j = 1; j < npcschlangengroesse; j++) {
        if (NPC.gibschlange()[j].x == kopf.px
            && NPC.gibschlange()[j].y == kopf.py) {
            return true;
        }
    }
    return false;
}



void Spielzustand::spielschritt(const char &eingabe) { //Rundenbasierter Spielschritt
    if (eingabe == 'q') {
        gameOver = true;
        return;
    }

    Schlangenglied kopf = python.gibschlange()[0];

    Point2d neuerKopf = NeuerKopfpunkt(kopf, eingabe);

    bool npclebt = !NPC.gibschlange().empty();
    Point2d npcneuerKopf;

    if (npclebt) {
        npcneuerKopf = berechneNPCBewegung();
    }

    if (gameOverDurchKollision(neuerKopf)) {
        gameOver = true;
        return;
    }


    if (npclebt && NPCKollision(npcneuerKopf)) {
        NPC.gibschlange().clear();
        NPC.erhoeheleben();
        npclebt = false;
        npcgegessen = false;

    }

    if (npclebt
        && neuerKopf.px == npcneuerKopf.px
        && neuerKopf.py == npcneuerKopf.py) {

        NPC.gibschlange().clear();
        NPC.erhoeheleben();
        npclebt = false;
        npcgegessen = false;

    }

    python.gibschlange().insert(python.gibschlange().begin(),
                                 Schlangenglied(neuerKopf.px, neuerKopf.py));

    if (gegessen) {
        gegessen = false;
    } else {
        python.gibschlange().pop_back();
    }
    if (npclebt) {
        NPC.gibschlange().insert(NPC.gibschlange().begin(),
                                Schlangenglied(npcneuerKopf.px, npcneuerKopf.py));
        if (npcgegessen) {
            npcgegessen = false;
        } else {
            NPC.gibschlange().pop_back();
        }
    }

    if (neuerKopf.px == futter.px && neuerKopf.py == futter.py) {
        gegessen = true;
        punktzahl+= 10;
        neuesFutter();
    }

    if (npclebt
        && npcneuerKopf.px == futter.px
        && npcneuerKopf.py == futter.py) {
        npcgegessen = true;
        neuesFutter();
    }

    if (NPC.gibschlange().empty()) {
        neuerNPC();
    }

}