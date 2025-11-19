#include <iostream>

using std::string;

struct Node {
    int val;

    Node* next = nullptr;

    Node* child_head = nullptr;
    Node* child_tail = nullptr;

    void add_child(Node* child) {
        if (child_tail == nullptr) {
            child_head = child_tail = child;
        } else {
            child_tail->next = child;
            child_tail = child;
        }
    }

    Node(int v) {
        this->val = v;
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

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    // n element stack
    MyStack stack = MyStack(n);
    int transport;
    for (int i = 0; i < n; i++) {
        std::cout << "stack empty?: " << stack.empty();
        // czytanie aż będzie 0
        while (std::cin >> transport) {
            if (transport == 0) {
                break;
            }
            stack.push(transport);
        }

        //int v;
        //std::cin >> v;
        //stack.push(v);
    }

}
