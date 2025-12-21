/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 17:39:14 by fredchar          #+#    #+#             */
/*   Updated: 2025/12/21 16:28:27 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

/*
Transforming Normals:

1. Inverse the matrix
2. Transpose the inversed matrix
3. Multiply with the object normal
4. Set w to 0 to reset translation effect
5. return the normalized world normal
*/

t_vec	normal_at_sp(t_obj *o, t_vec world_point)
{
	t_mat	inverse;
	t_mat	transpose_inverse;
	t_vec	object_point;
	t_vec	object_normal;
	t_vec	world_normal;

	inverse = mat_inverse(o->transform);
	object_point = mat_mul_vec(inverse, world_point);
	object_normal = tuple_sub(object_point, point(0, 0, 0));
	transpose_inverse = mat_transpose(inverse);
	world_normal = mat_mul_vec(transpose_inverse, object_normal);
	world_normal.w = 0;
	return (tuple_norm(world_normal));
}

t_vec	normal_at_pl(t_obj *o, t_vec world_point)
{
	t_mat	transpose_inverse;
	t_vec	object_normal;
	t_vec	world_normal;

	(void)world_point;
	object_normal = vector(0, 1, 0);
	transpose_inverse = mat_transpose(mat_inverse(o->transform));
	world_normal = mat_mul_vec(transpose_inverse, object_normal);
	world_normal.w = 0;
	return (tuple_norm(world_normal));
}

t_vec	normal_at_cy(t_obj *o, t_vec world_point)
{
	t_mat	inverse;
	t_vec	object_point;
	t_vec	object_normal;
	t_vec	world_normal;
	double	dist;

	inverse = mat_inverse(o->transform);
	object_point = mat_mul_vec(inverse, world_point);
	dist = object_point.x * object_point.x + object_point.z * object_point.z;
	if (dist < 1.0 && fabs(object_point.y - o->max_y) < EPSILON)
		object_normal = vector(0, 1, 0);
	else if (dist < 1.0 && fabs(object_point.y - o->min_y) < EPSILON)
		object_normal = vector(0, -1, 0);
	else
		object_normal = vector(object_point.x, 0, object_point.z);
	world_normal = mat_mul_vec(mat_transpose(inverse), object_normal);
	world_normal.w = 0;
	return (tuple_norm(world_normal));
}

inline t_vec	reflect(t_vec in, t_vec normal)
{
	t_vec	new_normal;

	new_normal = tuple_scm(2 * tuple_dot(in, normal), normal);
	return (tuple_sub(in, new_normal));
}
