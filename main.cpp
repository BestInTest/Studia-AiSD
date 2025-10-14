#include <iostream>
#include <string>
#include <sstream>

using std::string;

string normalize(string s);
string match(const string& s);
bool isVowel(char c);

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    int n;
    //char slowo[200] = {};
    string linia;
    std::cin >> n;
    std::cin.ignore();


    for (int i = 0; i < n; i++) {
        std::getline(std::cin, linia);
        linia = normalize(linia);
        //std::cout << slowo << "\n";

        std::stringstream ss(linia);
        string word;

        while (ss >> word) {

        }
    }

    return 0;



}

string normalize(string s) {
    string result;
    for (char c : s) {
        if (isalpha(c)) {
            result += tolower(c);
        }
    }
    return result;
}

string match(const string &s) {
    if (s == "ua") return "malpa";
    if (s == "rar") return "lew";
    if (s == "io") return "osiol";
    if (s == "mu") return "bizon";
    if (s == "iha") return "kon";
    if (s == "tru") return "slon";
    if (s == "grr") return "tygrys";
    if (s == "pi") return "pingwin";
    if (s == "hu") return "sowa";
    if (s == "be") return "owca";
    if (s == "kwa") return "kaczka";
    return "nie wiem";
}

bool isVowel(char c) {
    //c = tolower(c);
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y';
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