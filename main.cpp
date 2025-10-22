#include <iostream>
#include <string>

using std::string;

struct Animal {
    string type; // gatunek
    int weight = 0; // tutaj też można spróbować zmienić z int na short
    string name; // todo: zmienić na char[11] jeśli będzie zabierać za dużo pamięci
};

Animal zoo[8][10001];
int sizes[8] = {};

int getIndexFor(string& animalType) {
    char c = animalType[0];
    switch(c) {
        case 'b': return 0; // bizon
        case 'a': return 1; // ara
        case 'n': return 2; // nosorozec
        case 'h': return 3; // hipopotam
        case 's': return 4; // szympans
        case 'g': return 5; // gnu
        case 'p': return 6; // paw
        case 'z': return 7; // zebra
        default: return -1;
    }
}

void ile(int size);
void ros(Animal arr[], int size);
void mal(Animal arr[], int size);
void addAndSort(Animal animal, Animal arr[], int& size);
void resolveAction(const string& line, string& action, string& arg);
Animal resolveAnimal(const string& line);
int stoi(string& s);

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    string linia;
    string action;
    string type;

    int n;
    std::cin >> n;
    std::cin.ignore();

    for (int i = 0; i < n; i++) {
        std::getline(std::cin, linia);
        resolveAction(linia, action, type);
        //std::cout << "Action: " << action << ", Type: " << type << "\n";

        int index = getIndexFor(type);
        Animal* arr = zoo[index];
        int& currentSize = sizes[index];
        if (action == "ile") {
            ile(currentSize);
        } else if (action == "ros") {
            ros(arr, currentSize);
        } else if (action == "mal") {
            mal(arr, currentSize);
        } else {
            Animal animal = resolveAnimal(linia);
            index = getIndexFor(animal.type); //nadpisanie zmiennej dlatego że przy dodawaniu zwierząt kolejność argumentów jest inna
            addAndSort(animal, zoo[index], sizes[index]); // tutaj jest problem
        }

        //resetowanie zmiennych
        action = "";
        type = "";
    }
}

void ile(int size) {
    std::cout << size << "\n";
}

void ros(Animal arr[], int size) {
    //standardowe wypisywanie bo sortowanie jest od najmniejszej masy do największej
    if (size == 0) {
        std::cout << "-\n";
        return;
    }

    for (int i = 0; i < size; i++) {
        std::cout << arr[i].name << " ";
    }
    std::cout << "\n";
}

void mal(Animal arr[], int size) {
    //wypisywanie ale od tyłu
    if (size == 0) {
        std::cout << "-\n";
        return;
    }

    for (int i = size - 1; i >= 0; i--) {
        std::cout << arr[i].name << " ";
    }
    std::cout << "\n";
}

void addAndSort(Animal animal, Animal arr[], int& size) {
    //wstawianie zwierzęcia w odpowiednie miejsce
    int i = size - 1;
    while (i >= 0 && arr[i].weight > animal.weight) {
        arr[i + 1] = arr[i];
        i--;
    }
    arr[i + 1] = animal;
    size++;
}

void resolveAction(const string& line, string& action, string& arg) {
    int i = 0;
    while (i < line.length() && !isspace(line[i])) {
        action += line[i];
        i++;
    }
    i++; //pomijanie spacji
    //wczytywanie drugiego argumentu
    while (i < line.length() && !isspace(line[i])) {
        arg += line[i];
        i++;
    }
}

Animal resolveAnimal(const string& line) {
    Animal animal;
    string word = "";
    int counter = 0;

    for (int i = 0; i <= line.size(); ++i) {
        char c = (i < line.size()) ? line[i] : ' ';

        if (!isspace(c)) {
            word += c;
        } else if (!word.empty()) {
            if (counter == 0) {
                animal.type = word;
            } else if (counter == 1) {
                animal.weight = stoi(word);
            } else if (counter == 2) {
                animal.name = word;
            }
            counter++;
            word = "";
        }
    }
    //std::cout << "Resolved animal: " << animal.type << " " << animal.weight << " " << animal.name << "\n";
    return animal;
}

int stoi(string& s) {
    int result = 0;
    for (char c : s) {
        result = result * 10 + (c - '0');
    }
    //std::cout << "stoi: " << result << "\n";
    return result;
}