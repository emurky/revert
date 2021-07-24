#include "revert.h"

int		main(int argc, char **argv)
{
	FILE	*file = NULL;
	t_list	*list = NULL;

	file = check_arguments(argc, argv[1]);
	if (!file) {
		return (1);
	}

	list = create_list(file);
	while (list->previous) {
		printf("%s", list->line);
		list = list->previous;
	}
	printf("%s", list->line);

	clear_list(list);
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

t_list	*create_list(FILE *file)
{
	t_list	*list = NULL;
	t_list	*previous_node = NULL;
	char	*buffer = NULL;
	size_t	linecapp;

	if (getline(&buffer, &linecapp, file)) {
		list = new_list_node(buffer);
	}

	while (getline(&buffer, &linecapp, file) > 0) {
		previous_node = list;
		list->next = new_list_node(buffer);
		list = list->next;
		list->previous = previous_node;
	}
	previous_node = list;
	list->next = new_list_node(buffer);
	list = list->next;
	list->previous = previous_node;
	free(buffer);

	return (list);
}

t_list	*new_list_node(char *buffer)
{
	t_list	*new_node = NULL;

	new_node = (t_list *)malloc(sizeof(t_list));
	new_node->line = strdup(buffer);
	new_node->next = NULL;
	new_node->previous = NULL;

	return (new_node);
}

void	clear_list(t_list *list)
{
	t_list	*clear = NULL;

	while (list->next) {
		clear = list;
		free(list->line);
		list = list->next;
		free(clear);
	}
	free(list->line);
	free(list);
}
