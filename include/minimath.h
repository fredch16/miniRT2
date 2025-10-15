/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimath.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:09:38 by fredchar          #+#    #+#             */
/*   Updated: 2025/10/15 18:12:30 by fredchar         ###   ########.fr       */
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

// printer.c

void	print_matrix4(t_matrix4 mat);
void	print_tuple4(t_tuple tup);

// equal.c

bool	equal(double a, double b);
bool	equal_tuple(t_tuple a, t_tuple b);
bool	equal_matrix(t_matrix4 a, t_matrix4 b);

// tuple_ops1.c

t_tuple	tuple_sub(const t_tuple a, const t_tuple b);
t_tuple	tuple_add(const t_tuple a, const t_tuple b);
t_tuple	tuple_neg(const t_tuple a);
t_tuple	tuple_scm(const double k, const t_tuple a);
t_tuple	tuple_scd(const t_tuple a, const double k);

// tuple_ops2.c

double	tuple_mag(const t_tuple a);
t_tuple	tuple_norm(const t_tuple a);
double	tuple_dot(const t_tuple a, const t_tuple b);
t_tuple	tuple_cro(const t_tuple a, const t_tuple b);

// create_tuples.c

t_tuple	point(double x, double y, double z);
t_tuple	vector(double x, double y, double z);



#endif
