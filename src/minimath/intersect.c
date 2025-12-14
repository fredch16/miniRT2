/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 19:27:35 by fredchar          #+#    #+#             */
/*   Updated: 2025/12/14 17:02:56 by swied            ###   ########.fr       */
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

t_xsn	*intersect_pl(t_ray ray, t_obj *o)
{
	t_vec	normal;
	double	t;
	double	denom;

	ray = ray_transform(ray, mat_inverse(o->transform));
	normal = vector(0, 1, 0);
	denom = tuple_dot(ray.direction, normal);
	if (fabs(denom) < EPSILON)
		return (NULL);
	t = -ray.origin.y / denom;
	return (x_new(o, t));
}

static bool	check_cylinder_cap(t_ray ray, double t, double radius)
{
	double	x;
	double	z;

	x = ray.origin.x + t * ray.direction.x;
	z = ray.origin.z + t * ray.direction.z;
	return ((x * x + z * z) <= (radius * radius));
}

static t_xsn	*intersect_caps(t_ray ray, t_obj *o)
{
	t_xsn	*xs;
	double	t;

	xs = NULL;
	if (!o->closed || fabs(ray.direction.y) < EPSILON)
		return (NULL);
	t = (o->min_y - ray.origin.y) / ray.direction.y;
	if (check_cylinder_cap(ray, t, 1.0))
		x_add_back(&xs, x_new(o, t));
	t = (o->max_y - ray.origin.y) / ray.direction.y;
	if (check_cylinder_cap(ray, t, 1.0))
		x_add_back(&xs, x_new(o, t));
	return (xs);
}

t_xsn	*intersect_cy(t_ray ray, t_obj *o)
{
	t_quadratic	q;
	t_xsn		*xs;
	double		y0;
	double		y1;

	ray = ray_transform(ray, mat_inverse(o->transform));
	q.a = ray.direction.x * ray.direction.x + ray.direction.z * ray.direction.z;
	if (fabs(q.a) < EPSILON)
		return (intersect_caps(ray, o));
	q.b = 2.0 * (ray.origin.x * ray.direction.x + ray.origin.z * ray.direction.z);
	q.c = ray.origin.x * ray.origin.x + ray.origin.z * ray.origin.z - 1.0;
	q.d = q.b * q.b - 4.0 * q.a * q.c;
	xs = NULL;
	if (q.d >= 0)
	{
		q.t1 = (-q.b - sqrt(q.d)) / (2.0 * q.a);
		q.t2 = (-q.b + sqrt(q.d)) / (2.0 * q.a);
		y0 = ray.origin.y + q.t1 * ray.direction.y;
		if (o->min_y < y0 && y0 < o->max_y)
			x_add_back(&xs, x_new(o, q.t1));
		y1 = ray.origin.y + q.t2 * ray.direction.y;
		if (o->min_y < y1 && y1 < o->max_y)
			x_add_back(&xs, x_new(o, q.t2));
	}
	x_add_back(&xs, intersect_caps(ray, o));
	return (xs);
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

// t_xsn	*intersect_sp(t_ray ray, t_obj *o)
// {
// 	t_vec		sp_to_ray;
// 	t_quadratic	q;
// 	t_xsn		*xs;

// 	sp_to_ray = tuple_sub(ray.origin, point(0, 0, 0));
// 	q.a = tuple_dot(ray.direction, ray.direction);
// 	q.b = 2 * tuple_dot(ray.direction, sp_to_ray);
// 	q.c = tuple_dot(sp_to_ray, sp_to_ray) - 1;
// 	q.d = (q.b * q.b) - (4 * q.a * q.c);
// 	xs = NULL;
// 	if (q.d < 0)
// 		return (NULL);
// 	double sqrt_d = sqrt(q.d);
// 	q.t1 = (-q.b - sqrt_d) / (2 * q.a);
// 	xs = x_new(o, q.t1);
// 	if (q.d > 0)
// 	{
// 		q.t2 = (-q.b + sqrt_d) / (2 * q.a);
// 		x_add_back(&xs, x_new(o, q.t2));
// 	}
// 	return (xs);
// }


// t_xsn	*intersect_sp(t_ray ray, t_obj *o)
// {
// 	t_vec		sp_to_ray;
// 	t_quadratic	q;
// 	t_xsn		*xs;

// 	printf("\n===== SPHERE INTERSECTION DEBUG =====\n");

// 	printf("Ray origin:     (%.5f, %.5f, %.5f)\n",
// 		ray.origin.x, ray.origin.y, ray.origin.z);
// 	printf("Ray direction:  (%.5f, %.5f, %.5f)\n",
// 		ray.direction.x, ray.direction.y, ray.direction.z);
// 	printf("Sphere object pointer: %p\n", (void *)o);

// 	// vector from sphere center (0,0,0) to ray origin
// 	sp_to_ray = tuple_sub(ray.origin, point(0, 0, 0));
// 	printf("sp_to_ray:      (%.5f, %.5f, %.5f)\n",
// 		sp_to_ray.x, sp_to_ray.y, sp_to_ray.z);

// 	// Quadratic coefficients
// 	q.a = tuple_dot(ray.direction, ray.direction);
// 	q.b = 2 * tuple_dot(ray.direction, sp_to_ray);
// 	q.c = tuple_dot(sp_to_ray, sp_to_ray) - 1;

// 	printf("a = %.8f\n", q.a);
// 	printf("b = %.8f\n", q.b);
// 	printf("c = %.8f\n", q.c);

// 	q.d = (q.b * q.b) - (4 * q.a * q.c);
// 	printf("Discriminant (d) = %.8f\n", q.d);

// 	xs = NULL;

// 	if (q.d < 0)
// 	{
// 		printf("No intersections (d < 0)\n");
// 		printf("===== END SPHERE DEBUG =====\n\n");
// 		return (NULL);
// 	}

// 	printf("Discriminant >= 0, computing roots...\n");
// 	double sqrt_d = sqrt(q.d);

// 	q.t1 = (-q.b - sqrt_d) / (2 * q.a);
// 	printf("t1 = (-b - sqrt(d)) / 2a = %.8f\n", q.t1);
// 	xs = x_new(o, q.t1);
// 	printf("Registered intersection at t1\n");

// 	if (q.d > 0)
// 	{
// 		q.t2 = (-q.b + sqrt_d) / (2 * q.a);
// 		printf("t2 = (-b + sqrt(d)) / 2a = %.8f\n", q.t2);
// 		x_add_back(&xs, x_new(o, q.t2));
// 		printf("Registered intersection at t2\n");
// 	}
// 	else
// 	{
// 		printf("Discriminant == 0 (tangent): only one intersection\n");
// 	}

// 	printf("===== END SPHERE DEBUG =====\n\n");
// 	return (xs);
// }
