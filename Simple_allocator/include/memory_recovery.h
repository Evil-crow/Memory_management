/*
 * 文件名: memory_recovery.h
 * 功能: 内存回收的函数原型
 */
#ifndef _MEMORY_RECOVERY_H
#define _MEMORY_RECOVERY_H
#include "list_node.h"
#include "block_node.h"

void memory_recovery(list **process_list, Node **block);

int memory_recovery_judge(list_node *list_node, block_node *block_node, int process_ID);

list_node *get_list_node(list *process_list, int process_ID);

block_node *get_block_node(Node *block, list_node *list_node);

int get_process_ID(void);

#endif
