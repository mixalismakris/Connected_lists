#define once  //ώστε να αποτραπεί ο ορισμός των κλάσεων δεύτερη φορά σε περίπτωση περισσότερων απο ένα include
#include <string>
#include <vector> //Για την βοηθητική συνάρτηση που παρέχεται από εκφώνηση
//αποφεύγεται η χρήση namespace στην βιβλιοθήκη για αποφυγή τυχών ζητημάτων.
class CopyNode; //Επείδη γράφτηκε πρώτα η BookNode αλλά χρησιμοποιείται ένας δείκτης CopyNode σε εκείνη, πρέπει να δηλώσουμε την ύπαρξη της CopyNode

class BookNode {
    private: 
       std::string title; // Αρχικοποίηση των στοιχείων της κλάσης BookNode
       std::string author;
       std::string ISBN;
       
       CopyNode* copiesHead; //Δείκτης τύπου CopyNode που δείχνει στην αρχή της δευτερεύουσας λίστας LOC με τα αντίγραφα των βιβλίων, εφόσον υπάρχει
       BookNode* next; //Δείκτης τύπου BookNode που δείχνει στον επόμενο κόμβο της κύριας λίστας LOB, με την επωνυμία του βιβλίου 

       friend class Library;/*Δίνουμε τις διπλανές ως φιλικές κλάσεις, έτσι ώστε να έχουν πρόρσβαη στα ιδιοτηκά στοιχεία*/
    public:
        BookNode(std::string d , std::string a, std::string isbn); /*Δημιουργία κατασκευαστή ώστε όταν δημιουργηθεί αντικείμενο τύπου BookNod
                                                                    τα στοιχεία του να έχουν αρχικές τιμές*/
        void addCopy(int copyid, std::string status = "available"); // αρχικοποίηση μεθόδων
        void removeCopy(int copyid);
        bool borrowCopy(int copyid);
        void returnCopy(int copyid);
        int countAvailable();

};

class CopyNode{
    private:
        int copyID;  //αρχικοποίηση στοιχείων CopyNode
        std::string status;
        CopyNode* next;

        friend class BookNode; /*Δίνουμε τις διπλανές ως φιλικές κλάσεις, έτσι ώστε να έχουν πρόρσβαη στα ιδιοτικά στοιχεία*/
        friend class Library;

    public:
        CopyNode(int c, std::string s = "available");/*Δημιουργία κατασκευαστή ώστε όταν δημιουργηθεί αντικείμενο τύπου CopyNode
                                                                    τα στοιχεία του να έχουν αρχικές τιμές με προκαθορισμένη στο status
                                                                    available βάση εκφώνησης*/


};

class Library{
    private: 
        BookNode* booksHead; //δείκτης τύπου BookNode, όπου δείχνει στην αρχή της κύριας λίστας με τις επωνυμίες των βιβλίων LOB

    public:
        Library(); // δεν χρειάζεται να αρχικοποιήσουμε παραμέτρους , αφού έχουμε ορίσει μόνο δείκτη που γίνεται αυτόματα nullptr
        ~Library();//καταστροφέας για αποδέσμευση μνήμης
        void addBook(std::string title,std::string author,std::string isbn);
        void removeBook(std::string isbn);
        BookNode* findBook(std::string isbn); //δηλώνεται ως τύπος αντικειμένου BookNode καθώς θα επιστρέψει βιβλίο
        void printAll(); 
        void loadFromFile(const std::string& filename);/*Περνάμε το filename με τέτοιο τρόπο ώστε να περάσει το όνομα κατά αναφορά και να μην δημιουργηθεί
                                                         αντίγραφο στην μνήμη για εξοικονόμιση χώρου και παράλληλα χρησιμοποιείται const για να αποφύγουμε
                                                         τυχόν λανθασμένη αλλαγή στο όνομα του αρχείου  */                                                                                                                       
        void saveToFile(const std::string& filename); 
};
std::vector<std::string> parseLine(const std::string& line, char delim = '|'); //δήλωση της έτοιμης συνάρτησης από εκφώνηση