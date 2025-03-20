/*
NAME 		: PURUSHOTHAM D
DATE 		: 12-02-2025
TITLE		: INVERTED SEARCH
DESCRIPTION	: The purpose of storing an index is to optimize speed and performance in finding relevant documents for a search query.
		  Without an index, the search engine would scan every document in the corpus, which would require considerable time and computing power.
 */

#include "head.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int option;   // declare the variables
    char choose;
    f_list *head = NULL;
    c_db arr[27];

    // Initialize hash table
    for (int i = 0; i < 27; i++) {
        arr[i].key = i;
        arr[i].m_link = NULL;
    }

    // Check command line arguments
    if (argc <= 1) {
        printf("Error: Insufficient Arguments\nUsage: ./a.out file1.txt file2.txt\n");
        return 0;
    } else {
        if (read_and_validate(argc, argv, &head) == SUCCESS) {
            printf("***** Read and Validate is Completed *****\n");
        } else {
            printf("***** Error: Read and Validate not Completed *****\n");
            return 0;
        }
    }

    // Menu-driven operations
    do {
        printf("\nSelect your choice among the following options:\n");
        printf("1. Create DataBase\n");
        printf("2. Display DataBase\n");
        printf("3. Search DataBase\n");
        printf("4. Save DataBase\n");
        printf("5. Update DataBase\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &option) != 1) option = 7;

        switch (option) {
            case 1:
                // Create database
                if (create_database(head, arr) == SUCCESS) {
                    printf("***** DataBase Created Successfully *****\n");
                } else {
                    printf("***** Error: Failed To Create Database *****\n");
                }
                break;
            case 2:
                // Display database
                if (display_database(arr) == SUCCESS) {
                    printf("***** DataBase Displayed Successfully *****\n");
                } else {
                    printf("***** Error: Failed To Display Database *****\n");
                }
                break;
            case 3:
                // Search database
                if (search_database(arr) == DATA_NOT_FOUND) {
                    printf("***** Word Not Found *****\n");
                }
                break;
            case 4:
                // Save database
                if (save_database(arr) == SUCCESS) {
                    printf("***** Database Saved Successfully *****\n");
                } else {
                    printf("***** Error: Failed To Save Database *****\n");
                }
                break;
            case 5:
                // Update database
                if (update_database(arr) == SUCCESS) {
                    printf("***** Database Updated Successfully *****\n");
                } else {
                    printf("***** Error: Failed To Update Database *****\n");
                }
                break;
            case 6:
                printf("***** Exit Successfully *****\n");
                return 0;
            default:
                printf("Invalid option. Please try again.\n");
                break;
        }

        printf("Do you want to continue (y/n): ");
        while (getchar() != '\n'); // Clear the newline character
        choose = getchar();
    } while (choose == 'y' || choose == 'Y');

    return 0;
}
