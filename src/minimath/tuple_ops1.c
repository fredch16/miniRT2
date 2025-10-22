/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_ops1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:20:02 by fredchar          #+#    #+#             */
/*   Updated: 2025/10/22 16:00:59 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

// THE SAME CODE
// inline t_vec	tuple_sub(t_vec *a, t_vec *b)
// {
// 	t_vec	c;

// 	c.x = a.x - b.x;
// 	c.y = a.y - b.y;
// 	c.z = a.z - b.z;
// 	c.w = a.w - b.w;
// 	return (c);
// }

inline t_vec	tuple_sub(const t_vec a, const t_vec b)
{
	return ((t_vec){a.x - b.x, a.y - b.y,	a.z - b.z, a.w - b.w});
}

inline t_vec	tuple_add(const t_vec a, const t_vec b)
{
	return ((t_vec){a.x + b.x, a.y + b.y,	a.z + b.z, a.w + b.w});
}

inline t_vec	tuple_neg(const t_vec a)
{
	return ((t_vec){-a.x, -a.y, -a.z, -a.w});
}

inline t_vec	tuple_scm(const double k, const t_vec a)
{
	return ((t_vec){k * a.x, k * a.y, k * a.z, k * a.w});
}

// USE SCM WHEN POSSIBLE SCD IS SLOWER
inline t_vec	tuple_scd(const t_vec a, const double k)
{
	return ((t_vec){a.x / k, a.y / k, a.z / k, a.w / k});
}
