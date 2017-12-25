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

void reverse(Node *block);

/* 冒泡排序的函数原型 */
void bubble_sort_ascending_address(Node *block);

void bubble_sort_ascending_size(Node *block);

void bubble_sort_descending_address(Node *block);

void bubble_sort_descending_size(Node *block);

void block_print(Node *block);

#endif
