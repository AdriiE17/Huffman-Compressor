#include "encodeh.h" 

int	main(int argc, char *argv[])
{	
	int			opt;
	t_node		*head;

	while ((opt = getopt(argc, argv, "c:")) != -1)
	{
		switch (opt)
		{
			case 'c':
				head = NULL;
				if (read_file(&head, optarg) == EXIT_FAILURE)
					return (EXIT_FAILURE);
				huffman(&nodes);
				if (write_file(&head, optarg) == EXIT_FAILURE)
				{
					free_tree(head);
					return (EXIT_FAILURE);
				}
				free_tree(head);
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
