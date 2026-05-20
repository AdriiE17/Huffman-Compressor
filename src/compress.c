#include "encodeh.h"

int     read_file(t_node **nodes, const char *file_name)
{
	t_node  *node;
	t_node  *existing_node;
	FILE    *file;
	char    c;

	file = fopen(file_name, "r");
	if (file == NULL)
	{
		perror("Error while reading file.\n");
		return (EXIT_FAILURE);
	}
	while ((c = fgetc(file)) != EOF)
	{
		if ((existing_node = find_char(nodes, c)) == NULL)
		{
			node = new_node(c, END_NODE, 1);
			add_node(nodes, node);
		}
		else
			existing_node->occurrences++;
	}
	fclose(file);
	return (EXIT_SUCCESS);
}

/* Checks over all node list the node with that char is already in */
t_node  *find_char(t_node **nodes, char c)
{
	t_node  *node;

	if (nodes == NULL)
		return (NULL);
	node = *nodes;
	while (node)
	{
		if (node->c == c)
			return (node);
		node = node->next;
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

void    huffman(t_node **nodes)
{
	t_node  *min[2];
	t_node  *node;
	size_t  last_bit_pos;
	size_t  i;
	size_t  j;
	size_t  k;

	while (nodes_size(*nodes) > 1)
	{
		min[0] = get_min_nodes(*nodes);
		delete_node(nodes, min[0]);
		min[1] = get_min_nodes(*nodes);
		delete_node(nodes, min[1]);
		node = new_node('\0', NOT_END_NODE, min[0]->occurrences + min[1]->occurrences);
		k = 0;
		for (i = 0; i < 2; i++)
		{
			j = 0;
			while (min[i]->end_nodes[j] != NULL)
			{
				last_bit_pos = get_last_bit_position(min[i]->end_nodes[j]->code);
				min[i]->end_nodes[j]->code[last_bit_pos] = i;
				min[i]->end_nodes[j]->code[last_bit_pos + 1] = END_OF_CODE;
				node->end_nodes[j + k] = min[i]->end_nodes[j];
				j++;
			}
			if (i == 0)
				k = j;
		}
		node->end_nodes[j + k] = NULL;
		if (min[0]->is_end_node == NOT_END_NODE)
			free(min[0]);
		if (min[1]->is_end_node == NOT_END_NODE)
			free(min[1]);
		add_node(nodes, node);
	}
}

size_t  get_last_bit_position(unsigned char code[])
{
	size_t  i;

	i = 0;
	while (code[i] != END_OF_CODE)
		i++;
	return (i);
}

void write_code(unsigned char code[], FILE *file)
{
	size_t  last_pos;

	last_pos = get_last_bit_position(code);
	while (last_pos-- > 0)
		fputc(code[last_pos] + '0', file);
}

int	write_file(t_node **nodes, const char *file_name)
{
	FILE    *input_file;
	FILE    *output_file;
	char    c;
	int		i;

	input_file = fopen(file_name, "r");
	if (input_file == NULL)
	{
		perror("Error while reading file.\n");
		return (EXIT_FAILURE);
	}
	output_file = fopen("output.huff", "w");
	if (output_file == NULL)
	{
		perror("Error while writing file.\n");
		return (EXIT_FAILURE);
	}
	while ((c = fgetc(input_file)) != EOF)
	{
		i = 0;
		while ((*nodes)->end_nodes[i] != NULL)
		{
			if ((*nodes)->end_nodes[i]->c == c)
			{
				write_code((*nodes)->end_nodes[i]->code, output_file);
				break;
			}
			i++;
		}		
	}
	fclose(input_file);
	fclose(output_file);
	return (EXIT_SUCCESS);
}
