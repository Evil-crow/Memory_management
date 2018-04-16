/*
 * 文件名: list_node.h
 * 功能: 二叉排序树的轮子声明
 */

#ifndef _LIST_NODE_H
#define _LIST_NODE_H

/* 二叉排序树data节点结构体:
 * 进程ID, 进程内存大小, 进程内存地址
 */
typedef struct _node {
    int list_process_ID;
    int list_process_size;
    int list_block_address;
} list_node;

/* 二叉排序树节点结构体:
 * 数据域, 左孩子指针, 右孩子指针
 */
typedef struct List_Node {
    list_node data;
    struct List_Node *LChild;
    struct List_Node *RChild;
} list;

void list_insert(list **process_list, list_node node);             // 二叉排序树插入操作

void list_print(list *process_list);                               // 二叉排序树遍历操作,中序遍历

void list_visit(list *process_list);                               // 节点信息访问函数

list_node *list_search(list **process_list, int list_process_ID);  // 二叉排序树节点查找函数

void list_delete(list **process_list, int list_process_ID);        // 二叉排序树节点删除函数

#endif
