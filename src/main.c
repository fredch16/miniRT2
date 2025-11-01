/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:24:39 by fredchar          #+#    #+#             */
/*   Updated: 2025/11/01 21:43:23 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include "MLX42/include/MLX42/MLX42.h"

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

#define WIDTH 1600 
#define HEIGHT 900 

// Exit the program as failure.
static void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

void	mlx_hook(mlx_key_data_t mlx_key_data, void *param)
{
	mlx_t *mlx = param;

	if (mlx_key_data.key == MLX_KEY_ESCAPE)
	{
		//free
		printf("WINDOW IS BEING CLOSED DUE TO ESCAPE KEY\n");
		mlx_close_window(mlx);
	}
}

int32_t	main(void)
{

	// MLX allows you to define its core behaviour before startup.
	// mlx_set_setting(MLX_MAXIMIZED, true);
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "42Balls", true);
	if (!mlx)
		ft_error();

	// Create and display the image.
	mlx_image_t* img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		ft_error();

	/* Do stuff */

	// === TEST: Computing the normal on a transformed sphere ===
	printf("\n=== TEST: Transformed Sphere Normal ===\n");
	
	t_obj *s = obj_create(OT_SPHERE);
	
	// m ← scaling(1, 0.5, 1) * rotation_z(π/5)
	// WICHTIG: Reihenfolge! Erst rotation_z, dann scaling (rechts nach links)
	t_mat m = mat_mul_mat(scaling(1, 0.5, 1), rotation_z(M_PI / 5));
	s->transform = m;
	
	// n ← normal_at(s, point(0, √2/2, -√2/2))
	double sqrt2_div2 = sqrt(2) / 2;
	t_vec n = normal_at_sp(s, point(0, sqrt2_div2, -sqrt2_div2));
	
	printf("Sphere Transform: scaling(1, 0.5, 1) × rotation_z(π/5)\n");
	printf("Point: (0, %.5f, %.5f)\n", sqrt2_div2, -sqrt2_div2);
	printf("Normal:\n");
	print_vec4(n);
	printf("\nErwartet: (0, 0.97014, -0.24254)\n");
	printf("Tatsächlich: (%.5f, %.5f, %.5f)\n", n.x, n.y, n.z);

	// === TEST: Reflecting a vector off a slanted surface ===
	printf("\n\n=== TEST: Reflecting a vector off a slanted surface ===\n");
	
	t_vec v = vector(0, -1, 0);
	double sqrt2_div_2 = sqrt(2) / 2;
	t_vec normal = vector(sqrt2_div_2, sqrt2_div_2, 0);
	t_vec r_reflected = reflect(v, normal);
	
	printf("Incoming vector v: ");
	print_vec4(v);
	printf("Surface normal n (√2/2, √2/2, 0): ");
	print_vec4(normal);
	printf("Reflected vector r: ");
	print_vec4(r_reflected);
	printf("Erwartet: (1, 0, 0)\n");

	t_ray	r;
	t_obj	*o = obj_create(OT_SPHERE);
	o->transform = mat_idt();
	// set standard material
	t_material mater;

	mater.ambient = 0.1;
	mater.diffuse = 0.9;
	mater.specular = 0.9;
	mater.shininess = 200;
	o->material = mater;

	int x = 0;
	int y = 0;
	r = ray(point(0, 0, -5), vector(-4, 2.5, 5));
	while (x < WIDTH)
	{
		y = 0;
		r.direction.y = 2.5;
		while (y < HEIGHT)
		{
			t_xsn *xs = intersect_sp(r, o);
			if (x_hit(xs))
				mlx_put_pixel(img, x, y, 0xFF0000FF);
			else
				mlx_put_pixel(img, x, y, 0x000000FF);
			y++;
			r.direction.y -= 0.005;
		}
		x++;
		r.direction.x += 0.005;
	}

	// Register a hook and pass mlx as an optional param.
	// NOTE: Do this before calling mlx_loop!
	mlx_key_hook(mlx, mlx_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
