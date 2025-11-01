/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 21:47:29 by swied             #+#    #+#             */
/*   Updated: 2025/11/01 23:20:40 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"
#include <math.h>

inline static t_colour	colour(double r, double g, double b)
{
	return ((t_colour){r, g, b});
}

static t_colour	colour_mul(t_colour c1, t_colour c2)
{
	t_colour	result;

	result.red = c1.red * c2.red;
	result.green = c1.green * c2.green;
	result.blue = c1.blue * c2.blue;
	return (result);
}

static t_colour	colour_scm(double scalar, t_colour c)
{
	t_colour	result;

	result.red = scalar * c.red;
	result.green = scalar * c.green;
	result.blue = scalar * c.blue;
	return (result);
}

static t_colour	colour_add(t_colour c1, t_colour c2)
{
	t_colour	result;

	result.red = c1.red + c2.red;
	result.green = c1.green + c2.green;
	result.blue = c1.blue + c2.blue;
	return (result);
}

static t_colour	calc_specular(t_material *m, t_point_light light,
					t_vec lightv, t_vec eyev, t_vec normalv)
{
	t_vec		reflectv;
	double		reflect_dot_eye;
	double		factor;
	t_colour	spec;

	reflectv = reflect(tuple_scm(-1, lightv), normalv);
	reflect_dot_eye = tuple_dot(reflectv, eyev);
	if (reflect_dot_eye <= 0)
		return (colour(0, 0, 0));
	factor = pow(reflect_dot_eye, m->shininess);
	spec = colour_scm(m->specular * factor, light.colour);
	spec = colour_scm(light.intensity, spec);
	return (spec);
}

t_colour	lighting(t_material *material, t_point_light light,
				t_vec point, t_vec eyev, t_vec normalv)
{
	t_colour	effective_color;
	t_colour	ambient;
	t_colour	diffuse;
	t_colour	specular;
	t_vec		lightv;
	double		light_dot_normal;

	effective_color = colour_mul(material->colour, light.colour);
	effective_color = colour_scm(light.intensity, effective_color);
	lightv = tuple_norm(tuple_sub(light.position, point));
	ambient = colour_scm(material->ambient, effective_color);
	light_dot_normal = tuple_dot(lightv, normalv);
	if (light_dot_normal < 0)
	{
		diffuse = colour(0, 0, 0);
		specular = colour(0, 0, 0);
	}
	else
	{
		diffuse = colour_scm(material->diffuse * light_dot_normal,
				effective_color);
		specular = calc_specular(material, light, lightv, eyev, normalv);
	}
	return (colour_add(colour_add(ambient, diffuse), specular));
}
