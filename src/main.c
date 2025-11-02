/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:24:39 by fredchar          #+#    #+#             */
/*   Updated: 2025/11/02 22:43:12 by fredchar         ###   ########.fr       */
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
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "miniRT - Phong Shading", true);
	if (!mlx)
		ft_error();

	mlx_image_t* img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		ft_error();

	// Setup sphere at origin with red material
	t_obj *sphere = obj_create(OT_SPHERE);
	sphere->transform = mat_idt();  // Identity = centered at (0,0,0)
	sphere->material = (t_material){0.1, 0.9, 0.9, 200, {1, 0.2, 1}};
	
	// Setup light source (top-left behind camera)
	


	t_world world;
	t_obj	*s1 = obj_create(OT_SPHERE); 
	t_obj	*s2 = obj_create(OT_SPHERE); 
	s1->material = (t_material){0.1, 0.7, 0.3, 200, {0.1, 1.0, 0.5}};
	s1->transform = translation(-0.5, 1, 0.5);
	s1->material = (t_material){0.1, 0.7, 0.2, 200, {0.8, 1.0, 0.6}};
	t_mat mat = mat_mul_mat(rotation_x(M_PI / 2), scaling(10, 0.01, 10));
	mat = mat_mul_mat(rotation_y(M_PI / 4), mat);
	mat = mat_mul_mat(translation(0, 0, 5), mat);
	s2->material = (t_material){0.1, 0.7, 0.2, 0, {1.0, 0.9, 0.9}};
	s2->transform = mat;
	obj_add_back(&s1, s2);
	world.obj_list = s1;

	// t_obj	*s3 = obj_create(OT_SPHERE);
	// s3->transform = translation(0, 0, 1);
	// world.obj_list = s3;
	world.light = (t_point_light){{1, 1, 1}, {-10, 10, -10, 1}, 1};

	t_ray r = ray(point(0, 0, -10), vector(0, 0, 1));
	print_colour(colour_at(&world, r));

	// Camera setup
	t_vec ray_origin = point(0, 4, -200);  // Camera 5 units back
	double wall_z = 10;  // Canvas in front of sphere
	double wall_size = 7.0;
	double aspect = (double)WIDTH / (double)HEIGHT;
	double pixel_size = wall_size / HEIGHT;
	double half_height = wall_size / 2;
	double half_width = (wall_size * aspect) / 2;

	for (int y = 0; y < HEIGHT; y++)
	{
		double world_y = half_height - pixel_size * y;
		
		for (int x = 0; x < WIDTH; x++)
		{
			double world_x = -half_width + pixel_size * x;
			t_vec target = point(world_x, world_y, wall_z);
			t_vec direction = tuple_norm(tuple_sub(target, ray_origin));
			t_ray r = ray(ray_origin, direction);
			
			t_colour color = colour_at(&world, r);
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
		}
		
	

	// Register a hook and pass mlx as an optional param.
	// NOTE: Do this before calling mlx_loop!
	mlx_key_hook(mlx, mlx_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
