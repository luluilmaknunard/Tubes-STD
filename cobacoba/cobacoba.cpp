#include "cobacoba.h"
#include <iostream>
using namespace std;

// Membuat node teks baru
Node* createNode(const string& text) {
    Node* newNode = new Node();
    newNode->text = text;
    newNode->next = nullptr;
    return newNode;
}

// Menambahkan teks pada posisi tertentu
Node* insertText(Node* head, const string& text, int position) {
    Node* newNode = createNode(text);
    if (position == 1) {
        newNode->next = head;
        return newNode;
    }

    Node* current = head;
    for (int i = 1; i < position - 1 && current != nullptr; i++) {
        current = current->next;
    }

    if (current == nullptr) return head;

    newNode->next = current->next;
    current->next = newNode;
    return head;
}

// Menghapus teks pada posisi tertentu
Node* deleteText(Node* head, int position) {
    if (!head) return nullptr;

    if (position == 1) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return head;
    }

    Node* current = head;
    for (int i = 1; i < position - 1 && current->next != nullptr; i++) {
        current = current->next;
    }

    if (!current->next) return head;

    Node* temp = current->next;
    current->next = temp->next;
    delete temp;
    return head;
}

// Memodifikasi teks pada posisi tertentu
Node* modifyText(Node* head, const string& text, int position) {
    Node* current = head;
    for (int i = 1; i < position && current != nullptr; i++) {
        current = current->next;
    }

    if (current) current->text = text;
    return head;
}

// Menampilkan teks
void displayText(Node* head) {
    Node* current = head;
    int line = 1;
    while (current) {
        cout << line << ": " << current->text << endl;
        current = current->next;
        line++;
    }
}

// Menambahkan operasi ke stack
void pushStack(StackNode*& top, const string& operation, int position, const string& text) {
    StackNode* newNode = new StackNode();
    newNode->operation = operation;
    newNode->position = position;
    newNode->text = text;
    newNode->next = top;
    top = newNode;
}

// Mengambil operasi dari stack
bool popStack(StackNode*& top, string& operation, int& position, string& text) {
    if (!top) return false;

    StackNode* temp = top;
    operation = top->operation;
    position = top->position;
    text = top->text;
    top = top->next;
    delete temp;

    return true;
}

// Undo operasi terakhir
Node* undoOperation(Node* head, StackNode*& undoStack, StackNode*& redoStack) {
    string operation, text;
    int position;

    if (!popStack(undoStack, operation, position, text)) {
        cout << "Tidak ada operasi untuk di-undo.\n";
        return head;
    }

    if (operation == "insert") {
        head = deleteText(head, position);
        pushStack(redoStack, "delete", position, text);
    } else if (operation == "delete") {
        head = insertText(head, text, position);
        pushStack(redoStack, "insert", position, text);
    } else if (operation == "modify") {
        string oldText = head->text; // Simpan teks lama
        head = modifyText(head, text, position);
        pushStack(redoStack, "modify", position, oldText);
    }

    return head;
}

// Redo operasi terakhir
Node* redoOperation(Node* head, StackNode*& redoStack, StackNode*& undoStack) {
    string operation, text;
    int position;

    if (!popStack(redoStack, operation, position, text)) {
        cout << "Tidak ada operasi untuk di-redo.\n";
        return head;
    }

    if (operation == "insert") {
        head = insertText(head, text, position);
        pushStack(undoStack, "insert", position, text);
    } else if (operation == "delete") {
        head = deleteText(head, position);
        pushStack(undoStack, "delete", position, text);
    } else if (operation == "modify") {
        string oldText = head->text; // Simpan teks lama
        head = modifyText(head, text, position);
        pushStack(undoStack, "modify", position, oldText);
    }

    return head;
}
