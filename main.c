#include <stdio.h>
#include <stdlib.h>
#include "library.h"          //we include our own library.h file using quotes "" instead of angle brackets <>.

int main() {
    // Initialize our library data storage
    Book library[MAX_BOOKS];
    
    
    
    //int bookCount = 0; //We had this before. This would keep track of how many books we have in our library array
    // INSTEAD OF int bookCount = 0; WE ARE NOW LOADING THE DATA HERE: (for data persistence)

    int bookCount = loadData(library);

    if (bookCount > 0) {
        printf("\nSuccessfully loaded %d books from previous session.\n", bookCount);
    } else {
        printf("\nNo previous data found. Starting with an empty library.\n");
    }

    int choice;

    // This loop keeps the menu running until the user chooses to exit
    while (1) {             //creates an infinite loop. The only way out is if the user presses 0, which triggers the exit(0) function to safely shut down the program.
        printf("\n====================================\n");
        printf("    LIBRARY MANAGEMENT SYSTEM       \n");
        printf("====================================\n");
        printf("1. Add New Book\n");
        printf("2. Display All Books\n");
        printf("3. Search Book by ID\n");
        printf("4. Issue Book\n");
        printf("5. Return Book\n");
        printf("6. Save Data to File\n");
        printf("0. Exit\n");
        printf("====================================\n");
        printf("Enter your choice: ");
        
        // Read the user's choice
        scanf("%d", &choice);                        //This waits for the librarian to type a number and press Enter. The & symbol is crucial in C. 
                                                     // It passes the memory address of the choice variable so scanf knows exactly where to store the input.

        // Route the choice to the correct function
        switch (choice) {
                                                    // Modular preparation: Right now, our case statements just print placeholders. In the next steps, we will replace those printf lines with actual function calls like addBook()
            case 1:                                 // When the librarian selects option 1, we print a message indicating that they chose to add a new book.
                
                printf("\n-> You chose: Add New Book (Logic coming soon!)\n");
                // We pass the array, and the MEMORY ADDRESS (&) of bookCount

                addBook(library, &bookCount);
                break;
            
            case 2:
                // We do NOT use the & symbol here, just the variable name

                displayBooks(library, bookCount);
                break;
            
            case 3:
                searchBook(library, bookCount);
                break;
            
            case 4:
                issueBook(library, bookCount);
                break;
            case 5:
                returnBook(library, bookCount);
                break;

            case 6:
                saveData(library, bookCount);
                break;
            case 0:
                printf("\nExiting the system. Goodbye!\n");
                exit(0); // This cleanly terminates the program
            default:
                printf("\nInvalid choice! Please select a number between 0 and 6.\n");
        }
    }

    return 0;
}