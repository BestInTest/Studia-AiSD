#include <iostream>
#include <vector>
#include <string>

using namespace std;

void initTables();
int getAnimalIndex(string& name, int& n);
bool isAllowedOnThisStage(char stageChar, string& allowedStages);
bool isConflict(int animalId, int slot);

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
int conflictMasks[20];
int slotMasks[25]; // Maska zwierząt obecnych w danym slocie
int schedule[25][3]; // [slot][scena index], wartość to id zwierzęcia lub -1 (jeśli wolne)


bool startBacktrack(int animalId, int& n) {
    if (animalId == n) {
        // udało się przypisać miejsca wszystkim zwierzętom
        return true;
    }

    Animal& current = zoo[animalId];

    // Sprawdzanie wszystkich możliwych slotow
    for (int slot = current.minSlot; slot <= current.maxSlot; slot++) {

        if (isConflict(animalId, slot)) {
            continue; // konflikt
        }

        // Sprawdzanie scen
        string sceneStr = "ABC";
        for (int scene = 0; scene < 3; scene++) {
            char sceneChar = sceneStr[scene];

            // Sprawdzamy czy zwierze może wystąpić na danej scenie
            if (!isAllowedOnThisStage(sceneChar, current.allowedStages)) {
                continue; // Nie może
            }

            // Sprawdzamy czy miejsce (scena w tym slocie) jest wolne
            if (schedule[slot][scene] != -1) {
                continue; // Zajete
            }

            // Nie ma konfliktu ani zajętej sceny więc znaleziono miejsce
            schedule[slot][scene] = animalId;
            slotMasks[slot] |= (1 << animalId);
            current.assignedSlot = slot;
            current.assignedStage = sceneChar;

            // Rekurencja do następnego zwierzecia
            if (startBacktrack(animalId + 1, n)) {
                return true;
            }

            // Cofanie wyboru jeśli solve zwróci false
            schedule[slot][scene] = -1;
            slotMasks[slot] &= ~(1 << animalId); // and z negacją bitu aby usunąć zwierzę z maski
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

        if (id1 != -1 && id2 != -1) {
            /*
             Ustawianie bitów konfliktów dla obu zwierząt
             Poprzez przesuniecie 1 o id pozycji w lewo (1 << id)
            */
            conflictMasks[id1] |= (1 << id2);
            conflictMasks[id2] |= (1 << id1);
        }
    }

    if (startBacktrack(0, n)) {
        for (int i = 0; i < n; i++) {
            cout << zoo[i].name << " " << zoo[i].assignedSlot << " " << zoo[i].assignedStage << "\n";
        }
    } else {
        cout << "NIE";
    }

    return 0;
}

void initTables() {
    // Puste maski konfliktów
    for (int i = 0; i < 20; i++) {
        conflictMasks[i] = 0;
    }

    // Puste maski slotów
    for (int i = 0; i < 25; i++) {
        slotMasks[i] = 0;
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

bool isAllowedOnThisStage(char stageChar, string& allowedStages) {
    for (int i = 0; i < allowedStages.length(); i++) {
        if (allowedStages[i] == stageChar) {
            return true;
        }
    }
    return false;
}

bool isConflict(int animalId, int slot) {
    // Sprawdzamy czy maska slotu ma jakieś bity konfliktu dla danego zwierzęcia
    return (slotMasks[slot] & conflictMasks[animalId]) != 0;
}