#ifndef ENCODEH_H
# define ENCODEH_H

# define END_NODE 1
# define NOT_END_NODE 0

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct	s_node
{
	unsigned char	c;
	unsigned int	occurrences;

	// For end nodes
	struct s_node	*next_end;
	struct s_node	*previous_end;
	
	// For building the tree
	struct s_node	*next;
	struct s_node	*previous;

    struct s_node	*left;
    struct s_node	*right;
	struct s_node	*parent;
}	t_node;

/* Compressing */
int		read_file(t_node **head, const char *file_name);
t_node	*find_char(t_node **head, unsigned char c);
void	huffman(t_node **head);
int		write_file(t_node **head, const char *file_name);
int		get_bit(t_node *node);
t_node	*get_first_element(t_node **head);
void	print_bytes(t_node **head, FILE *input_file, FILE *output_file);
void	print_header(t_node **head, FILE *file);

/* Decompressing */
int		read_write_compressed_file(t_node **head, const char *file_name);
int		write_decompressed_file();

/* Node management */
t_node  *new_node(unsigned char c, unsigned int occurrences);
void    add_node(t_node **head, int is_end_node, t_node *new);
t_node  *last_node(t_node *node);
void    delete_node(t_node **head, t_node *node);
size_t	nodes_size(t_node *node);
void	free_tree(t_node *head);

t_node	*get_min_nodes(t_node *node);

#endif
