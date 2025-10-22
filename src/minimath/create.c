/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 14:54:23 by fredchar          #+#    #+#             */
/*   Updated: 2025/10/22 17:35:03 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

inline t_vec	point(double x, double y, double z)
{
	return ((t_vec){x, y, z, 1});
}

inline t_vec	vector(double x, double y, double z)
{
	return ((t_vec){x, y, z, 0});
}

// inline t_mat	mat(const t_vec row0, const t_vec row1, const t_vec row2, const t_vec row3)
// {
// 	return((t_mat){
// 		.c[0] = row0;
// 		.c[1] = row0;
// 		.c[2] = row0;
// 		.c[3] = row0;
// 	})
// }