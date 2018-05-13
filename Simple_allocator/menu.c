/*
 * 文件名: menu.c
 * 功能: 菜单函数实现
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "menu.h"
#include "block_node.h"
#include "list_node.h"
#include "memory_allocation.h"
#include "memory_recovery.h"

Node *block;                            // low操作,全局的区块链

list *process_list = NULL;              // lowB操作,全局的二叉树根,为了初始化,一定要置为NULL,全局静态变量NULL

block_node *temp;                       // lowB操作,记录上次分配操作节点

void submenu(void)
{
    int choice;
    char character;

    while(1) {
        printf("-------------Memory Submenu-------------\n\n");
        printf("            1.First fit\n\n");
        printf("            2.Best fit\n\n");
        printf("            3.Worst fit\n\n");
        printf("            4.Next fit\n\n");
        printf("            5.Exit\n\n");
        printf("-----------------------------------------\n\n");
        printf("Please input your choice: ");
        scanf("%d",&choice);
        getchar( );
        printf("Press [Enter] to continue. . .\n");
        if (scanf("%c",&character) == 1) {
            system("clear");
        }
        switch(choice) {
            case 1: temp = memory_first_fit(&block, &process_list); break;
            case 2: temp = memory_best_fit(&block, &process_list); break;
            case 3: temp = memory_worst_fit(&block, &process_list); break;
            case 4: temp = memory_next_fit(&block, &temp, &process_list); break;
            case 5: return;
            default: break;
        }
        getchar( );
        printf("Press [Enter] to continue. . .\n");
        if (scanf("%c",&character) == 1) {
            system("clear");
        }
    }
}


void menu(void)
{
    ready( );
    int choice;
    char character;

    while(1) {
        printf("-------------Memory simulation-----------\n\n");
        printf("            1. Init memory\n\n");
        printf("            2. Allocate memory\n\n");
        printf("            3. Reclaime memory\n\n");
        printf("            4. Print list table\n\n");
        printf("            5. Print block table\n\n");
        printf("            6. Exit\n\n");
        printf("-------------------End-------------------\n\n");
        printf("Please input your choice: ");                        // 处理缓冲区,清屏的操作
        scanf("%d",&choice);
        getchar( );
        printf("Press [Enter] to continue. . .\n");
        if (scanf("%c",&character) == 1) {
            system("clear");
        }
        switch (choice) {
            case 1:
                block = init_block( );
                printf("Init_OK!\n");
                break;
            case 2:
                submenu( );
                break;
            case 3:
                memory_recovery(&process_list, &block);
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
        getchar( );
        printf("Press [Enter] to continue. . .\n");
        if (scanf("%c",&character) == 1) {
            system("clear");
        }
    }
}

void ready(void)                          // 闲着没事干的操作
{
    char character;

    printf("Are you ready?(y/N): ");
    scanf("%c",&character);
    getchar( );
    if (character == 'y') {
        sleep(2);
        system("clear");
    }
    else if (character == 'N')
        exit(0);
    else {
        printf("Unknown\n");
        ready( );
    }
}