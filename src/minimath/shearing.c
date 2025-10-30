/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shearing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 23:58:27 by swied             #+#    #+#             */
/*   Updated: 2025/10/30 23:58:29 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

/*
Shearing:
Verschiebt jede Koordinate proportional zu den anderen Koordinaten.

Beispiel: shearing(1, 0, 0, 0, 0, 0)
  Punkt (2, 3, 4) wird zu (2+3, 3, 4) = (5, 3, 4)
  x verschiebt sich um den y-Wert
*/

t_mat	shearing(double xy, double xz, double yx, double yz, double zx, double zy)
{
	t_mat	result;

	result = mat_idt();
	result.c[1].x = xy;
	result.c[2].x = xz;
	result.c[0].y = yx;
	result.c[2].y = yz;
	result.c[0].z = zx;
	result.c[1].z = zy;
	return (result);
}
