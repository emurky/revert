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

void	buffer_handler(char *buffer)
{
	ssize_t		linelen = 0;
	char		*nl_pointer = NULL;
	char		remainder[BUFFER_SIZE + 1];
bzero(remainder, '\0');
	nl_pointer = strrchr(buffer, '\n');
	*nl_pointer = '\0';
	while (nl_pointer) {
		nl_pointer = strrchr(buffer, '\n');
		// *nl_pointer = '\0';
		nl_pointer++;
		linelen = strlen(nl_pointer) + 1;
		write(1, nl_pointer, linelen);
		nl_pointer =  buffer + BUFFER_SIZE - (linelen + 1);
		*nl_pointer = '\0';
		strcpy(remainder, buffer);
	}

}

void	print_reverted_lines(int fd)
{
	ssize_t		linelen = 0;
	off_t 		file_pos = 0;
	off_t		prev_file_pos = 0;
	int			bytes_read = 0;

	// char		c = -1;
	char		buffer[BUFFER_SIZE + 1];
	char		*nl_pointer = NULL;
	// off_t		lseek_check;

size_t	bufflen = 0;
size_t	tmp_bufflen = 0;

int end = false;
size_t		buffer_size;
buffer_size = BUFFER_SIZE;
	file_pos = lseek(fd, -(0 + BUFFER_SIZE), SEEK_END);
	while (true) {
		// if (end) {
		// 	bytes_read = read(fd, buffer, prev_file_pos + 1);
		// 	buffer[prev_file_pos + 1] = '\0';
		// }
		// else {
			bytes_read = read(fd, buffer, BUFFER_SIZE);
			buffer[BUFFER_SIZE] = '\0';
		// }
		nl_pointer = strrchr(buffer, '\n');
		while (nl_pointer) {
			
			if (bufflen > BUFFER_SIZE) {
				tmp_bufflen = bufflen;
				linelen = strlen(nl_pointer);
				write(1, nl_pointer, linelen);
				// read(fd, buffer, linelen);
				while ((bufflen / BUFFER_SIZE) > 0) {
					read(fd, buffer, BUFFER_SIZE);
					write(1, buffer, BUFFER_SIZE);
					bufflen -= BUFFER_SIZE;
				}
				read(fd, buffer, bufflen);
				write(1, buffer, bufflen);
				// write(1, "\n", 1);
				bufflen = 0;
				file_pos = lseek(fd, -(tmp_bufflen + BUFFER_SIZE), SEEK_CUR);
				bytes_read = read(fd, buffer, BUFFER_SIZE);
				nl_pointer = strrchr(buffer, '\n');
				*nl_pointer = '\0';
				// bytes_read = read(fd, buffer, BUFFER_SIZE);
			}
			else {
				linelen = strlen(nl_pointer);
				write(1, nl_pointer, linelen);
				*nl_pointer = '\0';
				// write(1, nl_pointer, linelen);
			}
			nl_pointer = strrchr(buffer, '\n');
		}
		if (!bufflen && !nl_pointer) {
			bufflen = strlen(buffer);
			// file_pos = lseek(fd, -(0 + BUFFER_SIZE), SEEK_CUR);
		}
		else if (bufflen) {
			bufflen += BUFFER_SIZE;
			// file_pos = lseek(fd, -(0 + BUFFER_SIZE), SEEK_CUR);
		}
		prev_file_pos = file_pos;
		if (end) {
			write(1, "\n", 1);
			nl_pointer = strchr(buffer, '\n');
			while (!nl_pointer) {
				write(1, buffer, strlen(buffer));
				read(fd, buffer, strlen(buffer));
				nl_pointer = strchr(buffer, '\n');
			}
			write(1, buffer, nl_pointer - buffer);
			write(1, "\n", 1);
			break ;
		}
		file_pos = lseek(fd, -(2 * BUFFER_SIZE), SEEK_CUR);
		if (file_pos == -1) {
			file_pos = lseek(fd, 0, SEEK_SET);
			end = true;
		}
	}
	
	// file_pos = lseek(fd, 0, SEEK_SET);

	// bytes_read = read(fd, buffer, prev_file_pos + 1);
	// buffer[prev_file_pos + 1] = '\0';
	// nl_pointer = strrchr(buffer, '\n');

	// while (nl_pointer) {
	// 	linelen = strlen(nl_pointer);
	// 	// *nl_pointer = '\0';
	// 	write(1, nl_pointer, linelen);
	// 	*nl_pointer = '\0';
	// 	nl_pointer = strrchr(buffer, '\n');
	// }


	// write(1, "\n", 1);
	// write(1, buffer, strlen(buffer));
	// write(1, "\n", 1);
	// return ;
}

size_t	printline(int fd)
{
	char		c = -1;
	size_t		linelen = 1;
	int			bytes_read;

	bytes_read = read(fd, &c, sizeof(char));
	if (c == EOF) {
		return (1);
	}
	while (c != '\n' && bytes_read) {
		write(1, &c, 1);
		bytes_read = read(fd, &c, sizeof(char));
		linelen++;
	}
	/* it is commented to be more alike tac */
	// if (!bytes_read) {
	// 	linelen--;
	// }
	write(1, "\n", 1);

	return (linelen);
}
