#include "encodeh.h" 

int	main(int argc, char *argv[])
{	
	int			opt;
	t_node		*head;

	if (argc < 3)
		return (write(2,"Usage: ./encodeh -c <file> | -d <file>\n",40), 1);

	head = NULL;
	while ((opt = getopt(argc, argv, "c:d:")) != -1)
	{
		switch (opt)
		{
			case 'c':
				if (read_file(&head, optarg) == EXIT_FAILURE)
					return (EXIT_FAILURE);
				huffman(&head);
				if (write_file(&head, optarg) == EXIT_FAILURE)
				{
					free_tree(head);
					return (EXIT_FAILURE);
				}
				free_tree(head);
				break;
			case 'd':
				if (read_write_compressed_file(&head, optarg) == EXIT_FAILURE)
					return (EXIT_FAILURE);
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
