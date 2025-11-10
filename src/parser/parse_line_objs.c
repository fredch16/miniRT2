/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_objs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 18:29:46 by fredchar          #+#    #+#             */
/*   Updated: 2025/11/10 01:34:05 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

inline	t_material	material_default_sp()
{
	return ((t_material){0.1, 0.7, 0.3, 200, {0, 0, 0}});
}

inline	t_material	material_default_pl()
{
	return ((t_material){0.1, 0.7, 0.3, 20, {0, 0, 0}});
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
	sp->transform = mat_mul_mat( \
		translation(centre.x, centre.y, centre.z), \
		scaling(radius, radius, radius));
	p = move_to_space(p);
	sp->material.colour = atocol(p);
	obj_add_back(&w->obj_list, sp);
	return (0);
}

t_mat	rotation_from_axis_angle(t_vec axis, double angle)
{
	t_mat	r;
	double	c = cos(angle);
	double	s = sin(angle);
	double	t = 1.0 - c;

	r = mat_idt();
	r.c[0].x = c + axis.x * axis.x * t;
	r.c[0].y = axis.x * axis.y * t - axis.z * s;
	r.c[0].z = axis.x * axis.z * t + axis.y * s;

	r.c[1].x = axis.y * axis.x * t + axis.z * s;
	r.c[1].y = c + axis.y * axis.y * t;
	r.c[1].z = axis.y * axis.z * t - axis.x * s;

	r.c[2].x = axis.z * axis.x * t - axis.y * s;
	r.c[2].y = axis.z * axis.y * t + axis.x * s;
	r.c[2].z = c + axis.z * axis.z * t;
	return (r);
}


int	parse_plane(t_world *w, t_parse_node *n)
{
	printf("Parsing plane\n");
	char		*p;
	t_obj		*pl;
	t_vec		centre;
	t_vec		normal;

	if (!w || !n || !n->content)
		return (-1);
	pl = obj_create(OT_PLANE);
	pl->material = material_default_pl();
	p = n->content + 3;
	centre = ato3dcrds(p);
	p = skip_spaces(p);
	p = move_to_space(p);
	p = skip_spaces(p);
	normal = ato3dcrds(p);
	if (verify_3dnorm(normal) < 0)
		return (w->parser.error_flag++, printf("Plane orientation vector not normalised\n"), -1);
	t_vec	up_default = {0, 1, 0, 0};

	// in the case of the input vector being equal to default
	if (equal_tuple(normal, up_default))
		pl->transform = translation(centre.x, centre.y, centre.z);
	else if (equal_tuple(normal, tuple_scm(-1, up_default))) // input is opposite
		pl->transform = mat_mul_mat(translation(centre.x, centre.y, centre.z), rotation_x(M_PI));
	else
	{
		t_vec	axis = tuple_norm(tuple_cro(up_default, normal));
		double	angle = acos(tuple_dot(normal, up_default));
		t_mat	rotate = rotation_from_axis_angle(axis, angle);
		t_mat	translate = translation(centre.x, centre.y, centre.z);
		pl->transform = mat_mul_mat(translate, rotate);
	}
	p = move_to_space(p);
	pl->material.colour = atocol(p);
	if (verify_colours(pl->material.colour) < 0)
		return (w->parser.error_flag++, printf("Plane Colour out of range 0 - 255\n"), -1);
	obj_add_back(&w->obj_list, pl);
	return (0);
}
