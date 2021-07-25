#include "revert.h"

int		main(int argc, char **argv)
{
	FILE		*file = NULL;
	size_t		lines_count = 0;

	file = check_arguments(argc, argv[1]);
	if (!file) {
		return (1);
	}

	lines_count = count_lines_in_file(file) - 1;
	print_reverted_lines(file, lines_count);
	
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

size_t	count_lines_in_file(FILE *file)
{
	size_t		lines_count = 0;
	char c = fgetc(file);

	if (c == EOF) {
		return (1);
	}
	while (c != EOF) {
		if (c == '\n') {
			lines_count++;
		}
		c = fgetc(file);
	}

	return (lines_count);
}

void	print_reverted_lines(FILE *file, size_t lines_count)
{
	ssize_t		linelen = 0;

	fseek(file, -2, SEEK_END);
	while (lines_count > 1) {
		while ((fgetc(file) != '\n') && (lines_count > 1)) {
			fseek(file, -2, SEEK_CUR);
		}
		linelen = printline(file);
		fseek(file, -(linelen + 2), SEEK_CUR);
		lines_count--;
	}
	fseek(file, 0, SEEK_SET);
	printline(file);
}

size_t	printline(FILE *file)
{
	char		c;
	size_t		linelen = 1;

	while ((c = fgetc(file)) != '\n') {
		if (c == EOF) {
			return (1);
		}
		putchar(c);
		linelen++;
	}
	putchar('\n');

	return (linelen);
}
