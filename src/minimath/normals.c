/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 17:39:14 by fredchar          #+#    #+#             */
/*   Updated: 2025/11/01 20:36:22 by swied            ###   ########.fr       */
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

inline t_vec	reflect(t_vec in, t_vec normal)
{
	t_vec	new_normal;

	new_normal = tuple_scm(2 * tuple_dot(in, normal), normal);
	return (tuple_sub(in, new_normal));
}
