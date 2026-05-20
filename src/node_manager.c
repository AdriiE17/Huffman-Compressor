#include "encodeh.h"

/* Creates a new node */
t_node  *new_node(char c, int is_end_node, unsigned int occurrences)
{
	t_node  *node;

	node = (t_node *)malloc(sizeof(t_node));
	if (node == NULL)
		return (NULL);
	node->c = c;
	node->code[0] = END_OF_CODE;
	node->occurrences = occurrences;
	node->is_end_node = is_end_node;
	node->next = NULL;
	node->previous = NULL;
	if (is_end_node == END_NODE)
	{
		node->end_nodes[0] = node;
		node->end_nodes[1] = NULL;
	}
	return (node);
}

/* Addes a node at the end of an existing node list */
void    add_node(t_node **nodes, t_node *new)
{
	t_node  *last;

	if (nodes)
	{
		if (*nodes)
		{
			last = last_node(*nodes);
			last->next = new;
			new->previous = last;
		}
		else
			*nodes = new;
	}
}

/* Given any node of a node list, returns the last element */
t_node  *last_node(t_node *node)
{
	if (node)
	{
		while (node->next)
			node = node->next;
	}
	return (node);
}

/* Deletes a given node of the node list */
void    delete_node(t_node **nodes, t_node *node)
{
	if (nodes && *nodes && node)
	{
		if (node->next && node->previous)
		{
			node->next->previous = node->previous;
			node->previous->next = node->next;
		}
		else if (node->next && !node->previous)
		{
			*nodes = node->next;
			node->next->previous = NULL;
		}
		else if (!node->next && node->previous)
			node->previous->next = NULL;
		else
			*nodes = NULL;
	}
}

/* Given an element of a node list, gives the number of elements from that element (or the size of the list if that element is the first one) */
size_t  nodes_size(t_node *node)
{
	size_t  size;

	size = 0;
	while (node)
	{
		node = node->next;
		size++;
	}
	return (size);
}
