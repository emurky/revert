#include "revert.h"

int		main(int argc, char **argv)
{
	FILE	*file;
	size_t	linecapp;
	t_list	*head = NULL;
	t_list	*list = NULL;
	char	*buffer = NULL;

	file = arguments_handling(argc, argv[1]);
	if (!file) {
		return (1);
	}

	if (getline(&buffer, &linecapp, file)) {
		list = malloc(sizeof(t_list));
		head = list;
		list->line = strdup(buffer);
		list->next = NULL;
		list->previous = NULL;
	}

	while (getline(&buffer, &linecapp, file) > 0) {
		new_list_node(&list, buffer);
	}
	getline(&buffer, &linecapp, file);
	new_list_node(&list, buffer);

	while (list->previous) {
		printf("%s", list->line);
		list = list->previous;
	}
	printf("%s", list->line);

	clear_list(head);
	free(buffer);
	fclose(file);
	return (0);
}

FILE	*arguments_handling(int argc, char *file_path)
{
	FILE	*file;

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

void	new_list_node(t_list **list, char *buffer)
{
	t_list	*previous_node;

	previous_node = *list;
	(*list)->next = malloc(sizeof(t_list));
	(*list) = (*list)->next;
	(*list)->line = strdup(buffer);
	(*list)->next = NULL;
	(*list)->previous = previous_node;
}

void	clear_list(t_list *list)
{
	t_list	*clear;

	while (list->next) {
		clear = list;
		free(list->line);
		list = list->next;
		free(clear);
	}
	free(list);
	free(list->line);
}
