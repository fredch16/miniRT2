/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 16:36:47 by fredchar          #+#    #+#             */
/*   Updated: 2025/11/02 23:17:36 by fredchar         ###   ########.fr       */
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
	comps.normalv = normal_at_sp(comps.obj, comps.point);
	if (tuple_dot(comps.normalv, comps.eyev) < 0)
	{
		comps.inside = true;
		comps.normalv = tuple_neg(comps.normalv);
	}
	else
		comps.inside = false;
	comps.over_point = tuple_add(tuple_scm(EPSILON, comps.normalv), comps.point);
	return (comps);
}

// t_colour	shade_hit(t_world *w, t_comps c)
// {
// 	return (lighting(&(c.obj->material), w->light, c.point, c.eyev, c.normalv));
// }

bool	is_shadowed(t_world *w, t_vec point)
{
	t_vec	poi_to_light;
	double	distance;
	t_ray	r;
	t_xsn	*xs;

	poi_to_light = tuple_sub(w->light.position, point);
	distance = tuple_mag(poi_to_light);
	poi_to_light = tuple_norm(poi_to_light);
	r = ray(point, poi_to_light);
	xs = intersect_world(w, r);
	xs = x_hit(xs);
	if (xs && xs->t < distance)
		return (true);
	else
		return (false);
}

t_colour	colour_at(t_world *w, t_ray r)
{
	t_xsn	*xs;
	t_xsn	*hit;
	bool	in_shade;

	xs = NULL;
	hit = NULL;
	xs = intersect_world(w, r);
	// print_xs(xs);
	if (!xs)
		return ((t_colour){0, 0, 0});
	// printf("\n\nLOOKING FOR HIT\n\n");
	hit = x_hit(xs);
	// print_xs(hit);
	if (!hit)
		return ((t_colour){0, 0, 0});
	t_comps comps;
	comps = prep_comps(hit, r);
	// print_comps(comps);
	in_shade = is_shadowed(w, comps.over_point);
	t_colour col = lighting(xs->xs_obj->material, w->light, comps, in_shade);
	return (col);
}