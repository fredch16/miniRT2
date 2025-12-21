/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_objs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 18:29:46 by fredchar          #+#    #+#             */
/*   Updated: 2025/12/21 17:27:42 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

t_material	material_default_sp(void)
{
	return ((t_material){0.1, 0.7, 0.3, 200, {0, 0, 0}});
}

t_material	material_default_pl(void)
{
	return ((t_material){0.1, 0.7, 0.3, 20, {0, 0, 0}});
}

t_mat	rotation_from_axis_angle(t_vec axis, double angle)
{
	t_mat	r;
	double	c;
	double	s;
	double	t;

	c = cos(angle);
	s = sin(angle);
	t = 1.0 - c;
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

t_mat	get_plane_transform(t_vec centre, t_vec normal)
{
	t_vec	up_default;
	t_vec	axis;
	double	angle;

	up_default = vector(0, 1, 0);
	if (equal_tuple(normal, up_default))
		return (translation(centre.x, centre.y, centre.z));
	if (equal_tuple(normal, tuple_scm(-1, up_default)))
		return (mat_mul_mat(translation(centre.x, centre.y, centre.z),
				rotation_x(M_PI)));
	axis = tuple_norm(tuple_cro(up_default, normal));
	angle = acos(tuple_dot(normal, up_default));
	return (mat_mul_mat(translation(centre.x, centre.y, centre.z),
			rotation_from_axis_angle(axis, angle)));
}

int	parse_sphere_color(t_obj *sp, char *p)
{
	sp->material.colour = atocol(p);
	if (verify_colours(sp->material.colour) < 0)
		return (-1);
	return (0);
}
