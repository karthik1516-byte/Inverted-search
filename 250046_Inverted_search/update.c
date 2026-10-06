#include "inverted.h"

// Add new file to database and rebuild inverted index
int update_database(M_node *HT[], F_node **head)
{
    char file_name[20];  // Buffer for file name input

    printf("Enter the file name to add : ");  // Prompt user
    scanf("%19s", file_name);  // Read file name

    // Check if file already exists in list
    if (check_duplicates(*head, file_name) == SUCCESS)  // File exists in list
    {
        printf("INFO : File already exists in database.\n");  // Print duplicate message
        return FAILURE;  // Return failure
    }  // End of if

    // Check if file exists in file system
    if (fopen(file_name, "r") == NULL)  // File not found in directory
    {
        printf("INFO : File '%s' does not exist in the current directory.\n", file_name);  // Print not found message
        return FAILURE;  // Return failure
    }  // End of if

    // Add file to linked list
    if (insert_last(head, file_name) == FAILURE)  // Addition failed
    {
        printf("INFO : Unable to add file to database.\n");  // Print error message
        return FAILURE;  // Return failure
    }  // End of if

    create_database(HT, *head);  // Rebuild database with new file
    return SUCCESS;  // Return success
}  // End of function
