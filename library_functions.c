#include <stdio.h>
#include <string.h>     // We need this for string manipulation
#include "library.h"

void addBook(Book library[], int *bookCount) {
    
    // 1. Check if the library is full

    if (*bookCount >= MAX_BOOKS) {
        printf("\nError: Library is full. Cannot add more books.\n");
        return;
    }

    // 2. Create a temporary Book struct to hold the new data
    
    
    Book newBook;

    printf("\nEnter Book ID: ");
    scanf("%d", &newBook.id);

    // THE C TRAP: scanf leaves a newline character ('\n') in the input buffer.
    // Clear the newline character left by scanf before we use fgets to read strings. If we don't do this, fgets will read the leftover '\n' and think it's an empty string.

    while (getchar() != '\n'); 

    printf("Enter Book Title: ");

    // We use fgets instead of scanf for strings because scanf stops at the first space.
    // fgets reads the whole line, including spaces (e.g., "Ibitaramo ku Mateka y’u Rwanda").  // Book by Kagiraneza Zephyrin

    fgets(newBook.title, MAX_TITLE, stdin);

    newBook.title[strcspn(newBook.title, "\n")] = 0; // Remove trailing newline    // fgets adds the '\n' to the string when you press Enter. We want to remove that.

    printf("Enter Book Author: ");
    fgets(newBook.author, MAX_AUTHOR, stdin);
    newBook.author[strcspn(newBook.author, "\n")] = 0; // Remove trailing newline

    // 3. Set default status
    newBook.isIssued = 0; // 0 means available

    // 4. Save the book into our array and increment the counter
    library[*bookCount] = newBook;
    (*bookCount)++;       // The parentheses are required here due to C's order of operations

    printf("\nSuccess: '%s' added to the library!\n", newBook.title);
}

void displayBooks(Book library[], int bookCount) {
    // 1. Check if the library is empty
    if (bookCount == 0) {
        printf("\nThe library is currently empty. Please add some books first!\n");
        return;
    }

    // 2. Print the table header
    printf("\n===============================================================================\n");
    // The minus sign (e.g., %-30s) means "left-align this text in a space of 30 characters"
    printf("%-5s | %-35s | %-20s | %-10s\n", "ID", "TITLE", "AUTHOR", "STATUS");
    printf("===============================================================================\n");

    // 3. Loop through the array and print each book
    for (int i = 0; i < bookCount; i++) {
        // We use a ternary operator (? :) to print "Issued" or "Available" based on the 0 or 1 integer
        printf("%-5d | %-35s | %-20s | %-10s\n", 
               library[i].id, 
               library[i].title, 
               library[i].author, 
               library[i].isIssued == 0 ? "Available" : "Issued");
    }
    printf("===============================================================================\n");
}

void searchBook(Book library[], int bookCount) {
    if (bookCount == 0) {
        printf("\nThe library is currently empty.\n");
        return;
    }

    int searchId;
    printf("\nEnter the Book ID to search for: ");
    scanf("%d", &searchId);

    // Loop through our array to find a match
    for (int i = 0; i < bookCount; i++) {
        if (library[i].id == searchId) {
            // We found a match! Print the details and exit the function early.
            printf("\n--- Book Found ---\n");
            printf("ID: %d\n", library[i].id);
            printf("Title: %s\n", library[i].title);
            printf("Author: %s\n", library[i].author);
            printf("Status: %s\n", library[i].isIssued == 0 ? "Available" : "Issued");
            printf("------------------\n");
            return; // Exit the function immediately since IDs are unique
        }
    }

    // If the loop finishes without hitting the 'return' above, the book doesn't exist.
    printf("\nSorry, no book found with ID: %d\n", searchId);
}

void issueBook(Book library[], int bookCount) {
    if (bookCount == 0) {
        printf("\nThe library is currently empty.\n");
        return;
    }

    int issueId;
    printf("\nEnter the Book ID to issue: ");
    scanf("%d", &issueId);

    for (int i = 0; i < bookCount; i++) {
        if (library[i].id == issueId) {
            // We found the book! Now check if it's already issued.
            if (library[i].isIssued == 1) {
                printf("\nSorry, '%s' is already issued to someone else.\n", library[i].title);
            } else {
                // Flip the flag to 1 (Issued)
                library[i].isIssued = 1;
                printf("\nSuccess: '%s' has been issued.\n", library[i].title);
            }
            return; // We are done, exit the function
        }
    }
    printf("\nSorry, no book found with ID: %d\n", issueId);
}

void returnBook(Book library[], int bookCount) {
    if (bookCount == 0) {
        printf("\nThe library is currently empty.\n");
        return;
    }

    int returnId;
    printf("\nEnter the Book ID to return: ");
    scanf("%d", &returnId);

    for (int i = 0; i < bookCount; i++) {
        if (library[i].id == returnId) {
            // We found the book! Now check if it's actually issued.
            if (library[i].isIssued == 0) {
                printf("\nNotice: '%s' is already in the library. It wasn't issued.\n", library[i].title);
            } else {
                // Flip the flag back to 0 (Available)
                library[i].isIssued = 0;
                printf("\nSuccess: '%s' has been returned and is now available.\n", library[i].title);
            }
            return; // We are done, exit the function
        }
    }
    printf("\nSorry, no book found with ID: %d\n", returnId);
}

void saveData(Book library[], int bookCount) {
    // Open a file named "library.dat" in "Write Binary" mode
    FILE *file = fopen("library.dat", "wb");
    
    if (file == NULL) {
        printf("\nError: Could not open file for saving.\n");
        return;
    }

    // 1. Save the total number of books first
    fwrite(&bookCount, sizeof(int), 1, file);
    
    // 2. Save the entire array of structs in one single line of code!
    fwrite(library, sizeof(Book), bookCount, file);
    
    fclose(file); // ALWAYS close your files to prevent memory leaks
    
    printf("\nSuccess: Library data saved to 'library.dat'!\n");
}

int loadData(Book library[]) {
    // Open the file in "Read Binary" mode
    FILE *file = fopen("library.dat", "rb");
    
    if (file == NULL) {
        // If the file doesn't exist yet (like on the very first run), just return 0 books
        return 0;
    }

    int count = 0;
    
    // 1. Read the total number of books
    fread(&count, sizeof(int), 1, file);
    
    // 2. Read all the books directly into our array
    fread(library, sizeof(Book), count, file);
    
    fclose(file);
    
    return count; // Return the loaded count so main() knows how many books we have
}