/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pnlist_to_world.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:17:45 by fredchar          #+#    #+#             */
/*   Updated: 2025/11/16 17:16:30 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"


int	construct_world(t_world *w, t_parse_node *n)
{
	printf("1\n");
	if (full_empty(n->content) == 0)
		return (0);
	else if (ft_strncmp(n->content, "# ", 2) == 0)
		return (0);
	else if (ft_strncmp(n->content, "A ", 2) == 0)
		return (parse_ambient(w, n));
	else if (ft_strncmp(n->content, "C ", 2) == 0)
		return (parse_camera(w, n));
	else if (ft_strncmp(n->content, "L ", 2) == 0)
		return (parse_light(w, n));
	else if (ft_strncmp(n->content, "sp ", 3) == 0)
		return (parse_sphere(w, n));
	else if (ft_strncmp(n->content, "pl ", 3) == 0)
		return (parse_plane(w, n));
	else if (ft_strncmp(n->content, "cy ", 3) == 0)
		return (parse_cylinder(w, n));
	printf("2\n");
	return (-1); // unknown ID
}