#include "encodeh.h"

/* Creates a new node */
t_node  *new_node(unsigned char c, unsigned int occurrences)
{
	t_node  *node;

	node = (t_node *)malloc(sizeof(t_node));
	if (node == NULL)
		return (NULL);
	node->c = c;
	node->occurrences = occurrences;
	node->next = NULL;
	node->previous = NULL;
	node->next_end = NULL;
	node->previous_end = NULL;
	node->left = NULL;
	node->right = NULL;
	node->parent = NULL;
	return (node);
}

/* Addes a node at the end of an existing node list */
void    add_node(t_node **head, int is_end_node, t_node *new)
{
	t_node  *last;

	if (head)
	{
		if (*head)
		{
			last = last_node(*head);
			last->next = new;
			new->previous = last;
			if (is_end_node == END_NODE)
			{
				last->next_end = new;
				new->previous_end = last;
			}
		}
		else
			*head = new;
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

/* Deletes a given node of the node list (it doesn't free its memory) */
void    delete_node(t_node **head, t_node *node)
{
	if (head && *head && node)
	{
		if (node->next && node->previous)
		{
			node->next->previous = node->previous;
			node->previous->next = node->next;
		}
		else if (node->next && !node->previous)
		{
			*head = node->next;
			node->next->previous = NULL;
		}
		else if (!node->next && node->previous)
			node->previous->next = NULL;
		else
			*head = NULL;
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

// Frees the whole tree
void	free_tree(t_node *head)
{
	if (head != NULL)
	{
		if (head->left != NULL)
			free_tree(head->left);
		if (head->right != NULL)
			free_tree(head->right);
		free(head);
	}
}
