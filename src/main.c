#include "compress.h" 

int	main(int argc, char *argv[])
{	
	int			opt;
	const char	*name_file;
	t_node		*nodes;
	size_t		size;

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
	if (read_file(&nodes, &size, name_file) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	size_t	i;
	printf("size = %zu\n", size);
	for (i = 0; i < size; i++)
		printf("El caracter %c aparece %d veces.\n", nodes[i].c, nodes[i].occurrences);
	
	free(nodes);
	return (EXIT_SUCCESS);
}
int	read_file(t_node **nodes_pointer, size_t *size, const char *name_file)
{
	t_node	*nodes;
	FILE	*file;
	t_node	*tmp;
	int		char_position;
	char	byte;

	file = fopen(name_file, "rb");
	if (file == NULL)
	{
		perror("Error while reading file.\n");
		return (EXIT_FAILURE);
	}
	*size = 0;
	nodes = NULL;
	while ((byte = fgetc(file)) != EOF)
	{
		if ((char_position = find_char(nodes, *size, byte)) == -1)
		{
			(*size)++;
			tmp = (t_node *)realloc(nodes, (*size)*sizeof(t_node));
			if (tmp == NULL)
			{
				free(nodes);
				perror("Error while reading file. Realloc error.\n");
				return (EXIT_FAILURE);
			}
			nodes = tmp;
			nodes[*size - 1].c = byte;
			nodes[*size - 1].is_end_node = END_NODE;
			nodes[*size - 1].occurrences = 1;
		}
		else
			nodes[char_position].occurrences++;
	}
	*nodes_pointer = nodes;
	return (EXIT_SUCCESS);
}

int	find_char(t_node *nodes, size_t size, char byte)
{
	size_t	i;

	for (i = 0; i < size; i++)
	{
		if (nodes[i].c == byte)
			return ((int) i);
	}
	return (-1);
}
