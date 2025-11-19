#include <iostream>

using std::string;

struct Node {
    int val;

    // Licznik dzieci aby pilnować limitu 3
    int child_count = 0;

    Node* next = nullptr; // Wskaźnik na następnego brata (lista jednokierunkowa)

    Node* child_head = nullptr; // Pierwsze dziecko
    Node* child_tail = nullptr; // Ostatnie dziecko


    void add_child(Node* child) {
        if (child_tail == nullptr) {
            child_head = child_tail = child;
        } else {
            child_tail->next = child;
            child_tail = child;
        }
        child_count++; // Trzeba zwiększyc licznik po dodaniu
    }

    Node(int v) {
        this->val = v;
        this->child_count = 0;
        this->next = nullptr;
        this->child_head = nullptr;
        this->child_tail = nullptr;
    }
};

class MyStack {
private:
    int* data;
    int max_size;
    int _size; // aktualny rozmiar stosu

public:
    MyStack() : MyStack(128) {
    }
    MyStack(int n) {
        data = new int[n];
        max_size = n;
        _size = 0;
    }
    ~MyStack() {
        delete[] data;
    }

    int size() {
        return _size;
    }

    int top() {
        //mozna dodac sprawdzanie czy stos nie jest pusty
        return data[_size - 1];
    }

    void pop() {
        _size--;
    }

    bool empty() {
        return _size == 0;
    }

    // do czyszczenia stosu przed nowym transportem
    void clear() {
        _size = 0;
    }

    void push(int v) {
        if (_size == max_size) {
            max_size *= 2;
            int* new_data = new int[max_size];
            //kopiowanie
            for (int i = 0; i < _size; i++) {
                new_data[i] = data[i];
            }

            delete[] data;
            data = new_data;
        }
        data[_size] = v;
        _size++;
    }
};

// Prosta kolejka potrzebna do budowania drzewa (FIFO)
class MyQueue {
private:
    Node** data;
    int capacity;
    int q_head;
    int q_tail;

public:
    MyQueue() {
        capacity = 128; // Zaczynamy od małej wartości
        data = new Node*[capacity];
        q_head = 0;
        q_tail = 0;
    }

    ~MyQueue() {
        delete[] data;
    }

    void push(Node* node) {
        // Jeśli tablica jest pełna zwiększamy pojemność
        if (q_tail == capacity) {
            if (q_head > capacity / 2) {
                int size = q_tail - q_head;
                for (int i = 0; i < size; i++) {
                    data[i] = data[q_head + i];
                }
                q_head = 0;
                q_tail = size;
            } else {
                // Zwiększamy rozmiar tablicy
                capacity *= 2;
                Node** new_data = new Node*[capacity];
                for (int i = q_head; i < q_tail; i++) {
                    new_data[i] = data[i];
                }
                delete[] data;
                data = new_data;
            }
        }
        data[q_tail++] = node;
    }

    void pop() {
        q_head++;
    }

    Node* front() {
        return data[q_head];
    }

    bool empty() {
        return q_head == q_tail;
    }

    void clear() {
        q_head = 0;
        q_tail = 0;
    }
};

void print_postorder(Node* node) {
    if (node == nullptr) return;

    // iteracja po liście dzieci (od child_head do child_tail)
    Node* curr = node->child_head;
    while (curr != nullptr) {
        print_postorder(curr);
        curr = curr->next;
    }

    // Na końcu wypisujemy rodzica
    std::cout << node->val << " ";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    int t; // liczba transportów
    std::cin >> t;

    MyStack stack = MyStack(1024);
    MyQueue queue;
    Node* root = nullptr;

    // pętla po wszystkich transportach
    while(t--) {
        stack.clear(); // Czyścimy stos przed nowym transportem

        int transport;
        // Czytanie transportu aż będzie 0
        while (std::cin >> transport && transport != 0) {
            stack.push(transport);
        }


        // Jeżeli nie ma korzenia to trzeba go stworzyć
        if (root == nullptr) {
            root = new Node(stack.top());
            stack.pop();
            queue.push(root); // Dodajemy korzeń do kolejki budowy
        }

        while (!stack.empty()) {
            int val = stack.top();
            stack.pop();

            Node* newNode = new Node(val);

            // Szukamy w kolejce rodzica który ma wolne miejsce (ponizej 3 dzieci)
            while (!queue.empty() && queue.front()->child_count == 3) {
                queue.pop(); // Ten węzeł jest już pełny więc go zdejmujemy
            }

            Node* parent = queue.front(); // Pobieramy rodzica
            parent->add_child(newNode); // Dodajemy nowe dziecko
            queue.push(newNode); // Dodajemy nowe dziecko do kolejki
        }

        /*
         * Jesli po zakonczeniu transportu bieżący rodzic w kolejce jest napoczęty
         * (ma 1 lub 2 dzzieci) to uznajemy go za zamkniętego.
         * Następny transport musi się zacząć od nowego (pustego) węzła.
        */
        if (!queue.empty()) {
            Node* frontNode = queue.front();
            if (frontNode->child_count > 0 && frontNode->child_count < 3) { // Jesli ma 1 lub 2 dzieci to usuwamy go z kolejki
                queue.pop();
            }
        }
    }

    print_postorder(root);
}