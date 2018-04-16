/*
 * 文件名: list_node.c
 * 功能: 二叉排序树的轮子实现
 */

#include <stdio.h>
#include <stdlib.h>
#include "list_node.h"

void list_insert(list **process_list, list_node node)
{
    if ((*process_list) == NULL) {                                      // 当前节点指针为空,则可以进行插入
        list *new_node = (list *)malloc(sizeof(list));
        new_node->data.list_process_ID = node.list_process_ID;
        new_node->data.list_block_address = node.list_block_address;
        new_node->data.list_process_size = node.list_process_size;
        new_node->LChild = NULL;
        new_node->RChild = NULL;
        *process_list = new_node;                                       // 进行节点指针的赋值
        printf("insert OK!\n");
        return;
    }

    else if (node.list_process_ID < ((*process_list)->data.list_process_ID))  // 若要插入的节点 < 当前节点 ,则进入左子树
        list_insert(&((*process_list)->LChild), node);
    else                                                                // 反之,进入右子树 (Process_ID不可相同)
        list_insert(&((*process_list)->RChild), node);
}

list_node *list_search(list **process_list, int list_process_ID)
{
    if ((*process_list) == NULL)
        return NULL;

    // 查找与插入同理,不过会返回节点指针而已
    list *temp = *process_list;
    while (temp != NULL) {
        if (temp->data.list_process_ID == list_process_ID)
            return &(temp->data);
        else if (temp->data.list_process_ID > list_process_ID) {
            temp = temp->LChild;
        }
        else
            temp = temp->RChild;
    }

    return NULL;
}

void list_delete(list **process_list, int list_process_ID)
{
    int direction;
    list *temp, *prev;
    temp = (*process_list);

    /* 记录前驱节点的同时,进行结点的查找 */
    prev = temp;
    while ((temp != NULL) && (temp->data.list_process_ID != list_process_ID)) {
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

    if(temp == NULL) {
        printf("Can't find node!\n");
        return ;
    }

    /* 1. 处理叶子的情况 */
    if ((temp->LChild == NULL) && (temp->RChild == NULL)) {
        if (prev == temp) {
            (*process_list) = NULL;
            return ;
        }
        if (direction == 0)
            prev->LChild = NULL;
        else
            prev->RChild = NULL;

        free(temp);
    }

    /* 2. 处理只有左子树的情况 */
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

    /* 3. 同上理,处理只有右子树的情况 */
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

    /* 4. 处理左右子树同时存在的情况 */
    else {
        list *pre_prev;
        pre_prev = temp->RChild;

        /* 若要删除的节点是根节点
         * 查找到其中序前驱,进行data与交换
         * 之后,调用自身进行节点删除即可
         */
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

/* 打印函数进行中序遍历即可 */

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
