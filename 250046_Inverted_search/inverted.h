#ifndef INVERTED_H
#define INVERTED_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define SUCCESS		1  // Success status code
#define FAILURE		0  // Failure status code

// File node structure for linked list of file names
typedef struct file
{
    char f_name[20];  // File name
    struct file *link;  // Pointer to next file node
}F_node;

// Sub node structure for file details in inverted index
typedef struct Sub
{
    int word_count;  // Number of times word appears in file
    char filename[20];  // Name of file containing word
    struct Sub *sub_link;  // Pointer to next file entry for same word
}S_node;

// Main node structure for storing words in inverted index
typedef struct Main
{
    char word[25];  // The word from text files
    int file_count;  // Total number of files containing this word
    S_node *sub_link;  // Pointer to list of files with word counts
    struct Main *main_link;  // Pointer to next word node in hash table
}M_node;

// Hash table structure (27 entries: A-Z and special characters)
typedef struct Hash
{
    int index[27];  // Index for hash table
    struct Main *main_link;  // Pointer to main word list
}H_node;

// Function to create inverted database from files
void create_database(M_node *HT[], F_node *head);
// Function to display entire inverted database
void display_database(M_node *HT[]);
// Function to search for a word in the database
void search_database(M_node *HT[]);
// Function to save database to file
void save_database(M_node *HT[]);
// Function to add new file to database
int update_database(M_node *HT[],F_node **head);

// Function to validate files passed as command-line arguments
void validate_files(char *argv[], F_node **head);
// Function to insert file name at end of linked list
int insert_last(F_node **head, char *f_name);
// Function to check if file already exists in list
int check_duplicates(F_node *head, char *f_name);
// Function to print all file names in list
int print_filenames(F_node *head);
// Function to get hash index from first character of word
int get_index(char *word);

#endif
