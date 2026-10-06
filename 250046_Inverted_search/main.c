#include "inverted.h"

int main(int argc, char *argv[])
{
    F_node *head = NULL;  // Head pointer for file list
    M_node *HT[27];  // Hash table with 27 buckets (A-Z + special)
    int i;  // Loop counter
    int option;  // User menu choice

    // Initialize all hash table entries to NULL
    for (i = 0; i < 27; i++)
    {
        HT[i] = NULL;
    }

    // If files passed as arguments, add them to the file list
    if (argc > 1)  // Arguments provided
    {
        validate_files(argv, &head);  // Validate and add files
    }  // End of if

    // Display menu and process user choices until exit
    do  // Start of menu loop
    {
        printf("Select your choice among following operations:\n1. Create Database\n2. Display Database\n3. Save Database\n4. Search\n5. Update Database\n6. Exit\n\nEnter your choice : ");  // Display menu

        scanf("%d", &option);  // Read user choice

        // Handle user menu selection
        switch (option)  // Switch on user choice
        {
            case 1:  // Create database from files
                create_database(HT, head);  // Call create function
                break;  // Exit case

            case 2:  // Display entire database
                display_database(HT);  // Call display function
                break;  // Exit case

            case 3:  // Save database to file
                save_database(HT);  // Call save function
                break;  // Exit case

            case 4:  // Search for word in database
                search_database(HT);  // Call search function
                break;  // Exit case

            case 5:  // Add new file and rebuild database
                update_database(HT, &head);  // Call update function
                break;  // Exit case

            case 6:  // Exit program
                break;  // Exit case

            default:  // Invalid menu choice
                printf("INFO : Please enter the valid option\n");  // Print error message
                break;  // Exit case
        }  // End of switch
    } while (option != 6);  // End of menu loop

    return 0;
}
