#include "revert.h"

int		main(int argc, char **argv)
{
	int		fd;

	fd = check_arguments(argc, argv[1]);
	if (fd < 0) {
		return (1);
	}

	print_reverted_lines(fd);
	
	close(fd);
	return (0);
}

int		check_arguments(int argc, char *file_path)
{
	int		fd;

	if (argc != 2) {
		printf("Error\nThere must be only one argument as a file name\n");
		return (-1);
	}

	fd = open(file_path, O_RDONLY);
	if (fd < 0) {
		printf("Error\nCannot open file\n");
		return (-1);
	}

	return (fd);
}

void	print_reverted_lines(int fd)
{
	ssize_t		linelen = 0;
	int 		file_pos = 0;
	int			read_check;
	char		c = -1;

	lseek(fd, -2, SEEK_END);
	while (file_pos != -1) {
		read_check = read(fd, &c, sizeof(char));
		while (c != '\n') {
			file_pos = lseek(fd, -2, SEEK_CUR);
			if (file_pos == -1) {
				lseek(fd, -1, SEEK_CUR);
				printline(fd);
				return ;
			}
			read_check = read(fd, &c, sizeof(char));
		}
		linelen = printline(fd);
		file_pos = lseek(fd, -(linelen + 2), SEEK_CUR);
	}
	write(1, "\n", 1);

	return ;
}

size_t	printline(int fd)
{
	char		c = -1;
	size_t		linelen = 1;
	int			read_check;

	read_check = read(fd, &c, sizeof(char));
	if (c == EOF) {
		return (1);
	}
	while (c != '\n' && read_check) {
		write(1, &c, 1);
		read_check = read(fd, &c, sizeof(char));
		linelen++;
	}
	if (!read_check) {
		linelen--;
	}
	write(1, "\n", 1);

	return (linelen);
}
