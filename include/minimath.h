/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimath.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:09:38 by fredchar          #+#    #+#             */
/*   Updated: 2025/10/31 00:04:45 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMATH_H
# define MINIMATH_H

# include "miniRT.h"
# include "types.h"
# include <stdbool.h>

// printer.c

void	print_mat(t_mat mat);
void	print_vec4(t_vec tup);
void	print_xs(t_xsn *xs);

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
t_ray	ray(t_vec origin, t_vec direction);

// matmul.c

t_mat	mat_mul_mat(const t_mat a, const t_mat b);
t_vec	mat_mul_vec(const t_mat m, const t_vec v);
t_mat	mat_transpose(const t_mat a);

// mat_determinant.c

double	mat_get(const t_mat m, int row, int col);
double	det_3x3_sub(const t_mat m, int skip_row, int skip_col);
double	mat_determinant(const t_mat m);

// mat_inverse.c

bool	mat_is_invertible(const t_mat m);
t_mat	mat_inverse(const t_mat m);

// transformations.c

t_mat	translation(double x, double y, double z);
t_mat	scaling(double x, double y, double z);
t_mat	rotation_x(double r);
t_mat	rotation_y(double r);
t_mat	rotation_z(double r);

// intersections.c

t_vec	ray_pos(t_ray ray, double t_val);
t_xsn	*intersect_sp(t_ray ray, t_obj *o);
t_xsn	*x_hit(t_xsn *xs);

// lists.c

t_xsn	*x_new(t_obj *o, double t);
void	x_add_back(t_xsn **xlist, t_xsn *n);
t_obj	*obj_create(enum e_obj_type ot);
void	obj_add_back(t_obj **objlist, t_obj *n);

// shearing.c

t_mat	shearing(double xy, double xz, double yx, double yz, double zx, double zy);

#endif
