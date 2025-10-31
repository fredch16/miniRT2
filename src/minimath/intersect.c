/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 19:27:35 by fredchar          #+#    #+#             */
/*   Updated: 2025/10/31 01:39:22 by fredchar         ###   ########.fr       */
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
	t_xsn	*xs;

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
		if (tmp->t > 0 && tmp->t < lnn)
		{
			lnn = tmp->t;
			hit = tmp;
		}
		tmp = tmp->next;
	}
	return (hit);

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
