#ifndef _LIST_NODE_H
#define _LIST_NODE_H

typedef struct _node {
    int list_process_ID;
    int list_process_size;
    int list_block_address;
} list_node;

typedef struct List_Node {
    list_node data;
    struct List_Node *LChild;
    struct List_Node *RChild;
} list;

void list_insert(list **process_list, list_node node);

void list_print(list *process_list);

void list_visit(list *process_list);

list_node *list_search(list **process_list, int list_process_ID);

void list_delete(list **process_list, int list_process_ID);

#endif
