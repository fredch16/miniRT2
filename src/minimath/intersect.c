/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 19:27:35 by fredchar          #+#    #+#             */
/*   Updated: 2025/10/30 15:36:17 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

// test this
t_vec	ray_pos(t_ray ray, double t_val)
{
	return (tuple_add(ray.origin, tuple_scm(t_val, ray.direction)));
}