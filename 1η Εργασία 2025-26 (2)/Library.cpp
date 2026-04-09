#include <sstream>
#include <fstream>
#include "Library.h"
#include <iostream>
using namespace std;

// Βοηθητική συνάρτηση για την διάσπαση μιας γραμμής από το αρχείο σε tokens με βάση τον διαχωριστή '|'
vector<string> parseLine(const std::string& line, char delim) {
    vector<string> tokens;
    stringstream ss(line);
    string token;
    while (getline(ss, token, delim)) { 
        tokens.push_back(token);
    }
    return tokens;
}

// Υλοποίηση constructor της κλάσης CopyNode
CopyNode::CopyNode(int c, string s) {
    copyID = c;  //Αρχικοποιήση τιμών
    status = s;
    next = nullptr;
    
}

// Υλοποίηση constructor της κλάσης BookNode
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
    CopyNode* current = copiesHead; // διάτρεξη λίστας από την αρχή
    while(current){ //όσο υπάρχει κόμβος, επανέλαβε
        if (current -> copyID == copyid ){ //αν το copyid ισούται με αυτό που ψάχνουμε
            if(current -> status == "available"){
                current -> status = "borrowed";// αν είναι διαθέσιμο , άλλαξε την κατάσταση του σε δανεισμένο.
                return true;//βρέθηκε
            }
            return false;//άλλιως, δεν είναι διαθέσιμο (damaged/borrowed)

        }
        current = current -> next;//προχωράμε σε επόμενο κόμβο
    }

    return false; //δεν βρέθηκε
}
void BookNode::removeCopy(int copyid) {
    if (!copiesHead){ //αν η λίστα είναι κενή
        cout << "Δεν υπάρχουν αντίγραφα!"<< endl;
        return;
    }
    CopyNode* current = copiesHead;//αρχή της λίστας για διάτρεξη
    if (current ->copyID == copyid ){ //Αν αφαιρείται το πρώτο αντίγραφο
        if(current -> status == "borrowed"){ //είναι δανεισμένο
                cout <<"Το αντίγραφο έχει δανειστεί! Δεν μπορει να διαγραφεί."<<endl;
                return;
            }
        copiesHead = current -> next; //αν δεν είναι δανεισμένο ,ο πρώτος κόμβος γίνεται ο αμέσως επόμενος
        delete current;// διαγραφή τωρινού
        return;
    }
    while(current && current -> next){//όσο υπάρχει ο τωρινός κόμβος αλλα ΚΑΙ ο επόμενος, επανέλαβε
        if (current -> next -> copyID == copyid){ //ελέγχουμε τον επόμενο του τωρινόυ,για ευκολότερη αντιμετάθεση
            if(current -> next -> status == "borrowed"){ //είναι δανεισμένο
                cout <<"Το αντίγραφο έχει δανειστεί! Δεν μπορει να διαγραφεί."<<endl;
                return;
            }
            else{
                CopyNode* toDelete = current -> next; //προσωρινή μεταβλητή που βάζουμε τον προς διαγραφή δέικτη του επόμενου του τωρινόυ
                current -> next = current -> next -> next; //στον δείκτη του επόμενο του τωρινόυ βάζουμε τον ΕΠΟΜΕΝΟ του επομένου
                delete toDelete; //διαγράφουμε τον προς διαγραφή κόμβο
                return;
            }
        }
        current = current -> next; //διάσχηση λίστας
    }
    cout << "Το αντίγραφο δεν βρέθηκε." << endl;

}
void BookNode::returnCopy(int copyid) {
    CopyNode* current = copiesHead; // διάτρεξη λίστας από την αρχή
    while (current)//όσο υπάρχει κόμβος, επανέλαβε
    {
        if(current -> copyID == copyid){ //αν το copyid ισούται με αυτό που ψάχνουμε
            if (current -> status != "borrowed"){ //το βιβλίο δεν είναι δανεισμένο
                cout << "Το αντίγραφο δεν έχει δανειστεί!"<<endl;
                return;
            }
            string answer; //μεταβλητή για καταχώριση απάντησης
            while(true){//ώστε να γίνεται έλεγχος εγκυρότητας
                cout<<"Είναι το αντίτυπο σε καλή κατάσταση; (y/n)"<< endl; // ζητείται από τον χρήστη αν το βιβλίο είναι σε καλή κατάσταση
                cin >> answer;
                if (answer == "y" || answer == "Y" ){
                    current -> status = "available"; //αλλαγή κατάστασης σε διαθέσιμο
                    cout <<"Επιστράφηκε το βιβλίο σε καλή κατάσταση." <<endl;
                    return;
                }
                else if (answer == "n" || answer == "N"){
                    current -> status = "damaged"; //αλλαγή κατάστασης σε κατεστραμένο
                    cout <<"Επιστράφηκε το βιβλίο σε κακή κατάσταση." <<endl;
                    return;
                }
                else{
                    cout << "Παρακαλώ δώστε έγκυρη απάντηση (y/n)"<<endl;
                }
            }
        }
        current = current -> next;
    }
    cout << "Το αντίτυπο δεν βρέθηκε!"<< endl;

}
int BookNode::countAvailable() {
    int count = 0;
    CopyNode* current = copiesHead;//βρίσκουμε την αρχή της δευτερεύουσας λίστας για να την διατρέξουμε
    while(current){ //όσο υπάρχει κόμβος
        if(current -> status == "available") count += 1;  //αν διαθέσιμο,αύξηση του μετρητή
        current = current -> next; //επόμενος κόμβος
    }

    return count;
}

// Υλοποίηση της κλάσης Library
Library::Library() {
    booksHead = nullptr;

}
Library::~Library() {//καταστροφέας, αδειάζουμε όλη την μνήμη από τα βιβλία
    BookNode* currentBook = booksHead; //ώστε να διατρέξουμε την λίστα με τα βιβλία
    CopyNode* currentCopy;//ώστε να διατρέξουμε τις λίστες με τα αντίγραφα
    while(currentBook){//όσο υπάρχει βιβλίο
        currentCopy = currentBook -> copiesHead; //κεφαλή της λίστας των αντιγράφων του συγκεκριμένου βιβλίου
        while(currentCopy){
            CopyNode* toDeleteCopy = currentCopy; //αποθηκεύουμε το τωρινό αντίγραφο σε προσωρινή μεταβλητή ώστε να αντιγραφή
            currentCopy = currentCopy -> next; //επόμενος κόμβος
            delete toDeleteCopy; //διαγραφή αντιγράφου
        }
        BookNode* toDeleteBook = currentBook; //αποθηκεύουμε το τωρινό βιβλίο σε προσωρινή μεταβλητή ώστε να αντιγραφή
        currentBook = currentBook ->next; //επόμενος κόμβος
        delete toDeleteBook; //διαγραφή βιβλίου
    }

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
    BookNode* current = booksHead; // βρίσκουμε την κεφαλή της κύριας λίστας
    BookNode* previous = nullptr; //θα αποθηκεύουμε τον προηγούμενο κόμβο
    while (current ){//όσο υπάρχει κόμβος κύριας λίστας 
        if (current -> ISBN == isbn){ //αν το isbn αντιστοιχεί
            CopyNode* currentOfCopies = current -> copiesHead; //βρίσκουμε την κορυφή της λίστας των αντιγράφων του βιβλίου
            while(currentOfCopies){ //όσο υπάρχουν αντίγραφα
                if(currentOfCopies -> status == "borrowed"){ //αν έστω και ένα βιβλίο έχει δανειστεί , η διαγραφή ακυρώνεται
                    cout << "Υπάρχει δανεισμένο αντίγραφο! Το βιβλίο δεν μπορεί να διαγραφεί"<<endl; 
                    return;
                }
                currentOfCopies = currentOfCopies-> next;//διατρέχουμε την λίστα των αντιγράφων
            }
            //εφόσον περάσαμε την παραπάνω συνθήκη, μπορεί να αρχίσει η διαγραφή
            currentOfCopies = current -> copiesHead; //ξανά αρχικοποιούμε την κεφαλή των αντιγράφων
            while (currentOfCopies){
                CopyNode* toDelete = currentOfCopies; //αποθηκεύουμε τον διαγραφέντα κόμβο
                currentOfCopies = currentOfCopies -> next; // προχωράμε στον επόμενο
                delete toDelete;//διαγραφή αντιγράφου
                
            }
            //εφόσον φτάσουμε εδώ, έχουμε αδιάσει από αντίγραφα και είμαστε έτοιμη για αντιγραγή βιβλίου
            if (!previous){//ειδική περίπτωση πρώτου βιβλίου, δεν έχει πάρει τιμή το previous
                booksHead = current -> next;
                delete current;
                return;

            }
            else{//υπόλοιπες περιπτώσεις, έχει γίνει μια επανάληψη
                previous-> next = current -> next;
                delete current;
                return;


            }
            



        }
        previous = current; //αποθηκεύουμε τον τωρινό στη μεταλητή previous ώστε να τον έχουμε μετά για αντιμετάθεση
        current = current -> next;//προχωράμε στον επόμενο
       

    }
    cout << "Το βιβλίο δεν υπάρχει!"<<endl;

}

BookNode* Library::findBook(string isbn) {
    BookNode* current = booksHead; // Ξεκινάμε από την κεφαλή της λίστας, δηλαδή το πρώτο βιβλίο
    
    while (current) { //Όσο δεν έχουμε φτάσει στο τέλος της λίστας  
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
            cout << "Αριθμός διαθέσιμων αντιγράφων: " << current -> countAvailable() << endl;

            int totalCopies = 0; //μετρητής συνολικών αντιγράφων
            CopyNode* currentCopy = current -> copiesHead; //κεφαλή λίστας αντιγράφων για διάτρεξη.
            while(currentCopy){
                totalCopies++; //αυξάνουμε τα συνολικά αντίγραφα κατά ένα
                currentCopy = currentCopy -> next;//προχωράμε στον επόμενο κόμβο της λίστας

            }
            //έχουμε τον συνολικό αριθμό αντιγράφων, damaged και μη
            cout << "Αριθμός συνολικών αντιγράφων: " << totalCopies << endl;

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
            BookNode* b = findBook(lastIsbn); // Βρίσκουμε το βιβλίο με το τελευταίο ISBN που διαβάσαμε 
            if (b) { // Εάν το βιβλίο βρέθηκε, προσθέτουμε το αντίγραφο στο βιβλίο χρησιμοποιώντας τη μέθοδο addCopy
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
        // Ανοίγουμε αρχείο για εγγραφή (ofstream)
        // Διαγράφει τα παλιά περιεχόμενα και γράφει από την αρχή!
    ofstream file(filename);

    // Έλεγχος αν το αρχείο άνοιξε επιτυχώς
    if (!file.is_open()) {
        cout << "Σφάλμα: Δεν ήταν δυνατό το άνοιγμα του αρχείου για αποθήκευση.\n";
        return;
    }

    BookNode* currentBook = booksHead; // Ξεκινάμε από την κεφαλή της λίστας βιβλίων
    while (currentBook) {
        // Γράφουμε τις πληροφορίες του βιβλίου στο αρχείο με τη μορφή "BOOK|ISBN|Title|Author"
        file << "BOOK|" << currentBook->ISBN << "|" << currentBook->title << "|" << currentBook->author << "\n";
        
        CopyNode* currentCopy = currentBook->copiesHead; // Ξεκινάμε από την κεφαλή της λίστας αντιγράφων του τρέχοντος βιβλίου
        while (currentCopy) {
            file << "COPY|" << currentCopy->copyID << "|" << currentCopy->status << "\n"; // Γράφουμε τις πληροφορίες του αντιγράφου με τη μορφή "COPY|CopyID|Status"
            currentCopy = currentCopy->next; // Προχωράμε στον επόμενο κόμβο της λίστας αντιγράφων
        }
        currentBook = currentBook->next; // Προχωράμε στον επόμενο κόμβο της λίστας βιβλίων
    }
    file.close(); // Κλείνουμε το αρχείο μετά την ολοκλήρωση της εγγραφής
    cout << "Η βιβλιοθήκη αποθηκεύτηκε επιτυχώς στο αρχείο: " << filename << "\n";

}