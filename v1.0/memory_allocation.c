#include <stdio.h>
#include <stdlib.h>
#include "block_node.h"
#include "list_node.h"
#define REST 5

list_node get_information(void)
{
    list_node temp;
    printf("Please input the Process ID: ");
    scanf("%d",&(temp.list_process_ID));
    printf("Please input the Process size: ");
    scanf("%d",&(temp.list_process_size));

    return temp;
}

block_node *memory_first_fit(Node **block, list **process_list)
{
    list_node process_node = get_information( );
    block_node *temp, *prev;
    bubble_sort_ascending_address(*block);
    prev = temp =  (*block)->head->next;

    if (temp == NULL) {
        printf("The block is NULL! Error!\n");
        return NULL;
    }

    while (temp) {
        if (temp->block_size >= process_node.list_process_size)
            break;
        prev = temp;                            // ��¼��ǰһ���ڵ�
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Can't find a sutiable block for the process!\n");
        return NULL;
    }

    if (temp->block_size - process_node.list_process_size > REST) {
        process_node.list_block_address = temp->block_address;
        temp->block_address += process_node.list_process_size;
        temp->block_size -= process_node.list_process_size;

        list_insert(process_list, process_node);
    }
    else {
        process_node.list_process_size = temp->block_size;
        process_node.list_block_address = temp->block_address;
        prev->next = temp->next;
        free(temp);

        list_insert(process_list, process_node);
    }

    return temp;
}

block_node *memory_best_fit(Node **block, list **process_list)
{
    list_node process_node = get_information( );
    block_node *temp, *prev;
    bubble_sort_ascending_size(*block);
    prev = temp = (*block)->head->next;

    if (temp == NULL) {
        printf("The block is NULL! Error!\n");
        return NULL;
    }

    while (temp) {
        if (temp->block_size >= process_node.list_process_size)
            break;
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Can't find the node! Error!\n");
        return NULL;
    }

    if (temp->block_size - process_node.list_process_size > REST) {
        process_node.list_block_address = temp->block_address;
        temp->block_address += process_node.list_process_size;
        temp->block_size -= process_node.list_process_size;

        list_insert(process_list, process_node);
    }
    else {
        process_node.list_process_size = temp->block_size;
        process_node.list_block_address = temp->block_address;
        prev->next = temp->next;
        free(temp);

        list_insert(process_list, process_node);
    }

    return temp;
}

block_node *memory_worst_fit(Node **block, list **process_list)
{
    list_node process_node = get_information( );
    block_node *temp, *prev;
    bubble_sort_descending_size(*block);
    prev = temp = (*block)->head->next;

    if (temp == NULL) {
        printf("The block is NULL! Error!\n");
        return NULL;
    }

    while(temp) {
        if (temp->block_size > process_node.list_process_size)
            break;
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Can't find a suitable block!\n");
        return NULL;
    }

    if (temp->block_size - process_node.list_process_size > REST) {
        process_node.list_block_address = temp->block_address;
        temp->block_address += process_node.list_process_size;
        temp->block_size -= process_node.list_process_size;

        list_insert(process_list, process_node);
    }
    else {
        process_node.list_process_size = temp->block_size;
        process_node.list_block_address = temp->block_address;
        prev->next = temp->next;
        free(temp);
        temp = prev->next;

        list_insert(process_list, process_node);
    }

    return temp;
}

block_node *memory_next_fit(Node **block_head, block_node **block, list **process_list)
{
    list_node process_node = get_information( );
    block_node *temp, *prev;
    bubble_sort_ascending_address(*block_head);
    prev = temp = (*block);

    while(temp) {
        if (temp->block_size > process_node.list_process_size)
            break;
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        prev = temp = (*block_head)->head->next;
        while (temp != *block) {
            if (temp->block_size > process_node.list_process_size)
                break;
            prev = temp;
            temp = temp->next;
        }
    }

    if (temp == NULL) {
        printf("Error,Can't find a block !\n");
        return NULL;
    }

    if (temp->block_size - process_node.list_process_size > REST) {
        process_node.list_block_address = temp->block_address;
        temp->block_address += process_node.list_process_size;
        temp->block_size -= process_node.list_process_size;

        list_insert(process_list, process_node);
    }
    else {
        process_node.list_process_size = temp->block_size;
        process_node.list_block_address = temp->block_address;
        prev->next = temp->next;
        free(temp);
        temp = prev->next;

        list_insert(process_list, process_node);
    }
    
    return temp;

}
