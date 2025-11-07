/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pnlist_to_world.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:17:45 by fredchar          #+#    #+#             */
/*   Updated: 2025/11/07 16:50:49 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

int	parse_ambient(t_world *w, t_parse_node *n)
{
	printf("parsing ambient\n");
	char		*p;
	double		intensity;

	if (!w || !n || !n->content)
		return (-1);
	p = n->content + 1;
	intensity = ft_atod(p);
	p = skip_spaces(p);
	p = move_to_space(p);
	p = skip_spaces(p);
	w->ambient = atocol(p);
	w->ambient = colour_scm(intensity, w->ambient);
	return (0);
}



int	construct_world(t_world *w, t_parse_node *n)
{
	if (full_empty(n->content) == 0)
		return (0);
	if (ft_strncmp(n->content, "A ", 2) == 0)
		return (parse_ambient(w, n));
	// if (ft_strncmp(n->content, "C ", 2) == 0)
	// 	return (parse_camera(w, n));
	// if (ft_strncmp(n->content, "L ", 2) == 0)
	// 	return (parse_light(w, n));
	// if (ft_strncmp(n->content, "sp ", 3) == 0)
	// 	return (parse_sphere(w, n));
	// if (ft_strncmp(n->content, "pl ", 3) == 0)
	// 	return (parse_plane(w, n));
	// if (ft_strncmp(n->content, "cy ", 3) == 0)
	// 	return (parse_cylinder(w, n));
	return (-1); // unknown ID
}