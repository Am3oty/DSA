#include <iostream>

using namespace std;

class Node {
    public: int data;
    Node * Next;

    Node(int value): data(value),
    Next(nullptr) {}
    ~Node() {
        delete Next;
    }
};

class SingleLinkedList {
    private: Node * Head;
    Node * Last;
    int Size = 0;
    public: SingleLinkedList(int y) {
            Head = new Node(y);
            Last = Head;
            Size++;
        }

        ~SingleLinkedList() {
            delete Head;
        }

    void Append(int x) {
        Last -> Next = new Node(x);
        Last = Last -> Next;
        Size++;
    }

    void Display() {
        Node * Current = Head;
        while (Current != nullptr) {
            cout << Current -> data << endl;
            Current = Current -> Next;
        }
    }

    void Insert(int data, int position) {
        if (position < 1) {
            cout << "Invalid position!" << endl;
            return;
        }

        Node * newNode = new Node(data);

        if (position == 1) {
            if (Size == 1) {
                newNode -> Next = Head;
                Last = newNode -> Next;
                Head = newNode;
                return;
            } else if (Head == NULL) {
                Head = newNode;
                Last = newNode;
                Size++;
            } else {
                newNode -> Next = Head;
                Head = newNode;
                return;
            }
        }

        Node * Current = Head;
        for (int i = 1; i < position - 1 && Current != nullptr; ++i) {
            Current = Current -> Next;
        }

        if (Current == nullptr) {
            cout << "Position out of bounds!" << endl;
            delete newNode;
            return;
        }

        newNode -> Next = Current -> Next;
        Current -> Next = newNode;

        if (newNode -> Next == nullptr) {
            Last = newNode;
        }
    }
    int LinearSearch(int ValueToSearch) {
        Node * Current = Head;
        for (int i = 1; i < Size() + 1; i++) {
            if (Current -> data == ValueToSearch)
                return i;
            else
                Current = Current -> Next;

        }

        return -1;
    }

    void Sort() {
        bool swapped;
        Node * current;
        Node * lastSorted = nullptr;

        do {
            swapped = false;
            current = Head;
            while (current -> Next != lastSorted) {

                if (current -> data > current -> Next -> data) {
                    // Swap the data
                    int temp = current -> data;
                    current -> data = current -> Next -> data;
                    current -> Next -> data = temp;
                    swapped = true;
                }
                current = current -> Next;

            }

            lastSorted = current;
        } while (swapped);

    }

    void Delete(int position) {

        if (position < 1 || position > Size) {
            cout << "Invalid Position\n";
            return;
        } else if (position == 1 && Size == 1) {
            Head -> data = NULL;
            return;

            Size--;
        } else if (position == Size) { //Delete Last Node

            Node * Current = Head;
            while (Current -> Next -> Next != nullptr) {
                Current = Current -> Next;
            }

            Last = Current;
            delete Last -> Next;
            Last -> Next = nullptr;
            Size--;
            return;
        }
    }
};

int main() {
    SingleLinkedList mylist(100);
    mylist.Append(20);
    mylist.Append(75);
    mylist.Append(43);
    mylist.Append(5);
    mylist.Display();

    cout << "\nInserting 29 at position 2...\n";
    mylist.Insert(29, 2);
    mylist.Display();

    cout << "\Sorting the list...\n";
    mylist.Sort();
    mylist.Display();
    cout << "\Searching the list...\n";
    int position = mylist.LinearSearch(29);
    if (position > 0)
        cout << "We Found Value At Position " << position << endl;
    else
        cout << "Value Not Found" << endl;
    return 0;
}
