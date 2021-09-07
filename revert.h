#ifndef REVERT_H
# define REVERT_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <stdlib.h>

# ifndef	BUFFER_SIZE
# define	BUFFER_SIZE		42
# endif

int			check_arguments(int argc, char *file_path);
void		print_line(int fd, char *buffer, int *line_len);
size_t		print_line_1char(int fd);
void		handle_file_beginning(int fd, int file_pos);
void		print_reverted_lines(int fd);

#endif
