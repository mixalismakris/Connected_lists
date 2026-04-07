#include <iostream>
#include <windows.h> // Για την χρήση του SetConsoleOutputCP ώστε να εμφανίζονται σωστά τα ελληνικά στην κονσόλα
#include "Library.h"
using namespace std;

int main() {
    SetConsoleOutputCP(CP_UTF8); // Ορισμός του κωδικοποιητή για την σωστή εμφάνιση ελληνικών χαρακτήρων
    Library lib;

    lib.loadFromFile("library.txt");

    cout << "\n--- Λίστα βιβλίων  ---\n";
    lib.printAll();

    return 0;
}