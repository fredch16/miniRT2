/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 15:21:22 by swied             #+#    #+#             */
/*   Updated: 2025/12/22 15:21:23 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"
#include "../../include/parser.h"
#include <stdio.h>

void	cleanup_pn_list(t_parse_node *head, char *ln, int fd)
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

int	process_line(char **ln, t_parse_node **head)
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

int	check_file_extension(const char *filepath)
{
	size_t	len;

	if (!filepath)
		return (-1);
	len = ft_strlen(filepath);
	if (len < 3 || ft_strcmp(filepath + len - 3, ".rt") != 0)
	{
		printf("Error: File must have .rt extension\n");
		return (-1);
	}
	return (0);
}

static void	print_node(t_parse_node *cur, size_t i)
{
	char	*content;

	if (cur->content)
		content = cur->content;
	else
		content = "(null)";
	printf("[%zu] %s\n", i, content);
}

void	pn_print(t_parse_node *head)
{
	size_t			i;
	t_parse_node	*cur;

	i = 0;
	cur = head;
	if (!cur)
	{
		printf("[pn_print] list is empty\n");
		return ;
	}
	while (cur)
	{
		print_node(cur, i++);
		cur = cur->next;
	}
}
