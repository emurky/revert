#include "revert.h"

int		main(int argc, char **argv)
{
	FILE		*file = NULL;
	char		*buffer = NULL;
	size_t		lines_count = 0;

	file = check_arguments(argc, argv[1]);
	if (!file) {
		return (1);
	}

	lines_count = count_lines_in_file(file, &buffer) - 1;
	print_reverted_lines(file, &buffer, lines_count);

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
	size_t		lines_count = 0;
	ssize_t		linelen = 0;
	size_t		linecap = 0;

	while (linelen != EOF) {
		linelen = getline(buffer, &linecap, file);
		lines_count++;
	}

	return (lines_count);
}

void	print_reverted_lines(FILE *file, char **buffer, size_t lines_count)
{
	ssize_t		linelen = 0;
	size_t		linecap = 0;

	fseek(file, -2, SEEK_END);
	while (lines_count > 1) {
		while ((fgetc(file) != '\n') && (lines_count > 1)) {
			fseek(file, -2, SEEK_CUR);
		}
		linelen = getline(buffer, &linecap, file);
		printf("%s", *buffer);
		fseek(file, -(linelen + 2), SEEK_CUR);
		lines_count--;
	}
	fseek(file, 0, SEEK_SET);
	getline(buffer, &linecap, file);
	printf("%s", *buffer);
}
