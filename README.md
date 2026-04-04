Δομές Δεδομένων — 1η Εργασία 2025-26
Σύστημα Διαχείρισης Βιβλιοθήκης (Λίστα από Λίστες)
Προθεσμία: Πέμπτη 30 Απριλίου 2026

Δομή Αρχείων
├── Library.h           // Ορισμοί κλάσεων: CopyNode, BookNode, Library
├── Library.cpp         // Υλοποίηση μεθόδων
├── main.cpp            // Μενού + main()
├── CreateBooksLibrary.py  // Δημιουργία library.txt
├── library.txt         // Αρχείο δεδομένων (δημιουργείται από το .py)
└── README.md           // Αυτό το αρχείο

Βάζουμε και τις 3 κλάσεις (CopyNode, BookNode, Library) μέσα στο Library.h
γιατί η μία εξαρτάται από την άλλη. Η υλοποίηση πάει στο Library.cpp.


Πλάνο Υλοποίησης — Βήμα-Βήμα
Βήμα 1 ✏️ — Σκελετοί κλάσεων (Library.h)
Στόχος: Να κάνει compile χωρίς να κάνει τίποτα.
Γράφουμε στο Library.h:

CopyNode: πεδία copyID, status, next + constructor
BookNode: πεδία title, author, ISBN, copiesHead, next + constructor + δηλώσεις μεθόδων (κενές)
Library: πεδίο booksHead + constructor + δηλώσεις μεθόδων (κενές)

Στο Library.cpp βάζουμε κενά bodies για κάθε μέθοδο.
Στο main.cpp βάζουμε ένα απλό int main() { return 0; }.
Τεστ: g++ -o library main.cpp Library.cpp — πρέπει να κάνει compile χωρίς errors.

 CopyNode: πεδία + constructor
 BookNode: πεδία + constructor + κενές μέθοδοι
 Library: πεδία + constructor + κενές μέθοδοι
 Compile OK


Βήμα 2 🔗 — Λίστα αντιτύπων LOC (BookNode::addCopy)
Στόχος: Sorted insertion αντιτύπων βάσει copyID.
Υλοποιούμε τη BookNode::addCopy(copyId, status):

Δημιουργία νέου CopyNode
Εύρεση σωστής θέσης στη λίστα (ταξινομημένη βάσει copyID)
Εισαγωγή στη σωστή θέση (προσοχή στην περίπτωση εισαγωγής στην αρχή!)

Τεστ στη main:
cppBookNode book("Test Book", "Author", "123-456");
book.addCopy(3);
book.addCopy(1);
book.addCopy(2);
// Εκτύπωση: πρέπει να βγαίνει 1 → 2 → 3

 addCopy με sorted insertion
 Τεστ: εισαγωγή σε τυχαία σειρά → εκτύπωση σε σωστή σειρά


Βήμα 3 📚 — Λίστα βιβλίων LOB (Library::addBook + printAll)
Στόχος: Sorted insertion βιβλίων βάσει title + εκτύπωση.
Υλοποιούμε:

Library::addBook(title, author, isbn) — sorted insertion βάσει title (με < operator σε strings)
Library::printAll() — διατρέχει τη LOB και τυπώνει κάθε βιβλίο

Τεστ στη main:
cppLibrary lib;
lib.addBook("Data Structures", "Sahni", "978-1");
lib.addBook("Algorithms", "Cormen", "978-2");
lib.addBook("C++ Primer", "Lippman", "978-3");
lib.printAll();
// Πρέπει να βγαίνει: Algorithms → C++ Primer → Data Structures

 addBook με sorted insertion
 printAll
 Τεστ: τυχαία σειρά → αλφαβητική εκτύπωση


Βήμα 4 📂 — Φόρτωση από αρχείο (loadFromFile)
Στόχος: Διαβάζουμε το library.txt και χτίζουμε τις λίστες.

Τρέχουμε πρώτα το CreateBooksLibrary.py με NUM_BOOKS=3 για μικρό αρχείο
Συμπληρώνουμε τα δύο TODO στη loadFromFile():

Για γραμμή BOOK: καλούμε addBook()
Για γραμμή COPY: βρίσκουμε τον τελευταίο BookNode που μπήκε, καλούμε addCopy()


Χρησιμοποιούμε τη parseLine() που μας δίνεται

Τεστ:
cppLibrary lib;
lib.loadFromFile("library.txt");
lib.printAll();
// Ελέγχουμε ότι βγαίνουν αλφαβητικά με σωστά αντίτυπα

 loadFromFile: BOOK branch
 loadFromFile: COPY branch
 Τεστ με μικρό library.txt (3 βιβλία)


Βήμα 5 🔍 — Αναζήτηση (findBook + Επιλογή 4)
Στόχος: Βρίσκουμε βιβλίο βάσει ISBN.

Library::findBook(isbn) — διατρέχει τη LOB, επιστρέφει BookNode* ή nullptr
Λογική μενού Επιλογή 4: ζητά ISBN, εμφανίζει στοιχεία + λίστα αντιτύπων
 findBook
 Επιλογή 4 στο menu


Βήμα 6 🗑️ — Διαγραφές + Destructor
Στόχος: Σωστή αποδέσμευση μνήμης. ΠΡΟΣΟΧΗ ΣΤΟΥΣ ΔΕΙΚΤΕΣ!
Υλοποιούμε:

BookNode::removeCopy(copyId) — αφαίρεση κόμβου από LOC + delete
Library::removeBook(isbn) — πρώτα σβήνει ΟΛΑ τα copies, μετά τον BookNode + σύνδεση prev→next
~Library() — destructor: σβήνει κάθε BookNode (μαζί με τα copies του)

Αποκλεισμοί:

removeBook: αν κάποιο αντίτυπο είναι "borrowed" → ΑΠΟΡΡΙΨΗ
removeCopy: αν αντίτυπο είναι "borrowed" → ΑΠΟΡΡΙΨΗ

Τεστ:
cpp// Φόρτωσε, διέγραψε copy, διέγραψε book, printAll
// Ιδανικά τρέξε με valgrind: valgrind ./library

 removeCopy
 removeBook (ελέγχει borrowed πρώτα)
 ~Library destructor
 Τεστ: κανένα memory leak


Βήμα 7 📖 — Δανεισμός & Επιστροφή
Στόχος: Αλλαγή status αντιτύπων.

BookNode::borrowCopy(copyId) — αλλάζει σε "borrowed" ΜΟΝΟ αν "available"
BookNode::returnCopy(copyId) — ρωτά τον χρήστη: καλή κατάσταση; "available" : "damaged"
BookNode::countAvailable() — μετράει copies με status == "available"
 borrowCopy
 returnCopy (με ερώτηση κατάστασης)
 countAvailable


Βήμα 8 💾 — Αποθήκευση (saveToFile)
Στόχος: Γράφουμε τη δομή πίσω στο αρχείο.

Library::saveToFile(filename) — γράφει σε ΙΔΙΑ μορφή με library.txt
Μορφή: BOOK|ISBN|title|author ακολουθούμενο από COPY|copyId|status

Τεστ κύκλου:
loadFromFile → κάνε αλλαγές → saveToFile → loadFromFile → printAll
// Πρέπει να βγαίνει σωστά!

 saveToFile
 Τεστ: load → save → load → verify


Βήμα 9 📋 — Menu Loop (main.cpp)
Στόχος: Ολοκλήρωση menu με όλες τις επιλογές 0-11.
Στο main.cpp:

while loop με εμφάνιση μενού
switch/if-else για κάθε επιλογή
Σωστά μηνύματα σφάλματος (ISBN δεν βρέθηκε, αντίτυπο ήδη borrowed, κ.λπ.)
Επιλογή 0: ρωτά αν θέλει αποθήκευση πριν κλείσει
Επιλογή 1: αν υπάρχει ήδη φορτωμένη, ζητά επιβεβαίωση

ΕπιλογήΛειτουργίαΧρησιμοποιεί1ΦόρτωσηloadFromFile, ~Library2ΑποθήκευσηsaveToFile3ΕμφάνισηprintAll4ΑναζήτησηfindBook5Νέο βιβλίοaddBook (ελέγχει ISBN)6Διαγραφή βιβλίουremoveBook7Νέο αντίτυποfindBook → addCopy8Διαγραφή αντιτύπουfindBook → removeCopy9ΔανεισμόςfindBook → borrowCopy10ΕπιστροφήfindBook → returnCopy11ΔιαθέσιμαfindBook → countAvailable0ΈξοδοςsaveToFile (προαιρετικά)

 Menu loop
 Κάθε επιλογή συνδεδεμένη
 Μηνύματα σφάλματος
 Επιβεβαιώσεις (load over existing, save before exit)


Βήμα 10 ✅ — Testing + Σχόλια + Τεκμηρίωση
Στόχος: Τελικός έλεγχος & παράδοση.
Edge cases να τεστάρετε:

Κενή βιβλιοθήκη: printAll, save, search
Διαγραφή βιβλίου με borrowed αντίτυπα → πρέπει να αρνηθεί
Διπλό ISBN στο addBook → πρέπει να αρνηθεί
Δανεισμός ήδη borrowed αντιτύπου → πρέπει να αρνηθεί
Επιστροφή available αντιτύπου → πρέπει να αρνηθεί
Load πάνω σε υπάρχουσα βιβλιοθήκη → πρέπει να ρωτήσει
Μεγάλο αρχείο (NUM_BOOKS=50) → λειτουργεί κανονικά;

Τεκμηρίωση:

Σχόλια σε κάθε μέθοδο (τι κάνει, παράμετροι, τι επιστρέφει)
Ξεχωριστό κείμενο: περιγραφή δομών, αλγόριθμοι insertion/deletion, δυσκολίες
 Edge case testing
 Σχόλια στον κώδικα
 Κείμενο τεκμηρίωσης
 Valgrind: 0 leaks
 Τελικό compile + εκτέλεση


Πρόταση Μοιράσματος Δουλειάς
Άτομο ΑΆτομο ΒΒήμα 2: addCopy (LOC)Βήμα 3: addBook + printAll (LOB)Βήμα 6: removeCopy + destructorΒήμα 4: loadFromFileΒήμα 7: borrow/return/countΒήμα 5: findBookΒήμα 8: saveToFileΜαζί: Βήμα 1 (σκελετοί), Βήμα 9 (menu), Βήμα 10 (testing)

Σημαντικές Υπενθυμίσεις
⚠️ ΜΗΝ χρησιμοποιήσετε C++ containers (vector, list, map, κ.λπ.) — μόνο δικές σας linked lists
⚠️ ΜΗΝ χρησιμοποιήσετε πίνακες (arrays) για τις λειτουργίες
⚠️ Η εισαγωγή πρέπει να είναι sorted insertion — ΟΧΙ εισαγωγή + sort μετά
⚠️ Κάθε new πρέπει να έχει αντίστοιχο delete — τσεκάρετε με valgrind
