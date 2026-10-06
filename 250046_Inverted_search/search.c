#include "inverted.h"

// Search for a word in the inverted database and display results
void search_database(M_node *HT[])
{
    char word[26];  // Buffer for search word

    printf("Enter the word to search: ");  // Prompt user for word
    scanf("%24s", word);  // Read search word

    int index;  // Hash index for word

    // Calculate hash index based on first character
    if(word[0] >= 'a' && word[0] <= 'z')  // Lowercase letter
        index = word[0] - 'a';  // Get index 0-25
    else if(word[0] >= 'A' && word[0] <= 'Z')  // Uppercase letter
        index = word[0] - 'A';  // Convert to lowercase index
    else  // Non-alphabetic character
        index = 26;  // Use index 26 for special characters

    M_node *temp = HT[index];  // Get first node in hash bucket

    // Search for matching word in bucket
    while(temp != NULL)  // Traverse linked list
    {
        if(strcmp(temp->word, word) == 0)  // Word found
        {
            printf("\nWord Found Successfully\n");  // Print success message
            printf("---------------------------------\n");  // Print separator
            printf("Word        : %s\n", temp->word);  // Display word
            printf("File Count  : %d\n", temp->file_count);  // Display file count
            printf("---------------------------------\n");  // Print separator

            S_node *sub = temp->sub_link;  // Get first file entry

            // Display all files containing this word
            while(sub != NULL)  // Traverse sub-node list
            {
                printf("File Name   : %s\n", sub->filename);  // Display filename
                printf("Word Count  : %d\n", sub->word_count);  // Display word count
                printf("---------------------------------\n");  // Print separator

                sub = sub->sub_link;  // Move to next file entry
            }  // End of inner loop

            return;  // Exit function
        }  // End of if

        temp = temp->main_link;  // Move to next word in bucket
    }  // End of while loop

    printf("Word \"%s\" not found in the database.\n", word);  // Print not found message
}  // End of function