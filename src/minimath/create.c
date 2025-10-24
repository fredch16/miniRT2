/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 14:54:23 by fredchar          #+#    #+#             */
/*   Updated: 2025/10/24 16:56:27 by fredchar         ###   ########.fr       */
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

inline t_vec	tuple(double x, double y, double z, double w)
{
	return ((t_vec){x, y, z, w});
}

inline t_mat	mat(const t_vec col0, const t_vec col1, const t_vec col2, const t_vec col3)
{
	return((t_mat){col0, col1, col2, col3});
}

inline t_mat	mat_idt()
{
	return((t_mat){vector(1, 0, 0), vector(0, 1, 0), vector(0, 0, 1), point(0, 0, 0)});
}