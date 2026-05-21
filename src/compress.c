#include "encodeh.h"

int     read_file(t_node **head, const char *file_name)
{
	t_node			*node;
	t_node			*existing_node;
	FILE			*file;
	int				c;

	file = fopen(file_name, "rb");
	if (file == NULL)
	{
		perror("Error while trying to open file.\n");
		return (EXIT_FAILURE);
	}
	while ((c = fgetc(file)) != EOF)
	{
		if ((existing_node = find_char(head, (unsigned char)c)) == NULL)
		{
			node = new_node((unsigned char)c, 1);
			add_node(head, END_NODE, node);
		}
		else
			existing_node->occurrences++;
	}
	fclose(file);
	return (EXIT_SUCCESS);
}

/* Checks over all node list the node with that char/byte is already in */
t_node  *find_char(t_node **head, unsigned char c)
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

// Returns 0 or	1 when climbing the tree up to the next node. If there is no parent node or something is wrong, returns -1
int	get_bit(t_node *node)
{
	t_node	*parent;

	parent = node->parent;
	if (parent == NULL)
		return (-1);
	if (node->parent->left == node)
		return (0);
	if (node->parent->right == node)
		return (1);
	return (-1);
}

void	print_header(t_node **head, FILE *file)
{
	t_node			*node;
	long long int	total_bytes;

	node = get_first_element(head);
	total_bytes = 0;
	while (node)
	{
		total_bytes += node->occurrences;
		node = node->next_end;
	}
    if (fwrite(&total_bytes, sizeof(long long int), 1, file) != 1)
		perror("Error while printing header.\n");
	node = get_first_element(head);
	while (node)
	{
		if (fwrite(&(node->c), sizeof(unsigned char), 1, file) != 1 ||
				fwrite(&(node->occurrences), sizeof(int), 1, file) != 1)
			perror("Error while printing header\n");
		node = node->next_end;
	}
}

/* Given the head node (parent of all parents) of a tree, returns the first element of the leafs (end nodes) linked list */
t_node	*get_first_element(t_node **head)
{
	t_node	*aux;
	t_node	*first_element;

	first_element = NULL;
	aux = *head;
	while (aux)
	{
		if (aux->left == NULL)
		{
			while (aux)
			{
				if (aux->previous_end == NULL)
				{
					first_element = aux;
					break;
				}
				aux = aux->previous_end;
			}
			break;
		}
		aux = aux->left;
	}
	return (first_element);
}

void	print_bytes(t_node **head, FILE *input_file, FILE *output_file)
{
	t_node			*first_element; // First element of the linked list of end nodes
	t_node			*aux;
	int				c;
	unsigned char	byte;
	int				n_bits;
	int				i;
	int				reversed_bits[257];

	byte = 0;
	n_bits = 0;
	first_element = get_first_element(head);
	while ((c = fgetc(input_file)) != EOF)
	{
		aux = first_element;
		while (aux)
		{
			if (aux->c == (unsigned char)c)
			{
				i = 0;
				while ((reversed_bits[i] = get_bit(aux)) != -1)
				{
					aux = aux->parent;
					i++;
				}
				while (i-- > 0)
				{
					byte = (byte << 1) | reversed_bits[i];
					n_bits++;
					if (n_bits == 8)
					{
						if (fputc(byte, output_file) == EOF)
							perror("Error while compressing file.\n");
						byte = 0;
						n_bits = 0;
					}
				}
				break;
			}	
			aux	= aux->next_end;
		}
	}
	if (n_bits > 0)
	{
		byte <<= 8 - n_bits;
		fputc(byte, output_file);
	}
}

int	write_file(t_node **head, const char *file_name)
{
	FILE	*input_file;
	FILE	*output_file;

	input_file = fopen(file_name, "rb");
	if (input_file == NULL)
	{
		perror("Error while trying to read file.\n");
		return (EXIT_FAILURE);
	}
	output_file = fopen("output.huff", "wb");
	if (output_file == NULL)
	{
		perror("Error while trying to create output file.\n");
		return (EXIT_FAILURE);
	}

	// Print file size and data for building the tree
	print_header(head, output_file);

	// Print bytes
	print_bytes(head, input_file, output_file);

	fclose(input_file);
	fclose(output_file);
	return (EXIT_SUCCESS);
}

