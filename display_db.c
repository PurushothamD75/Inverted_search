#include "head.h"

// Function to display the database
int display_database(c_db *hash_t) 
{
    printf("%-10s %-30s %-10s %-30s %-10s\n", "Index", "Word", "Filecount", "Filename", "Wordcount");

    for (int i = 0; i < 27; i++) 
    {
        m_node *main_node = hash_t[i].m_link;
        while (main_node) {
            s_node *sub_node = main_node->m_sub_link;
            while (sub_node) 
            
            {
                printf("%-10d %-30s %-10d %-30s %-10d\n", i, main_node->word, main_node->file_count, sub_node->file_name, sub_node->word_count);
                sub_node = sub_node->s_sub_link;
            }
            main_node = main_node->m_main_link;
        }
    }

    return SUCCESS;
}
