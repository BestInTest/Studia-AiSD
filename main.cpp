#include <iostream>
#include <string>

using std::string;

class Lista {
private:
    struct Node {
        typ_danych val;
        Node* next;
        Node(const typ_danych& v, Node* nx=nullptr) : val(v), next(nx) {}
    };
    Node* head; // pierwszy element (glowa)
    Node* tail; // ostatni element (ogon)
    unsigned int n;
    Node* node_at(pozycja p) {
        Node* cur = head;
        for (pozycja i=0; i<p && cur; ++i) cur = cur->next;
        return cur; // nullptr jeśli poza zakresem
    }
    Node* node_before(pozycja p) {
        if (p==0) return nullptr;
        return node_at(p-1);
    }

public:
    Lista() : head(nullptr), tail(nullptr), n(0) {}
    ~Lista() {
        Node* cur = head;
        while (cur) {
            Node* nx = cur->next;
            delete cur;
            cur = nx;
        }
    }
    bool empty() { return n == 0; }
    typ_danych Lista::front() {
        // zalozenie: lista niepusta
        return head->val;
    }
    typ_danych Lista::back() {
        // zalozenie: lista niepusta
        return tail->val;
    }
    void Lista::push_front(typ_danych x) {
        Node* nowy = new Node(x, head);
        head = nowy;
        if (!tail) tail = nowy; // jesli wczesniej pusto
        ++n;
    }
    void Lista::push_back(typ_danych x) {
        Node* nowy = new Node(x);
        if (!head) { // pusta lista
            head=tail=nowy;
        } else {
            tail->next= nowy; // dopinamy na ogon
            tail=nowy;
        }
        ++n;
    }
    void pop_front() {
        // zal.: n > 0
        Node* del = head;
        head = head->next;
        if (!head) tail = nullptr; // usunieto jedyny element
        delete del;
        --n;
    }
    void pop_back() {
        //zal.: n > 0
        if (head==tail) { // jeden element
            delete head;
            head = tail = nullptr;
            n = 0;
            return;
        }
        //znajdz przedostatni(O(n))
        Node* prev = head;
        while (prev->next != tail) prev = prev->next;
        delete tail;
        tail = prev;
        tail->next = nullptr;
        --n;
    }
    void insert(pozycja p, typ_danych x) {
        if (p > n) throw "Zly indeks"; //dopuszczamy p == n (na koniec)
        if (p == 0) { push_front(x); return; }
        if (p == n) { push_back(x); return; }
        Node* prev = node_before(p); //O(p)
        if (!prev || !prev->next) throw "Zly indeks";
        Node* nowy = new Node(x,prev->next);
        prev->next = nowy;
        ++n;
    }
    void Lista::erase(pozycja p) {
        if (p >= n) throw "Zly indeks";
        if (p == 0) { pop_front(); return; }
        Node* prev = node_before(p); // O(p)
        Node* del = prev->next;
        prev->next = del->next;
        if (del == tail) tail = prev; // aktualizacja ogona
        delete del;
        --n;
    }
    pozycja Lista::first() { return n == 0 ? 0u : 0u; }
    pozycja Lista::last() { return n == 0 ? 0u : (n-1); }
    pozycja Lista::next(pozycja p) {
        if (p+1 >= n) throw "Brak nastepnika";
        return p+1;
    }
    typ_danych& Lista::at(pozycja p) {
        if (p >= n) throw "Zly indeks";
        Node* nd = node_at(p); // O(p)
        return nd->val;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::cin.ignore();
}