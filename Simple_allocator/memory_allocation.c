/*
 * 文件名: memory_allocation.c
 * 功能: 内存分配的函数实现
 */

#include <stdio.h>
#include <stdlib.h>
#include "block_node.h"
#include "list_node.h"
#define REST 5                        // define确定符号常量REST,用于判断是否保留此区块

list_node get_information(void)       // 获取process相关信息,进程ID,以及进程内存大小
{
    list_node temp;
    printf("Please input the Process ID: ");
    scanf("%d",&(temp.list_process_ID));
    printf("Please input the Process size: ");
    scanf("%d",&(temp.list_process_size));

    return temp;
}

block_node *memory_first_fit(Node **block, list **process_list)       // first_fit算法实现
{
    list_node process_node = get_information( );
    block_node *temp, *prev;                           
    bubble_sort(*block, address_ascend);                             // 前提: 区块链按照地址升序排序
    prev = temp =  (*block)->head->next;

    if (temp == NULL) {
        printf("The block is NULL! Error!\n");
        return NULL;
    }

    while (temp) {                                                   // 算法: 查找排好序的链表中首个满足需求的空闲区块
        if (temp->block_size >= process_node.list_process_size)
            break;
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Can't find a sutiable block for the process!\n");
        return NULL;
    }

    if (temp->block_size - process_node.list_process_size > REST) {  // 处理: 如果分配后剩余大于REST,则区块链仅减少SIZE
        process_node.list_block_address = temp->block_address;
        temp->block_address += process_node.list_process_size;
        temp->block_size -= process_node.list_process_size;

        list_insert(process_list, process_node);                     // 新分配的二叉节点插入
    }
    else {                                                           // 否则: 将整个区块的分配,同时删除区块节点
        process_node.list_process_size = temp->block_size;
        process_node.list_block_address = temp->block_address;
        prev->next = temp->next;
        free(temp);

        list_insert(process_list, process_node);
    }

    return temp;                                                     // 为了:Next_fit算法,需要返回上次操作的节点
}

block_node *memory_best_fit(Node **block, list **process_list)       // best-fit算法的实现
{
    list_node process_node = get_information( );
    block_node *temp, *prev;                             
    bubble_sort(*block, size_ascend);                                // 按照区块大小的升序排列
    prev = temp = (*block)->head->next;

    if (temp == NULL) {
        printf("The block is NULL! Error!\n");
        return NULL;
    }

    while (temp) {                                                   // 查找到第一个满足条件的空闲区块
        if (temp->block_size >= process_node.list_process_size)
            break;
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Can't find the node! Error!\n");
        return NULL;
    }

    if (temp->block_size - process_node.list_process_size > REST) {    // 处理方法同上
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

block_node *memory_worst_fit(Node **block, list **process_list)    // 算法worst-fit算法实现
{
    list_node process_node = get_information( );
    block_node *temp, *prev;                          
    bubble_sort(*block, size_descend);                             // 按照内存区块大小的降序排列
    prev = temp = (*block)->head->next;

    if (temp == NULL) {
        printf("The block is NULL! Error!\n");
        return NULL;
    }

    while(temp) {                                                 // 查找到第一个满足需求的最大空闲区块
        if (temp->block_size > process_node.list_process_size)
            break;
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Can't find a suitable block!\n");
        return NULL;
    }

    if (temp->block_size - process_node.list_process_size > REST) {    // 处理方法同上
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

/* 传递参数,有三个 : 1. 区块链头指针 , 2. 上次操作的节点指针 , 3. 二叉树树根 */
block_node *memory_next_fit(Node **block_head, block_node **block, list **process_list)
{
    list_node process_node = get_information( );
    block_node *temp, *prev;        
    bubble_sort(*block_head, address_ascend);                 // next-fit与first-fit类似,仅是从上次操作后的节点出发,也是地址升序
    prev = temp = (*block);

    while(temp) {                                       // 先顺序查找到 链表尾
        if (temp->block_size > process_node.list_process_size)
            break;
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {                               // 若没有节点,则从头查找到上次的链表操作点
        prev = temp = (*block_head)->head->next;
        while (temp != *block) {
            if (temp->block_size > process_node.list_process_size)
                break;
            prev = temp;
            temp = temp->next;
        }
    }

    if (temp == NULL) {                              // 此时,如果temp仍为NULL,才能算作没有可用节点
        printf("Error,Can't find a block !\n");
        return NULL;
    }

    if (temp->block_size - process_node.list_process_size > REST) {     // 对找到的可用的区块节点处理方法同上
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
