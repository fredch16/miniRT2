/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:24:39 by fredchar          #+#    #+#             */
/*   Updated: 2025/12/15 15:26:55 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include "MLX42/include/MLX42/MLX42.h"

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
		mlx_close_window(mlx);
}

t_obj *create_sphere(double x, double y, double z, double radius, int r, int g, int b)
{
	t_obj *sphere = malloc(sizeof(t_obj));
	sphere->type = OT_SPHERE;
	sphere->transform = scaling(radius, radius, radius);
	sphere->transform = mat_mul_mat(translation(x, y, z), sphere->transform);
	sphere->material.ambient = 0.1;
	sphere->material.diffuse = 0.7;
	sphere->material.specular = 0.3;
	sphere->material.shininess = 200.0;
	sphere->material.colour = (t_colour){r/255.0, g/255.0, b/255.0};
	sphere->next = NULL;
	return sphere;
}

t_obj *create_plane(double x, double y, double z, double nx, double ny, double nz, int r, int g, int b)
{
	t_obj *plane = malloc(sizeof(t_obj));
	t_vec normal = vector(nx, ny, nz);
	t_vec up = vector(0, 1, 0);
	
	plane->type = OT_PLANE;
	
	// Rotation to align plane normal
	if (fabs(ny - 1.0) < 0.001)
		plane->transform = mat_idt();
	else if (fabs(ny + 1.0) < 0.001)
		plane->transform = rotation_x(M_PI);
	else
	{
		t_vec axis = tuple_cro(up, normal);
		axis = tuple_norm(axis);
		double angle = acos(tuple_dot(up, normal));
		double x_comp = axis.x;
		double y_comp = axis.y;
		double z_comp = axis.z;
		double s = sin(angle);
		double c = cos(angle);
		double t = 1.0 - c;
		
		plane->transform = (t_mat){{
			{t*x_comp*x_comp + c, t*x_comp*y_comp + z_comp*s, t*x_comp*z_comp - y_comp*s, 0},
			{t*x_comp*y_comp - z_comp*s, t*y_comp*y_comp + c, t*y_comp*z_comp + x_comp*s, 0},
			{t*x_comp*z_comp + y_comp*s, t*y_comp*z_comp - x_comp*s, t*z_comp*z_comp + c, 0},
			{0, 0, 0, 1}
		}};
	}
	plane->transform = mat_mul_mat(translation(x, y, z), plane->transform);
	
	plane->material.ambient = 0.1;
	plane->material.diffuse = 0.7;
	plane->material.specular = 0.3;
	plane->material.shininess = 200.0;
	plane->material.colour = (t_colour){r/255.0, g/255.0, b/255.0};
	plane->next = NULL;
	return plane;
}

t_obj *create_cylinder(double x, double y, double z, double radius, double height, 
						double nx, double ny, double nz, bool closed, int r, int g, int b)
{
	t_obj *cyl = malloc(sizeof(t_obj));
	t_vec axis = vector(nx, ny, nz);
	t_vec up = vector(0, 1, 0);
	
	cyl->type = OT_CYLINDER;
	cyl->min_y = 0;
	cyl->max_y = height;
	cyl->closed = closed;
	
	// Rotation to align cylinder axis
	if (fabs(ny - 1.0) < 0.001)
		cyl->transform = mat_idt();
	else if (fabs(ny + 1.0) < 0.001)
		cyl->transform = rotation_x(M_PI);
	else
	{
		t_vec rot_axis = tuple_cro(up, axis);
		rot_axis = tuple_norm(rot_axis);
		double angle = acos(tuple_dot(up, axis));
		double x_comp = rot_axis.x;
		double y_comp = rot_axis.y;
		double z_comp = rot_axis.z;
		double s = sin(angle);
		double c = cos(angle);
		double t = 1.0 - c;
		
		cyl->transform = (t_mat){{
			{t*x_comp*x_comp + c, t*x_comp*y_comp + z_comp*s, t*x_comp*z_comp - y_comp*s, 0},
			{t*x_comp*y_comp - z_comp*s, t*y_comp*y_comp + c, t*y_comp*z_comp + x_comp*s, 0},
			{t*x_comp*z_comp + y_comp*s, t*y_comp*z_comp - x_comp*s, t*z_comp*z_comp + c, 0},
			{0, 0, 0, 1}
		}};
	}
	
	t_mat scale = scaling(radius, 1, radius);
	cyl->transform = mat_mul_mat(cyl->transform, scale);
	cyl->transform = mat_mul_mat(translation(x, y, z), cyl->transform);
	
	cyl->material.ambient = 0.1;
	cyl->material.diffuse = 0.7;
	cyl->material.specular = 0.3;
	cyl->material.shininess = 200.0;
	cyl->material.colour = (t_colour){r/255.0, g/255.0, b/255.0};
	cyl->next = NULL;
	return cyl;
}

void add_sphere(t_world *world, t_obj *sphere)
{
	if (!world->obj_list)
		world->obj_list = sphere;
	else
	{
		t_obj *curr = world->obj_list;
		while (curr->next)
			curr = curr->next;
		curr->next = sphere;
	}
}

int	main(int ac, char **av)
{
	t_world	world;
	
	// Check for correct usage
	if (ac != 2)
	{
		ft_putstr_fd("Error\nUsage: ./miniRT <scene_file.rt>\n", 2);
		return (EXIT_FAILURE);
	}
	
	// Parse the scene file
	printf("Parsing scene file: %s\n", av[1]);
	if (parse_scene(av[1], &world) < 0)
	{
		ft_putstr_fd("Error\nFailed to parse scene file\n", 2);
		return (EXIT_FAILURE);
	}
	
	printf("Scene loaded successfully!\n");
	printf("Ambient: R=%.2f G=%.2f B=%.2f\n", 
		world.ambient.red, world.ambient.green, world.ambient.blue);
	printf("Light position: (%.2f, %.2f, %.2f) intensity: %.2f\n",
		world.light.position.x, world.light.position.y, world.light.position.z,
		world.light.intensity);
	
	// Count objects
	int obj_count = 0;
	t_obj *curr = world.obj_list;
	while (curr)
	{
		obj_count++;
		curr = curr->next;
	}
	printf("Number of objects: %d\n", obj_count);

	printf("Number of objects: %d\n", obj_count);

	// Initialize MLX
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "miniRT - Ray Tracer", true);
	if (!mlx)
	{
		free_world(&world);
		ft_error();
	}

	mlx_image_t* img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
	{
		free_world(&world);
		ft_error();
	}

	// Render scene
	printf("Starting render: %dx%d pixels...\n", WIDTH, HEIGHT);
	for (int y = 0; y < HEIGHT; y++)
	{
		// Progress indicator every 10%
		if (y % (HEIGHT / 10) == 0)
			printf("Rendering progress: %.1f%%\n", (float)y / HEIGHT * 100);
			
		for (int x = 0; x < WIDTH; x++)
		{
			t_ray r = ray_for_pixel(world.camera, x, y);
			t_colour color = colour_at(&world, r);
			mlx_put_pixel(img, x, y, colour_to_rgba(color));
		}
	}
	printf("Render complete!\n");

	// Register a hook and pass mlx as an optional param.
	// NOTE: Do this before calling mlx_loop!
	mlx_key_hook(mlx, mlx_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	
	// Clean up
	free_world(&world);
	
	return (EXIT_SUCCESS);
}
