/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 19:27:35 by fredchar          #+#    #+#             */
/*   Updated: 2025/12/17 16:33:33 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

// test this
inline t_vec	ray_pos(t_ray ray, double t_val)
{
	return (tuple_add(ray.origin, tuple_scm(t_val, ray.direction)));
}

t_xsn	*intersect_sp(t_ray ray, t_obj *o)
{
	t_vec		sp_to_ray;
	t_quadratic	q;
	t_xsn		*xs;

	xs = NULL;
	ray = ray_transform(ray, mat_inverse(o->transform));
	sp_to_ray = tuple_sub(ray.origin, point(0, 0, 0));
	q.a = tuple_dot(ray.direction, ray.direction);
	q.b = 2 * tuple_dot(ray.direction, sp_to_ray);
	q.c = tuple_dot(sp_to_ray, sp_to_ray) - 1;
	q.d = (q.b * q.b) - (4 * q.a * q.c);
	xs = NULL;
	if (q.d >= 0)
	{
		q.t1 = (-q.b - sqrt(q.d)) / (2 * q.a);
		xs = x_new(o, q.t1);
		if (q.d > 0)
		{
			q.t2 = (-q.b + sqrt(q.d)) / (2 * q.a);
			x_add_back(&xs, x_new(o, q.t2));
		}
	}
	return (xs);
}

t_xsn	*intersect_pl(t_ray ray, t_obj *o)
{
	t_xsn	*xs;
	double	t;

	ray = ray_transform(ray, mat_inverse(o->transform));
	if (fabs(ray.direction.y) < EPSILON)
		return (NULL);
	t = -ray.origin.y / ray.direction.y;
	if (t > EPSILON)
	{
		xs = x_new(o, t);
		return (xs);
	}
	return (NULL);
}

t_xsn	*x_hit(t_xsn *xs)
{
	t_xsn	*tmp;
	t_xsn	*hit;
	double	lnn;

	hit = NULL;
	tmp = xs;
	lnn = __DBL_MAX__;
	while (tmp)
	{
		if (tmp->t > EPSILON && tmp->t < lnn)
		{
			lnn = tmp->t;
			hit = tmp;
		}
		tmp = tmp->next;
	}
	return (hit);
}

t_xsn	*intersect_world(t_world *w, t_ray r)
{
	t_obj	*tmp;
	t_xsn	*xs;

	xs = NULL;
	tmp = w->obj_list;
	while (tmp)
	{
		if (tmp->type == OT_SPHERE)
			x_add_back(&xs, intersect_sp(r, tmp));
		else if (tmp->type == OT_PLANE)
			x_add_back(&xs, intersect_pl(r, tmp));
		else if (tmp->type == OT_CYLINDER)
			x_add_back(&xs, intersect_cy(r, tmp));
		tmp = tmp->next;
	}
	xs = x_sort(xs);
	return (xs);
}
