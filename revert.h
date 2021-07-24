#ifndef REVERT_H
# define REVERT_H

# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>

FILE		*check_arguments(int argc, char *file_path);
size_t		count_lines_in_file(FILE *file, char **buffer);
void		print_reverted_lines(FILE *file, char **buffer, size_t lines_count);

#endif
