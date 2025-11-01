/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:24:39 by fredchar          #+#    #+#             */
/*   Updated: 2025/11/01 17:56:11 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "MLX42/include/MLX42/MLX42.h"
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




	t_ray	r;
	t_obj	*o = obj_create(OT_SPHERE);
	o->transform = translation(0, 0, 0.0);

	print_vec4(normal_at_sp(o, point(1, 0, 0)));
	print_vec4(normal_at_sp(o, point(0, 1, 0)));
	print_vec4(normal_at_sp(o, point(0, 0, 1)));

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
