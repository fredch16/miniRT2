/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_objs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 18:29:46 by fredchar          #+#    #+#             */
/*   Updated: 2025/12/14 16:07:38 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

inline	t_material	material_default_sp()
{
	return ((t_material){0.1, 0.7, 0.3, 200, {0, 0, 0}});
}

int	parse_sphere(t_world *w, t_parse_node *n)
{
	printf("Parsing sphere\n");
	char		*p;
	t_obj		*sp;
	t_vec		centre;
	double		radius;

	if (!w || !n || !n->content)
		return (-1);
	sp = obj_create(OT_SPHERE);
	sp->material = material_default_sp();
	p = n->content + 3;
	if (!allowed_chars(p))
		return (-1);
	centre = ato3dcrds(p);
	p = skip_spaces(p);
	p = move_to_space(p);
	p = skip_spaces(p);
	radius = ft_atod(p) * 0.5; // remember because this is radius x2
	if (radius < 0)
		return (w->parser.error_flag++, printf("Sphere's radius can't be negative\n"), -1);
	sp->transform = mat_mul_mat( \
		translation(centre.x, centre.y, centre.z), \
		scaling(radius, radius, radius));
	p = move_to_space(p);
	sp->material.colour = atocol(p);
	if (verify_colours(sp->material.colour) < 0)
		return (w->parser.error_flag++, printf("Sphere Colour out of range 0 - 255\n"), -1);
	obj_add_back(&w->obj_list, sp);
	return (0);
}
