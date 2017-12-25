#include <stdio.h>
#include <stdlib.h>
#include "list_node.h"

void list_insert(list **process_list, list_node node)
{
    if ((*process_list) == NULL) {
        list *new_node = (list *)malloc(sizeof(list));
        new_node->data.list_process_ID = node.list_process_ID;
        new_node->data.list_block_address = node.list_block_address;
        new_node->data.list_process_size = node.list_process_size;
        new_node->LChild = NULL;
        new_node->RChild = NULL;
        *process_list = new_node;                                        //�½ڵ�������λ��
        printf("insert OK!\n");
        return;
    }

    else if (node.list_process_ID < ((*process_list)->data.list_process_ID))
        list_insert(&((*process_list)->LChild), node);
    else
        list_insert(&((*process_list)->RChild), node);
}

list *list_search(list **process_list, int list_process_ID)
{
    if ((*process_list) == NULL)
        return NULL;

    while ((*process_list) != NULL) {
        if ((*process_list)->data.list_process_ID == list_process_ID)
            return (*process_list);
        else if ((*process_list)->data.list_process_ID < list_process_ID) {
            (*process_list) = (*process_list)->LChild;
        }
        else
            (*process_list) = (*process_list)->RChild;
    }

    return NULL;
}

void list_delete(list **process_list, int list_process_ID)
{
    int direction;                            // ��������һ������/������
    list *temp, *prev;
    temp = (*process_list);

    prev = temp;
    while (temp->data.list_process_ID != list_process_ID) {
        prev = temp;
        if (temp->data.list_process_ID == list_process_ID)
            break;
        else if (list_process_ID < temp->data.list_process_ID) {
            temp = temp->LChild;
            direction = 0;
        }
        else {
            temp = temp->RChild;
            direction = 1;
        }
    }

    if(temp == NULL)
        return ;

    if ((temp->LChild == NULL) && (temp->RChild == NULL)) {
        if (direction == 0)
            prev->LChild = NULL;
        else
            prev->RChild = NULL;

        free(temp);
    }
    else if ((temp->LChild != NULL) && (temp->RChild == NULL)) {
        if (prev == temp) {
            (*process_list) = temp->LChild;
            free(temp);
        }
        else {
            if (direction == 0)
                prev->LChild = temp->LChild;
            else
                prev->RChild = temp->LChild;

            free(temp);
        }
    }
    else if ((temp->LChild ==NULL) && (temp->RChild != NULL)) {
        if (prev == temp) {
            (*process_list) = temp->RChild;
            free(temp);
        }
        else {
            if (direction == 0)
                prev->LChild = temp->RChild;
            else
                prev->RChild = temp->RChild;

            free(temp);
        }
    }
    else {                                              // ���µ������ǣ���/������������
        list *pre_prev;
        pre_prev = temp->RChild;

        if(prev == temp) {
            temp = prev->LChild;
            while(temp->RChild != NULL)
                temp = temp->RChild;
            list _temp = *temp;
            list_delete(process_list,temp->data.list_process_ID);
            (**process_list).data = _temp.data;
        }
        else {
            while(pre_prev->LChild != NULL)
                pre_prev = pre_prev->LChild;
            if (direction == 0)
                prev->LChild = temp->RChild;
            else
                prev->RChild = temp->RChild;
            pre_prev->LChild = temp->LChild;
            free(temp);
        }
    }
}

void list_print(list *process_list)
{
    if(process_list == NULL)
        return ;
    list_print(process_list->LChild);
    list_visit(process_list);
    list_print(process_list->RChild);
}

void list_visit(list *process_list)
{
    printf("|%-10d|  %10d|     %10d|\n"
            ,process_list->data.list_process_ID
            ,process_list->data.list_process_size
            ,process_list->data.list_block_address);
    printf("-----------------------------------------\n");
}
