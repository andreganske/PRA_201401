/**
 * This code is under GNU License Version 3.
 * 
 * Create by Andre Ganske, Deivid Sartori and Wesklei Migliorini
 */

#include "main.h"

void main(void) {

    printf("\nHello!");
    printf("\nAre you ready to an awesome play with BTrees???");
    printf("\nLet's get started!");

    menu();

    // testBTreeAll();
    exit(EXIT_SUCCESS);
}

void menu() {
    //to use random values
    srand(time(NULL));

    int menu, submenu, status = 0, position, quantity, subsubmenu;
    int size, blockSize = 4096, k_vias = 1000, ok = 1;

    //Function to sort
    void *cmpFisrt;
    void *cmpSecond;

    // execution time control
    clock_t time_start, time_end;

    do {
        printf("\n[0] Sort file");
        printf("\n[1] Read sorted entries");
        printf("\n[2] Generate index page");
        printf("\n[3] Add a new entry");
        printf("\n[4] Remove entry");
        printf("\n[9] Exit");
        
        printf("\n");
        scanf("%d", &menu);

        switch (menu) {

            case 0:
                printf("What is the block size (Default: 4096)?\n");
                scanf("%d", &blockSize);

                printf("The amount of 'k' (Default: 1000)?\n");
                scanf("%d", &k_vias);
                
                printf("\n What is the first key to sort:");
                printf("\n[0] Name Time A");
                printf("\n[1] Name Time B");
                printf("\n[2] Score (Default)");
                printf("\n[3] Date");
                printf("\n[4] Place");
                printf("\n");

                scanf("%d", &submenu);

                do {
                    printf("\n What is the second key to sort (don't choose the same!):");
                    printf("\n[0] Name Time A");
                    printf("\n[1] Name Time B");
                    printf("\n[2] Score");
                    printf("\n[3] Date (Date)");
                    printf("\n[4] Place");
                    printf("\n");

                    scanf("%d", &subsubmenu);
                    
                    if (submenu == subsubmenu) {
                        ok = 0;
                        printf("\nAre you crazy boy? I can't sort something by same field. Choose another one!");    
                    }
                    
                } while (ok = 0);

                time_start = time(NULL);
                
                /* sort function */
                
                time_end = time(NULL);

                executionTime(time_start, time_end);
                status = 1;
                break;

            case 1:
                printf("What is the page size? (Default: 4096)\n");
                scanf("%d", &blockSize);

                time_start = time(NULL);
                
                /* function to read  */
                
                time_end = time(NULL);

                executionTime(time_start, time_end);
                break;
                
            case 2:
                printf("Creating index\n");
                time_start = time(NULL);
                
                /* function to create index */
                
                time_end = time(NULL);

                executionTime(time_start, time_end);
                break;
                
            case 3:
                printf("What is the page size? (Default: 4096)\n");
                scanf("%d", &blockSize);
                break;
                
            case 4:
                printf("Select a entry to remove\n");
                scanf("%d", &position);
                
                time_start = time(NULL);
                                
                /* function to create index */
                
                time_end = time(NULL);

                executionTime(time_start, time_end);
                break;
                
            case 9:
                printf("\nGood bye!");
                break;
                
            default:
                status = 1;
                printf("\nPlease, select a valid option!!!");
                break;
        }

    } while (status == 1);
}

void executionTime(clock_t time_start, clock_t time_end) {
    double duration;
    // calc time elapsed
    duration = (double) (time_end - time_start); /// CLOCKS_PER_SEC;

    // print elapsed time
    printf("\n=> This function was running for %.2lf seconds\n", duration);
}
