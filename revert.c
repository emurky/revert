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

void	print_line(int fd, char *buffer, int *line_len)
{
	int		remainder = 0;
	
	while (*line_len >= BUFFER_SIZE) {
		*line_len -= read(fd, buffer, BUFFER_SIZE);
		write(1, buffer, BUFFER_SIZE);
	}
	remainder = *line_len % BUFFER_SIZE;
	*line_len -= read(fd, buffer, remainder);
	buffer[remainder] = '\0';
	write(1, buffer, remainder);
	write(1, "\n", 1);
}

size_t	print_line_1char(int fd)
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
	/* it is commented to be more alike tac */
	// if (!read_check) {
	// 	linelen--;
	// }
	write(1, "\n", 1);

	return (linelen);
}

void	handle_file_beginning(int fd, int file_pos)
{
	ssize_t		linelen = 0;
	int			read_check;
	char		c = -1;

	lseek(fd, file_pos, SEEK_SET);
	while (file_pos != -1) {
		read_check = read(fd, &c, sizeof(char));
		while (c != '\n') {
			file_pos = lseek(fd, -2, SEEK_CUR);
			if (file_pos == -1) {
				lseek(fd, -1, SEEK_CUR);
				print_line_1char(fd);
				return ;
			}
			read_check = read(fd, &c, sizeof(char));
		}
		linelen = print_line_1char(fd);
		file_pos = lseek(fd, -(linelen + 2), SEEK_CUR);
	}
	write(1, "\n", 1);

	return ;
}

void	print_reverted_lines(int fd)
{
	char	buffer[BUFFER_SIZE + 1];
	int		chars_in_file = 0;
	int		file_pos = 0;
	int		prev_file_pos = 0;
	int		line_len = 0;
	char	*nl_pointer = NULL;
	int		chars_until_nl = 0;
	int		prev_nl_pos = 0;

	bzero(buffer, sizeof(buffer));
	chars_in_file = lseek(fd, 0, SEEK_END);
	file_pos = chars_in_file;

	while (true) {
		prev_file_pos = file_pos;
		file_pos = lseek(fd, -(BUFFER_SIZE + 1), SEEK_CUR);
		if (file_pos < 0) {
			handle_file_beginning(fd, prev_file_pos);
			return ;
		}

		do {
			line_len += read(fd, buffer, BUFFER_SIZE);
			nl_pointer = strrchr(buffer, '\n');
			file_pos = lseek(fd, -2 * BUFFER_SIZE, SEEK_CUR);
			if (file_pos < 0) {
				handle_file_beginning(fd, prev_file_pos - 2);
				return ;
			}
			if (nl_pointer) {
				chars_until_nl = nl_pointer - buffer + 1;
				prev_file_pos = file_pos;
				file_pos = lseek(fd, chars_until_nl + BUFFER_SIZE, SEEK_CUR);
				line_len -= chars_until_nl;
				if (file_pos < 0) {
					handle_file_beginning(fd, prev_file_pos);
					return ;
				}
			}
		} while (!nl_pointer);

		prev_nl_pos = line_len;
		print_line(fd, buffer, &line_len);
		file_pos = lseek(fd, -prev_nl_pos, SEEK_CUR);
	}
}
