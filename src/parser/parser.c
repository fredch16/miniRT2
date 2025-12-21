/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 12:28:33 by fredchar          #+#    #+#             */
/*   Updated: 2025/12/21 20:35:28 by fredchar         ###   ########.fr       */
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
static void	cleanup_pn_list(t_parse_node *head, char *ln, int fd)
{
	t_parse_node	*tmp;

	free(ln);
	while (head)
	{
		tmp = head->next;
		free(head->content);
		free(head);
		head = tmp;
	}
	close(fd);
}

static int	process_line(char **ln, t_parse_node **head)
{
	t_parse_node	*node;
	size_t			len;

	len = ft_strlen(*ln);
	if (len > 0 && (*ln)[len - 1] == '\n')
		(*ln)[len - 1] = '\0';
	node = pn_new(*ln);
	if (!node)
		return (-1);
	pn_add_back(head, node);
	return (0);
}

t_parse_node	*pn_from_file(const char *filepath)
{
	int				fd;
	char			*ln;
	t_parse_node	*head;

	head = NULL;
	if (!filepath)
		return (NULL);
	fd = open(filepath, O_RDONLY);
	if (fd < 0)
		return (NULL);
	ln = get_next_line(fd);
	while (ln != NULL)
	{
		if (process_line(&ln, &head) < 0)
		{
			cleanup_pn_list(head, ln, fd);
			return (NULL);
		}
		ln = get_next_line(fd);
	}
	close(fd);
	return (head);
}

void	pn_print(t_parse_node *head)
{
	size_t			i;
	t_parse_node	*cur;
	char			*content;

	i = 0;
	cur = head;
	if (!cur)
	{
		printf("[pn_print] list is empty\n");
		return ;
	}
	while (cur)
	{
		if (cur->content)
			content = cur->content;
		else
			content = "(null)";
		printf("[%zu] %s\n", i++, content);
		cur = cur->next;
	}
}
