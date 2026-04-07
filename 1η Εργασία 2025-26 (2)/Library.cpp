#include <sstream>
#include <fstream>
#include "Library.h"
#include <iostream>
using namespace std;

// Βοηθητική συνάρτηση για την διάσπαση μιας γραμμής από το αρχείο σε tokens με βάση τον διαχωριστή '/'
vector<string> parseLine(const std::string& line, char delim) {
    vector<string> tokens;
    stringstream ss(line);
    string token;
    while (getline(ss, token, delim)) { 
        tokens.push_back(token);
    }
    return tokens;
}

// Υλοποίση constructor της κλάσης CopyNode
CopyNode::CopyNode(int c, string s) {
    copyID = c;  //Αρχικοποιήση τιμών
    status = s;
    next = nullptr;
    
}

// Υλοποίση constructor της κλάσης BookNode
BookNode::BookNode(string d, string a, string isbn) {
    title = d; //Αρχικοποίηση τιμών
    author = a;
    ISBN = isbn;
    copiesHead = nullptr;
    next = nullptr;

}
void BookNode::addCopy(int copyid, string status) {
    CopyNode* newCopy = new CopyNode(copyid, status);
    if (copiesHead == nullptr ||  copyid < copiesHead -> copyID ){/*περίπτωση όπου το νέο αντίγραφο πρέπει να μπει στην αρχή της λίστας.Αυτό συμβαίνει εάν
                                                                        η λίστα είναι κενή ή εάν το copyID του καινόυργιου αντιγράγου είναι μικρότερο από του ήδη
                                                                        πρώτου της λίστας*/
          
        newCopy -> next = copiesHead; // Ο δείκτης του επόμενου του νεόυ αντιγράγου (πλέον πρώτο) δείχνει στη παλία διεύθυνση του πρώτου
        copiesHead = newCopy;       // ο δείκτης που δείχνει στο πρώτο αντίγραφο , πλέον έχει την διέυθυνση του νέου αντιγράγου.

        
    }else // υπόλοιπες περιπτώσεις, δηλαδή εάν η εισαγωγή πρέπει να γίνει στο τέλος ή στο ενδιάμεσο της λίστας
    {
        CopyNode* current = copiesHead; //Δημιουρηούμε δείκτη με την διεύθυνση του τωρινού αντίγραφου,ώστε να διατρέξουμε την λίστα
        while (current -> next && current->next->copyID < copyid ){ /*όσο υπάρχει επόμενος κόμβος (δεν είμαστε στο τέλος της λίστας,αν
                                                                    είμαστε η συνθήκη σταματάει,και το αντίγραφο μπάινει στο τέλος της λίστας) και
                                                                    το copyID του επόμενου κόμβου είναι μικρότερο από το νέο που εισάγεται, η συνθήκη
                                                                    είναι αληθής.
                                                                    */
            current = current -> next; //διασχίζουμε την λίστα, προχωράμε έναν κόμβο μπροστά
        }
        //εφόσον έχει τελείωσει η συνθήκη έχει βρεθεί η θέση εισαγωγής του νέου αντιγράφου.

        newCopy -> next = current -> next;  //ο επόμενος δείκτης του νέου αντιγράφου τώρα δείχνει στον επόμενου εκέινου που βρέθηκε να καλύπτει την συνθήκη 
        current ->next = newCopy;   //ο επόμενος κόμβος του τωρινόυ πλέον δείχνει στην νέα εισαγωγή
        
        
        //Με τα παραπάνω έχει επιτευχθεί αντιμετάθεση. ο νέος κόμβος μπήκε μπροστά από τον current , ο current δέιχνει στον νέο
        //και ο νέος δέιχνει στον παλιό επόμενο του current
        // `current | `current + 1 (πρίν)
        // `current | `newCopy | current + 1 (μετά)


    }

}
bool BookNode::borrowCopy(int copyid) {
    return false;
}
void BookNode::removeCopy(int copyid) {

}
void BookNode::returnCopy(int copyid) {

}
int BookNode::countAvailable() {
    return 0;
}

// Υλοποίση της κλάσης Library
Library::Library() {
    booksHead = nullptr;

}
Library::~Library() {

}
void Library::addBook(string title, string author, string isbn) {
    BookNode* newBook = new BookNode(title,author,isbn ); //πανομοιότυπη υλοποίηση με την μέθοδο addCopy,απλώς η συνθήκη ταξινόμησης εδώ πρόκειται για το όνομα του βιβλίου
    
    if (booksHead == nullptr || newBook -> title < booksHead -> title) /*περίπτωση όπου το νέο βιβλίο πρέπει να μπει στην αρχή της λίστας.Αυτό συμβαίνει εάν
                                                                        η λίστα είναι κενή ή εάν το title του καινόυργιου βιβλίου είναι μικρότερο(αλφαριμητικά) από του ήδη
                                                                        πρώτου της λίστας*/
    {
        newBook -> next = booksHead; // Ο δείκτης του επόμενου του νεόυ βιβλίου (πλέον πρώτο) δείχνει στη παλία διεύθυνση του πρώτου
        booksHead = newBook;    // ο δείκτης που δείχνει στο πρώτο βιβλίο (αρχή λίστας), πλέον έχει την διέυθυνση του νέου βιβλίου.
        


    }else // υπόλοιπες περιπτώσεις, δηλαδή εάν η εισαγωγή πρέπει να γίνει στο τέλος ή στο ενδιάμεσο της λίστας

    {
       BookNode* current = booksHead; // μεταβλητή για να διατρέξουμε την λίστα
       while (current -> next && current ->next -> title < newBook -> title){   /*όσο υπάρχει διέυθυνση επόμενου βιβλίου και 
                                                                                ο τίτλος του επομένου του τωρινού παραμένει αλφαβητικά μικρότερος νέου
                                                                                είμαστε στην συνθήκη
                                                                                */
        current = current -> next ;//επόμενη διεύθυνση κόμβου

    }
    
    newBook -> next = current->next;
    current -> next = newBook;
    


    //Με τα παραπάνω έχει επιτευχθεί αντιμετάθεση. ο νέος κόμβος μπήκε μπροστά από τον current , ο current δέιχνει στον νέο
        //και ο νέος δέιχνει στον παλιό επόμενο του current
        // `current | `current + 1 (πρίν)
        // `current | `newBook | current + 1 (μετά)
    }


}
void Library::removeBook(string isbn) {

}

BookNode* Library::findBook(string isbn) {
    BookNode* current = booksHead; // Ξεκινάμε από την κεφαλή της λίστας, δηλαδή το πρώτο βιβλίο
    
    while (current != nullptr) { //Όσο δεν έχουμε φτάσει στο τέλος της λίστας  
        if (current->ISBN == isbn) { //Εάν το ISBN του τρέχοντος βιβλίου είναι ίσο με το ζητούμενο
            return current; // Τότε επιστρέφουμε τον δείκτη στο τρέχον βιβλίο 
        } else  {
            current = current->next; // Διαφορετικά, προχωράμε στον επόμενο κόμβο της λίστας
        }
    }
    
    return nullptr; // Επιστρέφουμε nullptr αν δεν βρεθεί το βιβλίο με το συγκεκριμένο ISBN στη λίστα
}

void Library::printAll() {
    BookNode* current = booksHead; // μεταβλητή για διάσχηση της λίστας

    if (!current) { //δεν υπάρχει βιβλίο στην βιβλιοθήκη
        cout <<"H βιβλιοθήκη είναι άδεια!"<<endl;;
        return; //έξοδος από την μέθοδο
    }
    while(current){ //όσο υπάρχει επόμενος κόμβος
            cout<< "Τίτλος: "<< current -> title << endl;
            cout<< "Συγγραφέας: " << current -> author <<endl ;
            cout << "ISBN: " << current -> ISBN << endl;
            cout << "Αριθμός διαθέσιμων βιβλίων: " << current -> countAvailable() << endl;

            current = current -> next; //επόμενη διεύθυνση κόμβου
    }

}

void Library::loadFromFile(const string& filename) {
   ifstream file(filename); // Δημιουργία αντικειμένου ifstream για το άνοιγμα του αρχείου με το όνομα που παρέχεται ως παράμετρος
   if (!file.is_open()) { // Έλεγχος αν το αρχείο άνοιξε επιτυχώς. Εάν όχι, εμφανίζεται μήνυμα σφάλματος και η μέθοδος επιστρέφει
        cout << "Σφάλμα: δεν ήταν δυνατό το άνοιγμα του αρχείου " << filename << "\n";
        return;
   }

   string line; // Μεταβλητή για την αποθήκευση κάθε γραμμής που διαβάζεται από το αρχείο   
   string lastIsbn = ""; // Μεταβλητή για την αποθήκευση του τελευταίου ISBN που διαβάστηκε, ώστε να συνδέσουμε τα αντίγραφα με το σωστό βιβλίο

   while (getline(file, line)) { // Διαβάζουμε το αρχείο γραμμή προς γραμμή μέχρι να φτάσουμε στο τέλος του αρχείου
        if (line.empty()) continue; // Εάν η γραμμή είναι κενή, παραλείπουμε την επεξεργασία και συνεχίζουμε με την επόμενη γραμμή

        vector<string> tokens = parseLine(line); // Χρησιμοποιούμε τη βοηθητική συνάρτηση parseLine για να διαχωρίσουμε τη γραμμή σε tokens με βάση τον διαχωριστή '|'

        if (tokens[0] == "BOOK") {      // Εάν το πρώτο token είναι "BOOK", σημαίνει ότι η γραμμή περιέχει πληροφορίες για ένα βιβλίο
            string ISBN = tokens[1];    // Ανάθεση του ISBN, του τίτλου και του συγγραφέα από τα αντίστοιχα tokens
            string title = tokens[2];
            string author = tokens[3];
            addBook(title, author, ISBN); // Κλήση της μεθόδου addBook για να προσθέσουμε το βιβλίο στη βιβλιοθήκη  
            lastIsbn = ISBN;
        } 
        else if (tokens[0] == "COPY") { // Έλεγχος αν το πρώτο token είναι "COPY", που σημαίνει ότι η γραμμή περιέχει πληροφορίες για ένα αντίγραφο βιβλίου
            string CopyID = tokens[1];
            string status = tokens[2];
            BookNode* b = findBook(lastIsbn); // Βρίσκουμε το βιβλίο με το τελευταίο ISBN που διαβάσαμε 
            if (b != nullptr) { // Εάν το βιβλίο βρέθηκε, προσθέτουμε το αντίγραφο στο βιβλίο χρησιμοποιώντας τη μέθοδο addCopy
                int copyId = stoi(tokens[1]);
                b->addCopy(copyId, tokens[2]);
            } else {
                cout << "Σφάλμα: δεν βρέθηκε το βιβλίο με ISBN " << lastIsbn << " για να προσθέσουμε το αντίγραφο.\n";
            }
        }
    }
    file.close(); // Κλείσιμο του αρχείου μετά την ολοκλήρωση της ανάγνωσης
    cout << "Η βιβλιοθήκη φορτώθηκε επιτυχώς από το αρχείο!\n";
}

void Library::saveToFile(const std::string& filename) {

}