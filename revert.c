#include "revert.h"

int		main(int argc, char **argv)
{
	FILE		*file = NULL;
	char		*buffer = NULL;
	size_t		line_count = 0;

	file = check_arguments(argc, argv[1]);
	if (!file) {
		return (1);
	}

	line_count = count_lines_in_file(file, &buffer) - 1;
	print_reverted_lines(file, &buffer, line_count);

	free(buffer);
	fclose(file);

	return (0);
}

FILE	*check_arguments(int argc, char *file_path)
{
	FILE	*file = NULL;

	if (argc != 2) {
		printf("Error\nThere must be only one argument as a file name\n");
		return (NULL);
	}

	file = fopen(file_path, "r");
	if (!file) {
		printf("Error\nCannot open file\n");
		return (NULL);
	}

	return (file);
}

size_t	count_lines_in_file(FILE *file, char **buffer)
{
	size_t		line_count = 0;
	ssize_t		linelen = 0;
	size_t		linecap = 0;

	while (linelen != EOF) {
		linelen = getline(buffer, &linecap, file);
		line_count++;
	}

	return (line_count);
}

void	print_reverted_lines(FILE *file, char **buffer, size_t line_count)
{
	size_t		line_count_buffer = 0;
	ssize_t		linelen = 0;
	size_t		linecap = 0;

	while (line_count) {
		rewind(file);
		line_count_buffer = line_count;
		while (line_count_buffer) {
			linelen = getline(buffer, &linecap, file);
			line_count_buffer--;
		}
		fseek(file, -linelen, SEEK_CUR);
		getline(buffer, &linecap, file);
		printf("%s", *buffer);
		line_count--;
	}
}
