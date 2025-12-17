/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 18:39:31 by fredchar          #+#    #+#             */
/*   Updated: 2025/12/17 18:39:43 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	pn_add_back(t_parse_node **pnlist, t_parse_node *n)
{
	t_parse_node	*tmp;

	if (!pnlist || !n)
		return ;
	if (!*pnlist)
		*pnlist = n;
	else
	{
		tmp = *pnlist;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = n;
	}
}

void	pn_clear(t_parse_node **pnlist)
{
	t_parse_node	*tmp;

	if (!pnlist || !*pnlist)
		return ;
	while (*pnlist)
	{
		tmp = (*pnlist)->next;
		free((*pnlist)->content);
		free(*pnlist);
		*pnlist = tmp;
	}
}

void	obj_clear(t_obj **objlist)
{
	t_obj	*tmp;

	if (!objlist || !*objlist)
		return ;
	while (*objlist)
	{
		tmp = (*objlist)->next;
		free(*objlist);
		*objlist = tmp;
	}
}

void	x_clear(t_xsn **xlist)
{
	t_xsn	*tmp;

	if (!xlist || !*xlist)
		return ;
	while (*xlist)
	{
		tmp = (*xlist)->next;
		free(*xlist);
		*xlist = tmp;
	}
}