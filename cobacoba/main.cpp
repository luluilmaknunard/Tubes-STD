#include "cobacoba.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
    Node* head = nullptr; // Head untuk linked list
    StackNode* undoStack = nullptr; // Stack untuk undo
    StackNode* redoStack = nullptr; // Stack untuk redo

    int choice;
    while (true) {
        cout << "\nText Editor Menu:\n";
        cout << "1. Insert Text\n";
        cout << "2. Delete Text\n";
        cout << "3. Modify Text\n";
        cout << "4. Display Text\n";
        cout << "5. Undo\n";
        cout << "6. Redo\n";
        cout << "7. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        if (choice == 7) break; // Keluar dari program

        int position;
        string text;

        switch (choice) {
            case 1: // Insert
                cout << "Enter position to insert: ";
                cin >> position;
                cin.ignore(); // Membersihkan buffer
                cout << "Enter text to insert: ";
                getline(cin, text);
                head = insertText(head, text, position);
                pushStack(undoStack, "insert", position, text); // Simpan operasi untuk undo
                // Bersihkan redoStack karena operasi baru
                redoStack = nullptr;
                break;

            case 2: // Delete
                cout << "Enter position to delete: ";
                cin >> position;
                if (head != nullptr) {
                    Node* current = head;
                    for (int i = 1; i < position && current != nullptr; i++) {
                        current = current->next;
                    }
                    if (current != nullptr) {
                        text = current->text; // Simpan teks untuk operasi undo
                        head = deleteText(head, position);
                        pushStack(undoStack, "delete", position, text);
                        // Bersihkan redoStack karena operasi baru
                        redoStack = nullptr;
                    } else {
                        cout << "Invalid position!\n";
                    }
                } else {
                    cout << "List is empty.\n";
                }
                break;

            case 3: // Modify
                cout << "Enter position to modify: ";
                cin >> position;
                cin.ignore(); // Membersihkan buffer
                cout << "Enter new text: ";
                getline(cin, text);
                if (head != nullptr) {
                    Node* current = head;
                    for (int i = 1; i < position && current != nullptr; i++) {
                        current = current->next;
                    }
                    if (current != nullptr) {
                        string oldText = current->text; // Simpan teks lama untuk undo
                        head = modifyText(head, text, position);
                        pushStack(undoStack, "modify", position, oldText);
                        // Bersihkan redoStack karena operasi baru
                        redoStack = nullptr;
                    } else {
                        cout << "Invalid position!\n";
                    }
                } else {
                    cout << "List is empty.\n";
                }
                break;

            case 4: // Display
                displayText(head);
                break;

            case 5: // Undo
                head = undoOperation(head, undoStack, redoStack);
                break;

            case 6: // Redo
                head = redoOperation(head, redoStack, undoStack);
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    cout << "Exiting Text Editor. Goodbye!\n";
    return 0;
}
