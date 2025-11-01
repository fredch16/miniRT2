/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:27:52 by fredchar          #+#    #+#             */
/*   Updated: 2025/11/01 21:40:37 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include "miniRT.h"
# include "minimath.h" // remove when fixing types



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

typedef struct s_ray
{
	t_vec	origin;
	t_vec	direction;
}	t_ray;

enum e_obj_type
{
	OT_SPHERE,
	OT_PLANE,
	OT_CYLINDER
};

typedef struct s_material
{
	double	ambient;
	double	diffuse;
	double	specular;
	double	shininess;
}	t_material;

typedef struct s_obj
{
	enum e_obj_type	type;
	t_mat			transform;
	struct s_obj	*next;
	t_material		material;
}	t_obj;

typedef struct s_quadratic
{
	double	a;
	double	b;
	double	c;
	double	t1;
	double	t2;
	double	d;
}	t_quadratic;

typedef struct s_xsn
{
	int	id;
	int	count;
	double	t;
	t_obj	*xs_obj;
	struct s_xsn	*next;
}	t_xsn;

typedef struct s_colour
{
	double	red;
	double	green;
	double	blue;
}	t_colour;

typedef struct s_rgb
{
	int32_t	r;
	int32_t	g;
	int32_t	b;
}	t_rgb;

typedef struct s_point_light
{
	t_colour	colour;
	t_vec		position;
	double		intensity;
}	t_point_light;

#endif