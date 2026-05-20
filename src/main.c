#include "compress.h" 

int	main(int argc, char *argv[])
{	
	int			opt;
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

	t_node *tmp;
	tmp = nodes;
	while (tmp)
	{
		printf("El caracter %c aparece %d veces.\n", tmp->c, tmp->occurrences);
		tmp = tmp->next;
	}
	
	clear_nodes(&nodes);
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
