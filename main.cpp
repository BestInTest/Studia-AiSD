#include <iostream>
#include <string>

using std::string;

struct Lemur {
    string name; // char name[16];
    char points = 0;
};

// Jednokierunkowa lista cykliczna
class Lista {
private:
    struct Node {
        Lemur val;
        Node* next;
        Node(const Lemur& v, Node* nx=nullptr) : val(v), next(nx) {}
    };
    Node* head; // pierwszy element (glowa)
    Node* tail; // ostatni element (ogon)
    unsigned int n;
    Node* node_at(int p) {
        Node* cur = head;
        for (int i=0; i<p && cur; ++i) cur = cur->next;
        return cur; // nullptr jeśli poza zakresem
    }
    Node* node_before(int p) {
        if (p == 0) return nullptr;
        return node_at(p-1);
    }

public:
    Lista() : head(nullptr), tail(nullptr), n(0) {}
    ~Lista() {
        while (!empty()) pop_front();
    }
    /*
    ~Lista() {
        Node* cur = head;
        while (cur) {
            Node* nx = cur->next;
            delete cur;
            cur = nx;
        }
    }*/
    bool empty() { return n == 0; }
    Lemur front() {
        // zalozenie: lista niepusta
        return head->val;
    }
    Lemur back() {
        // zalozenie: lista niepusta
        return tail->val;
    }
    void push_front(Lemur x) {
        Node* nowy = new Node(x, head);
        if (!head) {
            head = tail = nowy;
            nowy->next = nowy;
        } else {
            head = nowy;
            tail->next = head; // ogon wskazuje na nowa glowe
        }
        ++n;
    }
    void push_back(Lemur x) {
        Node* nowy = new Node(x);
        if (!head) { // pusta lista
            head = tail = nowy;
            nowy->next = nowy; //cykl 1-elementowy
        } else {
            tail->next = nowy; // dopinamy na ogon
            tail = nowy;
            tail->next = head; // domknij cykl
        }
        ++n;
    }
    void pop_front() {
        // zal.: n > 0
        if (head == tail) {
            delete head;
            head = tail = nullptr;
            n = 0;
            return;
        }
        Node* del = head;
        head = head->next;
        tail->next = head;
        delete del;
        --n;
    }
    void pop_back() {
        //zal.: n > 0
        if (head == tail) {
            delete tail;
            head = tail = nullptr;
            n = 0;
            return;
        }
        Node* prev = head;
        while (prev->next != tail) prev = prev->next; // O(n)
        delete tail;
        tail = prev;
        tail->next = head;
        --n;
    }
    /*
    * "insert/erase działają jak wcześniej, ale pamiętaj o utrzymaniu
    * tail->next=head."
    */
    void insert(int p, Lemur x) {
        if (p > n) throw "Zly indeks"; //dopuszczamy p == n (na koniec)
        if (p == 0) { push_front(x); return; }
        if (p == n) { push_back(x); return; }
        Node* prev = node_before(p); //O(p)
        if (!prev || !prev->next) throw "Zly indeks";
        Node* nowy = new Node(x,prev->next);
        prev->next = nowy;
        ++n;
    }
    void erase(int p) {
        if (p >= n) throw "Zly indeks";
        if (p == 0) { pop_front(); return; }
        Node* prev = node_before(p); // O(p)
        Node* del = prev->next;
        prev->next = del->next;
        if (del == tail) tail = prev; // aktualizacja ogona
        delete del;
        --n;
    }
    int first() { return n == 0 ? 0u : 0u; }
    int last() { return n == 0 ? 0u : (n-1); }
    int next(int p) {
        //if (p+1 >= n) throw "Brak nastepnika";
        if (p+1 >= n) return 0; // powrót na początek bo lista cykliczna
        return p+1;
    }
    Lemur& at(int p) {
        if (p >= n) throw "Zly indeks";
        Node* nd = node_at(p); // O(p)
        return nd->val;
    }
};

Lemur getTopLemur(Lista& lemury);

int main() {
    //std::ios_base::sync_with_stdio(false);
    //std::cout.tie(nullptr);
    //std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::cin.ignore();

    Lista lemury;
    string name;

    while (n--) {
        std::cin >> name;
        Lemur l;
        l.name = name;
        lemury.push_back(l);
    }

    int index = -1;
    char op = '\0';

    while (std::cin >> op) {
        if (op == 'X') {
            break;
        }

        index = lemury.next(index);

        if (op == 'R') {
            index = lemury.next(index);
            int points;
            std::cin >> points;
            lemury.at(index).points = (char) points;
            continue;
        }

        if (op == 'J') {
            index = lemury.next(index);
            Lemur newLemur;
            std::cin >> newLemur.name;
            lemury.insert(index, newLemur);
            continue;
        }

        if (op == 'L') {
            lemury.erase(index);
            index = lemury.next(index - 1); // dostosuj indeks po usunięciu
            continue;
        }
    }

    Lemur topLemur = getTopLemur(lemury);
    std::cout << topLemur.name << " " << (int) topLemur.points << std::endl;
    return 0;
}

Lemur getTopLemur(Lista& lemury) {
    Lemur topLemur;
    char maxPoints = 0;

    for (int i = 0; i <= lemury.last(); i++) {
        if (lemury.next(i) == 0) break; // zapobiega przekroczeniu zakresu w cyklicznej liście
        Lemur& currentLemur = lemury.at(i);
        if (currentLemur.points > maxPoints) {
            maxPoints = currentLemur.points;
            topLemur = currentLemur;
        }
    }
    return topLemur;
}