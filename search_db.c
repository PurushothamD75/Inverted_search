#include "head.h"
#include <stdio.h>
#include <string.h>

// Function to search the database
int search_database(c_db *hash_t) {
    char search_word[30];
    printf("Enter the word to search: ");
    scanf("%s", search_word);

    // Convert the search word to lowercase
    for (char *p = search_word; *p; p++) *p = tolower(*p);

    // Calculate the hash key
    int key = tolower(search_word[0]) - 'a';
    if (key < 0 || key >= 26) {
        key = 26;
    }

    m_node *main_node = hash_t[key].m_link;
    while (main_node != NULL) {
        if (strcmp(main_node->word, search_word) == 0) {
            printf("Word: %s\n", main_node->word);
            printf("Filecount: %d\n", main_node->file_count);

            s_node *sub_node = main_node->m_sub_link;
            while (sub_node != NULL) {
                printf("Filename: %s, Wordcount: %d\n", sub_node->file_name, sub_node->word_count);
                
                sub_node = sub_node->s_sub_link;
            }
            return SUCCESS;
        }
        main_node = main_node->m_main_link;
    }

    printf("Word not found in the database.\n");
    return DATA_NOT_FOUND;
}

