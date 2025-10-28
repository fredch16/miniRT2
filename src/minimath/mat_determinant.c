/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_determinant.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 01:36:26 by swied             #+#    #+#             */
/*   Updated: 2025/10/28 02:49:45 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

/*
Laplacescher Entwicklungssatz:
Um die Determinante einer 4×4-Matrix zu berechnen, geht man durch jedes Element der ersten Zeile.
Für jedes Element wird eine 3×3-Submatrix gebildet, indem die Zeile und die Spalte dieses Elements
weggelassen werden. Aus dieser Submatrix wird die 3×3-Determinante berechnet, die als Kofaktor dient.
Dieser Kofaktor wird mit dem entsprechenden Element der ersten Zeile multipliziert,
unter Berücksichtigung des wechselnden Vorzeichens, und alle Ergebnisse werden aufsummiert.
Das Endergebnis ist die Determinante der gesamten 4×4-Matrix.
*/

// Hilfsfunktion: Holt ein Element aus der Matrix (row, col)
inline double	mat_get(const t_mat m, int row, int col)
{
	if (row == 0)
		return (m.c[col].x);
	else if (row == 1)
		return (m.c[col].y);
	else if (row == 2)
		return (m.c[col].z);
	else
		return (m.c[col].w);
}

// Berechnet die 3x3 Determinante direkt für eine Submatrix
double	det_3x3_sub(const t_mat m, int skip_row, int skip_col)
{
	double	vals[9];
	int		i;
	int		j;
	int		idx;

	idx = 0;
	i = -1;
	while (++i < 4)
	{
		if (i == skip_row)
			continue ;
		j = -1;
		while (++j < 4)
		{
			if (j == skip_col)
				continue ;
			vals[idx++] = mat_get(m, i, j);
		}
	}
	return (vals[0] * (vals[4] * vals[8] - vals[5] * vals[7])
			- vals[1] * (vals[3] * vals[8] - vals[5] * vals[6])
			+ vals[2] * (vals[3] * vals[7] - vals[4] * vals[6]));
}

// Berechnet die Determinante einer 4x4 Matrix
double	mat_determinant(const t_mat m)
{
	double	det;
	int		col;
	double	cofactor;

	det = 0;
	col = 0;
	while (col < 4)
	{
		cofactor = det_3x3_sub(m, 0, col);
		if (col % 2 == 1)
			cofactor = -cofactor;
		det += mat_get(m, 0, col) * cofactor;
		col++;
	}
	return (det);
}
