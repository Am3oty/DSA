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
            newNode -> Next = Head;
            Head = newNode;
            if (Size == 0) {
                Last = Head;
            }
            Size++;
            return;
        } else if (Head == NULL) {
            Head = newNode;
            Last = newNode;
            Size++;
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
        Size++;

        if (newNode -> Next == nullptr) {
            Last = newNode;
        }
    }

    int LinearSearch(int ValueToSearch) {
        Node * Current = Head;
        for (int i = 1; i < Size + 1; i++) {
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
        }

        if (position == 1 && Size == 1) {
            Head -> data = NULL;
            Size--;
            return;

        } else if (position == 1) {
            Node * temp = Head;
            Head = Head -> Next;
            temp -> Next = nullptr; // Important to prevent recursive deletion
            delete temp;
            Size--;
            if (Size == 0) Last = nullptr;
            return;
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
        } else {

            Node * Current = Head;
            for (int i = 1; i < position - 1 && Current != nullptr; ++i) {
                Current = Current -> Next;
            }

            Node * Temp = Current -> Next -> Next;
            Current -> Next -> Next = nullptr;
            delete Current -> Next;
            Current -> Next = Temp;
            Size--;

        }
    }

    bool IsSorted() {
        Node * Current = Head;

        while (Current -> Next != nullptr) {
            if (Current -> data > Current -> Next -> data)
                return false;
            else {
                Current = Current -> Next;
            }
        }
        return true;
    }

    void RemoveDuplicate() {
        Node * current = Head;

        while (current != nullptr && current -> Next != nullptr) {
            Node * prev = current;
            Node * temp = current -> Next;

            while (temp != nullptr) {
                if (current -> data == temp -> data) {
                    Node * toDelete = temp;
                    prev -> Next = temp -> Next;
                    temp = temp -> Next;
                    toDelete -> Next = nullptr;
                    delete toDelete;
                    Size--;
                } else {
                    prev = temp;
                    temp = temp -> Next;
                }
            }

            current = current -> Next;
        }
    }
};

int main() {
    SingleLinkedList mylist(100);
    mylist.Append(20);
    mylist.Append(75);
    mylist.Append(43);
    mylist.Append(5);
    mylist.Append(5);
    mylist.Append(5);
    mylist.Append(5);
    mylist.Append(5);
    mylist.Display();

    cout << "\nInserting 29 at position 2...\n";
    mylist.Insert(29, 2);
    mylist.Display();
    cout << "\Checking if the list is sorted...\n";
    if (mylist.IsSorted())
        cout << "List is Sorted\n";
    else
        cout << "List is not sorted\n";
    cout << "\Sorting the list...\n";
    mylist.Sort();
    mylist.Display();
    cout << "\Checking if the list is sorted...\n";
    if (mylist.IsSorted())
        cout << "List is Sorted\n";
    else
        cout << "List is not sorted\n";
    cout << "\Searching the list...\n";
    int position = mylist.LinearSearch(29);
    if (position > 0)
        cout << "We Found Value At Position " << position << endl;
    else
        cout << "Value Not Found" << endl;

    cout << "\Deleting position 3 ...\n";
    mylist.Delete(3);
    mylist.Display();
    cout << "\Deleting Head ...\n";
    mylist.Delete(1);
    mylist.Display();
    cout << "\Removing Duplication ...\n";
    mylist.RemoveDuplicate();
    mylist.Display();
    return 0;
}
