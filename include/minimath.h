/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimath.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:09:38 by fredchar          #+#    #+#             */
/*   Updated: 2025/10/24 17:03:02 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMATH_H
# define MINIMATH_H

# include "miniRT.h"
# include <stdbool.h>

// w value is in place to specify a vector or a point
// w = 0 indicates a vector
// w = 1 indicates a point
typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
	double	w;
}	t_vec;

// each matrix will consist of 4 columns which will be represented
// using the previously defined vectors (tuples)
typedef struct s_mat
{
	t_vec	c[4];
}	t_mat;

// printer.c

void	print_mat(t_mat mat);
void	print_vec4(t_vec tup);

// equal.c

bool	equal(double a, double b);
bool	equal_tuple(t_vec a, t_vec b);
bool	equal_matrix(t_mat a, t_mat b);

// tuple_ops1.c

t_vec	tuple_sub(const t_vec a, const t_vec b);
t_vec	tuple_add(const t_vec a, const t_vec b);
t_vec	tuple_neg(const t_vec a);
t_vec	tuple_scm(const double k, const t_vec a);
t_vec	tuple_scd(const t_vec a, const double k);

// tuple_ops2.c

double	tuple_mag(const t_vec a);
t_vec	tuple_norm(const t_vec a);
double	tuple_dot(const t_vec a, const t_vec b);
t_vec	tuple_cro(const t_vec a, const t_vec b);

// create.c

t_vec	point(double x, double y, double z);
t_vec	vector(double x, double y, double z);
t_vec	tuple(double x, double y, double z, double w);
t_mat	mat(const t_vec col0, const t_vec col1, const t_vec col2, const t_vec col3);
t_mat	mat_idt();

// matmul.c

t_mat	mat_mul_mat(const t_mat a, const t_mat b);
t_vec	mat_mul_vec(const t_mat m, const t_vec v);
t_mat	mat_transpose(const t_mat a);

#endif
