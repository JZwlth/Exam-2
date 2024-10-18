#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

class DoublyLinkedList {
public:
    struct Node {
        string data;
        Node* prev;
        Node* next;
        Node(string val, Node* p = nullptr, Node* n = nullptr) {
            data = val;
            prev = p;
            next = n;
        }
    };

private:
    Node* head;
    Node* tail;

public:
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    void push_back(string v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void push_front(string v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void pop_front() {
        if (!head) {
            return;
        }

        Node* temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) {
            return;
        }
        Node* temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << "\t" << current->data << endl;
            current = current->next;
        }
    }

    Node* getHead() {
        return head;
    }

    Node* getTail() {
        return tail;
    }

    void remove(Node* node) {
        if (!node) return;
        if (node->prev)
            node->prev->next = node->next;
        else
            head = node->next;

        if (node->next)
            node->next->prev = node->prev;
        else
            tail = node->prev;

        delete node;
    }
};

int main() {
    // Read names from names.txt
    vector<string> names;
    ifstream namesFile("names.txt");
    string name;
    while (getline(namesFile, name)) {
        if (!name.empty())
            names.push_back(name);
    }
    namesFile.close();

    // Initialize random number generator
    srand(time(NULL));

    // Declare the line
    DoublyLinkedList line;

    // Store opens
    cout << "Store opens:" << endl;

    // Add 5 customers to the line
    for (int i = 0; i < 5; ++i) {
        // Pick a random name
        int index = rand() % names.size();
        string customerName = names[index];
        line.push_back(customerName);
        cout << "\t" << customerName << " joins the line" << endl;
    }

    // Output the resulting line
    cout << "Resulting line:" << endl;
    DoublyLinkedList::Node* current = line.getHead();
    while (current) {
        cout << "\t" << current->data << endl;
        current = current->next;
    }

    // Simulate time steps from 2 to 20
    for (int timeStep = 2; timeStep <= 20; ++timeStep) {
        cout << "Time step #" << timeStep << ":" << endl;

        // Event A: Customer at front is served (40%)
        int randNum = rand() % 100 + 1;
        if (randNum <= 40) {
            // Customer is served
            if (line.getHead()) {
                string servedCustomer = line.getHead()->data;
                line.pop_front();
                cout << "\t" << servedCustomer << " is served" << endl;
            }
        }

        // Event B: New customer joins at end (60%)
        randNum = rand() % 100 + 1;
        if (randNum <= 60) {
            // New customer joins
            int index = rand() % names.size();
            string customerName = names[index];
            line.push_back(customerName);
            cout << "\t" << customerName << " joins the line" << endl;
        }

        // Event C: Customer at end leaves (20%)
        randNum = rand() % 100 + 1;
        if (randNum <= 20) {
            // Customer at end leaves
            if (line.getTail()) {
                string leavingCustomer = line.getTail()->data;
                line.pop_back();
                cout << "\t" << leavingCustomer << " exits the rear of the line" << endl;
            }
        }

        // Event D: Any customer decides to leave (10% per customer)
        current = line.getHead();
        while (current) {
            DoublyLinkedList::Node* next = current->next;
            randNum = rand() % 100 + 1;
            if (randNum <= 10) {
                // Customer decides to leave
                cout << "\t" << current->data << " left the line" << endl;
                line.remove(current);
            }
            current = next;
        }

        // Event E: VIP customer joins front (10%)
        randNum = rand() % 100 + 1;
        if (randNum <= 10) {
            // VIP customer joins front
            int index = rand() % names.size();
            string vipCustomer = names[index];
            line.push_front(vipCustomer);
            cout << "\t" << vipCustomer << " (VIP) joins the front of the line" << endl;
        }

        // Output the resulting line
        cout << "Resulting line:" << endl;
        current = line.getHead();
        if (!current) {
            cout << "\tLine is empty" << endl;
        }
        while (current) {
            cout << "\t" << current->data << endl;
            current = current->next;
        }
    }

    return 0;
}
