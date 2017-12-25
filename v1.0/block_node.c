#include <stdio.h>
#include <stdlib.h>
#include "block_node.h"

void bubble_sort_ascending_address(Node *block)
{
    block_node *temp, *cur, *loop;
    temp = block->head;
    if(temp->next == NULL) {
        printf("Error,the block is NULL!\n");
        exit(0);
    }

    for(int i = 0; i < block->node_num; i++) {
        for(temp = block->head; temp->next->next != NULL; temp = temp->next) {
            if(temp->next->block_address > temp->next->next->block_address) {
                cur = temp->next;
                loop = temp->next->next;
                cur->next = loop->next;
                temp->next = loop;
                loop->next = cur;
            }
        }
    }
}

void bubble_sort_ascending_size(Node *block)
{
    block_node *temp, *cur, *loop;
    temp = block->head;
    if(temp->next == NULL) {
        printf("Error,the block is NULL!\n");
        exit(0);
    }

    for(int i = 0; i < block->node_num; i++) {
        for(temp = block->head; temp->next->next != NULL; temp = temp->next) {
            if(temp->next->block_size > temp->next->next->block_size) {
                cur = temp->next;
                loop = temp->next->next;
                cur->next = loop->next;
                temp->next = loop;
                loop->next = cur;
            }
        }
    }
}

void bubble_sort_descending_address(Node *block)
{
    block_node *temp, *cur, *loop;
    temp = block->head;
    if(temp->next == NULL) {
        printf("Error,the block is NULL!\n");
        exit(0);
    }

    for(int i = 0; i < block->node_num; i++) {
        for(temp = block->head; temp->next->next != NULL; temp = temp->next) {
            if(temp->next->block_address < temp->next->next->block_address) {
                cur = temp->next;
                loop = temp->next->next;
                cur->next = loop->next;
                temp->next = loop;
                loop->next = cur;
            }
        }
    }
}

void bubble_sort_descending_size(Node *block)
{
    block_node *temp, *cur, *loop;
    temp = block->head;
    if(temp->next == NULL) {
        printf("Error,the block is NULL!\n");
        exit(0);
    }

    for(int i = 0; i < block->node_num; i++) {
        for(temp = block->head; temp->next->next != NULL; temp = temp->next) {
            if(temp->next->block_size < temp->next->next->block_size) {
                cur = temp->next;
                loop = temp->next->next;
                cur->next = loop->next;
                temp->next = loop;
                loop->next = cur;
            }
        }
    }
}

Node *init_block(void)
{
    Node *block;
    int initial_address;
    int initial_size;
    int initial_arithmetic;
    int next_address;
    block = (Node *)malloc(sizeof(Node));
    block->head = (block_node *)malloc(sizeof(block_node));
    block->head->next = NULL;

    printf("Please input Initialize the first address: ");
    scanf("%d",&initial_address);
    printf("Please input Initialize the first block_size: ");
    scanf("%d",&initial_size);
    printf("Please input Initialize block number: ");
    scanf("%d",&block->node_num);
    printf("Please input Initialize block arithmetic: ");
    scanf("%d",&initial_arithmetic);

    for(int i = 0; i < block->node_num; i++) {
        block_node *pNew;
        pNew = (block_node *)malloc(sizeof(block_node));
        pNew->block_size = initial_size + i * initial_arithmetic;
        if(i == 0)
            pNew->block_address = initial_address;
        else
            pNew->block_address = next_address;
        next_address = pNew->block_address + pNew->block_size;

        pNew->next = block->head->next;                        /* 头插法录入节点 */
        block->head->next = pNew;
    }

    reverse(block);
    return block;
}

void reverse(Node *block)
{
    block_node *temp;
    temp = block->head->next;

    while(temp->next != NULL) {
        block_node *ptemp, *prev;
        ptemp = temp->next;
        prev = block->head->next;
        temp->next = ptemp->next;
        block->head->next = ptemp;
        ptemp->next = prev;
    }
}

void block_print(Node *block)
{
    if (block == NULL) {
        printf("The block is NULL!\n");
        return ;
    }
    block_node *temp = block->head->next;
    bubble_sort_ascending_address(block);

    if (temp == NULL) {
        printf("The block is NULL!\n");
        return ;
    }
    printf("------------------------\n");
    printf("|BLOCK_ARESS|BLOCK_SIZE|\n");
    printf("------------------------\n");
    while (temp) {
        printf("|%11d|%10d|\n",temp->block_address, temp->block_size);
        printf("------------------------\n");
        temp = temp->next;
    }
}
