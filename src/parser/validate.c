/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 15:36:31 by fredchar          #+#    #+#             */
/*   Updated: 2025/12/21 20:20:10 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

int	verify_content(t_parse_node *n)
{
	if (full_empty(n->content) == 0)
		return (0);
	if (ft_strncmp(n->content, "A ", 2) == 0)
		return (verify_ambient(n));
	if (ft_strncmp(n->content, "C ", 2) == 0)
		return (verify_camera(n));
	if (ft_strncmp(n->content, "L ", 2) == 0)
		return (verify_light(n));
	if (ft_strncmp(n->content, "sp ", 3) == 0)
		return (verify_sphere(n));
	if (ft_strncmp(n->content, "pl ", 3) == 0)
		return (verify_plane(n));
	if (ft_strncmp(n->content, "cy ", 3) == 0)
		return (verify_cylinder(n));
	return (-1);
}

int	verify_pn_list(t_parse_node *pnlist)
{
	t_parse_node	*tmp;

	tmp = pnlist;
	while (tmp)
	{
		if (verify_content(tmp) == -1)
			return (-1);
		tmp = tmp->next;
	}
	return (0);
}
