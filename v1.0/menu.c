#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "menu.h"
#include "block_node.h"
#include "list_node.h"
#include "memory_allocation.h"

Node *block;

list *process_list = NULL;

block_node *temp;

void submenu(void);

void menu(void)
{
    ready( );
    int choice;

    while(1) {
        printf("-------------Memory simulation-----------\n\n");
        printf("            1. Init memory\n\n");
        printf("            2. Allocate memory\n\n");
        printf("            3. Reclaime memory\n\n");
        printf("            4. Print list table\n\n");
        printf("            5. Print block table\n\n");
        printf("            6. Exit\n\n");
        printf("-------------------End-------------------\n\n");
        scanf("%d",&choice);
        switch (choice) {
            case 1:
                block = init_block( );
                printf("Init_OK!\n");
                break;
            case 2:
                submenu( );
                break;
            case 3:
                break;
            case 4:
                printf("-----------------------------------------\n");
                printf("|Process_ID|Process_SIZE|Process_ADDRESS|\n");
                printf("-----------------------------------------\n");
                list_print(process_list);
                break;
            case 5:
                block_print(block);
                break;
            case 6:
                exit(0);
                break;
            default:
                break;
        }
    }
}

void submenu(void)
{
    int choice;

    while(1) {
        printf("-------------Memory Submenu-------------\n\n");
        printf("            1.First fit\n\n");
        printf("            2.Best fit\n\n");
        printf("            3.Worst fit\n\n");
        printf("            4.Next fit\n\n");
        printf("            5.Exit\n\n");
        printf("-----------------------------------------\n\n");
        scanf("%d",&choice);
        switch(choice) {
            case 1: temp = memory_first_fit(&block, &process_list); break;
            case 2: temp = memory_best_fit(&block, &process_list); break;
            case 3: temp = memory_worst_fit(&block, &process_list); break;
            case 4: temp = memory_next_fit(&block, &temp, &process_list); break;
            case 5: return;
            default: break;
        }
    }
}

void ready(void)
{
    char character;
    printf("Are you ready?(y/N): ");
    scanf("%c",&character);
    getchar( );
    if (character == 'y')
        //sleep(2);        Linux
        return ;
    else if (character == 'N')
        exit(0);
    else {
        printf("Unknown\n");
        ready( );
    }
}
