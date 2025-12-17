/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 16:16:56 by fredchar          #+#    #+#             */
/*   Updated: 2025/12/17 16:22:25 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

/*
Helper: Berechnet Schnittpunkte mit den Zylinderdeckeln
*/
static void intersect_caps(t_ray ray, t_obj *o, t_xsn **xs)
{
	double t;

	if (!o->closed || fabs(ray.direction.y) < EPSILON)
		return;
	t = (o->min_y - ray.origin.y) / ray.direction.y;
	if (t > EPSILON && check_cylinder_cap(ray, t))
	{
		if (*xs)
			x_add_back(xs, x_new(o, t));
		else
			*xs = x_new(o, t);
	}
	t = (o->max_y - ray.origin.y) / ray.direction.y;
	if (t > EPSILON && check_cylinder_cap(ray, t))
	{
		if (*xs)
			x_add_back(xs, x_new(o, t));
		else
			*xs = x_new(o, t);
	}
}

static void add_quadratic_hits(t_ray ray, t_obj *o, t_quadratic q, t_xsn **xs)
{
	double y1;
	double y2;

	q.t1 = (-q.b - sqrt(q.d)) / (2 * q.a);
	q.t2 = (-q.b + sqrt(q.d)) / (2 * q.a);
	y1 = ray.origin.y + q.t1 * ray.direction.y;
	if (q.t1 > EPSILON && y1 > o->min_y && y1 < o->max_y)
	{
		if (*xs)
			x_add_back(xs, x_new(o, q.t1));
		else
			*xs = x_new(o, q.t1);
	}
	y2 = ray.origin.y + q.t2 * ray.direction.y;
	if (q.t2 > EPSILON && y2 > o->min_y && y2 < o->max_y)
	{
		if (*xs)
			x_add_back(xs, x_new(o, q.t2));
		else
			*xs = x_new(o, q.t2);
	}
}

/*
x² + z² = 1 (Grundgleichung Zylinder)
at² + bt + c = 0 (Finale quadtratische Gleichung)
a = dx² + dz² (Koeffizient von t²)
b = 2(ox×dx + oz×dz) (Koeffizient von t)
c = ox² + oz² - 1 (Konstanter Term)
*/
t_xsn *intersect_cy(t_ray ray, t_obj *o)
{
	t_quadratic q;
	t_xsn *xs;

	xs = NULL;
	ray = ray_transform(ray, mat_inverse(o->transform));
	q.a = ray.direction.x * ray.direction.x + ray.direction.z * ray.direction.z;
	if (fabs(q.a) < EPSILON)
	{
		intersect_caps(ray, o, &xs);
		return (xs);
	}
	q.b = 2 * (ray.origin.x * ray.direction.x + ray.origin.z * ray.direction.z);
	q.c = ray.origin.x * ray.origin.x + ray.origin.z * ray.origin.z - 1;
	q.d = (q.b * q.b) - (4 * q.a * q.c);
	if (q.d < 0)
		return (xs);
	/* delegate root handling to helper to satisfy norminette */
	add_quadratic_hits(ray, o, q, &xs);
	intersect_caps(ray, o, &xs);
	return (xs);
}
