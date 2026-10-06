#include "inverted.h"
#include <ctype.h>

// Clear entire database by freeing all allocated memory
static void clear_database(M_node *HT[])
{
    int i;  // Loop counter
    for (i = 0; i < 27; i++)  // For each hash bucket
    {
        while (HT[i] != NULL)  // While bucket has nodes
        {
            M_node *main_node = HT[i];  // Get current main node
            S_node *sub_node = main_node->sub_link;  // Get first sub node
            HT[i] = main_node->main_link;  // Move to next main node

            while (sub_node != NULL)  // Free all sub nodes
            {
                S_node *temp = sub_node;  // Save current sub node
                sub_node = sub_node->sub_link;  // Move to next
                free(temp);  // Free current sub node
            }

            free(main_node);  // Free main node
        }
    }
}

// Find main node with matching word in linked list
static M_node *find_main_node(M_node *head, const char *word)
{
    while (head != NULL)  // Traverse main node list
    {
        if (strcmp(head->word, word) == 0)  // Word found
        {
            return head;  // Return matching node
        }
        head = head->main_link;  // Move to next node
    }
    return NULL;  // Word not found
}

// Find sub node with matching filename in sub node list
static S_node *find_sub_node(M_node *main_node, const char *filename)
{
    S_node *sub_node = main_node->sub_link;  // Start from first sub node
    while (sub_node != NULL)  // Traverse sub node list
    {
        if (strcmp(sub_node->filename, filename) == 0)  // File found
        {
            return sub_node;  // Return matching node
        }
        sub_node = sub_node->sub_link;  // Move to next node
    }
    return NULL;  // File not found
}

// Create inverted database from input files
void create_database(M_node *HT[], F_node *head)
{
    F_node *temp = head;  // Pointer to current file
    int i;  // Loop counter

    clear_database(HT);  // Clear existing database
    for (i = 0; i < 27; i++)  // Reset all hash buckets
    {
        HT[i] = NULL;
    }

    if (head == NULL)  // No files to process
    {
        printf("INFO : No files available to build database.\n");  // Print info message
        printf("INFO : Pass file names as command-line arguments, for example: ./inverted_search file1.txt file2.txt\n");  // Print usage example
        printf("INFO : Or choose option 5 first to add a file interactively.\n");  // Print alternative option
        return;
    }

    while (temp != NULL)  // Process each file
    {
        FILE *fp = fopen(temp->f_name, "r");  // Open file
        if (fp == NULL)  // File not found
        {
            printf("INFO : Unable to open file '%s'.\n", temp->f_name);  // Print error message
            temp = temp->link;  // Move to next file
            continue;  // Skip to next file
        }

        char word[50];  // Buffer for reading words
        while (fscanf(fp, "%49s", word) == 1)  // Read each word
        {
            int j = 0;  // Character index
            char cleaned[50];  // Cleaned word buffer
            int index;  // Hash index
            M_node *main_node;  // Main node pointer
            S_node *sub_node;  // Sub node pointer

            // Extract only alphanumeric characters and convert to lowercase
            while (word[j] != '\0')
            {
                if (isalnum((unsigned char)word[j]))  // Character is alphanumeric
                {
                    cleaned[j] = tolower((unsigned char)word[j]);  // Convert to lowercase
                    j++;
                }
                else  // Non-alphanumeric found
                {
                    break;  // Stop processing word
                }
            }

            if (j == 0)  // No valid characters
            {
                continue;  // Skip this word
            }

            cleaned[j] = '\0';  // Null terminate cleaned word
            index = get_index(cleaned);  // Get hash index from first character

            main_node = find_main_node(HT[index], cleaned);  // Search for word
            if (main_node == NULL)  // Word is new
            {
                main_node = (M_node *)malloc(sizeof(M_node));  // Allocate main node
                if (main_node == NULL)  // Memory allocation failed
                {
                    fclose(fp);
                    return;
                }

                strcpy(main_node->word, cleaned);  // Copy word
                main_node->file_count = 0;  // Initialize file count
                main_node->sub_link = NULL;  // No files yet
                main_node->main_link = HT[index];  // Insert at bucket head
                HT[index] = main_node;  // Update bucket head
            }

            sub_node = find_sub_node(main_node, temp->f_name);  // Search for file
            if (sub_node == NULL)  // File entry is new
            {
                sub_node = (S_node *)malloc(sizeof(S_node));  // Allocate sub node
                if (sub_node == NULL)  // Memory allocation failed
                {
                    fclose(fp);
                    return;
                }

                strcpy(sub_node->filename, temp->f_name);  // Copy filename
                sub_node->word_count = 0;  // Initialize word count
                sub_node->sub_link = main_node->sub_link;  // Link to existing entries
                main_node->sub_link = sub_node;  // Insert at head
                main_node->file_count++;  // Increment file count
            }

            sub_node->word_count++;  // Increment word occurrence count
        }

        fclose(fp);  // Close file
        temp = temp->link;  // Move to next file
    }

    printf("INFO : Database created successfully.\n");  // Success message
}
