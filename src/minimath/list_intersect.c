/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_intersect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 16:37:56 by swied             #+#    #+#             */
/*   Updated: 2025/11/02 16:40:57 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

static void	x_insert_sorted(t_xsn **sorted, t_xsn *node)
{
	t_xsn	*tmp;

	if (!*sorted || node->t < (*sorted)->t)
	{
		node->next = *sorted;
		*sorted = node;
	}
	else
	{
		tmp = *sorted;
		while (tmp->next && tmp->next->t < node->t)
			tmp = tmp->next;
		node->next = tmp->next;
		tmp->next = node;
	}
}

t_xsn	*x_sort(t_xsn *xs)
{
	t_xsn	*sorted;
	t_xsn	*current;
	t_xsn	*next;

    sorted = NULL;
    current = xs;
	if (!xs || !xs->next)
		return (xs);
	while (current)
	{
		next = current->next;
		x_insert_sorted(&sorted, current);
		current = next;
	}
	return (sorted);
}
