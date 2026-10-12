//
// Created by semih on 10.12.2025.
//

#ifndef PROJEKT4SNAKE_SCHLANGE_H
#define PROJEKT4SNAKE_SCHLANGE_H
#include "std_lib_inc.h"
#include "Schlangenglied.h"
#include "Point2d.h"

class Schlange {
private:
    vector<Schlangenglied> schlange;
    int leben = 1;

public:
    void erhoeheleben();
    vector<Schlangenglied>& gibschlange();
    int gibleben();


};


#endif //PROJEKT4SNAKE_SCHLANGE_H
