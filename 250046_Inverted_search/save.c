#include "inverted.h"

// Save inverted database to file in text format
void save_database(M_node *HT[])
{
    FILE *fp = fopen("inverted_database.txt", "w");  // Open file for writing
    int i;  // Loop counter

    if (fp == NULL)  // File open failed
    {
        printf("INFO : Unable to save database.\n");  // Print error message
        return;  // Exit function
    }  // End of if

    // Traverse all hash buckets
    for (i = 0; i < 27; i++)  // Loop through all buckets
    {
        M_node *main_node = HT[i];  // Get first main node
        while (main_node != NULL)  // For each word
        {
            S_node *sub_node = main_node->sub_link;  // Get file entries
            fprintf(fp, "%s %d\n", main_node->word, main_node->file_count);  // Write word and file count
            while (sub_node != NULL)  // For each file
            {
                fprintf(fp, "  %s %d\n", sub_node->filename, sub_node->word_count);  // Write file and count
                sub_node = sub_node->sub_link;  // Move to next file
            }  // End of inner loop
            main_node = main_node->main_link;  // Move to next word
        }  // End of while loop
    }  // End of for loop

    fclose(fp);  // Close file
    printf("INFO : Database saved to inverted_database.txt\n");  // Print success message
}  // End of function
