#include <iostream>
#include <string>

using std::string;

struct Animal {
    string type; // gatunek
    int weight = 0;
    string name;
};

string animalTypes[] = {"bizon", "ara", "nosorozec", "hipopotam", "szympans", "gnu", "paw", "zebra"};
void ile();
void ros();
void mal();
Animal resolveAnimal(const string& line);
int stoi(string& s);

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    int n;
    string linia;
    std::cin >> n;
    std::cin.ignore();
    Animal arr[n];

    string nextOperation;
    for (int i = 0; i < n; i++) {
        //naśladować insertion sort - wstawiać od razu w odpowiednie miejsce zamiast sortować przy każdej komendzie
        //ewentualnie po dodaniu sortować od razu (i ustawiać flagę??)
        std::getline(std::cin, linia);
        Animal animal = resolveAnimal(linia);
    }
}

void ile() {

}

//nie warto sortować jak jest ros
void ros() {

}

void mal() {

}

Animal resolveAnimal(const string& line) {
    Animal animal; // TODO: zainicjować?
    string word;
    bool foundFlag = false;
    int counter = 0;

    for (char c : line) {
        //rozpoznawanie gatunku, nazwy i wagi
        if (foundFlag) {
            foundFlag = false;
            word = "";

            if (counter == 0) {
                animal.type = word;
            } else if (counter == 1) {
                animal.weight = stoi(word);
            } else if (counter == 2) {
                animal.name = word;
                break;
            }
        } else {
            if (isspace(c)) {
                foundFlag = true;
            } else {
                word += c;
                counter++;
            }
        }
    }
    return animal;
}

int stoi(string& s) {
    int result = 0;
    for (char c : s) {
        result = result * 10 + (c - '0');
    }
    std::cout << result << "\n";
    return result;
}