#include <iostream>
#include <string>
using namespace std;


// Structure for IT Support Issue (Singly Linked List Node)

struct Issue {
    int id;
    string employeeName;
    string department;
    string description;
    Issue* next;
};

// Linked List class
class IssueList {
    Issue* head;
public:
    IssueList() : head(nullptr) {}

    // Add new issue
    void addIssue(int id, string name, string dept, string desc) {
        Issue* newIssue = new Issue{id, name, dept, desc, nullptr};
        if (!head)
            head = newIssue;
        else {
            Issue* temp = head;
            while (temp->next)
                temp = temp->next;
            temp->next = newIssue;
        }
        cout << "✅ Issue added successfully!\n";
    }

    // Display all issues
    void displayAll() {
        if (!head) {
            cout << "⚠ No issues found.\n";
            return;
        }
        Issue* temp = head;
        cout << "\n--- All IT Support Issues ---\n";
        while (temp) {
            cout << "ID: " << temp->id
                 << " | Employee: " << temp->employeeName
                 << " | Dept: " << temp->department
                 << " | Problem: " << temp->description << endl;
            temp = temp->next;
        }
    }

    // Search issue by ID
    Issue* searchIssue(int id) {
        Issue* temp = head;
        while (temp) {
            if (temp->id == id)
                return temp;
            temp = temp->next;
        }
        return nullptr;
    }
};


// Circular Queue for Managing Service Queue

class CircularQueue {
    int front, rear, size;
    int* queue;
public:
    CircularQueue(int s) {
        size = s;
        queue = new int[s];
        front = rear = -1;
    }

    bool isFull() {
        return (front == 0 && rear == size - 1) || (rear == (front - 1) % (size - 1));
    }

    bool isEmpty() {
        return front == -1;
    }

    void enqueue(int id) {
        if (isFull()) {
            cout << "⚠ Service queue is full!\n";
            return;
        }
        if (front == -1)
            front = 0;
        rear = (rear + 1) % size;
        queue[rear] = id;
        cout << "✅ Issue ID " << id << " added to service queue.\n";
    }

    void dequeue(IssueList &issues) {
        if (isEmpty()) {
            cout << "⚠ No pending issues in queue.\n";
            return;
        }
        int id = queue[front];
        Issue* issue = issues.searchIssue(id);
        if (issue) {
            cout << "\n🧰 Resolving Issue ID: " << issue->id << endl;
            cout << "Employee: " << issue->employeeName
                 << " | Department: " << issue->department << endl;
            cout << "Problem: " << issue->description << endl;
            cout << "✅ Issue resolved successfully!\n";
        } else {
            cout << "❌ Issue not found in record.\n";
        }

        if (front == rear)
            front = rear = -1;
        else
            front = (front + 1) % size;
    }

    void displayQueue() {
        if (isEmpty()) {
            cout << "⚠ Queue is empty.\n";
            return;
        }
        cout << "\n--- Current Service Queue ---\n";
        int i = front;
        while (true) {
            cout << "Issue ID: " << queue[i] << endl;
            if (i == rear)
                break;
            i = (i + 1) % size;
        }
    }
};


int main() {
    IssueList issues;
    CircularQueue serviceQueue(5);

    int choice;
    do {
        cout << "\n========== IT SUPPORT HELPDESK ==========\n";
        cout << "1. Add New Issue\n";
        cout << "2. Display All Issues\n";
        cout << "3. Add Issue to Service Queue\n";
        cout << "4. Resolve Next Issue\n";
        cout << "5. Display Service Queue\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                int id;
                string name, dept, desc;
                cout << "Enter Issue ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter Employee Name: ";
                getline(cin, name);
                cout << "Enter Department: ";
                getline(cin, dept);
                cout << "Enter Problem Description: ";
                getline(cin, desc);
                issues.addIssue(id, name, dept, desc);
                break;
            }

            case 2:
                issues.displayAll();
                break;

            case 3: {
                int id;
                cout << "Enter Issue ID to add to queue: ";
                cin >> id;
                if (issues.searchIssue(id))
                    serviceQueue.enqueue(id);
                else
                    cout << "❌ Issue not found. Add it first.\n";
                break;
            }

            case 4:
                serviceQueue.dequeue(issues);
                break;

            case 5:
                serviceQueue.displayQueue();
                break;

            case 6:
                cout << "👋 Exiting IT Support Helpdesk System...\n";
                break;

            default:
                cout << "⚠ Invalid choice. Try again.\n";
        }

    } while (choice != 6);

    return 0;
}
