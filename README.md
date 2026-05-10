Library Management System
A C++ console application for managing books and their copies in a library, built as a university assignment for the Data Structures course (2025-2026).
Overview
The program implements a "list of lists" data structure using linked lists (no STL containers or arrays). A sorted linked list of books (LOB) is maintained alphabetically by title, where each book node holds a pointer to its own sorted linked list of copies (LOC), ordered by copy ID.
Features

Load/save library data from/to a text file
Add and remove books (sorted insertion by title)
Add and remove copies of a book (sorted insertion by copy ID)
Borrow and return copies with status tracking (available, borrowed, damaged)
Search books by ISBN
Display all books with available/total copy counts
Full dynamic memory management with proper cleanup

File Structure

Library.h — Class definitions for CopyNode, BookNode, and Library
Library.cpp — Method implementations
main.cpp — Menu loop and user interaction
CreateBooksLibrary.py — Helper script to generate sample library.txt data

Build & Run
bashg++ -o library main.cpp Library.cpp
./library
Data Format
The library.txt file uses pipe-delimited records:
BOOK|978-960-01-0001-1|Algorithms|Cormen
COPY|1|available
COPY|2|borrowed
BOOK|978-960-01-0002-8|Data Structures|Sahni
COPY|1|available
