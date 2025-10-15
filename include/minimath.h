/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimath.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:09:38 by fredchar          #+#    #+#             */
/*   Updated: 2025/10/15 14:07:20 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMATH_H
# define MINIMATH_H

# include "miniRT.h"
# include <stdbool.h>

// w value is in place to specify a vector or a point
// w = 0 indicates a vector
// w = 1 indicates a point
typedef struct s_tuple
{
	double	x;
	double	y;
	double	z;
	double	w;
}	t_tuple;

// each matrix will consist of 4 columns which will be represented
// using the previously defined vectors (tuples)
typedef struct s_matrix4
{
	t_tuple	c[4];
}	t_matrix4;

void	print_matrix4(t_matrix4 mat);

// equal.c

bool	equal(double a, double b);
bool	equal_tuple(t_tuple a, t_tuple b);
bool	equal_matrix(t_matrix4 a, t_matrix4 b);

#endif