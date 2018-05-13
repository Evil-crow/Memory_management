/*
 * 文件名: block_node.h
 * 功能: 内存区块链的轮子声明
 */

#ifndef _BLOCK_NODE_H
#define _BLOCK_NODE_H
#include <stdbool.h>

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

void bubble_sort(Node *block, bool (*compare)(block_node *, block_node *));

void exchange(block_node **temp, block_node **cur, block_node **loop);

bool address_ascend(block_node *, block_node *);

bool address_descend(block_node *, block_node *);

bool size_ascend(block_node *, block_node *);

bool size_descend(block_node *, block_node *);

/* 遍历区块链,打印信息函数 */
void block_print(Node *block);

#endif
