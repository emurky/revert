#include "revert.h"

#define BUFFER_SIZE		7

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
	(void)fd;
	char	buffer[BUFFER_SIZE + 1];
	int		read_ret = 0;
	char	*nl_pointer = NULL;
	int		nl_pos = 0;
	int		linelen = 0;
	int		lseek_ret = 0;
	int		buffers_without_nl = 0;
int	buffers_was_printed = false;

lseek_ret = lseek(fd, -(1 + BUFFER_SIZE), SEEK_END);
	do {
		read_ret = read(fd, buffer, BUFFER_SIZE);
		buffer[read_ret] = '\0';
		nl_pointer = strrchr(buffer, '\n');
		if (!nl_pointer) {
			buffers_without_nl++;
		}
		while (nl_pointer) {
			nl_pos = nl_pointer - buffer;
			nl_pointer++;
			linelen = strlen(nl_pointer);
			write(1, nl_pointer, linelen);
			while (buffers_without_nl) {
				read_ret = read(fd, buffer, BUFFER_SIZE);
				write(1, buffer, BUFFER_SIZE);
				buffer[read_ret] = '\0';
				buffers_was_printed = true;
				buffers_without_nl--;
			}
			if (!buffers_was_printed) {
				write(1, "\n", 1);
			}
			buffer[nl_pos] = '\0';
			lseek_ret = lseek(fd, -(linelen + 0), SEEK_CUR);
			nl_pointer = strrchr(buffer, '\n');
			buffers_was_printed = false;
		}
		lseek_ret = lseek(fd, -(0 + 2 * BUFFER_SIZE), SEEK_CUR);
	} while (lseek_ret != -1);
	linelen = strlen(buffer);
	write(1, buffer, linelen);
	write(1, "\n", 1);
}
