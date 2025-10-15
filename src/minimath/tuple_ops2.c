/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_ops2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 17:34:02 by fredchar          #+#    #+#             */
/*   Updated: 2025/10/15 17:55:10 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

inline double	tuple_mag(const t_tuple a)
{
	return ((double){sqrt((a.x * a.x) + (a.y * a.y)
			+ (a.z * a.z) + (a.w * a.w))});
}

inline t_tuple	tuple_norm(const t_tuple a)
{
	double mag;
	double inv;
	
	mag = tuple_mag(a); 
	inv = 1.0 / mag;
	return ((t_tuple){a.x * inv, a.y * inv, a.z * inv, a.w * inv});
}