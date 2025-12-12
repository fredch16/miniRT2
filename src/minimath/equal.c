/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 13:52:10 by fredchar          #+#    #+#             */
/*   Updated: 2025/12/12 15:09:01 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

inline bool	equal(const double a, const double b)
{
	if (fabs(a - b) < EPSILON)
		return (true);
	else
		return (false);
}

// bool equal_tuple(t_vec a, t_vec b)
// {
// 	if (!equal(a.x, b.x))
// 		return (false);
// 	if (!equal(a.y, b.y))
// 		return (false);
// 	if (!equal(a.z, b.z))
// 		return (false);
// 	if (!equal(a.w, b.w))
// 		return (false);
// 	return (true);
// }

inline bool	equal_tuple(const t_vec a, const t_vec b)
{
	return (equal(a.x, b.x)
		&& equal(a.y, b.y)
		&& equal(a.z, b.z)
		&& equal(a.w, b.w));
}

inline bool	equal_matrix(const t_mat a, const t_mat b)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!(equal_tuple(a.c[i], b.c[i])))
			return (false);
		i++;
	}
	return (true);
}
