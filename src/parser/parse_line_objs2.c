/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_objs2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 17:14:49 by fredchar          #+#    #+#             */
/*   Updated: 2025/12/21 23:53:16 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

int	parse_sphere(t_world *w, t_parse_node *n)
{
	char	*p;
	t_obj	*sp;
	t_vec	centre;
	double	radius;

	if (!w || !n || !n->content)
		return (-1);
	sp = obj_create(OT_SPHERE);
	sp->material = material_default_sp();
	p = n->content + 3;
	if (!allowed_chars(p))
		return (-1);
	centre = ato3dcrds(p);
	p = move_next(p);
	radius = ft_atod(p) * 0.5;
	if (radius < 0)
		return (parse_error(w, -1, ERR_SPHERE_DIAMETER));
	sp->transform = mat_mul_mat(
			translation(centre.x, centre.y, centre.z),
			scaling(radius, radius, radius));
	p = move_to_space(p);
	if (parse_sphere_color(sp, p) < 0)
		return (parse_error(w, -1, ERR_SPHERE_COLOUR));
	obj_add_back(&w->obj_list, sp);
	return (0);
}

static int	parse_plane_color(t_obj *pl, char *p)
{
	pl->material.colour = atocol(p);
	if (verify_colours(pl->material.colour) < 0)
		return (-1);
	return (0);
}

int	parse_plane(t_world *w, t_parse_node *n)
{
	char	*p;
	t_obj	*pl;
	t_vec	centre;
	t_vec	normal;

	if (!w || !n || !n->content)
		return (-1);
	pl = obj_create(OT_PLANE);
	pl->material = material_default_pl();
	p = n->content + 3;
	centre = ato3dcrds(p);
	p = move_next(p);
	normal = ato3dcrds(p);
	if (verify_3dnorm(normal) < 0)
		return (parse_error(w, -1, ERR_PLANE_ORIENT));
	p = move_to_space(p);
	pl->transform = get_plane_transform(centre, normal);
	if (parse_plane_color(pl, p) < 0)
		return (parse_error(w, -1, ERR_PLANE_COLOUR));
	obj_add_back(&w->obj_list, pl);
	return (0);
}
