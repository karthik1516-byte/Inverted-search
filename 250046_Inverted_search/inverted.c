#include "inverted.h"
#include <ctype.h>

// Get hash index from first character of word (0-25 for a-z, 26 for others)
int get_index(char *word)
{
    if (word == NULL || word[0] == '\0')  // Null or empty word
    {
        return 26;  // Return index for special characters
    }

    if (isalpha((unsigned char)word[0]))  // First character is letter
    {
        return tolower((unsigned char)word[0]) - 'a';  // Return 0-25
    }

    return 26;  // Return index for non-alphabetic first character
}

// Insert file name at end of linked list, check for duplicates first
int insert_last(F_node **head, char *f_name)
{
    F_node *new_node;  // New node to insert

    if (check_duplicates(*head, f_name) == SUCCESS)  // File already exists
    {
        return FAILURE;  // Return failure
    }

    new_node = (F_node *)malloc(sizeof(F_node));  // Allocate memory
    if (new_node == NULL)  // Memory allocation failed
    {
        return FAILURE;  // Return failure
    }

    strcpy(new_node->f_name, f_name);  // Copy file name
    new_node->link = NULL;  // Initialize next pointer

    if (*head == NULL)  // List is empty
    {
        *head = new_node;  // New node becomes head
    }
    else  // List is not empty
    {
        F_node *temp = *head;  // Start from head
        while (temp->link != NULL)  // Find last node
        {
            temp = temp->link;
        }
        temp->link = new_node;  // Attach new node at end
    }

    return SUCCESS;  // Return success
}

// Check if file name already exists in the linked list
int check_duplicates(F_node *head, char *f_name)
{
    while (head != NULL)  // Traverse through list
    {
        if (strcmp(head->f_name, f_name) == 0)  // File found
        {
            return SUCCESS;  // Return success (duplicate exists)
        }
        head = head->link;  // Move to next node
    }
    return FAILURE;  // File not found
}

// Print all file names in the linked list
int print_filenames(F_node *head)
{
    int count = 0;  // Counter for files

    while (head != NULL)  // Traverse through list
    {
        printf("%s\n", head->f_name);  // Print file name
        head = head->link;  // Move to next node
        count++;  // Increment counter
    }

    return count;  // Return total count
}

// Validate files passed as command-line arguments and add to list
void validate_files(char *argv[], F_node **head)
{
    int i = 1;  // Start from second argument (first is program name)

    while (argv[i] != NULL)  // Process all arguments
    {
        if (insert_last(head, argv[i]) == FAILURE)  // Try to add file
        {
            printf("INFO : File '%s' already exists or could not be added.\n", argv[i]);  // Print error
        }  // End of if
        i++;  // Move to next argument
    }  // End of while loop
}  // End of function
