/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimath.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:09:38 by fredchar          #+#    #+#             */
/*   Updated: 2025/10/14 15:14:01 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMATH_H
# define MATH_H

#include "miniRT.h"

#endif

typedef struct s_tuple
{
	double	x;
	double	y;
	double	z;
	double	w;
}	t_tuple;

typedef struct s_matrix4
{
	// each matrix will consist of 4 columns which will be represented
	// using the previously defined vectors (tuples)
	t_tuple c[4];
}	t_matrix4;