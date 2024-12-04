#ifndef COBACOBA_H_INCLUDED
#define COBACOBA_H_INCLUDED


#include <string>
using namespace std;

// Struktur node untuk teks
struct Node {
    string text;
    Node* next;
};

// Struktur node untuk stack operasi
struct StackNode {
    string operation;
    int position;
    string text;
    StackNode* next;
};

// Fungsi untuk mengelola teks
Node* createNode(const string& text);
Node* insertText(Node* head, const string& text, int position);
Node* deleteText(Node* head, int position);
Node* modifyText(Node* head, const string& text, int position);
void displayText(Node* head);

// Fungsi untuk operasi undo/redo
void pushStack(StackNode*& top, const string& operation, int position, const string& text);
bool popStack(StackNode*& top, string& operation, int& position, string& text);
Node* undoOperation(Node* head, StackNode*& undoStack, StackNode*& redoStack);
Node* redoOperation(Node* head, StackNode*& redoStack, StackNode*& undoStack);




#endif // COBACOBA_H_INCLUDED
