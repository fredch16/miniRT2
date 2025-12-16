/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 19:05:21 by fredchar          #+#    #+#             */
/*   Updated: 2025/12/16 19:05:55 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

inline t_ray	ray(t_vec origin, t_vec direction)
{
	return ((t_ray){origin, direction});
}
