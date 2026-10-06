#include "inverted.h"

// Display entire inverted database in formatted table
void display_database(M_node *HT[])
{
    int i, found = 0;  // Loop counter and flag for empty database

    printf("\n");  // Print newline
    printf("--------------------------------------------------------------------------------------------\n");  // Table border
    printf("  Index | Word                   File Count |  File Name               Word Count \n");  // Table header
    printf("--------------------------------------------------------------------------------------------\n");  // Table border

    for (i = 0; i < 27; i++)  // For each hash bucket
    {
        M_node *main = HT[i];  // Get first main node

        while (main != NULL)  // For each word in bucket
        {
            S_node *sub = main->sub_link;  // Get first file entry
            int first = 1;  // Flag for first file entry

            while (sub != NULL)  // For each file containing word
            {
                if (first)  // First file entry for this word
                {
                    printf("| %-5d | %-20s | %-10d | %-22s | %-10d |\n",  // Print with word and index
                           i,
                           main->word,
                           main->file_count,
                           sub->filename,
                           sub->word_count);
                    first = 0;  // No longer first
                }
                else  // Subsequent file entries
                {
                    printf("| %-5s | %-20s | %-10s | %-22s | %-10d |\n",  // Print blank index and word
                           "",
                           "",
                           "",
                           sub->filename,
                           sub->word_count);
                }

                sub = sub->sub_link;  // Move to next file
            }

            found = 1;  // Mark that data exists
            main = main->main_link;  // Move to next word
        }
    }

    printf("-------------------------------------------------------------------------------------------------\n");  // Table border

    if (!found)  // No data found
    {
        printf("INFO : Database is empty.\n");  // Print empty message
    }  // End of if
}  // End of function