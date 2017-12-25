#include <stdio.h>
#include <stdlib.h>
#include "list_node.h"
#include "block_node.h"
#include "memory_recovery.h"

#define FRONT 1
#define BACK 2
#define MIDDLE 3
#define NONE 0

void memory_recovery(list **process_list, Node **block)
{
    int process_ID,type;
    list_node *node_list;
    block_node *node_block;

    process_ID = get_process_ID( );
    node_list = get_list_node(*process_list, process_ID);
    node_block = get_block_node(*block, node_list);
    type = memory_recovery_judge(node_list, node_block, process_ID);

    printf("type: %d\n",type);
    printf("block_node: %d\n",node_block->block_address);

    if (type == NONE) {
        block_node *temp;
        temp = (block_node *)malloc(sizeof(block_node));
        temp->block_address = node_list->list_block_address;
        temp->block_size = node_list->list_process_size;
        temp->next = node_block->next;
        node_block->next = temp;
        list_delete(process_list, process_ID);
    }

    if (type == FRONT) {
        node_block->block_size += node_list->list_process_size;
        list_delete(process_list, process_ID);
    }

    if (type == BACK) {
        node_block->block_size += node_list->list_process_size;
        node_block->block_address = node_list->list_block_address;
        list_delete(process_list, process_ID);
    }

    if (type == MIDDLE) {
        node_block->block_size += node_block->next->block_size + node_list->list_process_size;
        node_block->next = node_block->next->next;
        list_delete(process_list, process_ID);
    }

    printf("Memory Recovery OK!\n");
}

int memory_recovery_judge(list_node *list_node, block_node *block_node, int process_ID)
{
    if ((block_node->block_address + block_node->block_size == list_node->list_block_address)
        && (block_node->next->block_address == list_node->list_block_address + list_node->list_process_size))
        return MIDDLE;
    else if (block_node->block_address + block_node->block_size == list_node->list_block_address)
        return FRONT;
    else if (block_node->next->block_address == list_node->list_block_address + list_node->list_process_size)
        return BACK;
    else
        return NONE;
}

list_node *get_list_node(list *process_list, int process_ID)
{
    list_node *temp;
    temp = list_search(&process_list, process_ID);
    return temp;
}

block_node *get_block_node(Node *block, list_node *list_node)
{
    block_node *temp, *prev;

    bubble_sort_ascending_address(block);
    prev = temp = block->head->next;
    if (temp == NULL) {
        printf("Error, no block node!\n");
        return NULL;
    }
    while (temp) {
        prev = temp;
        if (temp->block_address + temp->block_size >= list_node->list_block_address)
            break;
        temp = temp->next;
    }
    if (prev)
        return prev;
    return NULL;
}

int get_process_ID(void)
{
    int process_ID;

    printf("Please input the process_ID that you want to free: ");
    scanf("%d",&process_ID);

    return process_ID;
}
