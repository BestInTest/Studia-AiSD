#include <iostream>
#include <vector>
#include <string>

using namespace std;

void initTables();
int getAnimalIndex(string& name, int& n);

struct Animal {
    string name;
    int minSlot;
    int maxSlot;
    string allowedStages;

    // Do wyników
    int assignedSlot;
    char assignedStage;
};

vector<Animal> zoo;
bool conflicts[20][20];
int schedule[25][3]; // [slot][scena index], wartość to id zwierzęcia lub -1


bool solve(int animalId, int& n) {
    if (animalId == n) {
        // udało się przypisać miejsca wszystkim zwierzętom
        return true;
    }

    Animal& current = zoo[animalId];

    // Sprawdzanie wszystkich możliwych slotow
    for (int slot = current.minSlot; slot <= current.maxSlot; slot++) {

        // Sprawdzanie scen
        string sceneStr = "ABC";
        for (int scene = 0; scene < 3; scene++) {
            char sceneChar = sceneStr[scene];

            // Sprawdzamy czy zwierze może wystąpić na tej scenie
            if (current.allowedStages.find(sceneChar) == string::npos) { //todo: może zmienić?
                continue;
            }

            // Sprawdzamy czy miejsce jest wolne
            if (schedule[slot][scene] != -1) {
                continue; // Zajete przez kogoś innego
            }

            // Sprawdzanie czy jest konflikt z innymi zwierzętami
            bool conflictFound = false;
            for (int prev = 0; prev < animalId; prev++) {
                if (conflicts[animalId][prev] && zoo[prev].assignedSlot == slot) {
                    conflictFound = true;
                    break;
                }
            }

            if (conflictFound) {
                continue;
            }

            // Nie ma konfliktu więc znaleziono miejsce
            schedule[slot][scene] = animalId;
            current.assignedSlot = slot;
            current.assignedStage = sceneChar;

            // Rekurencja dla następnego zwierzecia
            if (solve(animalId + 1, n)) {
                return true;
            }

            // Cofamy wybór jeśli droga nie prowadzi do rozwiązania
            schedule[slot][scene] = -1;
            current.assignedSlot = 0;
            current.assignedStage = ' ';
        }
    }

    // Nie udało się znaleźć miejsca
    return false;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    initTables();

    int n; // liczba zwierząt
    int m; // liczba ograniczeń między zwierzętami
    int s; // liczba slotów czasowych

    cin >> n >> m >> s;

    // Wczytywanie zwierząt
    for (int i = 0; i < n; i++) {
        Animal a;
        cin >> a.name >> a.minSlot >> a.maxSlot >> a.allowedStages;
        a.assignedSlot = 0;
        zoo.push_back(a);
    }

    // Wczytywanie ograniczeń
    for (int i = 0; i < m; i++) {
        string name1, separator, name2;
        cin >> name1 >> separator >> name2;

        int id1 = getAnimalIndex(name1, n);
        int id2 = getAnimalIndex(name2, n);

        // Zapisujemy konflikt w obie strony
        if (id1 != -1 && id2 != -1) {
            conflicts[id1][id2] = true;
            conflicts[id2][id1] = true;
        }
    }

    if (solve(0, n)) {
        // Wypisujemy wynik w kolejności wejścia
        for (int i = 0; i < n; i++) {
            cout << zoo[i].name << " " << zoo[i].assignedSlot << " " << zoo[i].assignedStage << "\n";
        }
    } else {
        cout << "NIE";
    }

    return 0;
}

void initTables() {
    // Pusta tablica konfliktów
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            conflicts[i][j] = false;
        }
    }

    //Puste harmonogramy
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 3; j++) {
            schedule[i][j] = -1;
        }
    }
}

int getAnimalIndex(string& name, int& n) {
    for (int i = 0; i < n; i++) {
        if (zoo[i].name == name) {
            return i;
        }
    }
    return -1;
}