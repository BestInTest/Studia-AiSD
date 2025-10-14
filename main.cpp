#include <iostream>
#include <string>

using std::string;

char* match(string s) {
    //for () {

    //}
}

int main() {
    int n;
    //char slowo[200] = {};
    string slowo;
    std::cin >> n;


    for (int i = 0; i < n; i++) {
        std::getline(std::cin, slowo); // sprawdzic czy string alokuje do 200 znakow
        std::cout << slowo << "\n";
    }

    return 0;



}




// najpierw sprawdzic czy poprawnie wczytujemy linie
// wielkosc liter nie ma znaczenia wiec zrobic toLower
// zrobic isAlpha i wkladac kolejne litery do nowego stringa aby dostac oczyszczonego stringa
// mmmuu != mu - liczba spolglosek musi sie zgadzac?
// muuuu == mu - samogloski moga sie powtarzac
// mu mu mmm - nadal zle bo przez mmm nie mozemy stwierdzic
// mu iha - tutaj tez nie mozemy stwierdzic
// zrobic std::getline(std::cin, string do ktorego chcemy zapisac (CHYBA max 200 znakow)); - pozniej normalizowac i podzielic na slowa lub odwrotnie - pozielic i normalizowac
// sstream? ss(string)? ss >> slowo - dzielenie na wyrazy?
// std::unordered_map:
/*
 *"mu" = "bizon"
 *ale mozna to switch-casem to rozwiązać
*/