#ifndef REVERT_H
# define REVERT_H

# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>

typedef	struct		s_list
{
	char			*line;
	struct s_list	*next;
	struct s_list	*previous;
}					t_list;

FILE	*arguments_handling(int argc, char *file_path);
void	new_list_node(t_list **list, char *buffer);
void	clear_list(t_list *list);

#endif
