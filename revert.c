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

#define BUFFER_SIZE		6

void	print_line(int fd, char *buffer, int *line_len)
{
	int		mod = 0;
	
	while (*line_len >= BUFFER_SIZE) {
		*line_len -= read(fd, buffer, BUFFER_SIZE);
		write(1, buffer, BUFFER_SIZE);
	}
	mod = *line_len % BUFFER_SIZE;
	*line_len -= read(fd, buffer, mod);
	buffer[mod] = '\0';
	write(1, buffer, mod);
	write(1, "\n", 1);
}

void	print_reverted_lines(int fd)
{
	char	buffer[BUFFER_SIZE + 1];
	int		buffer_size = BUFFER_SIZE;
	int		chars_in_file = 0;
	int		lseek_ret = 0;
	int		line_len = 0;
	char	*nl_pointer = NULL;
	// int		check;
	// int		mod = 0;
	int		chars_until_nl = 0;
	int		prev_nl_pos = 0;
	// int		buffers_in_file = 0;
	int		end = false;

	bzero(buffer, sizeof(buffer));
	chars_in_file = lseek(fd, 0, SEEK_END);
	lseek_ret = chars_in_file;
	if (lseek_ret < buffer_size) {
		buffer_size = lseek_ret;
	}
	while (!end) {
		// if (2 * buffer_size > lseek_ret) {
		// 	buffer_size /= 2;
		// }
		lseek_ret = lseek(fd, -(BUFFER_SIZE + 1), SEEK_CUR);
		do {
			line_len += read(fd, buffer, BUFFER_SIZE);
			buffer[BUFFER_SIZE] = '\0';
			nl_pointer = strrchr(buffer, '\n');
			lseek_ret = lseek(fd, -2 * BUFFER_SIZE, SEEK_CUR);
			// if (lseek_ret == -1) {
			// 	lseek_ret = lseek(fd, 0, SEEK_SET);
			// 	line_len = read(fd, buffer, BUFFER_SIZE);
			// 	nl_pointer = strrchr(buffer, '\n');
			// 	while (!nl_pointer) {
			// 		write(1, buffer, BUFFER_SIZE);
			// 		read(fd, buffer, BUFFER_SIZE);
			// 		nl_pointer = strrchr(buffer, '\n');
			// 	}
			// 	*nl_pointer = '\0';
			// 	write(1, buffer, strlen(buffer));
			// 	write(1, "\n", 1);
			// 	end = true;
			// 	break ;
			// }
			if (nl_pointer) {
				chars_until_nl = nl_pointer - buffer + 1;
				lseek_ret = lseek(fd, chars_until_nl + BUFFER_SIZE, SEEK_CUR);
				line_len -= chars_until_nl;
			}
		} while (!nl_pointer);
		prev_nl_pos = line_len;
		print_line(fd, buffer, &line_len);
		// if (lseek_ret > 0 && !end) {
		// 	while (line_len >= BUFFER_SIZE) {
		// 		line_len -= read(fd, buffer, BUFFER_SIZE);
		// 		write(1, buffer, BUFFER_SIZE);
		// 	}
		// 	mod = line_len % BUFFER_SIZE;
		// 	line_len -= read(fd, buffer, mod);
		// 	buffer[mod] = '\0';
		// 	write(1, buffer, mod);
		// 	write(1, "\n", 1);
		// }
		lseek_ret = lseek(fd, -prev_nl_pos, SEEK_CUR);
	}
}

int		min(int x, int y) {
	if (x <= y) {
		return (x);
	}
	else {
		return (y);
	}
}