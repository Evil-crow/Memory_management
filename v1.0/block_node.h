/*
 * 文件名: block_node.h
 * 功能: 内存区块链的轮子声明
 */

#ifndef _BLOCK_NODE_H
#define _BLOCK_NODE_H

/* 区块链中单个节点 */
typedef struct node {
    int block_address;
    int block_size;
    struct node *next;
}block_node;

/* 数据区块链 */
typedef struct Block_Node {
    block_node *head;
    int node_num;
}Node;

/* 数据链块初始化 */
Node *init_block(void);

/* 因为采用头插法进行区块链的创建,逆置函数 */
void reverse(Node *block);

/* 冒泡排序的函数原型 */

/* 地址升序排序 */
void bubble_sort_ascending_address(Node *block);

/* 大小升序排序 */
void bubble_sort_ascending_size(Node *block);

/* 地址降序排序 */
void bubble_sort_descending_address(Node *block);

/* 大小降序排序 */
void bubble_sort_descending_size(Node *block);

/* 遍历区块链,打印信息函数 */
void block_print(Node *block);

#endif
