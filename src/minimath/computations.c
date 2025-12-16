/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 16:36:47 by fredchar          #+#    #+#             */
/*   Updated: 2025/12/16 18:59:14 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

t_comps	prep_comps(t_xsn *xs, t_ray r)
{
	t_comps	comps;

	comps.t = xs->t;
	comps.obj = xs->xs_obj;
	comps.point = ray_pos(r, comps.t);
	comps.eyev = tuple_neg(r.direction);
	if (comps.obj->type == OT_SPHERE)
		comps.normalv = normal_at_sp(comps.obj, comps.point);
	else if (comps.obj->type == OT_PLANE)
		comps.normalv = normal_at_pl(comps.obj, comps.point);
	else if (comps.obj->type == OT_CYLINDER)
		comps.normalv = normal_at_cy(comps.obj, comps.point);
	if (tuple_dot(comps.normalv, comps.eyev) < 0)
	{
		comps.inside = true;
		comps.normalv = tuple_neg(comps.normalv);
	}
	else
		comps.inside = false;
	comps.over_p = tuple_add(tuple_scm(EPSILON, comps.normalv), comps.point);
	return (comps);
}

bool	is_shadowed(t_world *w, t_vec point)
{
	t_vec	poi_to_light;
	double	distance;
	t_ray	r;
	t_xsn	*xs;
	t_xsn	*hit;

	poi_to_light = tuple_sub(w->light.position, point);
	distance = tuple_mag(poi_to_light);
	poi_to_light = tuple_norm(poi_to_light);
	r = ray(point, poi_to_light);
	xs = intersect_world(w, r);
	hit = x_hit(xs);
	if (hit && hit->t < (distance - EPSILON))
	{
		x_clear(&xs);
		return (true);
	}
	else
	{
		x_clear(&xs);
		return (false);
	}
}

t_colour	colour_at(t_world *w, t_ray r)
{
	t_xsn		*xs;
	t_xsn		*hit;
	bool		in_shade;
	t_comps		comps;
	t_colour	col;

	xs = NULL;
	hit = NULL;
	xs = intersect_world(w, r);
	if (!xs)
		return ((t_colour){0, 0, 0});
	hit = x_hit(xs);
	if (!hit)
		return ((t_colour){0, 0, 0});
	comps = prep_comps(hit, r);
	in_shade = is_shadowed(w, comps.over_p);
	col = lighting(hit->xs_obj->material, w, comps, in_shade);
	x_clear(&xs);
	return (col);
}
