/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 20:56:22 by fredchar          #+#    #+#             */
/*   Updated: 2025/12/16 17:57:16 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

t_xsn *x_new(t_obj *o, double t)
{
	t_xsn *new;

	new = ft_calloc(1, sizeof(t_xsn));
	if (!new)
		return (NULL);
	new->xs_obj = o;
	new->t = t;
	return (new);
}

void x_add_back(t_xsn **xlist, t_xsn *n)
{
	t_xsn *tmp;

	if (!xlist || !n)
		return;
	if (!*xlist)
		*xlist = n;
	else
	{
		tmp = *xlist;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = n;
	}
}

t_obj *obj_create(enum e_obj_type ot)
{
	t_obj *new;

	new = ft_calloc(1, sizeof(t_obj));
	if (!new)
		return (NULL);
	new->type = ot;
	new->transform = mat_idt();
	return (new);
}

void obj_add_back(t_obj **objlist, t_obj *n)
{
	t_obj *tmp;

	if (!objlist || !n)
		return;
	if (!*objlist)
		*objlist = n;
	else
	{
		tmp = *objlist;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = n;
	}
}

t_parse_node *pn_new(char *content)
{
	t_parse_node *new;

	new = ft_calloc(1, sizeof(t_parse_node));
	if (!new)
		return (NULL);
	new->content = content;
	return (new);
}

void pn_add_back(t_parse_node **pnlist, t_parse_node *n)
{
	t_parse_node *tmp;

	if (!pnlist || !n)
		return;
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
	t_parse_node *tmp;

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
	t_obj *tmp;

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
	t_xsn *tmp;

	if (!xlist || !*xlist)
		return ;
	while (*xlist)
	{
		tmp = (*xlist)->next;
		free(*xlist);
		*xlist = tmp;
	}
}