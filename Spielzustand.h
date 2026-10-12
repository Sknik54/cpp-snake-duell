//
// Created by semih on 11.12.2025.
//

#ifndef PROJEKT4SNAKE_SPIELZUSTAND_H
#define PROJEKT4SNAKE_SPIELZUSTAND_H
#include "std_lib_inc.h"
#include "Schlangenglied.h"
#include "Point2d.h"
#include "Schlange.h"


class Spielzustand {
public:
    int spielbreite;
    int spielhoehe;
    Schlange python;
    Schlange NPC;
    int punktzahl;
    bool gameOver;
    bool gegessen;
    bool npcgegessen;
    Point2d futter;


    void neuesFutter();

    bool neuerNPC();

    bool gameOverDurchKollision(const Point2d &kopf);

    void spielschritt(const char &eingabe);

    Point2d NeuerKopfpunkt(Schlangenglied kopf, char r);

    Point2d berechneNPCBewegung();

    bool NPCKollision(const Point2d& ziel);

};


#endif //PROJEKT4SNAKE_SPIELZUSTAND_H