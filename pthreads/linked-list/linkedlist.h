

#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H


typedef struct _list_node_t list_node_t;

/* Basic API for operations on a linked list */
void list_init(list_node_t **head);
size_t list_size(list_node_t *head);
int list_add(list_node_t *head, int item);
int list_remove(list_node_t *head, int item);
int list_contain(list_node_t *head, int item);
void list_print(list_node_t *head);



#endif
