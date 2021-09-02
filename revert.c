#include "revert.h"

#define BUFFER_SIZE		6

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
	char	buffer[BUFFER_SIZE + 1];
	// int		buffer_size = BUFFER_SIZE;
	int		lseek_ret = 0;
	int		read_ret = 0;
	char	*nl_pointer = NULL;
	int		check;
	int		mod = 0;
	int		chars_until_nl = 0;
	int		prev_nl_pos = 0;
	int		buffers_in_file = 0;
	
	bzero(buffer, sizeof(buffer));
	check = strlen(buffer);
	lseek_ret = lseek(fd, 0, SEEK_END);
	buffers_in_file = lseek_ret / BUFFER_SIZE;
	while (buffers_in_file) {
		lseek_ret = lseek(fd, -(BUFFER_SIZE + 1), SEEK_CUR);
		do {
			read_ret += read(fd, buffer, BUFFER_SIZE);
			buffer[BUFFER_SIZE] = '\0';
			nl_pointer = strrchr(buffer, '\n');
			lseek_ret = lseek(fd, -(2 * BUFFER_SIZE + 0), SEEK_CUR);
			if (nl_pointer) {
				chars_until_nl = nl_pointer - buffer + 1;
				lseek_ret = lseek(fd, chars_until_nl + BUFFER_SIZE, SEEK_CUR);
				read_ret -= chars_until_nl;
			}
		} while (!nl_pointer);
		prev_nl_pos = read_ret;
		while (read_ret >= BUFFER_SIZE) {
			read_ret -= read(fd, buffer, BUFFER_SIZE);
			write(1, buffer, strlen(buffer));
		}
		mod = read_ret % BUFFER_SIZE;
		read_ret -= read(fd, buffer, mod);
		buffer[mod] = '\0';
		write(1, buffer, mod);
		write(1, "\n", 1);
		lseek_ret = lseek(fd, -(prev_nl_pos + 0), SEEK_CUR);
		buffers_in_file--;
	}
}
