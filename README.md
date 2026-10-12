# Snake-Duell – C++-Konsolenspiel

Ein rundenbasiertes Snake-Spiel für die Konsole, das eine manuell gesteuerte Schlange gegen eine automatisch agierende NPC-Schlange antreten lässt. Das Spielfeld ist **zyklisch**: Verlassen die Schlangen eine Seite, erscheinen sie auf der gegenüberliegenden Seite wieder.

Das Projekt entstand im Rahmen einer Programmieraufgabe an der **Universität Osnabrück** (*„Snake Update: Schlangen-Duell“*). Ziel der Aufgabe war es, ein bestehendes Snake-Spiel durch Refactoring besser zu strukturieren und um eine zweite, autonom gesteuerte Schlange zu erweitern.

## Funktionen

- **Zwei Schlangen:** Spielerschlange (`O` für den Kopf, `o` für den Körper) und NPC-Schlange (`X` bzw. `x`).
- **Rundenbasierte Steuerung** über `w`, `a`, `s`, `d`; Beenden mit `q`.
- **Zyklische Spielfeldränder:** Beim Überschreiten eines Randes wird die Bewegung auf der gegenüberliegenden Seite fortgesetzt.
- **NPC-Bewegungslogik:** Die NPC-Schlange orientiert sich an der Position des Futters (`#`) und berücksichtigt die kürzeren Wege über die Spielfeldränder.
- **Kollisionen und Respawn:** Kollisionen können das Spiel beenden oder einen Neustart der NPC-Schlange auslösen.
- **Futter und Wachstum:** Beim Fressen wächst die entsprechende Schlange; die Spielerschlange erhält **10 Punkte** pro gefressenem Futter.
- **Fehlerbehandlung:** Ungültige Eingaben werden über Exceptions behandelt.

## Technologien und Lerninhalte

- **C++20**, **CMake**, Entwicklung mit **CLion**
- Objektorientierte Modellierung (`Schlange`, `Schlangenglied`, `Spielzustand`, `Point2d`)
- `std::vector`, Klassen, Methoden und Referenzen
- Aufteilung der Spiellogik auf mehrere Header- und Quelldateien
- Konsolenein- und -ausgabe sowie Ausnahmebehandlung

## Starten

### Mit CLion

1. Das Projektverzeichnis in **CLion** öffnen.
2. CLion die `CMakeLists.txt` laden lassen.
3. Das Target **`Projekt4snake`** auswählen und starten.
4. Im Ausgabefenster zuerst die **Spielfeldbreite**, danach die **Spielfeldhöhe** eingeben (jeweils **3 bis 25**). Anschließend die Schlange mit den unten beschriebenen Tasten steuern.

**Hinweis:** Die mitgelieferte `CMakeLists.txt` setzt **CMake 4.0 oder neuer** voraus. Falls deine lokale CLion-/CMake-Version älter ist, muss die Mindestversion ggf. angepasst werden; das wurde in dieser GitHub-Aufbereitung bewusst nicht am Originalcode verändert.

### Über das Terminal

Mit kompatibler CMake-Version:

```bash
cmake -S . -B build
cmake --build build
```

Anschließend die erzeugte Anwendung `Projekt4snake` (unter Windows `Projekt4snake.exe`) aus dem Build-Verzeichnis starten. Je nach Generator liegt sie ggf. in einem Unterverzeichnis wie `Debug`.

## Steuerung

| Eingabe | Aktion |
| --- | --- |
| `w` | Nach oben |
| `a` | Nach links |
| `s` | Nach unten |
| `d` | Nach rechts |
| `q` | Spiel beenden |

Zu Spielbeginn werden Breite und Höhe eingelesen; zum Beispiel:

```text
5 4
```

Die Ausgabe zeigt das Spielfeld sowie darunter `Punktzahl: 0`. Pro gültiger Bewegung wird das Spielfeld neu berechnet und ausgegeben.

## Spielregeln

Die Spielerschlange startet nahe der Mitte des Spielfeldes. Die Position des Futters wird anhand ihrer Kopfposition berechnet. Die NPC-Schlange erhält eine durch die Aufgabenstellung festgelegte Spawnposition; ist diese belegt, werden weitere Positionen versucht.

Die NPC-Schlange bewegt sich automatisch in Richtung Futter. Treffen Schlangen auf Hindernisse, werden Kollisionen ausgewertet. Eine Kollision der Spielerschlange mit einem Schlangenkörper führt zum Spielende. Die NPC-Schlange kann dagegen nach einem Zusammenstoß erneut erscheinen. Der aktuelle Punktestand wird nach den Zügen ausgegeben.

## Projektstruktur

```text
.
├── CMakeLists.txt       # Build-Konfiguration
├── main(3).cpp          # Programmeinstieg, Eingabe und Spielfeldausgabe
├── Spielzustand.h/.cpp  # Spielzustand, Bewegung, Futter und Kollisionen
├── Schlange.h/.cpp      # Schlangenobjekt und Lebenszähler
├── Schlangenglied.h/.cpp # Einzelnes Schlangensegment
├── Point2d.h/.cpp      # Zweidimensionale Position
└── std_lib_inc.h       # Im Lehrkontext bereitgestellter Hilfsheader
```

## Stand und Hinweise

Diese Veröffentlichung bewahrt **den eingereichten C++-Quellcode unverändert**. Die README beschreibt die implementierten Funktionen anhand des Codes und der Aufgabenstellung, ist aber **kein Nachweis**, dass sämtliche Anforderungen oder automatisierten Tests erfüllt sind.

Im bereitgestellten Artemis-Export stehen die offenen und versteckten Tests bei **0/1 bestanden**. Ob sie tatsächlich fehlgeschlagen sind oder zu diesem Zeitpunkt nicht ausgeführt wurden, lässt sich daraus allein nicht sicher ableiten. Daher wird hier keine Punktzahl oder Testabdeckung behauptet.

Es gibt bekannte Unterschiede zur wörtlich vorgegebenen Konsolenausgabe: Mehrere Fehlermeldungen beginnen im Code zusätzlich mit `Fehler:`, und die Schlussmeldung verwendet `Game over!` statt `Game Over!`. Falls die genaue Ausgabe für eine erneute Abgabe relevant ist, sollte das überprüft und ggf. korrigiert werden.

> **Hinweis zur Veröffentlichung:** Die Aufgabenstellung und `std_lib_inc.h` stammen aus dem Lehrkontext. Bitte vor dem öffentlichen Hochladen die Veröffentlichungsregeln der Universität sowie die Nutzungsrechte für bereitgestellte Hilfsdateien prüfen.
