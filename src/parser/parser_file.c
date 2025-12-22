/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 15:21:31 by swied             #+#    #+#             */
/*   Updated: 2025/12/22 15:28:15 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"
#include "../../include/parser.h"
#include <fcntl.h>

static int	read_file_lines(int fd, t_parse_node **head)
{
	char	*ln;

	ln = get_next_line(fd);
	while (ln != NULL)
	{
		if (process_line(&ln, head) < 0)
		{
			cleanup_pn_list(*head, ln, fd);
			return (-1);
		}
		ln = get_next_line(fd);
	}
	return (0);
}

t_parse_node	*pn_from_file(const char *filepath)
{
	int				fd;
	t_parse_node	*head;

	head = NULL;
	if (check_file_extension(filepath) < 0)
		return (NULL);
	fd = open(filepath, O_RDONLY);
	if (fd < 0)
	{
		printf("Error: Failed to read input file\n");
		return (NULL);
	}
	if (read_file_lines(fd, &head) < 0)
		return (NULL);
	close(fd);
	return (head);
}
