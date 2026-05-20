#ifndef COMPRESS_H
# define COMPRESS_H

# define END_NODE 1
# define NOT_END_NODE 0
# define TOTAL_CHARACTERS 256

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct	s_node
{
	char			c;
	char			code;
	int				is_end_node;
	unsigned int	occurrences;
	struct s_node	*next;
	struct s_node	*previous;
	struct s_node	*end_nodes[TOTAL_CHARACTERS];
}	t_node;

int		read_file(t_node **nodes, const char *name_file);
t_node	*find_char(t_node **nodes, char byte);
void	huffman(t_node **nodes);

/* Node management */
t_node  *new_node(char c, int is_end_node, unsigned int occurrences);
void    add_node(t_node **nodes, t_node *new);
t_node  *last_node(t_node *nodes);
void    delete_node(t_node **nodes, t_node *node);
size_t	nodes_size(t_node *node);

t_node	*get_min_nodes(t_node *node);

#endif
