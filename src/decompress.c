#include "encodeh.h"

int	read_write_compressed_file(t_node **head, const char *file_name)
{
	t_node			*node;
	FILE			*input_file;
	int				occurrences;
	long long int	total_characters;
	long long int	aux;
	int				c;

	input_file = fopen(file_name, "rb");
	if (input_file == NULL)
	{
		perror("Error while trying to open file.\n");
		return (EXIT_FAILURE);
	}

	// Read header and build tree
	if (fread(&total_characters, sizeof(long long int), 1, input_file) != 1)
	{
		printf("Error while reading file.\n");
		return (EXIT_FAILURE);
	}
	aux = total_characters;
	while (aux > 0)
	{
		c = fgetc(input_file);
		if (c == EOF || fread(&occurrences, sizeof(int), 1, input_file) != 1)
		{
			printf("Error while reading file or empty file.\n");
			return (EXIT_FAILURE);
		}
		node = new_node((unsigned char)c, occurrences);
		add_node(head, END_NODE, node);
		aux -= occurrences;
	}
	huffman(head);
	if (write_decompressed_file(head, total_characters, input_file) == EXIT_FAILURE)
	{
		free_tree(*head);
		return (EXIT_FAILURE);
	}
	fclose(input_file);
	return (EXIT_SUCCESS);
}

int	write_decompressed_file(t_node **head, long long int total_characters, FILE *input_file)
{
	FILE			*output_file;
	t_node			*node;
	unsigned char	byte;
	int				bit;
	int				i;
	int				c;

	output_file = fopen("decompressed", "wb");
	if (output_file == NULL)
	{
		perror("Error while trying to open output file.\n");
		return (EXIT_FAILURE);
	}
	node = *head;
	while (total_characters > 0)
	{
		c = fgetc(input_file);
		if (c == EOF)
		{
			perror("Error while reading or empty file.\n");
			return (EXIT_FAILURE);
		}
		byte = (unsigned char)c;
		for (i = 7; i >= 0; i--)
		{
			bit = (byte >> i) & 1;
			if (node->left == NULL || node->right == NULL)
			{
				if (fputc(node->c, output_file) == EOF)
					perror("Error while writing.\n");
				node = *head;
				total_characters--;
			}
			if (total_characters == 0)
				break;
			if (bit == 0)
				node = node->left;
			if (bit == 1)
				node = node->right;
		}
	}
	fclose(output_file);
	return (EXIT_SUCCESS);
}
