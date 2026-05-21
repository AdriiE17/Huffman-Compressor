#include "encodeh.h"

int     read_file(t_node **head, const char *file_name)
{
	t_node  *node;
	t_node  *existing_node;
	FILE    *file;
	char    c;

	file = fopen(file_name, "rb");
	if (file == NULL)
	{
		perror("Error while reading file.\n");
		return (EXIT_FAILURE);
	}
	while ((c = fgetc(file)) != EOF)
	{
		if ((existing_node = find_char(nodes, c)) == NULL)
		{
			node = new_node(c, 1);
			add_node(head, END_NODE, node);
		}
		else
			existing_node->occurrences++;
	}
	fclose(file);
	return (EXIT_SUCCESS);
}

/* Checks over all node list the node with that char is already in */
t_node  *find_char(t_node **head, char c)
{
	t_node  *node;

	if (head == NULL)
		return (NULL);
	node = *head;
	while (node)
	{
		if (node->c == c)
			return (node);
		node = node->next_end;
	}
	return (NULL);
}

/* Returns the first node whose occurrence is the minimum value starting from the given node */
t_node  *get_min_nodes(t_node *node)
{
	t_node  *min;

	min = node;
	node = node->next;
	while (node)
	{
		if (min->occurrences > node->occurrences)
			min = node;
		node = node->next;
	}
	return (min);
}

void    huffman(t_node **head)
{
	t_node  *min[2];
	t_node  *node;

	while (nodes_size(*head) > 1)
	{
		min[0] = get_min_nodes(*head);
		delete_node(head, min[0]);
		min[1] = get_min_nodes(*head);
		delete_node(head, min[1]);
		
		node = new_node('\0', min[0]->occurrences + min[1]->occurrences);
		
		min[0]->parent = node;
		min[1]->parent = node;
		node->left = min[0];
		node->right = min[1];

		add_node(head, NOT_END_NODE, node);
	}
}

int	write_file(t_node **head, const char *file_name)
{
	FILE			*input_file;
	FILE		    *output_file;

	input_file = fopen(file_name, "r");
	if (input_file == NULL)
	{
		perror("Error while reading file.\n");
		return (EXIT_FAILURE);
	}
	output_file = fopen("output.huff", "wb");
	if (output_file == NULL)
	{
		perror("Error while writing file.\n");
		return (EXIT_FAILURE);
	}

	/*
	char			c;
	unsigned char	byte;
	int				i;
	int				j;
	int				k;

	k = 0;
	byte = 0;
	while ((c = fgetc(input_file)) != EOF)
	{
		i = 0;
		while ((*nodes)->end_nodes[i] != NULL)
		{
			if ((*nodes)->end_nodes[i]->c == c)
			{
				j = 0;
				while ((*nodes)->end_nodes[i]->code[j] != END_OF_CODE)
				{
					if (k == 8)
					{
						k = 0;
						fputc(byte, output_file);
						byte = 0;
					}
					byte = (byte << 1) & (*nodes)->end_nodes[i]->code[j];
					k++;
					j++;
				}
				break;
			}
			i++;
		}		
	}
	if (k == 8)
		fputc(byte, output_file);
	else
		byte <<= 8 - k;
	*/


	fclose(input_file);
	fclose(output_file);
	return (EXIT_SUCCESS);
}
