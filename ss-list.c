#include "shell.h"

/**
 * add_node_to_start - adds a node to the start of the list
 * @head: address of pointer to head node
 * @string: string field of node
 * @number: node index used by history
 *
 * Return: size of list
 */
list_t *add_node_to_start(list_t **head, const char *string, int number)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	memory_set((void *)new_head, 0, sizeof(list_t));
	new_head->number = number;
	if (string)
	{
		new_head->string = string_duplicate(string);
		if (!new_head->string)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_node_to_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @string: string field of node
 * @number: node index used by history
 *
 * Return: size of list
 */
list_t *add_node_to_end(list_t **head, const char *string, int number)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	memory_set((void *)new_node, 0, sizeof(list_t));
	new_node->number = number;
	if (string)
	{
		new_node->string = string_duplicate(string);
		if (!new_node->string)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * write_linked_list_stringing - prints only the string element of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t write_linked_list_stringing(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		put_string(h->string ? h->string : "(nil)");
		put_string("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * remove_current_node - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int remove_current_node(list_t **head, unsigned int index)
{
	list_t *node, *previous_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->string);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			previous_node->next = node->next;
			free(node->string);
			free(node);
			return (1);
		}
		i++;
		previous_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_current_list - frees all nodes of a list
 * @head_pointer: address of pointer to head node
 *
 * Return: void
 */
void free_current_list(list_t **head_pointer)
{
	list_t *node, *next_node, *head;

	if (!head_pointer || !*head_pointer)
		return;
	head = *head_pointer;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->string);
		free(node);
		node = next_node;
	}
	*head_pointer = NULL;
}
