#include <iostream>
#include <windows.h> // Για την χρήση του SetConsoleOutputCP ώστε να εμφανίζονται σωστά τα ελληνικά στην κονσόλα
#include "Library.h"
using namespace std;

int main() {
    SetConsoleOutputCP(CP_UTF8); // Ορισμός του κωδικοποιητή για την σωστή εμφάνιση ελληνικών χαρακτήρων
    
    Library lib;

    // Φόρτωση βιβλιοθήκης από αρχείο
    lib.loadFromFile("library.txt");

    int choice = -1;

    // Το κεντρικό μενού (τρέχει συνεχώς μέχρι ο χρήστης να επιλέξει να βγει)
    while (choice != 0) {
        cout << "\n========== ΜΕΝΟΥ ΒΙΒΛΙΟΘΗΚΗΣ ==========\n";
        cout << "1. Προσθήκη νέου βιβλίου\n";
        cout << "2. Προσθήκη αντιτύπου\n";
        cout << "3. Διαγραφή βιβλίου\n";
        cout << "4. Αναζήτηση βιβλίου (βάσει ISBN)\n";
        cout << "0. Έξοδος\n";
        cout << "=========================================\n";
        cout << "Επιλογή: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Σε εξέλιξη...\n";
                break;
            case 2:
                cout << "Σε εξέλιξη...\n";
                break;
            case 3:
                cout << "Σε εξέλιξη...\n";
                break;
            case 4: {
                string targetIsbn;
                cout << "Δώσε το ISBN του βιβλίου που ψάχνεις: ";
                cin >> targetIsbn;

                // Ψάχνουμε το βιβλίο με την findbook
                BookNode* b = lib.findBook(targetIsbn);

                if (b == nullptr) {
                    cout << "Το βιβλίο με ISBN " << targetIsbn << " δεν βρέθηκε στη βιβλιοθήκη.\n";
                } else {
                    cout << "\n--- Στοιχεία Βιβλίου ---\n";
                    cout << "Τίτλος: " << b->title << "\n";
                    cout << "Συγγραφέας: " << b->author << "\n";

                    cout << "--- Αντίγραφα ---\n";

                    CopyNode* currentCopy = b->copiesHead;
                    if (currentCopy == nullptr) {
                        cout << "Δεν υπάρχουν καταχωρημένα αντίτυπα. \n";
                    } else {
                        while (currentCopy != nullptr) {
                            cout << " -> Κωδικός (ID): " << currentCopy->copyID 
                                 << " | Κατάσταση: " << currentCopy->status << "\n";
                            currentCopy = currentCopy->next;
                        }
                    }
                }
                break;
            }
                
            case 0:
                cout << "Έξοδος από το πρόγραμμα...\n";
                break;
            default:
                cout << "Μη έγκυρη επιλογή. Παρακαλώ δοκιμάστε ξανά.\n";
                break;
        }      
            
    }

    return 0;
}