/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:24:39 by fredchar          #+#    #+#             */
/*   Updated: 2025/12/14 17:14:20 by swied            ###   ########.fr       */
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
	{
		//free
		printf("WINDOW IS BEING CLOSED DUE TO ESCAPE KEY\n");
		mlx_close_window(mlx);
	}
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
	(void)ac;
	(void)av;
	
	// Hardcoded scene setup
	t_world	world = {0};
	
	// Ambient light: 0.2 intensity, white
	world.ambient = (t_colour){0.2, 0.2, 0.2};
	
	// Camera: pos(0,0,-50), looking at (0,0,1), FOV 70
	world.camera.hsize = WIDTH;
	world.camera.vsize = HEIGHT;
	world.camera.field_of_view = 70.0 * M_PI / 180.0;
	world.camera.transform = view_transform(
		point(0, 0, -50),
		point(0, 0, 0),
		vector(0, 1, 0)
	);
	double half_view = tan(world.camera.field_of_view / 2.0);
	double aspect = (double)WIDTH / (double)HEIGHT;
	if (aspect >= 1) {
		world.camera.half_width = half_view;
		world.camera.half_height = half_view / aspect;
	} else {
		world.camera.half_width = half_view * aspect;
		world.camera.half_height = half_view;
	}
	world.camera.pixel_size = (world.camera.half_width * 2) / WIDTH;
	
	// Point light: pos(0,100,-80), intensity 0.8, white
	world.light.position = point(0, 100, -80);
	world.light.colour = (t_colour){0.8, 0.8, 0.8};
	world.light.intensity = 0.8;
	
	// Create all spheres from many_spheres.rt
	add_sphere(&world, create_sphere(0, 0, 0, 8, 255, 0, 0));
	add_sphere(&world, create_sphere(-15, 0, 0, 6, 0, 255, 0));
	add_sphere(&world, create_sphere(15, 0, 0, 6, 0, 0, 255));
	add_sphere(&world, create_sphere(0, -15, 0, 6, 255, 255, 0));
	add_sphere(&world, create_sphere(0, 15, 0, 6, 255, 0, 255));
	add_sphere(&world, create_sphere(0, 0, 15, 6, 0, 255, 255));
	
	add_sphere(&world, create_sphere(-10, -10, 10, 4, 200, 100, 50));
	add_sphere(&world, create_sphere(10, -10, 10, 4, 100, 200, 50));
	add_sphere(&world, create_sphere(-10, 10, 10, 4, 50, 200, 100));
	add_sphere(&world, create_sphere(10, 10, 10, 4, 200, 50, 100));
	
	add_sphere(&world, create_sphere(-20, 0, 10, 5, 150, 150, 150));
	add_sphere(&world, create_sphere(20, 0, 10, 5, 100, 100, 100));
	add_sphere(&world, create_sphere(0, -20, 10, 5, 200, 200, 0));
	add_sphere(&world, create_sphere(0, 20, 10, 5, 0, 200, 200));
	
	add_sphere(&world, create_sphere(-7, -7, 5, 3, 255, 128, 0));
	add_sphere(&world, create_sphere(7, -7, 5, 3, 128, 255, 0));
	add_sphere(&world, create_sphere(-7, 7, 5, 3, 0, 255, 128));
	add_sphere(&world, create_sphere(7, 7, 5, 3, 128, 0, 255));
	
	add_sphere(&world, create_sphere(-12, 0, 20, 4, 255, 100, 100));
	add_sphere(&world, create_sphere(12, 0, 20, 4, 100, 255, 100));
	add_sphere(&world, create_sphere(0, -12, 20, 4, 100, 100, 255));
	add_sphere(&world, create_sphere(0, 12, 20, 4, 255, 255, 100));
	
	add_sphere(&world, create_sphere(-5, -5, -5, 2, 180, 90, 0));
	add_sphere(&world, create_sphere(5, -5, -5, 2, 90, 180, 0));
	add_sphere(&world, create_sphere(-5, 5, -5, 2, 0, 180, 90));
	add_sphere(&world, create_sphere(5, 5, -5, 2, 180, 0, 90));
	
	add_sphere(&world, create_sphere(-18, -8, 15, 3, 200, 50, 200));
	add_sphere(&world, create_sphere(18, -8, 15, 3, 50, 200, 200));
	add_sphere(&world, create_sphere(-18, 8, 15, 3, 200, 200, 50));
	add_sphere(&world, create_sphere(18, 8, 15, 3, 100, 150, 200));
	
	add_sphere(&world, create_sphere(-3, -3, 8, 2.5, 255, 200, 150));
	add_sphere(&world, create_sphere(3, -3, 8, 2.5, 150, 255, 200));
	add_sphere(&world, create_sphere(-3, 3, 8, 2.5, 200, 150, 255));
	add_sphere(&world, create_sphere(3, 3, 8, 2.5, 220, 220, 100));
	
	add_sphere(&world, create_sphere(-25, 0, 5, 4, 255, 50, 50));
	add_sphere(&world, create_sphere(25, 0, 5, 4, 50, 255, 50));
	add_sphere(&world, create_sphere(0, -25, 5, 4, 50, 50, 255));
	add_sphere(&world, create_sphere(0, 25, 5, 4, 255, 255, 50));
	
	add_sphere(&world, create_sphere(-8, -15, 12, 3, 170, 85, 170));
	add_sphere(&world, create_sphere(8, -15, 12, 3, 85, 170, 170));
	add_sphere(&world, create_sphere(-8, 15, 12, 3, 170, 170, 85));
	add_sphere(&world, create_sphere(8, 15, 12, 3, 120, 120, 200));
	
	// Additional larger spheres for stress test
	add_sphere(&world, create_sphere(-30, -30, 25, 10, 255, 100, 100));
	add_sphere(&world, create_sphere(30, -30, 25, 10, 100, 255, 100));
	add_sphere(&world, create_sphere(-30, 30, 25, 10, 100, 100, 255));
	add_sphere(&world, create_sphere(30, 30, 25, 10, 255, 255, 100));
	
	add_sphere(&world, create_sphere(-22, -22, 35, 8, 200, 150, 100));
	add_sphere(&world, create_sphere(22, -22, 35, 8, 150, 200, 100));
	add_sphere(&world, create_sphere(-22, 22, 35, 8, 100, 200, 150));
	add_sphere(&world, create_sphere(22, 22, 35, 8, 200, 100, 150));
	
	add_sphere(&world, create_sphere(0, 0, 40, 12, 180, 180, 255));
	add_sphere(&world, create_sphere(-15, 0, 30, 7, 255, 180, 180));
	add_sphere(&world, create_sphere(15, 0, 30, 7, 180, 255, 180));
	
	add_sphere(&world, create_sphere(0, -35, 20, 9, 200, 200, 100));
	add_sphere(&world, create_sphere(0, 35, 20, 9, 100, 200, 200));
	
	add_sphere(&world, create_sphere(-28, 0, 15, 6, 150, 100, 200));
	add_sphere(&world, create_sphere(28, 0, 15, 6, 100, 150, 200));
	
	// Wall spheres
	add_sphere(&world, create_sphere(0, -250, 0, 200, 180, 180, 180));
	add_sphere(&world, create_sphere(0, 0, 250, 200, 150, 150, 200));
	add_sphere(&world, create_sphere(-250, 0, 0, 200, 200, 150, 150));
	add_sphere(&world, create_sphere(250, 0, 0, 200, 150, 200, 150));
	add_sphere(&world, create_sphere(0, 600, 0, 200, 200, 200, 180));
	
	// Add a floor plane
	add_sphere(&world, (t_obj*)create_plane(0, -50, 0, 0, 1, 0, 100, 100, 100));
	
	// Add back wall plane
	add_sphere(&world, (t_obj*)create_plane(0, 0, 80, 0, 0, -1, 120, 120, 150));
	
	// Add left wall plane
	add_sphere(&world, (t_obj*)create_plane(-60, 0, 0, 1, 0, 0, 150, 120, 120));
	
	// Add right wall plane
	add_sphere(&world, (t_obj*)create_plane(60, 0, 0, -1, 0, 0, 120, 150, 120));
	
	// Add ceiling plane
	add_sphere(&world, (t_obj*)create_plane(0, 120, 0, 0, -1, 0, 130, 130, 130));
	
	// Add angled planes for interest
	add_sphere(&world, (t_obj*)create_plane(-45, 0, 40, 0.707, 0, -0.707, 200, 180, 100));
	add_sphere(&world, (t_obj*)create_plane(45, 0, 40, -0.707, 0, -0.707, 100, 180, 200));
	
	// Add some cylinders
	add_sphere(&world, (t_obj*)create_cylinder(-40, -50, 10, 3, 30, 0, 1, 0, true, 200, 100, 50));
	add_sphere(&world, (t_obj*)create_cylinder(40, -50, 10, 3, 30, 0, 1, 0, true, 50, 200, 100));
	add_sphere(&world, (t_obj*)create_cylinder(0, -50, -10, 4, 40, 0, 1, 0, true, 100, 100, 200));
	
	printf("OKAYYYY LETS GO - Hardcoded scene loaded\n");
	print_colour(world.ambient);

	// return (0);
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "miniRT - Ray Tracer", true);
	if (!mlx)
		ft_error();

	mlx_image_t* img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		ft_error();

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

	printf("\n\n\n\nDEBUGGING ZONE:\n");
	printf("Ambient\n");
	print_colour(world.ambient);
	printf("World Light\n");
	print_colour(world.light.colour);
	print_colour(colour_at(&world, ray_for_pixel(world.camera, 0, 0)));

	// Register a hook and pass mlx as an optional param.
	// NOTE: Do this before calling mlx_loop!
	mlx_key_hook(mlx, mlx_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
