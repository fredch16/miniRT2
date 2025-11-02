/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:24:39 by fredchar          #+#    #+#             */
/*   Updated: 2025/11/02 23:03:56 by swied            ###   ########.fr       */
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
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "miniRT - Ray Tracer", true);
	if (!mlx)
		ft_error();

	mlx_image_t* img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		ft_error();

	// Setup world with six spheres - "Putting It Together" from the book
	t_world world;
	
	// 1. Floor - extremely flattened sphere with matte texture
	t_obj *floor = obj_create(OT_SPHERE);
	floor->transform = scaling(10, 0.01, 10);
	floor->material = (t_material){0.1, 0.9, 0, 200, {1, 0.9, 0.9}};
	floor->material.specular = 0;
	
	// 2. Left wall - same scale and color as floor, rotated and translated
	// Transform order: scale -> rotate_x -> rotate_y -> translate
	t_obj *left_wall = obj_create(OT_SPHERE);
	left_wall->transform = mat_mul_mat(mat_mul_mat(mat_mul_mat(
		translation(0, 0, 5),
		rotation_y(-M_PI / 4)),
		rotation_x(M_PI / 2)),
		scaling(10, 0.01, 10));
	left_wall->material = floor->material;
	
	// 3. Right wall - identical to left wall but rotated opposite in y
	t_obj *right_wall = obj_create(OT_SPHERE);
	right_wall->transform = mat_mul_mat(mat_mul_mat(mat_mul_mat(
		translation(0, 0, 5),
		rotation_y(M_PI / 4)),
		rotation_x(M_PI / 2)),
		scaling(10, 0.01, 10));
	right_wall->material = floor->material;
	
	// 4. Middle - large green sphere (unit sphere) translated upward
	t_obj *middle = obj_create(OT_SPHERE);
	middle->transform = translation(-0.5, 1, 0.5);
	middle->material = (t_material){0.1, 0.7, 0.3, 200, {0.1, 1, 0.5}};
	
	// 5. Right - smaller green sphere scaled in half
	t_obj *right = obj_create(OT_SPHERE);
	right->transform = mat_mul_mat(
		translation(1.5, 0.5, -0.5),
		scaling(0.5, 0.5, 0.5));
	right->material = (t_material){0.1, 0.7, 0.3, 200, {0.5, 1, 0.1}};
	
	// 6. Left - smallest sphere scaled by a third
	t_obj *left = obj_create(OT_SPHERE);
	left->transform = mat_mul_mat(
		translation(-1.5, 0.33, -0.75),
		scaling(0.33, 0.33, 0.33));
	left->material = (t_material){0.1, 0.7, 0.3, 200, {1, 0.8, 0.1}};
	
	// Add all objects to the world
	// Temporarily disable walls to see all spheres
	// obj_add_back(&floor, left_wall);
	// obj_add_back(&floor, right_wall);
	obj_add_back(&floor, middle);
	obj_add_back(&floor, right);
	obj_add_back(&floor, left);
	world.obj_list = floor;
	
	// Light source - white, shining from above and to the left
	world.light = (t_point_light){{1, 1, 1}, point(-10, 10, -10), 1.0};

	// Setup camera - positioned to see all three spheres
	t_camera cam = camera(WIDTH, HEIGHT, M_PI / 3);  // 60° FOV
	cam.transform = view_transform(point(0, 1.5, -5), point(0, 1, 0), vector(0, 1, 0));

	// Render scene
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			t_ray r = ray_for_pixel(cam, x, y);
			t_colour color = colour_at(&world, r);
			mlx_put_pixel(img, x, y, colour_to_rgba(color));
		}
	}

	// Register a hook and pass mlx as an optional param.
	// NOTE: Do this before calling mlx_loop!
	mlx_key_hook(mlx, mlx_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
