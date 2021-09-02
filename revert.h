#ifndef REVERT_H
# define REVERT_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <stdlib.h>

int			check_arguments(int argc, char *file_path);
size_t		count_lines_in_file(int fd);
void		print_reverted_lines(int fd);
size_t		printline(int fd);
int		min(int x, int y);

#endif
