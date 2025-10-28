/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_inverse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 02:00:00 by swied             #+#    #+#             */
/*   Updated: 2025/10/28 02:53:49 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

/*
Matrix-Invertierung:
Für jedes Element (i,j) der inversen Matrix:
1. Berechne den Cofactor von (i,j) in der Original-Matrix
2. Transponiere (tausche i und j)
3. Dividiere durch die Determinante
*/

// Setzt ein Element in der Matrix (row, col)
static inline void	mat_set(t_mat *m, int row, int col, double value)
{
	if (row == 0)
		m->c[col].x = value;
	else if (row == 1)
		m->c[col].y = value;
	else if (row == 2)
		m->c[col].z = value;
	else
		m->c[col].w = value;
}

// Berechnet den Cofactor von Element (row, col)
static double	mat_cofactor(const t_mat m, int row, int col)
{
	double	minor;

	minor = det_3x3_sub(m, row, col);
	if ((row + col) % 2 == 1)
		return (-minor);
	return (minor);
}

// Prüft ob eine Matrix invertierbar ist (Determinante ≠ 0)
bool	mat_is_invertible(const t_mat m)
{
	return (!equal(mat_determinant(m), 0.0));
}

// Berechnet die inverse Matrix
t_mat	mat_inverse(const t_mat m)
{
	t_mat	result;
	double	det;
	int		row;
	int		col;
	double	cofactor;

	det = mat_determinant(m);
	if (equal(det, 0.0))
		return (mat_idt());
	row = 0;
	while (row < 4)
	{
		col = 0;
		while (col < 4)
		{
			cofactor = mat_cofactor(m, row, col);
			mat_set(&result, col, row, cofactor / det);
			col++;
		}
		row++;
	}
	return (result);
}
