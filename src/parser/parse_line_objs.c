/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_objs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 18:29:46 by fredchar          #+#    #+#             */
/*   Updated: 2025/11/08 00:09:46 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

inline	t_material	material_default_sp()
{
	return ((t_material){0.1, 0.7, 0.3, 200, {0, 0, 0}});
}

int	parse_sphere(t_world *w, t_parse_node *n)
{
	printf("parsing sphere\n");
	char		*p;
	t_obj		*sp;
	t_vec		centre;
	double		radius;

	if (!w || !n || !n->content)
		return (-1);
	sp = obj_create(OT_SPHERE);
	sp->material = material_default_sp();
	p = n->content + 3;
	centre = ato3dcrds(p);
	p = skip_spaces(p);
	p = move_to_space(p);
	p = skip_spaces(p);
	radius = ft_atod(p) * 0.5; // remember because this is radius x2
	printf("Incoming is the sphere coords and also here is the radius |%10.5f|\n", radius);
	print_vec4(centre);
	sp->transform = mat_mul_mat( \
		translation(centre.x, centre.y, centre.z), \
		scaling(radius, radius, radius));
	p = move_to_space(p);
	sp->material.colour = atocol(p);
	obj_add_back(&w->obj_list, sp);
	return (0);
}