/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 15:41:08 by swied             #+#    #+#             */
/*   Updated: 2025/10/28 15:43:45 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

/* Verschiebt einen Punkt um x, y, z. Vektoren werden nicht veraendert */

t_mat	translation(double x, double y, double z)
{
	t_mat	result;

	result = mat_idt();
	result.c[3].x = x;
	result.c[3].y = y;
	result.c[3].z = z;
	return (result);
}
