#include "revert.h"

int		main(int argc, char **argv)
{
	FILE		*file = NULL;

	file = check_arguments(argc, argv[1]);
	if (!file) {
		return (1);
	}

	print_reverted_lines(file);
	
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

void	print_reverted_lines(FILE *file)
{
	ssize_t		linelen = 0;
	int 		file_pos = 0;

	fseek(file, -2, SEEK_END);
	while (file_pos != -1) {
		while (fgetc(file) != '\n') {
			file_pos = fseek(file, -2, SEEK_CUR);
			if (file_pos == -1) {
				fseek(file, -1, SEEK_CUR);
				printline(file);
				return ;
			}
		}
		linelen = printline(file);
		file_pos = fseek(file, -(linelen + 2), SEEK_CUR);
	}
	if (file_pos == -1) {
		putchar('\n');
	}

	return ;
}

size_t	printline(FILE *file)
{
	char		c;
	size_t		linelen = 1;

	c = fgetc(file);
	if (c == EOF) {
		return (1);
	}
	while (c != '\n') {
		putchar(c);
		linelen++;
		c = fgetc(file);
	}
	putchar('\n');

	return (linelen);
}
