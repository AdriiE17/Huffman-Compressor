#ifndef ENCODEH_H
# define ENCODEH_H

# define END_NODE 1
# define NOT_END_NODE 0
# define TOTAL_CHARACTERS 256
# define END_OF_CODE 2

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct	s_node
{
	unsigned char	c;
	unsigned char	code[TOTAL_CHARACTERS - 1];
	int				is_end_node;
	unsigned int	occurrences;
	struct s_node	*next;
	struct s_node	*previous;
	struct s_node	*end_nodes[TOTAL_CHARACTERS];
}	t_node;

/* Compressing */
int		read_file(t_node **nodes, const char *name_file);
t_node	*find_char(t_node **nodes, char c);
void	huffman(t_node **nodes);
size_t	get_last_bit_position(unsigned char code[]);
void	print_code(unsigned char code[]);
int		write_file(t_node **nodes, const char *file_name);

/* Decompressing */


/* Node management */
t_node  *new_node(char c, int is_end_node, unsigned int occurrences);
void    add_node(t_node **nodes, t_node *new);
t_node  *last_node(t_node *nodes);
void    delete_node(t_node **nodes, t_node *node);
size_t	nodes_size(t_node *node);

t_node	*get_min_nodes(t_node *node);

#endif
