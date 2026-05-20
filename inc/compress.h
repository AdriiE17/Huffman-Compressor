#ifndef COMPRESS_H
# define COMPRESS_H

# define END_NODE 1
# define NOT_END_NODE 0

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct	s_node
{
	char			c;
	char			code;
	int				is_end_node;
	unsigned int	occurrences;
}	t_node;

int     read_file(t_node **nodes, size_t *size, const char *name_file);
int     find_char(t_node *nodes, size_t size, char byte);

#endif
