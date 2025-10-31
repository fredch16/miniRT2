/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 01:18:15 by fredchar          #+#    #+#             */
/*   Updated: 2025/10/31 01:20:10 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

inline t_ray	ray_transform(t_ray r, t_mat m)
{
	t_ray	new;

	new.origin = mat_mul_vec(m, r.origin);
	new.origin.w = 1;
	new.direction = mat_mul_vec(m, r.direction);
	new.direction.w = 0;
	return (new);
}