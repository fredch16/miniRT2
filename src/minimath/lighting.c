/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 21:47:29 by swied             #+#    #+#             */
/*   Updated: 2025/12/17 16:53:23 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"
#include <math.h>

static t_colour	calc_specular(t_material m, t_point_light light,
	t_vec lightv, t_comps c)
{
	t_vec		reflectv;
	double		reflect_dot_eye;
	double		factor;
	t_colour	spec;

	reflectv = reflect(tuple_scm(-1, lightv), c.normalv);
	reflect_dot_eye = tuple_dot(reflectv, c.eyev);
	if (reflect_dot_eye <= 0)
		return (colour(0, 0, 0));
	factor = pow(reflect_dot_eye, m.shininess);
	spec = colour_scm(m.specular * light.intensity * factor, light.colour);
	return (spec);
}

static t_colour	calc_diffuse(t_material material, double light_intensity,
	double light_dot_normal, t_colour effective_color)
{
	if (light_dot_normal < 0)
		return (colour(0, 0, 0));
	return (colour_scm(material.diffuse * light_dot_normal * light_intensity,
			effective_color));
}

t_colour	lighting(t_material material, t_world *w, t_comps c, bool in_shade)
{
	t_colour	effective_color;
	t_colour	ambient;
	t_colour	diffuse;
	t_colour	specular;
	t_vec		lightv;

	ambient = colour_mul(material.colour, w->ambient);
	if (in_shade)
		return (ambient);
	effective_color = colour_mul(material.colour, w->light.colour);
	lightv = tuple_norm(tuple_sub(w->light.position, c.point));
	diffuse = calc_diffuse(material, w->light.intensity,
			tuple_dot(lightv, c.normalv), effective_color);
	if (tuple_dot(lightv, c.normalv) < 0)
		specular = colour(0, 0, 0);
	else
		specular = calc_specular(material, w->light, lightv, c);
	return (colour_add(colour_add(ambient, diffuse), specular));
}
