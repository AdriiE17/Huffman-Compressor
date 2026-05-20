#include "compress.h" 

void print_binary(char c) {
    // Un char tiene 8 bits, por eso el bucle va de 7 a 0
    for (int i = 7; i >= 0; i--) {
        // Desplaza los bits a la derecha y aplica una máscara
        int bit = (c >> i) & 1;
        printf("%d", bit);
    }
    printf("\n");
}

int	main(int argc, char *argv[])
{	
	int			opt;
	int			i;
	const char	*name_file;
	t_node		*nodes;

	while ((opt = getopt(argc, argv, "c:")) != -1)
	{
		switch (opt)
		{
			case 'c':
				name_file = optarg;	
				break;
			case '?':
				printf("Unknown option or missing value.\n");
				break;
			default:
				break;
		}
	}
	nodes = NULL;
	if (read_file(&nodes, name_file) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	huffman(&nodes);
	i = 0;
	while (nodes->end_nodes[i] != NULL)
	{
		printf("El caracter %c aparece %d veces y tiene el código: ", nodes->end_nodes[i]->c, nodes->end_nodes[i]->occurrences);
	   	print_binary(nodes->end_nodes[i]->code);
		printf("\n");
		free(nodes->end_nodes[i]);
		i++;
	}
	free(nodes);	
	return (EXIT_SUCCESS);
}

int	read_file(t_node **nodes, const char *name_file)
{
	t_node	*node;
	t_node	*existing_node;
	FILE	*file;
	char	byte;

	file = fopen(name_file, "rb");
	if (file == NULL)
	{
		perror("Error while reading file.\n");
		return (EXIT_FAILURE);
	}
	while ((byte = fgetc(file)) != EOF)
	{
		if ((existing_node = find_char(nodes, byte)) == NULL)
		{
			node = new_node(byte, END_NODE, 1);
			add_node(nodes, node);
		}
		else
			existing_node->occurrences++;
	}
	return (EXIT_SUCCESS);
}

/* Checks over all node list the node with that char/byte is already in */
t_node	*find_char(t_node **nodes, char byte)
{
	t_node	*node;

	if (nodes == NULL)
		return (NULL);
	node = *nodes;
	while (node)
	{
		if (node->c == byte)
			return (node);
		node = node->next;
	}
	return (NULL);
}

/* Returns the first node whose occurrence is the minimum value starting from the given node */
t_node	*get_min_nodes(t_node *node)
{
	t_node	*min;

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

void	huffman(t_node **nodes)
{
	t_node	*min[2];
	t_node	*node;
	int		i;
	int		j;
	int		k;

	while (nodes_size(*nodes) > 1)
	{
		min[0] = get_min_nodes(*nodes);
		min[1] = get_min_nodes(min[0]->next);
		node = new_node('\0', NOT_END_NODE, min[0]->occurrences + min[1]->occurrences);
		j = 0;
		for (i = 0; i < 2; i++)
		{
			k = j;	
			while (min[i]->end_nodes[j] != NULL)
			{
				min[i]->end_nodes[j]->code = min[i]->end_nodes[i]->code << i;
				node->end_nodes[j + k] = min[i]->end_nodes[j];
				j++;
			}
			delete_node(nodes, min[i]);
		}
		node->end_nodes[j + k] = NULL;
		if (min[0]->is_end_node == NOT_END_NODE)
			free(min[0]);
		if (min[1]->is_end_node == NOT_END_NODE)
			free(min[1]);
		add_node(nodes, node);
	}
}
