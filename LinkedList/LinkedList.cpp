#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* Next;
    Node* Prev;

    Node(int value) {
        data = value;
        Next = nullptr;
        Prev = nullptr;
    }

    Node() {
        data = 0;
        Next = nullptr;
        Prev = nullptr;
    }
};

class DoubleLinkedList {
private:
    Node* Head;
    Node* Last;
    int Size = 0;

public:
    DoubleLinkedList(int y) {
        Head = new Node(y);
        Head->Next = Head;
        Head->Prev = Head;
        Last = Head;
        Size++;
    }

    DoubleLinkedList() {
        Head = nullptr;
        Last = nullptr;
    }

    ~DoubleLinkedList() {
        if (!Head) return;
        Node* current = Head;
        do {
            Node* temp = current;
            current = current->Next;
            delete temp;
        } while (current != Head);
        Head = nullptr;
        Last = nullptr;
    }

    void Append(int x) {
        Node* newNode = new Node(x);
        if (Head == nullptr) {
            Head = newNode;
            Head->Next = Head;
            Head->Prev = Head;
            Last = Head;
        }
        else {
            newNode->Prev = Last;
            newNode->Next = Head;
            Last->Next = newNode;
            Head->Prev = newNode;
            Last = newNode;
        }
        Size++;
    }

    void Display() {
        if (Head == nullptr) {
            cout << "List Is Empty" << endl;
            return;
        }

        Node* Current = Head;
        for (int i = 0; i < Size; i++) {
            cout << Current->data << endl;
            Current = Current->Next;
        }
    }

    void Insert(int data, int position) {
        if (position < 1 || position > Size + 1) {
            cout << "Invalid position!" << endl;
            return;
        }

        Node* newNode = new Node(data);
        if (position == 1) {
            if (!Head) {
                Head = newNode;
                Head->Next = Head;
                Head->Prev = Head;
                Last = Head;
            }
            else {
                newNode->Next = Head;
                newNode->Prev = Last;
                Last->Next = newNode;
                Head->Prev = newNode;
                Head = newNode;
            }
        }
        else {
            Node* Current = Head;
            for (int i = 1; i < position - 1; i++) {
                Current = Current->Next;
            }
            newNode->Next = Current->Next;
            newNode->Prev = Current;
            Current->Next->Prev = newNode;
            Current->Next = newNode;
            if (Current == Last) {
                Last = newNode;
            }
        }
        Size++;
    }

    int LinearSearch(int ValueToSearch) {
        Node* Current = Head;
        for (int i = 1; i <= Size; i++) {
            if (Current->data == ValueToSearch)
                return i;
            Current = Current->Next;
        }
        return -1;
    }

    void Sort() {
        if (!Head) return;
        bool swapped;
        Node* current;
        do {
            swapped = false;
            current = Head;
            for (int i = 0; i < Size - 1; i++) {
                if (current->data > current->Next->data) {
                    swap(current->data, current->Next->data);
                    swapped = true;
                }
                current = current->Next;
            }
        } while (swapped);
    }

    void Delete(int position) {
        if (position < 1 || position > Size) {
            cout << "Invalid Position\n";
            return;
        }

        if (Size == 1) {
            delete Head;
            Head = nullptr;
            Last = nullptr;
        }
        else if (position == 1) {
            Node* temp = Head;
            Head = Head->Next;
            Head->Prev = Last;
            Last->Next = Head;
            delete temp;
        }
        else {
            Node* Current = Head;
            for (int i = 1; i < position; i++) {
                Current = Current->Next;
            }
            Current->Prev->Next = Current->Next;
            Current->Next->Prev = Current->Prev;
            if (Current == Last)
                Last = Current->Prev;
            delete Current;
        }
        Size--;
    }

    bool IsSorted() {
        if (!Head) return false;
        Node* Current = Head;
        for (int i = 0; i < Size - 1; i++) {
            if (Current->data > Current->Next->data)
                return false;
            Current = Current->Next;
        }
        return true;
    }

    void RemoveDuplicate() {
        if (!Head) return;
        Node* current = Head;
        for (int i = 0; i < Size; i++) {
            Node* temp = current->Next;
            Node* prev = current;
            for (int j = i + 1; j < Size;) {
                if (temp->data == current->data) {
                    prev->Next = temp->Next;
                    temp->Next->Prev = prev;
                    Node* toDelete = temp;
                    temp = temp->Next;
                    delete toDelete;
                    Size--;
                }
                else {
                    prev = temp;
                    temp = temp->Next;
                    j++;
                }
            }
            current = current->Next;
        }
    }

    void Reverse() {
        if (!Head) return;

        Node* current = Head;
        Node* temp = nullptr;
        for (int i = 0; i < Size; i++) {
            temp = current->Prev;
            current->Prev = current->Next;
            current->Next = temp;
            current = current->Prev;
        }

        temp = Head;
        Head = Last;
        Last = temp;
    }

    void Concatenate(DoubleLinkedList* List) {
        if (!List || List->Head == nullptr) return;

        if (Head == nullptr) {
            Head = List->Head;
            Last = List->Last;
        }
        else {
            Last->Next = List->Head;
            List->Head->Prev = Last;
            Last = List->Last;
            Last->Next = Head;
            Head->Prev = Last;
        }

        Size += List->Size;
    }
};

int main() {
    DoubleLinkedList mylist(100);
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

    cout << "\nChecking if the list is sorted...\n";
    cout << (mylist.IsSorted() ? "List is Sorted\n" : "List is not sorted\n");

    cout << "\nSorting the list...\n";
    mylist.Sort();
    mylist.Display();

    cout << "\nChecking if the list is sorted...\n";
    cout << (mylist.IsSorted() ? "List is Sorted\n" : "List is not sorted\n");

    cout << "\nSearching the list...\n";
    int position = mylist.LinearSearch(29);
    cout << "Position : "<<position << endl;

    cout << "\nDeleting position 3 ...\n";
    mylist.Delete(3);
    mylist.Display();

    cout << "\nDeleting Head ...\n";
    mylist.Delete(1);
    mylist.Display();

    cout << "\nRemoving Duplication ...\n";
    mylist.RemoveDuplicate();
    mylist.Display();

    cout << "\nReversing List ...\n";
    mylist.Reverse();
    mylist.Display();

    cout << "\nConcatenating List ...\n";
    DoubleLinkedList* L2 = new DoubleLinkedList(1);
    L2->Append(5);
    L2->Append(8);
    L2->Append(10);
    L2->Append(25);
    mylist.Concatenate(L2);
    mylist.Display();

    return 0;
}
