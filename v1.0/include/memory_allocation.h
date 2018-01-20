/*
 * 文件名: memory_allocation.h
 * 功能: 内存分配的函数原型
 */

#ifndef _MEMORY_ALLOCATION_H
#define _MEMORY_ALLOCATION_H
#include "block_node.h"
#include "list_node.h"

block_node *memory_first_fit(Node **block, list **process_list);

block_node *memory_best_fit(Node **block, list **process_list);

block_node *memory_worst_fit(Node **block, list **process_list);

block_node *memory_next_fit(Node **block_head, block_node **block, list **process_list);

list_node get_information(void);

#endif // _MEMORY_ALLOCATION_H
