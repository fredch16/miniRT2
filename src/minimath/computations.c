/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 16:36:47 by fredchar          #+#    #+#             */
/*   Updated: 2025/11/02 18:34:47 by fredchar         ###   ########.fr       */
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

t_colour	shade_hit(t_world *w, t_comps c)
{
	return (lighting(&(c.obj->material), w->light, c.point, c.eyev, c.normalv));
}