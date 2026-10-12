//
// Created by semih on 10.12.2025.
//
#include "Schlange.h"
#include "std_lib_inc.h"

void Schlange::erhoeheleben() { //erhöht leben um 1
    leben++;
}

vector<Schlangenglied>& Schlange::gibschlange() { //returned vector schlange
    return schlange;
}

int Schlange::gibleben() { //returned leben
    return leben;
}
