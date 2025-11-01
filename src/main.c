/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:24:39 by fredchar          #+#    #+#             */
/*   Updated: 2025/11/01 23:26:41 by swied            ###   ########.fr       */
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
	// === TESTS BEFORE MLX INITIALIZATION ===
	
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

	// === TEST: Phong Lighting Model ===
	{
		printf("\n\n=== TEST 1: Lighting with eye between light and surface ===\n");
		
		t_material mat = {0.1, 0.9, 0.9, 200.0, {1, 1, 1}};
		t_vec position = point(0, 0, 0);
		
		t_vec eyev = vector(0, 0, -1);
		t_vec normalv = vector(0, 0, -1);
		t_point_light light = {{1, 1, 1}, point(0, 0, -10), 1.0};
	
	t_colour result = lighting(&mat, light, position, eyev, normalv);
	printf("Result: (%.5f, %.5f, %.5f)\n", result.red, result.green, result.blue);
	printf("Erwartet: (1.9, 1.9, 1.9)\n\n");
	
	// TEST 2: Eye between light and surface, eye offset 45°
	printf("=== TEST 2: Eye offset 45° ===\n");
	eyev = vector(0, sqrt(2)/2, -sqrt(2)/2);
	result = lighting(&mat, light, position, eyev, normalv);
	printf("Result: (%.5f, %.5f, %.5f)\n", result.red, result.green, result.blue);
	printf("Erwartet: (1.0, 1.0, 1.0)\n\n");
	
	// TEST 3: Eye opposite surface, light offset 45°
	printf("=== TEST 3: Light offset 45° ===\n");
	eyev = vector(0, 0, -1);
	light.position = point(0, 10, -10);
	result = lighting(&mat, light, position, eyev, normalv);
	printf("Result: (%.5f, %.5f, %.5f)\n", result.red, result.green, result.blue);
	printf("Erwartet: (0.7364, 0.7364, 0.7364)\n\n");
	
	// TEST 4: Eye in path of reflection vector
	printf("=== TEST 4: Eye in reflection path ===\n");
	eyev = vector(0, -sqrt(2)/2, -sqrt(2)/2);
	light.position = point(0, 10, -10);
	result = lighting(&mat, light, position, eyev, normalv);
	printf("Result: (%.5f, %.5f, %.5f)\n", result.red, result.green, result.blue);
	printf("Erwartet: (1.6364, 1.6364, 1.6364)\n\n");
	
	// TEST 5: Light behind surface
	printf("=== TEST 5: Light behind surface ===\n");
	eyev = vector(0, 0, -1);
	light.position = point(0, 0, 10);
	result = lighting(&mat, light, position, eyev, normalv);
	printf("Result: (%.5f, %.5f, %.5f)\n", result.red, result.green, result.blue);
	printf("Erwartet: (0.1, 0.1, 0.1) [nur ambient]\n");
	}

	// === MLX INITIALIZATION ===
	printf("\n\n=== Starting MLX Rendering ===\n");
	
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "42Balls", true);
	if (!mlx)
		ft_error();

	mlx_image_t* img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		ft_error();

	// Setup sphere with material
	t_obj *sphere = obj_create(OT_SPHERE);
	sphere->transform = translation(0, 1, 10);
	sphere->material = (t_material){0.1, 0.9, 0.9, 200, {1, 0.2, 1}};  // Magenta color
	
	// Setup light source
	t_point_light light = {{1, 1, 1}, point(-10, 10, -10), 1.0};
	
	// Ray-tracing loop
	t_vec ray_origin = point(0, 0, -5);
	double wall_z = 10;
	double wall_size = 7.0;
	double pixel_size = wall_size / WIDTH;
	double half = wall_size / 2;
	
	for (int y = 0; y < HEIGHT; y++)
	{
		double world_y = half - pixel_size * y;
		
		for (int x = 0; x < WIDTH; x++)
		{
			double world_x = -half + pixel_size * x;
			t_vec target = point(world_x, world_y, wall_z);
			t_vec direction = tuple_norm(tuple_sub(target, ray_origin));
			t_ray r = ray(ray_origin, direction);
			
			t_xsn *xs = intersect_sp(r, sphere);
			t_xsn *hit = x_hit(xs);
			
			if (hit)
			{
				t_vec hit_point = ray_pos(r, hit->t);
				t_vec normal = normal_at_sp(sphere, hit_point);
				t_vec eye = tuple_scm(-1, r.direction);
				
				t_colour color = lighting(&sphere->material,
										light, hit_point, eye, normal);
				
				// Convert color to RGBA (clamp to 0-255)
				int red = (int)(color.red * 255);
				int green = (int)(color.green * 255);
				int blue = (int)(color.blue * 255);
				if (red > 255) red = 255;
				if (green > 255) green = 255;
				if (blue > 255) blue = 255;
				
				uint32_t rgba = (red << 24) | (green << 16) | (blue << 8) | 0xFF;
				mlx_put_pixel(img, x, y, rgba);
			}
			else
				mlx_put_pixel(img, x, y, 0x000000FF);
		}
	}

	// Register a hook and pass mlx as an optional param.
	// NOTE: Do this before calling mlx_loop!
	mlx_key_hook(mlx, mlx_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
