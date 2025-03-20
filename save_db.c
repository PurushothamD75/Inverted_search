#include "head.h"
#include <stdio.h>

// Function to save the database to a file
int save_database(c_db *hash_t) 
{
    FILE *file = fopen("backup.txt", "w");
    if (file == NULL) 
    {
        printf("Error: Could not open file for writing.\n");
        return FAILURE;
    }

    for (int i = 0; i < 27; i++)
     {
        m_node *main_node = hash_t[i].m_link;
        while (main_node) {
            fprintf(file, "#;%s", main_node->word);
            s_node *sub_node = main_node->m_sub_link;
            while (sub_node) {
                fprintf(file, ";%s;%d", sub_node->file_name, sub_node->word_count);
                sub_node = sub_node->s_sub_link;
            }
            fprintf(file, "#\n");
            main_node = main_node->m_main_link;
        }
    }

    fclose(file);
    printf("Database successfully saved to backup.txt\n");
    return SUCCESS;
}
