#include "Library.h"

// Υλοποίση της κλάσης CopyNode
CopyNode::CopyNode(int c, std::string s) {
    
}

// Υλοποίση της κλάσης BookNode
BookNode::BookNode(std::string d, std::string a, std::string isbn) {

}
void BookNode::addCopy(int copyid, std::string status) {

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

}
Library::~Library() {

}
void Library::addBook(std::string title, std::string author, std::string isbn) {

}
void Library::removeBook(std::string isbn) {

}
BookNode* Library::findBook(std::string isbn) {
    return nullptr;
}
void Library::printAll() {

}
void Library::loadFromFile(const std::string& filename) {

}
void Library::saveToFile(const std::string& filename) {
    
}