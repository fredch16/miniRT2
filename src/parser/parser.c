/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 12:28:33 by fredchar          #+#    #+#             */
/*   Updated: 2025/12/22 15:21:45 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"
#include "../../include/parser.h"
#include <stdio.h>

int	parse_that_jawn(t_world *world, char *filename)
{
	t_parse_node	*pn;
	t_parse_node	*head;

	pn = pn_from_file(filename);
	if (!pn)
		return (-1);
	head = pn;
	if (DEBUG)
		pn_print(pn);
	while (pn && world->parser.error_flag == 0)
	{
		world->parser.error_flag = construct_world(world, pn);
		if (world->parser.error_flag < 0)
			return (printf("Error\n"), -1);
		pn = pn->next;
	}
	if (world->parser.a_count < 1)
		return (printf("Error: MiniRT needs an Ambient Element\n"), -1);
	if (world->parser.l_count < 1)
		return (printf("Error: MiniRT needs a Light Element\n"), -1);
	if (world->parser.c_count < 1)
		return (printf("Error: MiniRT needs a Camera Element\n"), -1);
	pn_clear(&head);
	return (0);
}
