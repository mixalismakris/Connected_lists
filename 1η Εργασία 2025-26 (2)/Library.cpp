#include "Library.h"
#include <iostream>
using namespace std;

// Υλοποίση constructor της κλάσης CopyNode
CopyNode::CopyNode(int c, std::string s) {
    copyID = c;  //Αρχικοποιήση τιμών
    status = s;
    next = nullptr;

    
}

// Υλοποίση constructor της κλάσης BookNode
BookNode::BookNode(std::string d, std::string a, std::string isbn) {
    title = d; //Αρχικοποίηση τιμών
    author = a;
    ISBN = isbn;
    copiesHead = nullptr;
    next = nullptr;

}
void BookNode::addCopy(int copyid, std::string status) {
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
void Library::addBook(std::string title, std::string author, std::string isbn) {
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
void Library::removeBook(std::string isbn) {

}
BookNode* Library::findBook(std::string isbn) {
    return nullptr;
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
void Library::loadFromFile(const std::string& filename) {

}
void Library::saveToFile(const std::string& filename) {
    
}