/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 12:28:33 by fredchar          #+#    #+#             */
/*   Updated: 2025/11/05 13:03:09 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"
#include "../../include/parser.h"
#include <fcntl.h>
#include <stdio.h>


/*
 * Read the file at `filepath` line-by-line using get_next_line and build
 * a null-terminated linked list of `t_parse_node`. Each node takes ownership
 * of the malloc'd string returned by get_next_line (we strip the trailing
 * '\n' if present). On failure returns NULL and frees any partially-built
 * list.
 */
t_parse_node	*pn_from_file(const char *filepath)
{
	int fd;
	char *ln;
	t_parse_node *head = NULL;
	t_parse_node *node;

	if (!filepath)
		return (NULL);
	fd = open(filepath, O_RDONLY);
	if (fd < 0)
		return (NULL);
	while ((ln = get_next_line(fd)) != NULL)
	{
		size_t len = ft_strlen(ln);
		if (len > 0 && ln[len - 1] == '\n')
			ln[len - 1] = '\0';
		node = pn_new(ln);
		if (!node)
		{
			/* allocation failure: free partial list and the last line */
			free(ln);
			while (head)
			{
				t_parse_node *tmp = head->next;
				free(head->content);
				free(head);
				head = tmp;
			}
			close(fd);
			return (NULL);
		}
		pn_add_back(&head, node);
	}
	close(fd);
	return (head);
}

/* Debug helper: print each parse node's content with an index */
void	pn_print(t_parse_node *head)
{
	size_t i = 0;
	t_parse_node *cur = head;

	if (!cur)
	{
		printf("[pn_print] list is empty\n");
		return;
	}
	while (cur)
	{
		printf("[%zu] %s\n", i++, cur->content ? cur->content : "(null)");
		cur = cur->next;
	}
}

