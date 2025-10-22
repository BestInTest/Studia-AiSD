#include <iostream>
#include <string>

using std::string;

struct Animal {
    string type; // gatunek
    int weight = 0;
    string name;
};

void ile(string& animalType, Animal arr[], int size);
void ros(string& animalType, Animal arr[], int size);
void mal(string& animalType, Animal arr[], int size);
void addAndSort(Animal animal, Animal arr[], int& size);
void resolveAction(const string& line, string& action, string& arg);
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
    Animal arr[n]; // sus
    int currentSize = 0;

    for (int i = 0; i < n; i++) {
        //naśladować insertion sort - wstawiać od razu w odpowiednie miejsce zamiast sortować przy każdej komendzie
        //ewentualnie po dodaniu sortować od razu (i ustawiać flagę??)
        std::getline(std::cin, linia);
        string action;
        string arg;
        resolveAction(linia, action, arg);
        if (action == "ile") {
            //std::cout << "ile" << "\n";
            ile(arg, arr, currentSize);
        } else if (action == "ros") {
            //std::cout << "ros" << "\n";
            ros(arg, arr, currentSize);
        } else if (action == "mal") {
            //std::cout << "mal" << "\n";
            mal(arg, arr, currentSize);
        } else {
            //std::cout << "add" << "\n";
            Animal animal = resolveAnimal(linia);
            addAndSort(animal, arr, currentSize);
        }
    }
}

void ile(string& animalType, Animal arr[], int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i].type == animalType) {
            count++;
        }
    }
    //std::cout << "ile " << animalType << ": " << count << "\n";
    std::cout << count << "\n";
}

void ros(string& animalType, Animal arr[], int size) {
    //standardowe wypisywanie bo sortowanie jest od najmniejszej masy do największej
    bool foundAntyhing = false;
    for (int i = 0; i < size; i++) {
        if (arr[i].type == animalType) {
            std::cout << arr[i].name << " ";
            foundAntyhing = true;
        }
    }
    if (!foundAntyhing) {
        std::cout << "-";
    }
    std::cout << "\n";
}

void mal(string& animalType, Animal arr[], int size) {
    //wypisywanie ale od tyłu
    bool foundAntyhing = false;
    for (int i = size - 1; i >= 0; i--) {
        if (arr[i].type == animalType) {
            std::cout << arr[i].name << " ";
            foundAntyhing = true;
        }
    }
    if (!foundAntyhing) {
        std::cout << "-";
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