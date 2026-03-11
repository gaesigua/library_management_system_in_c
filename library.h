#ifndef LIBRARY_H
#define LIBRARY_H

#define MAX_TITLE 100
#define MAX_AUTHOR 50
#define MAX_BOOKS 100 // Let's set a maximum capacity for our library array

typedef struct {
    int id;
    char title[MAX_TITLE];
    char author[MAX_AUTHOR];
    int isIssued; // 0 for available, 1 for issued
} Book;              // / This is the Book type the compiler is looking for

// Add function signature: We declare the addBook function prototype

void addBook(Book library[], int *bookCount);        //This is the addBook declaration


// Read function signature: We are declaring this to be able to read the library data and display it in the future.
void displayBooks(Book library[], int bookCount);


// Search function signature: We are declaring this to be able to search for a book by its ID in the future.
void searchBook(Book library[], int bookCount);

// Issue and Return function signatures: we are declaring these to be able to issue and return books in the future.
void issueBook(Book library[], int bookCount);
void returnBook(Book library[], int bookCount);


// File handling function signatures: We are declaring these to be able to save our library data to a file and load it back when the program starts in the future.
void saveData(Book library[], int bookCount);
int loadData(Book library[]);

#endif