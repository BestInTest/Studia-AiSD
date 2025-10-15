#include <iostream>
#include <string>

using std::string;

//string normalize(string s);
string match(const string& s);
bool isVowel(char c);
string processSound(const string& s);
void splitWords(const string& line, string words[], int& wordCount);

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    int n;
    string linia;
    std::cin >> n;
    std::cin.ignore();

    for (int i = 0; i < n; i++) {
        std::getline(std::cin, linia);

        string words[201];
        int wordCount = 0;
        splitWords(linia, words, wordCount);

        // Dla przypadku kiedy jest pusta linijka
        if (wordCount == 0) {
            std::cout << "nie wiem\n";
            continue;
        }

        string firstAnimal = "nie wiem";
        bool consistent = true; // do oznaczania czy wszystkie slowa pasuja do tego samego zwierzaka

        // przetwarzanie dźwięku
        string processedSound = processSound(words[0]);
        if (processedSound.empty()) {
            consistent = false;
        } else {
            firstAnimal = match(processedSound);
        }

        if (firstAnimal == "nie wiem") {
            consistent = false;
        }

        // sprawdzanie pozostalych slow
        for (int j = 1; j < wordCount; j++) {
            string currentProcessed = processSound(words[j]);
            if (currentProcessed.empty()) {
                continue;
            }
            if (match(currentProcessed) != firstAnimal) {
                consistent = false;
                break;
            }
        }

        if (consistent) {
            std::cout << firstAnimal << "\n";
        } else {
            std::cout << "nie wiem\n";
        }
    }

    return 0;
}

string processSound(const string& s) {
    // normalizacja
    string normalized;
    for (char c : s) {
        if (isalpha(c)) {
            normalized += tolower(c);
        }
    }

    if (normalized.empty()) {
        return "";
    }

    // usuwanie powtarzajacych sie samogłosek
    string result;
    result += normalized[0];
    for (int i = 1; i < (int) normalized.length(); ++i) {
        //std::cout << "normalized[i]: " << normalized[i] << " normalized[i-1]: " << normalized[i-1] << "\n";

        // Jeśli aktualny znak jest samogłoską i jest taki sam jak poprzedni to go pomijamy
        if (isVowel(normalized[i]) && normalized[i] == normalized[i-1]) {
            continue;
        }
        result += normalized[i];
    }
    //std::cout << result << "\n";
    return result;
}

void splitWords(const string& line, string words[], int& wordCount) {
    wordCount = 0;
    string currentWord;
    for (char c : line) {
        if (isspace(c)) { // Koniec słowa
            //std::cout << currentWord << "\n";
            if (!currentWord.empty()) {
                words[wordCount++] = currentWord; // Dodanie stworzonego słowa do tablicy
                currentWord = "";
            }
        } else {
            // Tworzenie słowa
            currentWord += c;
        }
    }
    if (!currentWord.empty()) {
        words[wordCount++] = currentWord;
    }
}

/*
string normalize(string s) {
    string result;
    for (char c : s) {
        if (isalpha(c)) {
            result += tolower(c);
        }
    }
    return result;
}*/

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