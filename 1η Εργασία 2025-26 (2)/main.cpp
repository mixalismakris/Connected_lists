#include <iostream>
#include <windows.h> // Για την χρήση του SetConsoleOutputCP ώστε να εμφανίζονται σωστά τα ελληνικά στην κονσόλα
#include "Library.h"
using namespace std;

int main() {
    SetConsoleOutputCP(CP_UTF8); /* Ορισμός του κωδικοποιητή για την σωστή εμφάνιση ελληνικών χαρακτήρων, 
                                    καθώς τα αρχεία κειμένου μπορεί να περιέχουν χαρακτήρες εκτός του ASCII */
    
    Library* lib = new Library(); // Δημιουργία αντικειμένου τύπου Library για να διαχειριστούμε τη βιβλιοθήκη μας
    bool isLoaded = false; // Μεταβλητή για να ελέγχουμε αν έχει φορτωθεί η βιβλιοθήκη από αρχείο, ώστε να μην φορτώνεται ξανά σε κάθε εκτέλεση του προγράμματος

    lib->loadFromFile("library.txt"); // Φόρτωση της βιβλιοθήκης από το αρχείο "library.txt" κατά την εκκίνηση του προγράμματος
    isLoaded = true; // Ορισμός της μεταβλητής isLoaded σε true μετά την επιτυχή φόρτωση της βιβλιοθήκης

    int choice = -1;

    // Το κεντρικό μενού (τρέχει συνεχώς μέχρι ο χρήστης να επιλέξει να βγει)
    while (choice != 0) {
        cout << "\n========== ΜΕΝΟΥ ΒΙΒΛΙΟΘΗΚΗΣ ==========\n";
        cout << "1. Φόρτωση βιβλιοθήκης από αρχείο\n";
        cout << "2. Αποθήκευση βιβλιοθήκης σε αρχείο\n";
        cout << "3. Εμφάνιση όλων των βιβλίων\n";
        cout << "4. Αναζήτηση βιβλίου (βάσει ISBN)\n";
        cout << "5. Προσθήκη νέου βιβλίου\n";
        cout << "6. Διαγραφή βιβλίου\n";
        cout << "7. Προσθήκη νέου αντιτύπου\n";
        cout << "8. Διαγραφή αντιτύπου\n";
        cout << "9. Δανεισμός Αντιτύπου\n";
        cout << "10. Επιστροφή Αντιτύπου\n";
        cout << "11. Εμφάνιση διαθέσιμων αντιτύπων βιβλίου\n";
        cout << "0. Έξοδος\n";
        cout << "=========================================\n";
        cout << "Επιλογή: ";
        cin >> choice;

        // Επεξεργασία της επιλογής του χρήστη και κλήση της αντίστοιχης λειτουργίας
        switch (choice) {
            case 1: { // Φόρτωση από αρχείο (με έλεγχο αν έχει ήδη φορτωθεί)
                if (isLoaded) {
                    string ans;
                    cout << "Η βιβλιοθήκη είναι ήδη φορτωμένη. Θέλετε να διαγραφούν τα τρέχοντα δεδομένα και να γίνει επαναφόρτωση; (y/n): ";
                    cin >> ans;
                    if (ans == "y" || ans == "Y") {
                        delete lib; // Καλεί τον ~Library() για να καθαρίσει τη μνήμη!
                        lib = new Library(); // Φτιάχνει μια νέα, κενή βιβλιοθήκη
                        lib->loadFromFile("library.txt");
                    }
                } else {
                    lib->loadFromFile("library.txt");
                    isLoaded = true;
                }
                break;
            }
            case 2: // Αποθήκευση σε αρχείο (με επιβεβαίωση από τον χρήστη)
                lib->saveToFile("library.txt");
                break;            
            case 3: // Εμφάνιση όλων των βιβλίων και των διαθέσιμων αντιτύπων τους
                lib->printAll();
                break;
            case 4: { // Αναζήτηση
                string isbn;
                cout << "Δώσε ISBN: ";
                cin >> isbn;
                BookNode* b = lib->findBook(isbn);
                if (!b) {
                    cout << "Σφάλμα: Το βιβλίο δεν βρέθηκε.\n";
                } else {
                    cout << "\nΤίτλος: " << b->title << "\nΣυγγραφέας: " << b->author << "\n";
                    CopyNode* currentCopy = b->copiesHead;
                    if (!currentCopy) cout << "Δεν υπάρχουν αντίτυπα.\n";
                    while (currentCopy) {
                        cout << " -> ID: " << currentCopy->getCopyID() << " | Κατάσταση: " << currentCopy->getStatus() << "\n";
                        currentCopy = currentCopy->getNext();
                    }
                }
                break;
            }
            case 5: { // Νέο βιβλίο (με έλεγχο για διπλό ISBN)
                string title, author, isbn;
                cout << "Δώσε ISBN: ";
                cin >> isbn;
                
                if (lib->findBook(isbn) != nullptr) {
                    cout << "Σφάλμα: Το ISBN υπάρχει ήδη στη βιβλιοθήκη!\n";
                } else {
                    cout << "Δώσε Τίτλο: ";
                    cin.ignore(); // Καθαρισμός του buffer για να διαβάσει σωστά τα κενά
                    getline(cin, title);
                    cout << "Δώσε Συγγραφέα: ";
                    getline(cin, author);
                    lib->addBook(title, author, isbn);
                    cout << "Το βιβλίο προστέθηκε επιτυχώς!\n";
                }
                break;
            }
            case 6: { // Διαγραφή βιβλίου (με έλεγχο αν υπάρχει)
                string isbn;
                cout << "Δώσε ISBN βιβλίου προς διαγραφή: ";
                cin >> isbn;
                lib->removeBook(isbn);
                break;
            }
            case 7: { // Νέο αντίτυπο (με έλεγχο αν υπάρχει το βιβλίο)
                string isbn;
                int copyId;
                cout << "Δώσε ISBN βιβλίου: ";
                cin >> isbn;
                BookNode* b = lib->findBook(isbn);
                if (b) {
                    cout << "Δώσε νέο ID αντιτύπου: ";
                    cin >> copyId;
                    b->addCopy(copyId, "available");
                    cout << "Το αντίτυπο προστέθηκε!\n";
                } else {
                    cout << "Σφάλμα: Το βιβλίο δεν βρέθηκε.\n";
                }
                break;
            }
            case 8: { // Διαγραφή αντιτύπου (με έλεγχο αν υπάρχει το βιβλίο και το αντίτυπο)
                string isbn;
                int copyId;
                cout << "Δώσε ISBN βιβλίου: ";
                cin >> isbn;
                BookNode* b = lib->findBook(isbn);
                if (b) {
                    cout << "Δώσε ID αντιτύπου προς διαγραφή: ";
                    cin >> copyId;
                    b->removeCopy(copyId);
                } else cout << "Σφάλμα: Το βιβλίο δεν βρέθηκε.\n";
                break;
            }
            case 9: { // Δανεισμός (με έλεγχο αν υπάρχει το βιβλίο και το αντίτυπο και αν είναι διαθέσιμο)
                string isbn;
                int copyId;
                cout << "Δώσε ISBN βιβλίου: ";
                cin >> isbn;
                BookNode* b = lib->findBook(isbn);
                if (b) {
                    cout << "Δώσε ID αντιτύπου για δανεισμό: ";
                    cin >> copyId;
                    if (b->borrowCopy(copyId)) {
                        cout << "Επιτυχής δανεισμός!\n";
                    } else {
                        cout << "Σφάλμα: Το αντίτυπο είναι ήδη δανεισμένο ή δεν βρέθηκε.\n";
                    }
                } else cout << "Σφάλμα: Το βιβλίο δεν βρέθηκε.\n";
                break;
            }
            case 10: { // Επιστροφή (με έλεγχο αν υπάρχει το βιβλίο και το αντίτυπο)
                string isbn;
                int copyId;
                cout << "Δώσε ISBN βιβλίου: ";
                cin >> isbn;
                BookNode* b = lib->findBook(isbn);
                if (b) {
                    cout << "Δώσε ID αντιτύπου για επιστροφή: ";
                    cin >> copyId;
                    b->returnCopy(copyId);
                } else cout << "Σφάλμα: Το βιβλίο δεν βρέθηκε.\n";
                break;
            }
            case 11: { // Διαθέσιμα αντίτυπα (με έλεγχο αν υπάρχει το βιβλίο)
                string isbn;
                cout << "Δώσε ISBN βιβλίου: ";
                cin >> isbn;
                BookNode* b = lib->findBook(isbn);
                if (b) {
                    cout << "Διαθέσιμα αντίτυπα: " << b->countAvailable() << "\n";
                } else cout << "Σφάλμα: Το βιβλίο δεν βρέθηκε.\n";
                break;
            }
             // Εάν ο χρήστης επιλέξει 0, εμφανίζεται μήνυμα εξόδου και το πρόγραμμα τερματίζει 
            case 0: { // Έξοδος (με επιβεβαίωση αποθήκευσης)
                string ans;
                cout << "Θέλετε να αποθηκεύσετε τις αλλαγές στο αρχείο πριν την έξοδο; (y/n): ";
                cin >> ans;
                if (ans == "y" || ans == "Y") {
                    lib->saveToFile("library.txt");
                }
                cout << "Τερματισμός προγράμματος...\n";
                break;
            }
            default:          // Εάν ο χρήστης εισάγει μια μη έγκυρη επιλογή, εμφανίζεται μήνυμα σφάλματος και το μενού εμφανίζεται ξανά
                cout << "Μη έγκυρη επιλογή. Παρακαλώ δοκιμάστε ξανά.\n";
                break;
        }      
            
    }
    delete lib; // Καλεί τον ~Library() για να καθαρίσει τη μνήμη πριν το πρόγραμμα τερματίσει

    return 0;
}