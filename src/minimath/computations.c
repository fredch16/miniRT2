/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 16:36:47 by fredchar          #+#    #+#             */
/*   Updated: 2025/11/02 21:07:00 by swied            ###   ########.fr       */
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
	return (comps);
}

// t_colour	shade_hit(t_world *w, t_comps c)
// {
// 	return (lighting(&(c.obj->material), w->light, c.point, c.eyev, c.normalv));
// }

t_colour	colour_at(t_world *w, t_ray r)
{
	t_xsn	*xs;
	t_xsn	*hit;

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
	t_colour col = lighting(comps.obj->material, w->light, comps.point, comps.eyev, comps.normalv);
	return (col);
}