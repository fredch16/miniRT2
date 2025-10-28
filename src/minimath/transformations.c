/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 15:41:08 by swied             #+#    #+#             */
/*   Updated: 2025/10/28 15:53:44 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

/*
Verschiebt einen Punkt um x, y, z.

- Vektoren werden nicht verschoben.
*/

t_mat	translation(double x, double y, double z)
{
	t_mat	result;

	result = mat_idt();
	result.c[3].x = x;
	result.c[3].y = y;
	result.c[3].z = z;
	return (result);
}

/*
Skaliert einen Punkt oder Vektor um die Faktoren x, y, z.

- Skaliert Punkte UND Vektoren
- Inverse Skalierung: scaling(1/x, 1/y, 1/z)
- Negative Werte = Spiegelung (Reflection)
*/

t_mat	scaling(double x, double y, double z)
{
	t_mat	result;

	result = mat_idt();
	result.c[0].x = x;
	result.c[1].y = y;
	result.c[2].z = z;
	return (result);
}
