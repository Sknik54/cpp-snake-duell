#include "std_lib_inc.h"
#include "Spielzustand.h"
#include "Schlange.h"
#include "Schlangenglied.h"
#include "Point2d.h"

int Spielfeld() { //lest Spielfeld ein
    int wert;
    if (!(cin >> wert)) {
        throw runtime_error("Fehler: Programm wegen fehlender Spielfeldeingabe beendet.");
    }
    if (wert < 3 || wert > 25) {
        throw out_of_range("Fehler: Eingabe ausserhalb des zulaessigen Bereiches.");
    }
    return wert;
}

char Steuereingabe() { //Steuerung der Spielerschlange
    char eingabe;
    cin >> eingabe;

    switch (eingabe) {
        case 'w': case 'a': case 's': case 'd': case 'q':
            return eingabe;
        default:
            throw invalid_argument(
                "Fehler: Unzulaessige Eingabe! Nutze w, a, s, d zum Bewegen oder q zum Beenden."
            );
    }
}

vector<vector<string>> Spielfeldaufbau(Spielzustand& spiel) { //baut Spielfeld auf
    vector<vector<string>> feld(spiel.spielhoehe + 2,
        vector<string>(spiel.spielbreite + 2));

    for (int i = 0; i < spiel.spielbreite + 2; i++) {
        feld[0][i] = "-";
        feld[spiel.spielhoehe + 1][i] = "-";
    }

    for (int i = 0; i < spiel.spielhoehe + 2; i++) {
        feld[i][0] = "|";
        feld[i][spiel.spielbreite + 1] = "|";
    }

    feld[spiel.futter.py][spiel.futter.px] = "#";

    for (int i = 1; i < spiel.python.gibschlange().size(); i++) {
        if (feld[spiel.python.gibschlange()[i].y][spiel.python.gibschlange()[i].x] == "") {
            feld[spiel.python.gibschlange()[i].y]
                [spiel.python.gibschlange()[i].x] = "o";
        }
    }

    if (!spiel.python.gibschlange().empty()) {
        feld[spiel.python.gibschlange()[0].y]
            [spiel.python.gibschlange()[0].x] = "O";
    }

    if (!spiel.NPC.gibschlange().empty()) {
        feld[spiel.NPC.gibschlange()[0].y][spiel.NPC.gibschlange()[0].x] = "X";
    }

    for (int i = 1; i < spiel.NPC.gibschlange().size(); i++) {
        if (feld[spiel.NPC.gibschlange()[i].y][spiel.NPC.gibschlange()[i].x] == "") {
            feld[spiel.NPC.gibschlange()[i].y]
                [spiel.NPC.gibschlange()[i].x] = "x";
        }
    }

    return feld;
}

int main() {
    Spielzustand s;
    s.gameOver = false;
    s.punktzahl = 0;
    s.gegessen = false;
    s.npcgegessen = false;

    try {
        s.spielbreite = Spielfeld();
        s.spielhoehe  = Spielfeld();
    } catch (exception& e) {
        cout << e.what() << "\n";
        return 0;
    }

    int kopfX = (s.spielbreite / 2) + 1;
    int kopfY = (s.spielhoehe / 2) + 1;

    s.python.gibschlange().push_back(Schlangenglied(kopfX, kopfY));

    s.futter.px = ((17 * kopfX) % s.spielbreite) + 1;
    s.futter.py = ((13 * kopfY) % s.spielhoehe) + 1;

    s.neuerNPC();

    auto feld_init = Spielfeldaufbau(s);
    for (int i = 0; i < feld_init.size(); i++) {
        for (int j = 0; j < feld_init[i].size(); j++) {
            if (feld_init[i][j] == "") cout << " ";
            else cout << feld_init[i][j];
        }
        cout << "\n";
    }
    cout << "Punktzahl: " << s.punktzahl << "\n";

    while (!s.gameOver) {
        char eingabe;
        while (true) {
            try {
                eingabe = Steuereingabe();
                break;
            } catch (invalid_argument& e) {
                cout << e.what() << "\n";
            }
        }

        s.spielschritt(eingabe);
        if (s.gameOver) break;

        auto feld = Spielfeldaufbau(s);
        for (int i = 0; i < feld.size(); i++) {
            for (int j = 0; j < feld[i].size(); j++) {
                if (feld[i][j] == "") cout << " ";
                else cout << feld[i][j];
            }
            cout << "\n";
        }
        cout << "Punktzahl: " << s.punktzahl << "\n";
    }

    cout << "Game over! Gesamtpunktzahl: " << s.punktzahl << "\n";
    return 0;
}
