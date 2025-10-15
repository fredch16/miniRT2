/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tuples.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 14:54:23 by fredchar          #+#    #+#             */
/*   Updated: 2025/10/15 15:57:36 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

inline t_tuple	point(double x, double y, double z)
{
	return ((t_tuple){x, y, z, 1});
}

inline t_tuple	vector(double x, double y, double z)
{
	return ((t_tuple){x, y, z, 0});
}
