#ifndef _LIST_H_
#define _LIST_H_

#include "compiler.h"

struct list {
	struct list *next;
	struct list *prev;
};

#define LIST_NODE(l)							\
	struct list l = { .next = &l, .prev = &l }

static inline void list_node_init(struct list *l)
{
	l->next = l;
	l->prev = l;
}

#define list_entry(ptr, type, member)					\
	container_of(ptr, type, member)

#define list_first_entry(ptr, type, member)				\
	list_entry((ptr)->next, type, member)

#define list_last_entry(ptr, type, member)				\
	list_entry((ptr)->prev, type, member)

#define list_next_entry(pos, member)					\
	list_entry((pos)->member.next, typeof(*pos), member)

#define list_empty(l)							\
	((l)->next == (l)->prev)

#define list_is_head(pos, head, member)					\
	(&(pos)->member == (head))

#define list_for_each_entry(pos, head, member)				\
	for ((pos) = list_first_entry(head, typeof(*pos), member);	\
	     !list_is_head(pos, head, member);				\
	     (pos) = list_next_entry(pos, member))

static inline void list_add(struct list *node, struct list *head)
{
	node->next = head->next;
	node->prev = head;
	head->next->prev = node;
	head->next = node;
}

static inline void list_add_tail(struct list *node, struct list *head)
{
	node->next = head;
	node->prev = head->prev;
	head->prev->next = node;
	head->prev = node;
}

static inline void list_del(struct list *node)
{
	node->prev->next = node->next;
	node->next->prev = node->prev;

	list_node_init(node);
}
#endif /* _LIST_H_ */
