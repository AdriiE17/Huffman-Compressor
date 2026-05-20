#include "encodeh.h" 

void print_code(unsigned char code[])
{
	size_t  last_pos;

	last_pos = get_last_bit_position(code);
	while (last_pos-- > 0)
		printf("%d", code[last_pos]);
}

int	main(int argc, char *argv[])
{	
	int			opt;
	t_node		*nodes;

	while ((opt = getopt(argc, argv, "c:")) != -1)
	{
		switch (opt)
		{
			case 'c':
				nodes = NULL;
				if (read_file(&nodes, optarg) == EXIT_FAILURE)
					return (EXIT_FAILURE);
				huffman(&nodes);

				/*
				int	i = 0;
				while (nodes->end_nodes[i] != NULL)
				{
					printf("El caracter %c aparece %d veces y tiene el código: ", nodes->end_nodes[i]->c, nodes->end_nodes[i]->occurrences);
					print_code(nodes->end_nodes[i]->code);
					printf("\n");
					free(nodes->end_nodes[i]);
					i++;
				}
				*/

				if (write_file(&nodes, optarg) == EXIT_FAILURE)
				{
					free(nodes);
					return (EXIT_FAILURE);
				}
				free(nodes);
				break;
			case '?':
				printf("Unknown option or missing value.\n");
				break;
			default:
				break;
		}
	}
	return (EXIT_SUCCESS);
}
