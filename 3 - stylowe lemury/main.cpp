#include <iostream>
#include <string>

using std::string;

struct Lemur {
    string name; // char name[16];
    int points = 0;
};

// Dwukierunkowa lista cykliczna
class Lista {
public:
    struct Node {
        Lemur val;
        Node* next;
        Node* prev;
        Node(const Lemur& v, Node* nx=nullptr, Node* pv=nullptr) : val(v), next(nx), prev(pv) {}
    };
private:
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
        Node* nowy = new Node(x, /*next*/head, /*prev*/nullptr);
        if (!head) {
            head = tail = nowy;
            nowy->next = nowy;
        } else {
            head->prev = nowy;
            head = nowy;
            tail->next = head; // ogon wskazuje na nowa glowe
        }
        ++n;
    }
    void push_back(Lemur x) {
        Node* nowy = new Node(x, /*next*/nullptr, /*prev*/tail);
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
        head->prev = tail; // utrzymaj dwukierunkowe powiązania w liście cyklicznej
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
        Node* del = tail;
        Node* prev = tail->prev;
        if (!prev) {
            // fallback jeśli prev nie był utrzymywany: O(n)
            prev = head;
            while (prev->next != tail) prev = prev->next;
        }
        prev->next = head;
        head->prev = prev;
        tail = prev;
        delete del;
        --n;
    }
    /*
    * "insert/erase działają jak wcześniej, ale pamiętaj o utrzymaniu
    * tail->next=head."
    */
    void insert(int p, Lemur x) {
        if (p > n) throw "Zly indeks"; // dopuszczamy p == n (na koniec)
        if (p == 0) { push_front(x); return; }
        if (p == n) { push_back(x); return; }
        Node* prev = node_before(p); // O(p)
        if (!prev || !prev->next) throw "Zly indeks";
        Node* next = prev->next;
        Node* nowy = new Node(x, next, prev);
        prev->next = nowy;
        next->prev = nowy;
        ++n;
    }
    // Wstawia nowy węzeł przed podanym `pos`. Jeśli `pos == nullptr` => push_back.
    void insert_before(Node* pos, const Lemur& x) {
        if (!pos) { // traktujemy jako dodanie na koniec
            push_back(x);
            return;
        }
        if (!head) { // pusta lista
            Node* nowy = new Node(x, nullptr, nullptr);
            head = tail = nowy;
            nowy->next = nowy;
            nowy->prev = nowy;
            ++n;
            return;
        }
        if (pos == head) { // wstawienie przed głową -> nowa głowa
            Node* nowy = new Node(x, head, tail);
            head->prev = nowy;
            tail->next = nowy;
            head = nowy;
            ++n;
            return;
        }
        // przypadek ogólny
        Node* prev = pos->prev;
        Node* nowy = new Node(x, pos, prev);
        prev->next = nowy;
        pos->prev = nowy;
        ++n;
    }
    void erase(int p) {
        if (p >= n) throw "Zly indeks";
        if (p == 0) { pop_front(); return; }
        Node* prev = node_before(p); // O(p)
        Node* del = prev->next;
        Node* next = del->next;
        // połącz prev z next
        prev->next = next;
        if (next) next->prev = prev;
        // jeśli usuwamy ogon, zaktualizuj tail i utrzymaj cykl
        if (del == tail) {
            tail = prev;
            tail->next = head;
            head->prev = tail;
        }
        delete del;
        --n;
    }
    void erase(Node* del) {
        if (!del || !head) throw "Zly indeks";
        // jedyny element
        if (head == tail && del == head) {
            delete head;
            head = tail = nullptr;
            n = 0;
            return;
        }
        Node* prev = del->prev;
        Node* next = del->next;
        // fallback jeśli prev/next nie były utrzymywane
        if (!prev) {
            prev = head;
            while (prev->next != del) prev = prev->next;
        }
        if (!next) {
            next = head;
            while (next->prev != del) next = next->next;
        }
        // połącz prev z next
        prev->next = next;
        next->prev = prev;
        // zaktualizuj head/tail jeśli usuwamy na końcach
        if (del == head) head = next;
        if (del == tail) tail = prev;
        // utrzymaj cykl
        tail->next = head;
        head->prev = tail;
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
    Node* getHead() { return head; }
    Node* getTail() { return tail; }
};

Lemur getBetter(const Lemur& lemur1, const Lemur& lemur2);

void printList(Lista& lemury) {
    for (int i = 0; i <= lemury.last(); i++) {
        Lemur& l = lemury.at(i);
        std::cout << l.name << " " << (int) l.points << "\n";
    }
    std::cout << "--------------------" << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::cin.ignore();

    Lemur bestLemur;
    Lista lemury;
    string name;

    while (n--) {
        std::cin >> name;
        Lemur l;
        l.name = name;
        lemury.push_back(l);
    }

    Lista::Node* curr = lemury.getTail();
    char op = '\0';

    while (std::cin >> op) {
        if (op == 'X') {
            break;
        }
        //printList(lemury);

        //if (!curr) curr = lemury.getHead();
        //if (!curr) break;
        curr = curr->next;

        if (op == 'R') {
            Lemur& currLemur = curr->val;
            int points;
            std::cin >> points;
            currLemur.points += (char) points;

            // Aktualizacja najlepszego lemura
            bestLemur = getBetter(bestLemur, currLemur);
            continue;
        }

        if (op == 'J') {
            Lemur newLemur;
            std::cin >> newLemur.name;
            lemury.insert_before(curr, newLemur);
            curr = curr->prev; // dostosuj curr do nowo wstawionego lemura
            continue;
        }

        if (op == 'L') {
            lemury.erase(curr);
            //index -= 1; // dostosuj indeks po usunięciu
            continue;
        }
    }

    std::cout << bestLemur.name << " " << (int) bestLemur.points << "\n";
    return 0;
}

Lemur getBetter(const Lemur& lemur1, const Lemur& lemur2) {
    if (lemur1.points > lemur2.points) {
        return lemur1;
    }
    if (lemur2.points > lemur1.points) {
        return lemur2;
    }
    // Równa liczba punktów, zwracamy pierwszego
    return lemur1;
}
