/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matmul.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:16:16 by fredchar          #+#    #+#             */
/*   Updated: 2025/10/22 17:32:19 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"


inline t_vec	mat_mul_vec(const t_mat m, const t_vec v)
{
	return (t_vec){
		m.c[0].x * v.x + m.c[1].x * v.y + m.c[2].x * v.z + m.c[3].x * v.w,
		m.c[0].y * v.x + m.c[1].y * v.y + m.c[2].y * v.z + m.c[3].y * v.w,
		m.c[0].z * v.x + m.c[1].z * v.y + m.c[2].z * v.z + m.c[3].z * v.w,
		m.c[0].w * v.x + m.c[1].w * v.y + m.c[2].w * v.z + m.c[3].w * v.w
	};
}

inline t_mat	mat_mul_mat(const t_mat a, const t_mat b)
{
	t_mat	res;

	res.c[0] = mat_mul_vec(a, b.c[0]);
	res.c[1] = mat_mul_vec(a, b.c[1]);
	res.c[2] = mat_mul_vec(a, b.c[2]);
	res.c[3] = mat_mul_vec(a, b.c[3]);
	return (res);
}
