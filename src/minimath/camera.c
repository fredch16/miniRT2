/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 19:26:23 by swied             #+#    #+#             */
/*   Updated: 2025/11/16 18:21:07 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

t_mat   view_transform(t_vec from, t_vec to, t_vec up)
{
    t_vec   forward;
    t_vec   upn;
    t_vec   left;
    t_vec   true_up;
    t_mat   orientation;
	double  left_mag;

	forward = tuple_norm(tuple_sub(to, from));
	upn = tuple_norm(up);
	left = tuple_cro(forward, upn);
	left_mag = tuple_mag(left);
	/* If forward and up are (nearly) parallel, choose a stable fallback up */
	if (left_mag < 1e-6)
	{
		t_vec alt_up = tuple(0, 1, 0, 0);
		/* pick an alternative that is not parallel to forward */
		if (fabs(tuple_dot(forward, alt_up)) > 0.999)
			alt_up = tuple(0, 0, 1, 0);
		upn = tuple_norm(alt_up);
		left = tuple_cro(forward, upn);
	}
	left = tuple_norm(left);
	true_up = tuple_cro(left, forward);
    orientation = mat(
        tuple(left.x, left.y, left.z, 0),
        tuple(true_up.x, true_up.y, true_up.z, 0),
        tuple(-forward.x, -forward.y, -forward.z, 0),
        tuple(0, 0, 0, 1)
    );
    return (mat_mul_mat(orientation, translation(-from.x, -from.y, -from.z)));
}

t_camera	camera(int hsize, int vsize, double field_of_view)
{
	t_camera	cam;
	double		half_view;
	double		aspect;

	cam.hsize = hsize;
	cam.vsize = vsize;
	cam.field_of_view = field_of_view;
	cam.transform = mat_idt();
	half_view = tan(field_of_view * 0.5);
	aspect = (double)hsize / (double)vsize;
	if (aspect >= 1.0)
	{
		cam.half_width = half_view;
		cam.half_height = half_view / aspect;
	}
	else
	{
		cam.half_width = half_view * aspect;
		cam.half_height = half_view;
	}
	cam.pixel_size = (cam.half_width * 2.0) / (double)hsize;
	return (cam);
}

t_ray	ray_for_pixel(t_camera cam, int px, int py)
{
	t_vec	origin;
	t_mat	inverse;
	double	world_x;
	double	world_y;

	world_x = cam.half_width - (((double)px + 0.5) * cam.pixel_size);
	world_y = cam.half_height - (((double)py + 0.5) * cam.pixel_size);
	inverse = mat_inverse(cam.transform);
	origin = mat_mul_vec(inverse, point(0, 0, 0));

    /* Camera-space convention: use image-plane z = +1 for rays. */

	t_vec	pixel_neg = mat_mul_vec(inverse, point(world_x, world_y, -1));
	t_vec	dir_neg = tuple_norm(tuple_sub(pixel_neg, origin));
	t_vec	pixel_pos = mat_mul_vec(inverse, point(world_x, world_y, 1));
	t_vec	dir_pos = tuple_norm(tuple_sub(pixel_pos, origin));
	/* Choose the direction whose dot with the parsed camera forward is >= 0 */
	if (tuple_dot(dir_neg, cam.forward) >= 0)
		return (ray(origin, dir_neg));
	return (ray(origin, dir_pos));
}
