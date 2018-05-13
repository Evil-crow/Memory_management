/*
 * 文件名: block_node.c
 * 功能: 内存区块链的轮子
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "block_node.h"
/*
 * 采用冒泡法进行链表排序
 *
 * 带有头指针的链表排序
 *
 * 按照地址升序进行排序
 *
 * 下面几个函数照葫芦画瓢,同理
 *
 * TODO: 改成按照qsort( )的实现方式
 *
 * qsort(void *__base, size_t __nmemb, size_t __size, __compar_fn_t __compar);
 *
 */

void exchange(block_node **temp, block_node **cur, block_node **loop)
{
    *cur = (*temp)->next;
    *loop = (*temp)->next->next;
    (*cur)->next = (*loop)->next;
    (*temp)->next = *loop;
    (*loop)->next = *cur;
}

void bubble_sort(Node *block, bool (*compare)(block_node *, block_node *))
{
    block_node *temp, *cur, *loop;
    temp = block->head;
    if (temp->next == NULL) {
        printf("Error,the block is NULL!\n");
        return ;
    }

    for (int i = 0; i < block->node_num; ++i)
        for (temp = block->head; temp->next->next != NULL; temp = temp->next)
            if (compare(temp->next, temp->next->next))
                exchange(&temp, &cur, &loop);
}

bool address_ascend(block_node *a, block_node *b)
{
    return a->block_address > b->block_address ? true : false;
}

bool address_descend(block_node *a, block_node *b)
{
    return a->block_address < b->block_address ? true : false;
}

bool size_ascend(block_node *a, block_node *b)
{
    return a->block_size > b->block_size ? true : false;
}

bool size_descend(block_node *a, block_node *b)
{
    return a->block_size < b->block_size ? true : false;
}

Node *init_block(void)
{
    Node *block;
    int initial_address;                   // 初始化地址
    int initial_size;                      // 初始化区块大小
    int initial_arithmetic;                // 区块大小间隔
    int next_address;                      // 计算下一个区块地址
    block = (Node *)malloc(sizeof(Node));                          // 进行区块链的初始化
    block->head = (block_node *)malloc(sizeof(block_node));
    block->head->next = NULL;

    /*
     * 录入区块链信息:
     *
     * 起始地址, 首区块大小, 区块编号, 区块大小等差
     *
     */
    printf("Please input Initialize the first address: ");
    scanf("%d",&initial_address);
    printf("Please input Initialize the first block_size: ");
    scanf("%d",&initial_size);
    printf("Please input Initialize block number: ");
    scanf("%d",&block->node_num);
    printf("Please input Initialize block arithmetic: ");
    scanf("%d",&initial_arithmetic);

    for(int i = 0; i < block->node_num; i++) {
        block_node *pNew;
        pNew = (block_node *)malloc(sizeof(block_node));
        pNew->block_size = initial_size + i * initial_arithmetic;
        if(i == 0)
            pNew->block_address = initial_address;
        else
            pNew->block_address = next_address;
        next_address = pNew->block_address + pNew->block_size;

        pNew->next = block->head->next;                        /* 头插法录入节点 */
        block->head->next = pNew;
    }

    reverse(block);                                            /* 链表逆置为升序 , 后期看来是多余的操作,有各种排序函数调用*/
    return block;
}

void reverse(Node *block)
{
    block_node *temp;
    temp = block->head->next;

    while(temp->next != NULL) {
        block_node *ptemp, *prev;
        ptemp = temp->next;
        prev = block->head->next;
        temp->next = ptemp->next;
        block->head->next = ptemp;
        ptemp->next = prev;
    }
}

void block_print(Node *block)
{
    if (block == NULL) {                                     // 区块链为空,异常
        printf("The block is NULL!\n");
        return ;
    }
    block_node *temp = block->head->next;                   
    bubble_sort(block, address_ascend);                      // 按地址,进行升序排序

    if (temp == NULL) {                                      // 异常处理
        printf("The block is NULL!\n");
        return ;
    }
    printf("------------------------\n");
    printf("|BLOCK_ARESS|BLOCK_SIZE|\n");
    printf("------------------------\n");
    while (temp) {                                           // 格式化打印所有区块链信息
        printf("|%11d|%10d|\n",temp->block_address, temp->block_size);
        printf("------------------------\n");
        temp = temp->next;
    }
}
