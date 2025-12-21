/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_objs3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 17:35:34 by fredchar          #+#    #+#             */
/*   Updated: 2025/12/21 23:53:36 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

static int	parse_cylinder_color(t_obj *cy, char *p)
{
	cy->material.colour = atocol(p);
	if (verify_colours(cy->material.colour) < 0)
		return (-1);
	return (0);
}

static int	parse_cylinder_and_apply(t_obj *cy, t_vec centre, t_vec normal,
	char **p)
{
	double	radius;
	double	height;

	radius = ft_atod(*p) * 0.5;
	*p = move_to_space(*p);
	*p = skip_spaces(*p);
	height = ft_atod(*p);
	cy->transform = get_plane_transform(centre, normal);
	cy->transform = mat_mul_mat(cy->transform, scaling(radius, radius, radius));
	cy->min_y = 0.000001;
	cy->max_y = height - 0.000001;
	return (0);
}

int	parse_cylinder(t_world *w, t_parse_node *n)
{
	t_obj	*cy;
	t_vec	centre;
	t_vec	normal;
	char	*p;

	if (!w || !n || !n->content)
		return (-1);
	cy = obj_create(OT_CYLINDER);
	cy->material = material_default_pl();
	cy->closed = 1;
	p = n->content + 3;
	centre = ato3dcrds(p);
	p = move_next(p);
	normal = ato3dcrds(p);
	if (verify_3dnorm(normal) < 0)
		return (parse_error(w, -1, ERR_CYLINDER_ORIENT));
	p = move_skip(p);
	parse_cylinder_and_apply(cy, centre, normal, &p);
	p = move_skip(p);
	if (parse_cylinder_color(cy, p) < 0)
		return (parse_error(w, -1, ERR_CYLINDER_COLOUR));
	obj_add_back(&w->obj_list, cy);
	return (0);
}
