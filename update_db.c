#include "head.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to update the database
int update_database(c_db *hash_t) {
    char filename[50];
    printf("Enter the file name to update the database: ");
    scanf("%s", filename);

    // Check if the filename is "backup.txt"
    if (strcmp(filename, "backup.txt") != 0) {
        printf("Error: Only 'backup.txt' is allowed to update the database.\n");
        return FAILURE;
    }

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return FAILURE;
    }

    char word[30];
    int key;

    while (fscanf(file, "%s", word) != EOF) {
        // Convert word to lowercase
        for (char *p = word; *p; p++) *p = tolower(*p);

        // Calculate the hash key
        key = tolower(word[0]) - 'a';
        if (key < 0 || key >= 26) {
            // If the key is out of bounds, set to the last index
            key = 26;
        }

        // Find or create the main node
        m_node *curr = hash_t[key].m_link;
        int found = 0;
        while (curr != NULL) {
            if (strcmp(curr->word, word) == 0) {
                found = 1;
                break;
            }
            curr = curr->m_main_link;
        }

        // If the word is not found, create a new main node
        if (!found) {
            m_node *new_node = (m_node *)malloc(sizeof(m_node));
            if (new_node == NULL) {
                printf("Error: Memory allocation failed.\n");
                fclose(file);
                return FAILURE;
            }
            strcpy(new_node->word, word);
            new_node->file_count = 0;  // Set to 0 initially, will be incremented
            new_node->m_main_link = hash_t[key].m_link;
            new_node->m_sub_link = NULL;
            hash_t[key].m_link = new_node;
            curr = new_node;
        }

        // Check if the file is already in the subnode list
        s_node *sub_node = curr->m_sub_link;
        int file_found = 0;
        while (sub_node != NULL) {
            if (strcmp(sub_node->file_name, filename) == 0) {
                sub_node->word_count++;
                file_found = 1;
                break;
            }
            sub_node = sub_node->s_sub_link;
        }

        // If the file is not found in the subnode list, add a new subnode
        if (!file_found) {
            s_node *new_sub_node = (s_node *)malloc(sizeof(s_node));
            if (new_sub_node == NULL) {
                printf("Error: Memory allocation failed.\n");
                fclose(file);
                return FAILURE;
            }
            strcpy(new_sub_node->file_name, filename);
            new_sub_node->word_count = 1;
            new_sub_node->s_sub_link = curr->m_sub_link;
            curr->m_sub_link = new_sub_node;
            curr->file_count++;  // Increment the file count only when a new file is added
        }
    }

    fclose(file);
    printf("Database successfully updated from %s\n", filename);
    return SUCCESS;
}
